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
 * @file   tci_tm_te.cpp
 * @author Mateusz Pusz
 * @date   Sat Apr  7 20:23:44 2007
 * 
 * @brief  
 * 
 * 
 */


extern "C" {
#include "freettcn/tci_tm_te.h"
#include "freettcn/tci_te_tm.h"
}
#include "te.h"


void tciRootModule(String moduleId)
{
  try {
    // obtain requested module
    freettcn::TE::CModulesContainer &modContainer = freettcn::TE::CModulesContainer::Instance();
    freettcn::TE::CModule &module = modContainer.Get(moduleId);
    
    freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
    
    try {
      // check if TTCN Executable is running test case or control part
      if (te.RootModule().Running()) {
        tciError("Cannot set TTCN Root Module while tests are running");
        return;
      }
    }
    catch(freettcn::ENotFound) {
    }
    
    // set given module as active module
    te.RootModule(module);
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


TciModuleParameterListType tciGetModuleParameters(TciModuleIdType moduleName)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // get active module
  const freettcn::TE::CModule &module = te.RootModule();
  
  // check if the same module given
  if (module.Name() != moduleName.moduleName) {
    std::string str;
    str = "ERROR: Given module: ";
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


TciTestCaseIdListType tciGetTestCases()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // get active module
  const freettcn::TE::CModule &module = te.RootModule();
  
  return module.TestCases();
}


TciParameterTypeListType tciGetTestCaseParameters(TciTestCaseIdType testCaseId)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // get active module
  const freettcn::TE::CModule &module = te.RootModule();
  
  // check if the same module given
  if (module.Name() != testCaseId.moduleName) {
    std::string str;
    str = "ERROR: Given test case module: ";
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


TriPortIdList tciGetTestCaseTSI(TciTestCaseIdType testCaseId)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // get active module
  const freettcn::TE::CModule &module = te.RootModule();
  
  // check if the same module given
  if (module.Name() != testCaseId.moduleName) {
    std::string str;
    str = "ERROR: Given test case module: ";
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


void tciStartTestCase(TciTestCaseIdType testCaseId, TciParameterListType parameterlist)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // get active module
  freettcn::TE::CModule &module = te.RootModule();
  
  // check if the same module given
  if (module.Name() != testCaseId.moduleName) {
    std::string str;
    str = "ERROR: Given test case module: ";
    str += testCaseId.moduleName;
    str += " different than root module: ";
    str += module.Name();
    
    // send an error
    tciError(const_cast<char *>(str.c_str()));
    return;
  }
  
  module.TestCase(&module.TestCase(testCaseId.objectName));
  module.TestCase().Start(parameterlist);
}


void tciStopTestCase()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // get active module
  const freettcn::TE::CModule &module = te.RootModule();
  if (module.Running()) {
    module.TestCase().Stop();
    module.TestCase(0);
  }
}


TriComponentId tciStartControl()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // get active module
  freettcn::TE::CModule &module = te.RootModule();
  
  return module.ControlStart();
  
//   // obtain module parameters
//   module.ParametersSet();
}


void tciStopControl()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  // get active module
  freettcn::TE::CModule &module = te.RootModule();
  if (module.Running())
    module.ControlStop();
}
