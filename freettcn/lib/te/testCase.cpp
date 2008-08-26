//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) library.

// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   testCase.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:04:10 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/testCase.h"
#include "freettcn/te/te.h"
#include "freettcn/te/module.h"
#include "freettcn/te/behavior.h"
#include "freettcn/te/port.h"
#include "freettcn/te/timer.h"
#include "freettcn/te/basicTypes.h"
#include "freettcn/te/sourceData.h"
#include "freettcn/tools/tools.h"
#include "freettcn/tools/logMask.h"
#include "freettcn/tools/ttcnWrappers.h"
#include "freettcn/tools/timeStampMgr.h"
extern "C" {
#include "freettcn/ttcn3/tci_te_tm.h"
#include "freettcn/ttcn3/tci_te_ch.h"
#include "freettcn/ttcn3/tri_te_sa.h"
#include "freettcn/ttcn3/tci_tl.h"
}



freettcn::TE::CTestCase::CTestCase(CModule &module, const char *name, const freettcn::TE::CSourceData *srcData,
                                   const freettcn::TE::CTestComponentType &mtcType, const CBehavior &behavior,
                                   const freettcn::TE::CTestComponentType *systemType /* 0 */):
  _module(module), _srcData(srcData),
  _mtcType(mtcType), _behavior(behavior), _systemType(systemType ? *systemType : mtcType),
  _mtc(0), _system(0), _verdict(CBasicTypes::Verdict(), VERDICT_NONE)
{
  _id.moduleName = _module.Id().moduleName;
  _id.objectName = const_cast<char *>(name);
  _id.aux = 0;
}

freettcn::TE::CTestCase::~CTestCase()
{
  if (_srcData)
    delete _srcData;
}

TciTestCaseIdType freettcn::TE::CTestCase::Id() const
{
  return _id;
}

freettcn::TE::CTestComponentType::CInstanceRemote &freettcn::TE::CTestCase::MTC() const
{
  if (_mtc)
    return *_mtc;
  throw ENotFound(E_DATA, "MTC test component not found!!!");
}

freettcn::TE::CTestComponentType::CInstanceRemote &freettcn::TE::CTestCase::System() const
{
  if (_system)
    return *_system;
  throw ENotFound(E_DATA, "SYSTEM test component not found!!!");
}

const freettcn::TE::CVerdictType::CInstance &freettcn::TE::CTestCase::Verdict() const
{
  return _verdict;
}

void freettcn::TE::CTestCase::Verdict(TVerdict verdict)
{
  // update verdict
  if (verdict > _verdict.Value())
    _verdict.Value(verdict);
}

TciParameterTypeListType freettcn::TE::CTestCase::Parameters() const
{
  TciParameterTypeListType tcParams;
  tcParams.length = 0;
  tcParams.parList = 0;
  
  return tcParams;
}

TriPortIdList freettcn::TE::CTestCase::SystemInterface() const
{
  TriPortIdList portList = _systemType.Ports();
  
  // add component data to port list
  for(int i=0; i<portList.length; i++) {
    portList.portIdList[i]->compInst.compName = "SYSTEM";
    portList.portIdList[i]->compInst.compType = _systemType.Id();
  }
  
  return portList;
}


void freettcn::TE::CTestCase::Start(const char *src, int line,
                                    freettcn::TE::CTestComponentType::CInstanceLocal *creator,
                                    const TciParameterListType *parameterList,
                                    TriTimerDuration duration)
{
  TriComponentId creatorId;
  
  // set current test case
  _module.ActiveTestCase(*this);
  
  // saet initial verdict value
  _verdict.Value(VERDICT_NONE);
  
  if (creator) {
    creatorId = creator->Id();
  }
  else {
    src = _srcData->Source();
    line = _srcData->Line();
    creatorId = _module.ModuleComponentId();
  }
  
  TciParameterListType parList;
  if (parameterList) {
    parList = *parameterList;
  }
  else {
    parList.length = 0;
    parList.parList = 0;
  }
  
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(freettcn::CLogMask::CMD_TE_TC_START))
    tliTcStart(0, te.TimeStampMgr().Get(), const_cast<char *>(src), line, creatorId, _id, parList, duration);
  
  // create MTC
  _mtc = &_module.TestComponentCreateReq(src, line, creatorId, TCI_MTC_COMP, _mtcType, "MTC");
  
  // create SYSTEM component
  _system = &_module.TestComponentCreateReq(src, line, _mtc->Id(), TCI_SYS_COMP, _systemType, "SYSTEM");
  
  // give a chance to create static connections and the initialization of TSI ports
  if (te.Logging() && te.LogMask().Get(freettcn::CLogMask::CMD_TE_TC_EXECUTE))
    tliTcExecute(0, te.TimeStampMgr().Get(), const_cast<char *>(src), line, _mtc->Id(), _id, parList, duration);
  
  tciExecuteTestCaseReq(_id, SystemInterface());
  
  // start MTC
  _module.TestComponentStartReq(src, line, creatorId, *_mtc, _behavior, parList);
  
  // inform TM about TC execution
  tciTestCaseStarted(_id, parList, duration);
}


void freettcn::TE::CTestCase::Execute(TciTestCaseIdType testCaseId, TriPortIdList tsiPortList)
{
  // set current test case
  _module.ActiveTestCase(*this);
  
  if (triExecuteTestCase(&testCaseId, &tsiPortList) != TRI_OK) {
    /// @todo do something
  }
}


void freettcn::TE::CTestCase::Stop()
{
  CTTCNExecutable &te = CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(CLogMask::CMD_TE_TC_STOP))
    // log
    tliTcStop(0, te.TimeStampMgr().Get(), 0, 0, _mtc->Id());
  
  // set verdict to ERROR
  _verdict.Value(VERDICT_ERROR);
  
  _mtc->Kill();
  
//   // reset local module
//   _module.Reset();
  
//   // reset other modules
//   tciResetReq();
}



void freettcn::TE::CTestCase::PortAdd(CPort &port)
{
  _allPortStates.push_back(&port);
}
