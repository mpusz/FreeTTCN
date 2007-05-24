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
 * @file   te.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:04:58 2007
 * 
 * @brief  
 * 
 * 
 */


#include "freettcn/te/te.h"
#include "freettcn/te/module.h"
#include "freettcn/te/modulesContainer.h"
#include "freettcn/te/behavior.h"
#include "freettcn/te/testCase.h"
#include "freettcn/te/timer.h"
#include "freettcn/tools/logMask.h"
#include "freettcn/tools/timeStamp.h"
extern "C" {
#include "freettcn/ttcn3/tci_te_tm.h"
#include "freettcn/ttcn3/tci_te_ch.h"
#include "freettcn/ttcn3/tri_te_sa.h"
#include "freettcn/ttcn3/tci_tl.h"
}
#include <iostream>



freettcn::TE::CTTCNExecutable freettcn::TE::CTTCNExecutable::_instance;

freettcn::TE::CTTCNExecutable &freettcn::TE::CTTCNExecutable::Instance()
{
  return _instance;
}


freettcn::TE::CTTCNExecutable::CTTCNExecutable():
  _rootModule(0)
{
}


freettcn::TE::CTTCNExecutable::~CTTCNExecutable()
{
}


freettcn::TE::CModule &freettcn::TE::CTTCNExecutable::RootModule() const throw(ENotFound)
{
  if (_rootModule)
    return *_rootModule;
  
  std::cout << "ERROR: Root Module not set" << std::endl;
  throw freettcn::ENotFound();
}





void freettcn::TE::CTTCNExecutable::RootModule(String moduleId)
{
  try {
    // obtain requested module
    freettcn::TE::CModulesContainer &modContainer = freettcn::TE::CModulesContainer::Instance();
    freettcn::TE::CModule &module = modContainer.Get(moduleId);
    
    // check if TTCN Executable is running test case or control part
    if (_rootModule && _rootModule->Running()) {
      tciError("Cannot set TTCN Root Module while tests are running");
      return;
    }
    
    // set given module as active module
    _rootModule = &module;
    
    // init module
    _rootModule->Init();
  }
  catch(freettcn::ENotFound) {
    std::string str;
    str = "TTCN Module '";
    str += moduleId;
    str += "' not found";
    tciError(const_cast<char *>(str.c_str()));
    return;
  }
}


TciModuleParameterListType freettcn::TE::CTTCNExecutable::ModuleParametersGet(const TciModuleIdType &moduleName) const
{
  const freettcn::TE::CModule &module = RootModule();
  
  // check if the same module given
  if (strcmp(module.Id().moduleName, moduleName.moduleName)) {
    std::string str;
    str = "Given module: ";
    str += moduleName.moduleName;
    str += " different than root module: ";
    str += module.Id().moduleName;
    
    // send an error
    tciError(const_cast<char *>(str.c_str()));
    
    // return dummy data
    TciModuleParameterListType modParList;
    modParList.length = 0;
    modParList.modParList = 0;
    
    return modParList;
  }
  
  return module.Parameters();
}


TciTestCaseIdListType freettcn::TE::CTTCNExecutable::TestCasesGet() const
{
  return RootModule().TestCases();
}


TciParameterTypeListType freettcn::TE::CTTCNExecutable::TestCaseParametersGet(const TciTestCaseIdType &testCaseId) const
{
  const freettcn::TE::CModule &module = RootModule();
  
  // check if the same module given
  if (strcmp(module.Id().moduleName, testCaseId.moduleName)) {
    std::string str;
    str = "Given test case module: ";
    str += testCaseId.moduleName;
    str += " different than root module: ";
    str += module.Id().moduleName;
    
    // send an error
    tciError(const_cast<char *>(str.c_str()));
    
    // return dummy data
    TciParameterTypeListType tcParams;
    tcParams.length = 0;
    tcParams.parList = 0;
    
    return tcParams;
  }
  
  return module.TestCase(testCaseId.objectName).Parameters();
}


TriPortIdList freettcn::TE::CTTCNExecutable::TestCaseTSIGet(const TciTestCaseIdType &testCaseId) const
{
  const freettcn::TE::CModule &module = RootModule();
  
  // check if the same module given
  if (strcmp(module.Id().moduleName, testCaseId.moduleName)) {
    std::string str;
    str = "Given test case module: ";
    str += testCaseId.moduleName;
    str += " different than root module: ";
    str += module.Id().moduleName;
    
    // send an error
    tciError(const_cast<char *>(str.c_str()));
    
    // return dummy data
    TriPortIdList portList;
    portList.portIdList = 0;
    portList.length = 0;
    
    return portList;
  }
  
  return module.TestCase(testCaseId.objectName).SystemInterface();
}


