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
 * @file   module.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:05:46 2007
 * 
 * @brief  
 * 
 * 
 */


#include "module.h"
#include "modulesContainer.h"
#include "te.h"
#include "testComponent.h"
#include "behavior.h"
#include "testCase.h"
#include "sourceData.h"
#include "tools.h"
#include <iostream>
extern "C" {
#include "freettcn/tci_te_tm.h"
#include "freettcn/tci_te_ch.h"
#include "freettcn/tri_te_sa.h"
#include "freettcn/tri_te_pa.h"
#include "freettcn/tci_tl.h"
}


freettcn::TE::CModule::CParameter::CParameter(const char *name):
  CInitObject(name), _defaultValue(0), _value(0)
{
  
}

freettcn::TE::CModule::CParameter::~CParameter()
{
//   if (_defaultValue)
//     delete _defaultValue;
//   if (_value)
//     delete value;
}

TciValue freettcn::TE::CModule::CParameter::DefaultValue() const
{
  return _defaultValue;
}

void freettcn::TE::CModule::CParameter::Value(TciValue value)
{
//   if (_value)
//     delete value;
  _value = value;
}









freettcn::TE::CModule::CModule(const char *name):
  CInitObject(name), _ctrlBehavior(0), _ctrlSrcData(0),
  //_ctrlCompType(*this), 
  _ctrlRunning(false), _currTestCase(0), __modParList(0), __testCaseIdList(0)
{
  freettcn::TE::CModulesContainer &modContainer = freettcn::TE::CModulesContainer::Instance();
  modContainer.Register(*this);
  
  _id.moduleName = const_cast<char *>(Name());
  _id.objectName = _id.moduleName;
  _id.aux = this;
}

freettcn::TE::CModule::~CModule()
{
  Purge(_testCaseList);
  Purge(_parameterList);
  Purge(_allEntityStates);
  Purge(_behaviorList);
  
  if (_ctrlSrcData)
    delete _ctrlSrcData;
  
  // delete temporary variables
  if (__modParList)
    delete[] __modParList;
  if (__testCaseIdList)
    delete[] __testCaseIdList;
}


const TciModuleIdType &freettcn::TE::CModule::Id() const
{
  return _id;
}


TriComponentId freettcn::TE::CModule::ModuleComponentId() const
{
  TriComponentId id;
  
  // first creator
  id.compInst.data = 0;
  id.compInst.bits = 0;
  id.compInst.aux = 0;
  id.compName = "";
  id.compType = Id();
  
  return id;
}


// const freettcn::TE::CControlComponentType &freettcn::TE::CModule::ControlComponentType() const
// {
//   return _ctrlCompType;
// }


void freettcn::TE::CModule::Cleanup()
{
}


bool freettcn::TE::CModule::Running() const
{
  return _ctrlRunning || _currTestCase;
}


void freettcn::TE::CModule::Reset()
{
  if (Running()) {
    if (_currTestCase) {
      _currTestCase->Stop();
      
      // reset SA only if test case is running
      triSAReset();
    }
    
    _ctrlRunning = false;
    
    // reset PA
    triPAReset();
  }
}


void freettcn::TE::CModule::Register(CParameter *parameter)
{
  _parameterList.push_back(parameter);
  parameter->Init();
}

void freettcn::TE::CModule::Register(CTestCase *tc)
{
  _testCaseList.push_back(tc);
  tc->Init();
}

void freettcn::TE::CModule::Register(const freettcn::TE::CBehavior *ctrlBehavior, const freettcn::TE::CSourceData *ctrlSrcData)
{
  _ctrlBehavior = ctrlBehavior;
  _ctrlSrcData = ctrlSrcData;
}

void freettcn::TE::CModule::ParametersSet() throw(freettcn::EOperationFailed)
{
  // obtain and set module parameters values
  for(ParameterList::iterator it=_parameterList.begin(); it != _parameterList.end(); ++it) {
    TciValue val = tciGetModulePar(const_cast<char *>((*it)->Name()));
//     if (!val && (*it)->DefaultValue())
//       val = new((*it)->DefaultValue());
    
    if (!val)
      throw freettcn::EOperationFailed();
    
    (*it)->Value(val);
  }
}

TciModuleParameterListType freettcn::TE::CModule::Parameters() const
{
  TciModuleParameterListType modParList;
  modParList.length = _parameterList.size();
  if (__modParList)
    delete[] __modParList;
  modParList.modParList = __modParList = new TciModuleParameterType[modParList.length];
  
  unsigned int i=0;
  for(ParameterList::const_iterator it=_parameterList.begin(); it != _parameterList.end(); ++it, i++) {
    modParList.modParList[i].parName = const_cast<char *>((*it)->Name());
    modParList.modParList[i].defaultValue = ((*it)->DefaultValue());
  }
  
  return modParList;
}


TciTestCaseIdListType freettcn::TE::CModule::TestCases() const
{
  TciTestCaseIdListType tcList;
  tcList.length = _testCaseList.size();
  if (__testCaseIdList)
    delete[] __testCaseIdList;
  tcList.idList = __testCaseIdList = new TciTestCaseIdType[tcList.length];
  
  unsigned int i=0;
  for(TestCaseList::const_iterator it=_testCaseList.begin(); it!=_testCaseList.end(); ++it, i++) {
    tcList.idList[i].moduleName = const_cast<char *>(Name());
    tcList.idList[i].objectName = const_cast<char *>((*it)->Name());
    tcList.idList[i].aux = 0;
  }
  
  return tcList;
}

