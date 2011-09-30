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
#include <freettcn/tools/tools.h>
#include <freettcn/tools/ttcnWrappers.h>
#include <freettcn/tools/timeStampMgr.h>
#include <freettcn/tools/exception.h>
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

TciParameterTypeListType freettcn::TM::CTestManagement::CTestCase::Parameters() const
{
  return tciGetTestCaseParameters(Id());
}

TriPortIdList freettcn::TM::CTestManagement::CTestCase::Interface() const
{
  return tciGetTestCaseTSI(Id());
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

void freettcn::TM::CTestManagement::CTestCase::Terminated(const VerdictValue &verdict, const TciParameterListType &parameterlist)
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

const Value &freettcn::TM::CTestManagement::CModuleParameter::DefaultValue() const
{
  return _defaultValue;
}

void freettcn::TM::CTestManagement::CModuleParameter::ValueSet(const Value &value)
{
  _value = value;
}

const Value &freettcn::TM::CTestManagement::CModuleParameter::ValueGet() const
{
  if (!_value) {
    if (tciNotPresent(_defaultValue))
      throw EOperationFailed(E_DATA, "Module Parameter value not set!!!");
    
    return 0;
  }
  
  return _value;
}



// ********************************** L O G   M A S K *************************************

freettcn::TM::CLogMask::CLogMask(bool enabled /* true */):
  freettcn::CLogMask(CMD_TM_NUM, enabled)
{
}

freettcn::TM::CLogMask::~CLogMask()
{
}



// **************************** T E S T   M A N A G E M E N T *****************************

freettcn::TM::CTestManagement *freettcn::TM::CTestManagement::_instance = 0;

freettcn::TM::CTestManagement &freettcn::TM::CTestManagement::Instance()
{
  if (_instance)
    return *_instance;
  
  throw ENotInitialized(E_DATA, "Test Management instance not inited!!!");
}

freettcn::TM::CTestManagement::CTestManagement() :
  _status(NOT_RUNNING), _ctrlCompId(0), _tc(0)
{
  _instance = this;
}

freettcn::TM::CTestManagement::~CTestManagement()
{
  Clear();
  _instance = 0;
}

freettcn::TM::CTestManagement::TStatus freettcn::TM::CTestManagement::Status() const
{
  return _status;
}

void freettcn::TM::CTestManagement::Clear()
{
  Purge(_modParList);
  Purge(_tcList);
  
  _status = NOT_RUNNING;
}

freettcn::TM::CTestManagement::CTestCase &freettcn::TM::CTestManagement::TestCaseGet(const std::string &testCaseId) const
{
  for(CTCList::const_iterator it = _tcList.begin(); it != _tcList.end(); ++it) {
    if ((*it)->Name() == testCaseId)
      return *(*it);
  }
  
  throw ENotFound(E_DATA, "Test case '" + testCaseId + "' not found!!!");
}


const freettcn::TM::CTestManagement::CTCList &freettcn::TM::CTestManagement::TCList() const
{
  return _tcList;
}

const freettcn::TM::CTestManagement::CModuleParList &freettcn::TM::CTestManagement::ModuleParameterList() const
{
  return _modParList;
}

void freettcn::TM::CTestManagement::Init(const std::string &moduleId)
{
  if (_status != NOT_RUNNING)
    throw EOperationFailed(E_DATA, "Module '" + moduleId + "' already running!!!");
  
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
    if (_status != NOT_RUNNING) {
      if (_tc)
        TestCaseStop();
      else
        ControlStop();
    }
  } catch(EOperationFailed &) {
    std::cout << "ERROR: " << __FUNCTION__ << " problem!!!" << std::endl;
  }
}


const Value &freettcn::TM::CTestManagement::ModuleParameterGet(const TciModuleParameterIdType &parameterId) const
{
  for(CModuleParList::const_iterator it = _modParList.begin(); it != _modParList.end(); ++it) {
    if ((*it)->Name() == parameterId)
      return (*it)->ValueGet();
  }
  
  return 0;
}


void freettcn::TM::CTestManagement::TestCaseStart(const std::string &testCaseId, const TciParameterListType &parameterlist)
{
  _status = RUNNING_TEST_CASE;
  _tc = &TestCaseGet(testCaseId);
  _tc->Start(parameterlist);
}


void freettcn::TM::CTestManagement::TestCaseStarted(const TciTestCaseIdType &testCaseId, const TciParameterListType &parameterList, double timer)
{
  _tc = &TestCaseGet(testCaseId.objectName);
  _tc->Started(parameterList, timer);
  
  if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_TM_TC_STARTED)) {
    TriComponentId comp = { { 0 } };
    comp.compName = nullptr;
    comp.compType.moduleName = nullptr;
    comp.compType.objectName = nullptr;

    TciParameterListType parList(parameterList);
    tliTcStarted(0, TimeStampMgr().Get(), 0, 0, comp, testCaseId, parList, timer);
  }
}


void freettcn::TM::CTestManagement::TestCaseTerminated(const VerdictValue &verdict, const TciParameterListType &parameterList)
{
  if (_tc) {
    if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_TM_TC_TERMINATED)) {
      TriComponentId comp = { { 0 } };
      comp.compName = nullptr;
      comp.compType.moduleName = nullptr;
      comp.compType.objectName = nullptr;

      TciParameterListType parList(parameterList);
      tliTcTerminated(0, TimeStampMgr().Get(), 0, 0, comp, _tc->Id(), parList, verdict);
    }
    
    _tc->Terminated(verdict, parameterList);
    
    _tc = 0;
  }
  
  if (_status == RUNNING_TEST_CASE)
    _status = NOT_RUNNING;
}


void freettcn::TM::CTestManagement::TestCaseStop()
{
  if (_status == RUNNING_TEST_CASE) {
    if (_tc)
      _tc->Stop();
    else
      throw EOperationFailed(E_DATA, "Test Case not set!!!");
  }
  else
    throw EOperationFailed(E_DATA, "TestCase not running!!!");
}


void freettcn::TM::CTestManagement::ControlStart()
{
  _status = RUNNING_CONTROL;
  _ctrlCompId = new CTriComponentId(tciStartControl());
}


void freettcn::TM::CTestManagement::ControlStop()
{
  if (_status == RUNNING_CONTROL) {
    _status = NOT_RUNNING;
    tciStopControl();
  }
  else
    throw EOperationFailed(E_DATA, "Control not running");
}


void freettcn::TM::CTestManagement::ControlTerminated()
{
  if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_TM_CTRL_TERMINATED))
    tliCtrlTerminated(0, TimeStampMgr().Get(), 0, 0, _ctrlCompId->Id());
  
  delete _ctrlCompId;
  _ctrlCompId = 0;
  _status = NOT_RUNNING;
}