void freettcn::TE::CTTCNExecutable::TestCaseStart(const TciTestCaseIdType &testCaseId, const TciParameterListType &parameterlist) const
{
  freettcn::TE::CModule &module = RootModule();
  
  // check if the same module given
  if (strcmp(module.Id().moduleName, testCaseId.moduleName)) {
    std::string str;
    str = "Given test case module: ";
    str += testCaseId.moduleName;
    str += " different than root module: ";
    str += module.Id().moduleName;
    
    // send an error
    tciError(const_cast<char *>(str.c_str()));
    return;
  }
  
  freettcn::TE::CTestCase &tc = module.TestCase(testCaseId.objectName);
  
  // obtain module parameters
  module.ParametersGet();
  
  // set as current test case
  module.ActiveTestCase(tc);
  
  // start test case
  tc.Start(0, 0, 0, &parameterlist, 0);
}


void freettcn::TE::CTTCNExecutable::TestCaseStop() const
{
  freettcn::TE::CModule &module = RootModule();
  if (module.Running())
    module.ActiveTestCase().Stop();
}


const TriComponentId &freettcn::TE::CTTCNExecutable::ControlStart() const
{
  freettcn::TE::CModule &module = RootModule();
  
  // obtain module parameters
  module.ParametersGet();
  
  return module.ControlStart();
}


void freettcn::TE::CTTCNExecutable::ControlStop() const
{
  freettcn::TE::CModule &module = RootModule();
  if (module.Running())
    module.ControlStop();
}


const TriComponentId &freettcn::TE::CTTCNExecutable::TestComponentCreate(TciTestComponentKindType kind,
                                                                         TciType componentType,
                                                                         String name) const
{
  if (kind == TCI_CTRL_COMP && componentType) {
    std::cout << "ERROR: 'componentType' given for Control component!!!" << std::endl;
    
    // return dummy data
    TriComponentId ctrlId;
    ctrlId.compInst.data = 0;
    ctrlId.compInst.bits = 0;
    ctrlId.compInst.aux = 0;
    ctrlId.compName = 0;
    ctrlId.compType.moduleName = 0;
    ctrlId.compType.objectName = 0;
    ctrlId.compType.aux = 0;
    
    return ctrlId;
  }
  
  return RootModule().TestComponentCreate(kind, componentType, name);
}


void freettcn::TE::CTTCNExecutable::TestComponentStart(const TriComponentId &componentId,
                                                       const TciBehaviourIdType &behaviorId,
                                                       const TciParameterListType &parameterList) const
{
  RootModule().TestComponentStart(componentId, behaviorId, parameterList);
}


void freettcn::TE::CTTCNExecutable::TestComponentStop(const TriComponentId &componentId) const
{
  RootModule().TestComponentStop(componentId);
}


void freettcn::TE::CTTCNExecutable::TestComponentKill(const TriComponentId &componentId) const
{
  RootModule().TestComponentKill(componentId);
}


void freettcn::TE::CTTCNExecutable::Connect(const TriPortId &fromPort, const TriPortId &toPort) const
{
  RootModule().Connect(fromPort, toPort);
}

void freettcn::TE::CTTCNExecutable::Disconnect(const TriPortId &fromPort, const TriPortId &toPort) const
{
  RootModule().Disconnect(fromPort, toPort);
}

void freettcn::TE::CTTCNExecutable::Map(const TriPortId &fromPort, const TriPortId &toPort) const
{
  RootModule().Map(fromPort, toPort);
}

void freettcn::TE::CTTCNExecutable::Unmap(const TriPortId &fromPort, const TriPortId &toPort) const
{
  RootModule().Unmap(fromPort, toPort);
}

void freettcn::TE::CTTCNExecutable::TestComponentTerminated(const TriComponentId &componentId,
                                                            TciVerdictValue verdict) const
{
  RootModule().TestComponentTerminated(componentId, verdict);
}


void freettcn::TE::CTTCNExecutable::TestCaseExecute(const TciTestCaseIdType &testCaseId, const TriPortIdList &tsiPortList) const
{
  freettcn::TE::CTestCase &tc = RootModule().TestCase(testCaseId.objectName);
  
  // set as current test case
  RootModule().ActiveTestCase(tc);

  // prepare test case
  tc.Execute(testCaseId, tsiPortList);
}


void freettcn::TE::CTTCNExecutable::Reset() const
{
  // stop running module
  RootModule().Reset();
}



// PA requests
void freettcn::TE::CTTCNExecutable::Timeout(const TriTimerId* timerId) throw(freettcn::ENotFound)
{
  if (!timerId) {
    std::cout << "ERROR: TimerId = NULL!!!" << std::endl;
    throw freettcn::ENotFound();
  }
  
  freettcn::TE::CIdObject &object = CIdObject::Get(*timerId);
  try {
    dynamic_cast<freettcn::TE::CTimer &>(object).Timeout();
  }
  catch(std::exception &ex) {
    std::cout << "ERROR: System exception: " << ex.what() << " caught!!!" << std::endl;
    throw freettcn::ENotFound();
  }
}
