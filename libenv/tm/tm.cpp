//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcnenv (Free TTCN Environment) library.

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
 * @file   tm.cpp
 * @author Mateusz Pusz
 * @date   Fri Apr  6 17:55:10 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/tm/tm.h"
extern "C" {
#include <freettcn/ttcn3/tci_tm_te.h>
#include <freettcn/ttcn3/tci_value.h>
#include <freettcn/ttcn3/tci_tl.h>
}
#include <iostream>



// ******************************** T E S T    C A S E ************************************

freettcn::TM::CTestManagement::CTestCase::CTestCase(const TciTestCaseIdType &id):
  _id(id)
{
}

freettcn::TM::CTestManagement::CTestCase::~CTestCase()
{
}

std::string freettcn::TM::CTestManagement::CTestCase::Name() const
{
  return _id.objectName;
}

TciTestCaseIdType freettcn::TM::CTestManagement::CTestCase::Id() const
{
  return _id;
}

void freettcn::TM::CTestManagement::CTestCase::Print() const
{
  std::cout << _id.moduleName << "." << _id.objectName << std::endl;
}


void freettcn::TM::CTestManagement::CTestCase::Start(const TciParameterListType &parameterlist)
{
//   TciTestCaseIdType testCaseId;
//   testCaseId.moduleName = _tm.ModuleId().c_str();
//   testCaseId.objectName = ;
//   testCaseId.aux = ;
  tciStartTestCase(_id, parameterlist);
}

void freettcn::TM::CTestManagement::CTestCase::Started(const TciParameterListType &parameterList, double timer)
{
}

void freettcn::TM::CTestManagement::CTestCase::Terminated(TciVerdictValue verdict, const TciParameterListType &parameterlist)
{
}

void freettcn::TM::CTestManagement::CTestCase::Stop()
{
  tciStopTestCase();
  /// @todo set verdict to ERROR
}



// *************************** M O D U L E   P A R A M E T E R ****************************

freettcn::TM::CTestManagement::CModuleParameter::CModuleParameter(const TciModuleParameterType &par):
  _parName(par.parName), _defaultValue(par.defaultValue), _value(0)
{
}

freettcn::TM::CTestManagement::CModuleParameter::~CModuleParameter()
{
}

std::string freettcn::TM::CTestManagement::CModuleParameter::Name() const
{
  return _parName;
}

TciValue freettcn::TM::CTestManagement::CModuleParameter::Value() throw(freettcn::EOperationFailed)
{
  if (!_value) {
    if (!_defaultValue) {
      std::cout << "ERROR: Module Parameter value not set" << std::endl;
      throw freettcn::EOperationFailed();
    }
    
    // copy from default value
    _value = tciNewInstance(tciGetType(_defaultValue));
    
    /// @todo - set from default value
  }
  
  return _value;
}

void freettcn::TM::CTestManagement::CModuleParameter::Print() const
{
  std::cout << _parName << std::endl;
}



// ********************************** L O G   M A S K *************************************

freettcn::TM::CLogMask::CLogMask(bool enabled /* true */):
  freettcn::CLogMask(freettcn::LOG_TM_NUM, enabled)
{
}

freettcn::TM::CLogMask::~CLogMask()
{
}



// **************************** T E S T   M A N A G E M E N T *****************************

freettcn::TM::CTestManagement *freettcn::TM::CTestManagement::_instance = 0;

freettcn::TM::CTestManagement &freettcn::TM::CTestManagement::Instance() throw(ENotFound)
{
  if (_instance)
    return *_instance;
  
  throw ENotFound();
}

freettcn::TM::CTestManagement::CTestManagement() :
  _moduleRunning(false), _tc(0)
{
  _instance = this;
}

freettcn::TM::CTestManagement::~CTestManagement()
{
  Clear();
  _instance = 0;
}

void freettcn::TM::CTestManagement::Clear()
{
  // clear module parameters list
  for(ModuleParList::iterator it=_modParList.begin(); it != _modParList.end(); ++it)
    delete *it;
  _modParList.clear();
  
  // clear test cases list
  for(TCList::iterator it=_tcList.begin(); it != _tcList.end(); ++it)
    delete *it;
  _tcList.clear();
  
  _moduleRunning = false;
}

freettcn::TM::CTestManagement::CTestCase &freettcn::TM::CTestManagement::TestCaseGet(const std::string &testCaseId) const throw(freettcn::ENotFound)
{
  for(TCList::const_iterator it = _tcList.begin(); it != _tcList.end(); ++it) {
    if ((*it)->Name() == testCaseId)
      return *(*it);
  }
  
  std::cout << "ERROR: Test case not found" << std::endl;
  throw freettcn::ENotFound();
}


void freettcn::TM::CTestManagement::ModuleParamsSet()
{
}