freettcn::TE::CTestCase &freettcn::TE::CModule::TestCase(const char *tcId) const throw(ENotFound)
{
  for(TestCaseList::const_iterator it=_testCaseList.begin(); it != _testCaseList.end(); ++it)
    if ((*it)->Name() == tcId)
      return *(*it);
  std::cout << "ERROR: Test Case not found" << std::endl;
  throw freettcn::ENotFound();
}

void freettcn::TE::CModule::TestCase(freettcn::TE::CTestCase *tc)
{
  _currTestCase = tc;
}

freettcn::TE::CTestCase *freettcn::TE::CModule::TestCase() const
{
  return _currTestCase;
}


TriComponentId freettcn::TE::CModule::ControlStart()
{
  // obtain module parameters
//   ParametersSet();

  _ctrlRunning = true;
  
  return TestComponentCreateReq(_ctrlSrcData->Source(), _ctrlSrcData->Line(), ModuleComponentId(), TCI_CTRL_COMP, 0, "CONTROL");
}


void freettcn::TE::CModule::ControlStop() throw(EOperationFailed)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(LOG_TE_CTRL_STOP))
    // log
    tliCtrlStop(0, te.TimeStamp().Get(), 0, 0, ModuleComponentId());
  
  if (_currTestCase)
    _currTestCase->Stop();
  
  tciResetReq();
  
  // notify TM about control part termination
  tciControlTerminated();
  
  _ctrlRunning = 0;
}


const freettcn::TE::CBehavior &freettcn::TE::CModule::ControlBehavior() const throw(ENotFound)
{
  if (_ctrlBehavior)
    return *_ctrlBehavior;
  else {
    std::cout << "ERROR: Control Behavior not set" << std::endl;
    throw freettcn::EOperationFailed();
  }
}


void freettcn::TE::CModule::BehaviorAdd(freettcn::TE::CBehavior *behavior)
{
  _behaviorList.push_back(behavior);
}


const freettcn::TE::CBehavior &freettcn::TE::CModule::Behavior(const TciBehaviourIdType &behavior) const throw(freettcn::ENotFound)
{
  for(BehaviorList::const_iterator it=_behaviorList.begin(); it!=_behaviorList.end(); ++it) {
    TciBehaviourIdType id = (*it)->Id();
    if (!strcmp(behavior.objectName, id.objectName))
      return *(*it);
  }
  
  std::cout << "ERROR!!! Behavior not found" << std::endl;
  throw freettcn::ENotFound();
}



void freettcn::TE::CModule::TestComponentAdd(freettcn::TE::CTestComponent &component)
{
  _allEntityStates.push_back(&component);
}


freettcn::TE::CTestComponent &freettcn::TE::CModule::TestComponent(const TriComponentId &component) const throw(freettcn::ENotFound)
{
  for(TestCompList::const_iterator it=_allEntityStates.begin(); it!=_allEntityStates.end(); ++it) {
    TriComponentId id = (*it)->Id();
    if (component.compInst.aux == id.compInst.aux)
      return *(*it);
  }
  
  std::cout << "ERROR!!! Test component not found" << std::endl;
  throw freettcn::ENotFound();
}



TriComponentId freettcn::TE::CModule::TestComponentCreateReq(const char *src, int line,
                                                             const TriComponentId &creatorId,
                                                             TciTestComponentKindType kind,
                                                             const CTestComponentType *compType, String name)
{
  TriComponentId compId = tciCreateTestComponentReq(kind, const_cast<void *>(reinterpret_cast<const void*>(compType)), name);
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  if (te.Logging() && te.LogMask().Get(LOG_TE_C_CREATE))
    // log
    tliCCreate(0, te.TimeStamp().Get(), const_cast<char *>(src), line, creatorId, compId, name);
  
  if (kind == TCI_CTRL_COMP) {
    // start control test component immediately using default control behavior
    
    // control does not have parameters
    TciParameterListType parameterList;
    parameterList.length = 0;
    parameterList.parList = 0;
    
    if (te.Logging() && te.LogMask().Get(LOG_TE_CTRL_START))
      // log
      tliCtrlStart(0, te.TimeStamp().Get(), const_cast<char *>(src), line, creatorId);
    
    TestComponentStartReq(src, line, creatorId, compId, ControlBehavior().Id(), parameterList);
  }
  
  return compId;
}


void freettcn::TE::CModule::TestComponentStartReq(const char *src, int line,
                                                  const TriComponentId &creatorId,
                                                  const TriComponentId &componentId,
                                                  const TciBehaviourIdType &behaviorId,
                                                  const TciParameterListType &parameterList)
{
  tciStartTestComponentReq(componentId, behaviorId, parameterList);
  
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(LOG_TE_C_START))
    // log
    tliCStart(0, te.TimeStamp().Get(), const_cast<char *>(src), line, creatorId, componentId, behaviorId, parameterList);
}
