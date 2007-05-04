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
#include "freettcn/te/basicTypes.h"
#include "freettcn/te/module.h"
#include "freettcn/te/modulesContainer.h"
#include "freettcn/te/behavior.h"
#include "freettcn/te/testCase.h"
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
  if (strcmp(module.Name(), moduleName.moduleName)) {
    std::string str;
    str = "Given module: ";
    str += moduleName.moduleName;
    str += " different than root module: ";
    str += module.Name();
    
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
  if (strcmp(module.Name(), testCaseId.moduleName)) {
    std::string str;
    str = "Given test case module: ";
    str += testCaseId.moduleName;
    str += " different than root module: ";
    str += module.Name();
    
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
  if (strcmp(module.Name(), testCaseId.moduleName)) {
    std::string str;
    str = "Given test case module: ";
    str += testCaseId.moduleName;
    str += " different than root module: ";
    str += module.Name();
    
    // send an error
    tciError(const_cast<char *>(str.c_str()));
    
    // return dummy data
    TriPortIdList portList;
    portList.portIdList = 0;
    portList.length = 0;
    
    return portList;
  }
  
  return module.TestCase(testCaseId.objectName).Ports();
}


void freettcn::TE::CTTCNExecutable::TestCaseStart(const TciTestCaseIdType &testCaseId, const TciParameterListType &parameterlist) const
{
  freettcn::TE::CModule &module = RootModule();
  
  // check if the same module given
  if (strcmp(module.Name(), testCaseId.moduleName)) {
    std::string str;
    str = "Given test case module: ";
    str += testCaseId.moduleName;
    str += " different than root module: ";
    str += module.Name();
    
    // send an error
    tciError(const_cast<char *>(str.c_str()));
    return;
  }
  
  freettcn::TE::CTestCase &tc = module.TestCase(testCaseId.objectName);
  
  // set as current test case
  module.TestCase(&tc);
  
  // start test case
  tc.Start(0, 0, 0, parameterlist, 0);
}


void freettcn::TE::CTTCNExecutable::TestCaseStop() const
{
  freettcn::TE::CModule &module = RootModule();
  if (module.Running()) {
    if (freettcn::TE::CTestCase *tc = module.TestCase())
      tc->Stop();
  }
}


TriComponentId freettcn::TE::CTTCNExecutable::ControlStart() const
{
  return RootModule().ControlStart();
}


void freettcn::TE::CTTCNExecutable::ControlStop() const
{
  freettcn::TE::CModule &module = RootModule();
  if (module.Running())
    module.ControlStop();
}


TriComponentId freettcn::TE::CTTCNExecutable::TestComponentCreate(TciTestComponentKindType kind,
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
  
  const freettcn::TE::CType *type = 0;
  if (componentType)
    type = static_cast<const freettcn::TE::CType *>(componentType);
  else if (kind == TCI_CTRL_COMP)
    type = &freettcn::TE::CBasicTypes::ControlComponent();
  else {
    std::cout << "ERROR!!! TciType not defined" << std::endl;
    throw EOperationFailed();
  }
  
  freettcn::TE::CType::CInstance *instance = type->InstanceCreate();
  freettcn::TE::CTestComponentType::CInstance *cInstance = dynamic_cast<freettcn::TE::CTestComponentType::CInstance *>(instance);
  if (!cInstance) {
    std::cout << "ERROR!!! TciType does not specify Component type" << std::endl;
    throw EOperationFailed();
  }
  
  cInstance->Init(RootModule(), kind, name);
  TriComponentId compId = cInstance->Id();
  
  return compId;
}


void freettcn::TE::CTTCNExecutable::TestComponentStart(const TriComponentId &componentId,
                                                       const TciBehaviourIdType &behaviorId,
                                                       const TciParameterListType &parameterList) const
{
  freettcn::TE::CTestComponentType::CInstance &component = RootModule().TestComponent(componentId);
  const freettcn::TE::CBehavior &behavior = RootModule().Behavior(behaviorId);
  component.Start(behavior, parameterList);
}


void freettcn::TE::CTTCNExecutable::Connect(const TriPortId &fromPort, const TriPortId &toPort)
{

}

void freettcn::TE::CTTCNExecutable::Disconnect(const TriPortId &fromPort, const TriPortId &toPort)
{

}

void freettcn::TE::CTTCNExecutable::Map(const TriPortId &fromPort, const TriPortId &toPort)
{
  if (triMap(&fromPort, &toPort) != TRI_OK) {
    /// @todo do something
  }
}

void freettcn::TE::CTTCNExecutable::Unmap(const TriPortId &fromPort, const TriPortId &toPort)
{
  if (triUnmap(&fromPort, &toPort) != TRI_OK) {
    /// @todo do something
  }
}

void freettcn::TE::CTTCNExecutable::TestComponentTerminated(const TriComponentId &componentId,
                                                            TciVerdictValue verdict) const
{
//   cmp.Terminated();

//   if (cmp.Type() == MTC) {
//     tciTestCaseTerminated(verdict, parms);
//   }
//   else {
//     bool terminated = true;
//     for(ptc) {
//       if (!ptc.Terminated()) {
//         terminated = false;
//         break;
//       }
//     }
//     if (terminated) {
//       /// @todo not sure
//       tciTestComponentTerminatedReq(mtc, verdict);
//     }
//   }

  if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_TE_C_TERMINATED)) {
    // log
    TriComponentId ctrlId;
    ctrlId.compInst.data = 0;
    ctrlId.compInst.bits = 0;
    ctrlId.compInst.aux = 0;
    ctrlId.compName = "saComp";
    ctrlId.compType.moduleName = "IP";
    ctrlId.compType.objectName = "IP_SA";
    ctrlId.compType.aux = 0;
    
    tliCTerminated(0, TimeStamp().Get(), "ip.ttcn", 122, ctrlId, 0);
  }
  
  // reset current test case
  RootModule().TestCase(0);
}


void freettcn::TE::CTTCNExecutable::TestCaseExecute(const TciTestCaseIdType &testCaseId, const TriPortIdList &tsiPortList) const
{
  freettcn::TE::CTestCase &tc = RootModule().TestCase(testCaseId.objectName);
  
  // set as current test case
  RootModule().TestCase(&tc);

  // prepare test case
  tc.Execute(testCaseId, tsiPortList);
}


void freettcn::TE::CTTCNExecutable::Reset() const
{
  // stop running module
  RootModule().Reset();
}
