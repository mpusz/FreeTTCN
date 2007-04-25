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

#include "testCase.h"
#include "te.h"
#include "module.h"
#include "behavior.h"
extern "C" {
#include "freettcn/tci_te_tm.h"
#include "freettcn/tci_te_ch.h"
#include "freettcn/tri_te_sa.h"
#include "freettcn/tci_tl.h"
}
#include <iostream>



freettcn::TE::CTestCase::CTestCase(const std::string &name):
  CInitObject(name), _behavior(0), _module(0)
{
}

freettcn::TE::CTestCase::~CTestCase()
{
  if (_behavior)
    delete _behavior;
}

void freettcn::TE::CTestCase::Register(CBehavior *behavior)
{
  _behavior = behavior;
}

void freettcn::TE::CTestCase::Module(CModule &module)
{
  _module = &module;
}

freettcn::TE::CModule &freettcn::TE::CTestCase::Module() const throw(freettcn::EOperationFailed)
{
  if (_module)
    return *_module;
  
  std::cout << "ERROR: Module not set" << std::endl;
  throw freettcn::EOperationFailed();
}

TciParameterTypeListType freettcn::TE::CTestCase::Parameters() const
{
  TciParameterTypeListType tcParams;
  tcParams.length = 0;
  tcParams.parList = 0;
  
  return tcParams;
}

TriPortIdList freettcn::TE::CTestCase::Ports() const
{
  TriPortIdList portList;
  portList.portIdList = 0;
  portList.length = 0;
  
  return portList;
}


void freettcn::TE::CTestCase::Start(TciParameterListType parameterlist)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // create MTC
  TciType mtcType = 0;                            /**< @todo MTC type support */
  _mtcId = te.TestComponentCreateReq(0, TCI_MTC_COMP, mtcType, "MTC");
  
  // give a chance to create static connections and the initialization of TSI ports
  TciTestCaseIdType testCaseId;
  testCaseId.moduleName = "";                     /**< @todo Module name */
  testCaseId.objectName = const_cast<char *>(Name().c_str());
  testCaseId.aux = 0;
  
  // log
  /// @todo should be moved to the start of the function
  if (te.Logging() && te.LogMask().Get(LOG_TE_TC_START)) {
    TriTimerDuration dur = 0.0;                   /**< @todo Timer duration should be set */
    TriParameterList parList;                     /**< @todo Paramters list should be translated */
    parList.length = 0;
    parList.parList = 0;
    
    tliTcStart(0, te.TimeStamp().Get(), 0, 0, _mtcId, testCaseId, parList, dur);
  }
  
  // log
  if (te.Logging() && te.LogMask().Get(LOG_TE_TC_EXECUTE)) {
    TriTimerDuration dur = 0.0;                   /**< @todo Timer duration should be set */
    TriParameterList parList;                     /**< @todo Paramters list should be translated */
    parList.length = 0;
    parList.parList = 0;
    
    tliTcExecute(0, te.TimeStamp().Get(), "ip.ttcn", 123, _mtcId, testCaseId, parList, dur);
  }
  tciExecuteTestCaseReq(testCaseId, Ports());
  
  // start MTC
  TciBehaviourIdType behavior;
  behavior.moduleName = 0;
  behavior.objectName = 0;
  behavior.aux = 0;
  
  TciParameterListType parameterList;
  parameterList.length = 0;
  parameterList.parList = 0;
  
  te.TestComponentStartReq(0, _mtcId, behavior, parameterList);
  
  _module->_running = true;
}


void freettcn::TE::CTestCase::Execute(TciTestCaseIdType testCaseId, TriPortIdList tsiPortList)
{
  // set current test case
  _module->TestCase(this);
  
  if (triExecuteTestCase(&testCaseId, &tsiPortList) != TRI_OK) {
    /// @todo do something
  }
}


void freettcn::TE::CTestCase::Stop()
{
  // log
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(LOG_TE_TC_STOP))
    tliTcStop(0, te.TimeStamp().Get(), 0, 0, _mtcId);
  
  tciResetReq();
  
  /// @todo set verdict to ERROR
  
  // notify TM about test case termination
  TciValue error = 0;
  TciParameterListType parList;
  parList.length = 0;
  parList.parList = 0;
  tciTestCaseTerminated(error, parList);
}