void freettcn::TM::CTestManagement::Init(const std::string &moduleId) throw(freettcn::EOperationFailed)
{
  if (_moduleRunning) {
    std::cout << "ERROR: Module already running" << std::endl;
    throw freettcn::EOperationFailed();
  }
  
  // free previous state
  Clear();
  
  // select root TTCN-3 module
  /// @todo perform below operation on all TE's in environment
  tciRootModule(const_cast<char *>(moduleId.c_str()));
  
  // obtain and store module parameters with its default values
  TciModuleIdType moduleName;
  moduleName.moduleName = const_cast<char *>(moduleId.c_str());
  moduleName.objectName = 0;
  moduleName.aux = 0;
  TciModuleParameterListType modParList = tciGetModuleParameters(moduleName);
  for (long i=0; i<modParList.length; i++)
    _modParList.push_back(new freettcn::TM::CTestManagement::CModuleParameter(modParList.modParList[i]));
  
  // obtain and store module test cases
  TciTestCaseIdListType tcList = tciGetTestCases();
  for (long i=0; i<tcList.length; i++)
    _tcList.push_back(new freettcn::TM::CTestManagement::CTestCase(tcList.idList[i]));
}


void freettcn::TM::CTestManagement::Log(const TriComponentId &testComponentId, String message)
{
  std::cout << "Log: " << message << std::endl;
}

void freettcn::TM::CTestManagement::Error(String message)
{
  std::cout << "ERROR: " << message << std::endl;
  
  Abort();
}

void freettcn::TM::CTestManagement::Abort()
{
  try {
    if (_moduleRunning) {
      if (_tc)
        TestCaseStop();
      else
        ControlStop();
    }
  } catch(EOperationFailed) {
    std::cout << "ERROR: " << __FUNCTION__ << " problem!!!" << std::endl;
  }
}


TciValue freettcn::TM::CTestManagement::ModuleParameterGet(const TciModuleParameterIdType &parameterId) const
{
  for(ModuleParList::const_iterator it = _modParList.begin(); it != _modParList.end(); ++it) {
    if ((*it)->Name() == parameterId)
      return (*it);
  }
  
  return 0;
}


void freettcn::TM::CTestManagement::TestCaseInit(const std::string &testCaseId) throw(freettcn::ENotFound)
{
  CTestCase &tc = TestCaseGet(testCaseId);

  // set module parameters
  ModuleParamsSet();
  
  // obtain test case parameters
  TciParameterTypeListType parList = tciGetTestCaseParameters(tc.Id());
  
  // obtain Test System Interfaces used by the test case 
  TriPortIdList portList = tciGetTestCaseTSI(tc.Id());
}


void freettcn::TM::CTestManagement::TestCaseStart(const std::string &testCaseId, const TciParameterListType &parameterlist) throw(ENotFound)
{
  _tc = &TestCaseGet(testCaseId);
  _tc->Start(parameterlist);
}


void freettcn::TM::CTestManagement::TestCaseStarted(const TciTestCaseIdType &testCaseId, const TciParameterListType &parameterList, double timer)
{
  _moduleRunning = true;
  _tc = &TestCaseGet(testCaseId.objectName);
  _tc->Started(parameterList, timer);
  
  if (Logging() && LogMask().Get(freettcn::LOG_TM_TC_STARTED)) {
    TriComponentId comp = { { 0 } };
    comp.compName = "";
    comp.compType.moduleName = "";
    comp.compType.objectName = "";
    TriParameterList parList;                     /**< @todo Paramters list should be translated */
    parList.length = 0;
    parList.parList = 0;
    tliTcStarted(0, TimeStamp().Get(), 0, 0, comp, testCaseId, parList, timer);
  }
}


void freettcn::TM::CTestManagement::TestCaseTerminated(TciVerdictValue verdict, const TciParameterListType &parameterlist)
{
  if (_tc) {
    _tc->Terminated(verdict, parameterlist);
    
    if (Logging() && LogMask().Get(freettcn::LOG_TM_TC_TERMINATED)) {
      TriComponentId comp = { { 0 } };
      comp.compName = "";
      comp.compType.moduleName = "";
      comp.compType.objectName = "";
      TriParameterList parList;                     /**< @todo Paramters list should be translated */
      parList.length = 0;
      parList.parList = 0;
      tliTcTerminated(0, TimeStamp().Get(), 0, 0, comp, _tc->Id(), parList, verdict);
    }
    
    _tc = 0;
  }
  
  _moduleRunning = false;
}


void freettcn::TM::CTestManagement::TestCaseStop()  throw(EOperationFailed)
{
  if (_tc)
    _tc->Stop();
  else {
    std::cout << "ERROR: Test Case not set" << std::endl;
    throw freettcn::EOperationFailed();
  }
}


void freettcn::TM::CTestManagement::ControlInit()
{
  // set module parameters
  ModuleParamsSet();
}


void freettcn::TM::CTestManagement::ControlStart()
{
  _moduleRunning = true;
  _ctrlCompId = tciStartControl();
}


void freettcn::TM::CTestManagement::ControlStop() throw(EOperationFailed)
{
  if (_moduleRunning) {
    _moduleRunning = false;
    tciStopControl();
  }
  else {
    std::cout << "ERROR: Module not running" << std::endl;
    throw freettcn::EOperationFailed();
  }
}


void freettcn::TM::CTestManagement::ControlTerminated()
{
  _moduleRunning = false;
  
  if (Logging() && LogMask().Get(freettcn::LOG_TM_CTRL_TERMINATED))
    tliCtrlTerminated(0, TimeStamp().Get(), 0, 0, _ctrlCompId);
}
