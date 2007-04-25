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
#include "te.h"
#include "testComponent.h"
#include "behavior.h"
#include "testCase.h"
#include "tools.h"
#include <iostream>
extern "C" {
#include "freettcn/tci_te_tm.h"
#include "freettcn/tci_te_ch.h"
#include "freettcn/tri_te_sa.h"
#include "freettcn/tri_te_pa.h"
#include "freettcn/tci_tl.h"
}


// freettcn::CQualifiedName::CQualifiedName(String moduleName, String objectName, void *aux)
// {
//   _name.moduleName = moduleName;
//   _name.objectName = objectName;
//   _name.aux = aux;
// }

// const QualifiedName &freettcn::CQualifiedName::Get() const
// {
//   return _name;
// }



// freettcn::CModule::CModule(const CQualifiedName &id) :
//   _id(id)
// {
// }

// const TciModuleIdType &freettcn::CModule::Id() const
// {
//   return _id.Get();
// }



freettcn::TE::CModule::CParameter::CParameter(const std::string &name):
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

freettcn::TE::CModule::CModule(const std::string &name):
  CInitObject(name), _ctrlBehavior(0), _tc(0), __modParList(0), __tcIdList(0), _running(false)
{
  freettcn::TE::CModulesContainer &modContainer = freettcn::TE::CModulesContainer::Instance();
  modContainer.Register(*this);
}

freettcn::TE::CModule::~CModule()
{
  freettcn::TE::CModulesContainer &modContainer = freettcn::TE::CModulesContainer::Instance();
  modContainer.Deregister(*this);
  
  Purge(_tcList);
  Purge(_parameterList);
  
  if (_ctrlBehavior)
    delete _ctrlBehavior;
  
  // delete temporary variables
  if (__modParList)
    delete[] __modParList;
  if (__tcIdList)
    delete[] __tcIdList;
}


bool freettcn::TE::CModule::Running() const
{
  return _running;
}


void freettcn::TE::CModule::Reset()
{
  if (Running()) {
    if (_tc)
      // reset SA only if test case is running
      triSAReset();
    
    _running = false;
    
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
  _tcList.push_back(tc);
  tc->Module(*this);
  tc->Init();
}

void freettcn::TE::CModule::Register(CBehavior *ctrlBehavior)
{
  _ctrlBehavior = ctrlBehavior;
}

void freettcn::TE::CModule::ParametersSet() throw(freettcn::EOperationFailed)
{
  // obtain and set module parameters values
  for(ParameterList::iterator it=_parameterList.begin(); it != _parameterList.end(); ++it) {
    TciValue val = tciGetModulePar(const_cast<char *>((*it)->Name().c_str()));
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
    modParList.modParList[i].parName = const_cast<char *>((*it)->Name().c_str());
    modParList.modParList[i].defaultValue = ((*it)->DefaultValue());
  }
  
  return modParList;
}

TciTestCaseIdListType freettcn::TE::CModule::TestCases() const
{
  TciTestCaseIdListType tcList;
  tcList.length = _tcList.size();
  if (__tcIdList)
    delete[] __tcIdList;
  tcList.idList = __tcIdList = new TciTestCaseIdType[tcList.length];
  
  unsigned int i=0;
  for(TCList::const_iterator it=_tcList.begin(); it != _tcList.end(); ++it, i++) {
    tcList.idList[i].moduleName = const_cast<char *>(Name().c_str());
    tcList.idList[i].objectName = const_cast<char *>((*it)->Name().c_str());
    tcList.idList[i].aux = (*it);
  }
  
  return tcList;
}

freettcn::TE::CTestCase &freettcn::TE::CModule::TestCase(const std::string &tcId) const throw(ENotFound)
{
  for(TCList::const_iterator it=_tcList.begin(); it != _tcList.end(); ++it)
    if ((*it)->Name() == tcId)
      return *(*it);
  std::cout << "ERROR: Test Case not found" << std::endl;
  throw freettcn::ENotFound();
}

void freettcn::TE::CModule::TestCase(freettcn::TE::CTestCase *tc)
{
  _tc = tc;
}

freettcn::TE::CTestCase &freettcn::TE::CModule::TestCase() const throw(EOperationFailed)
{
  if (_tc)
    return *_tc;
  else {
    std::cout << "ERROR: Test Case not set" << std::endl;
    throw freettcn::EOperationFailed();
  }
}

TriComponentId freettcn::TE::CModule::ControlStart()
{
  _running = true;
  
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  return te.TestComponentCreateReq(0, TCI_CTRL_COMP, 0, "CONTROL");
}


void freettcn::TE::CModule::ControlStop() throw(EOperationFailed)
{
  // log
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(LOG_TE_CTRL_STOP)) {
    /// @todo ControlID should be created
    TriComponentId ctrlId;
    ctrlId.compInst.data = 0;
    ctrlId.compInst.bits = 0;
    ctrlId.compInst.aux = 0;
    ctrlId.compName = "saComp";
    ctrlId.compType.moduleName = "IP";
    ctrlId.compType.objectName = "IP_SA";
    ctrlId.compType.aux = 0;
    
    tliCtrlStop(0, te.TimeStamp().Get(), 0, 0, ctrlId);
  }
  
  _tc = 0;
  
  tciResetReq();
  
  // notify TM about control part termination
  tciControlTerminated();
}



freettcn::TE::CModulesContainer::CModulesContainer()
{
}

freettcn::TE::CModulesContainer &freettcn::TE::CModulesContainer::Instance()
{
  static freettcn::TE::CModulesContainer container;
  
  return container;
}

void freettcn::TE::CModulesContainer::Register(CModule &module)
{
  _modList.push_back(&module);
}

void freettcn::TE::CModulesContainer::Deregister(const CModule &module)
{
  /// @todo remove
}

freettcn::TE::CModule &freettcn::TE::CModulesContainer::Get(const std::string &moduleId) const throw(ENotFound)
{
  for(ModuleList::const_iterator it=_modList.begin(); it != _modList.end(); ++it)
    if ((*it)->Name() == moduleId)
      return *(*it);
  std::cout << "ERROR: Module not found" << std::endl;
  throw freettcn::ENotFound();
}

