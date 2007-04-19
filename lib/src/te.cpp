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


#include "te.h"
extern "C" {
#include "freettcn/tci_te_tm.h"
#include "freettcn/tci_te_ch.h"
#include "freettcn/tri_te_sa.h"
#include "freettcn/tri_te_pa.h"
}
#include "tools.h"
#include <iostream>



freettcn::TE::CObject::CObject(const std::string &name):
  _name(name), _inited(false)
{
}

freettcn::TE::CObject::~CObject()
{
}

const std::string &freettcn::TE::CObject::Name() const
{
  return _name;
}

void freettcn::TE::CObject::Init()
{
  if (!_inited) {
    Initialize();
    _inited = true;
  }
}




freettcn::TE::CTestCase::CTestCase(const std::string &name):
  CObject(name), _module(0)
{
}

freettcn::TE::CTestCase::~CTestCase()
{
}

void freettcn::TE::CTestCase::Register(CModule &module)
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
  // create MTC
  TciType mtcType = 0;                            /**< @todo MTC type support */
  _mtcId = tciCreateTestComponentReq(TCI_MTC_COMP, mtcType, 0);
  
  // give a chance to create static connections and the initialization of TSI ports
  TciTestCaseIdType testCaseId;
  testCaseId.moduleName = "";                     /**< @todo Module name */
  testCaseId.objectName = const_cast<char *>(Name().c_str());
  testCaseId.aux = 0;
  
  tciExecuteTestCaseReq(testCaseId, Ports());
  
  // start MTC
  TciBehaviourIdType behavior;
  behavior.moduleName = 0;
  behavior.objectName = 0;
  behavior.aux = 0;
  
  TciParameterListType parameterList;
  parameterList.length = 0;
  parameterList.parList = 0;
  
  tciStartTestComponentReq(_mtcId, behavior, parameterList);
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
  tciResetReq();
  
  /// @todo set verdict to ERROR
  
  // notify TM about test case termination
  TciValue error = 0;
  TciParameterListType parList;
  parList.length = 0;
  parList.parList = 0;
  tciTestCaseTerminated(error, parList);
}



freettcn::TE::CModule::CParameter::CParameter(const std::string &name):
  CObject(name), _defaultValue(0), _value(0)
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
  CObject(name), _running(false), _tc(0), __modParList(0), __tcIdList(0)
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
    if (_tc) {
      // reset SA only if test case is running
      triSAReset();
    }
    
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
  tc->Register(*this);
  tc->Init();
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
  return tciCreateTestComponentReq(TCI_CTRL_COMP, 0, 0);
}


void freettcn::TE::CModule::ControlStop() throw(EOperationFailed)
{
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


void freettcn::TE::CTTCNExecutable::Reset()
{
  // stop running module
  RootModule().Reset();
}


void freettcn::TE::CTTCNExecutable::RootModule(freettcn::TE::CModule &module)
{
  _rootModule = &module;
  
  // init module
  _rootModule->Init();
}


freettcn::TE::CModule &freettcn::TE::CTTCNExecutable::RootModule() const throw(ENotFound)
{
  if (_rootModule)
    return *_rootModule;
  
  std::cout << "ERROR: Root Module not set" << std::endl;
  throw freettcn::ENotFound();
}


TriComponentId freettcn::TE::CTTCNExecutable::TestComponentCreate(TciTestComponentKindType kind,
                                                                  TciType componentType,
                                                                  String name)
{
  TriComponentId ctrlId;
  ctrlId.compInst.data = 0;
  ctrlId.compInst.bits = 0;
  ctrlId.compInst.aux = 0;
  ctrlId.compName = "saComp";
  ctrlId.compType.moduleName = "IP";
  ctrlId.compType.objectName = "IP_SA";
  ctrlId.compType.aux = 0;
  
  return ctrlId;
}


void freettcn::TE::CTTCNExecutable::TestComponentStart(TriComponentId component,
                                                       TciBehaviourIdType behavior,
                                                       TciParameterListType parameterList)
{
//   cmp.Started();
}


void freettcn::TE::CTTCNExecutable::TestComponentTerminated(TriComponentId component, TciVerdictValue verdict)
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
}



void freettcn::TE::CTTCNExecutable::Connect(TriPortId fromPort, TriPortId toPort)
{

}

void freettcn::TE::CTTCNExecutable::Disconnect(TriPortId fromPort, TriPortId toPort)
{

}

void freettcn::TE::CTTCNExecutable::Map(TriPortId fromPort, TriPortId toPort)
{
  if (triMap(&fromPort, &toPort) != TRI_OK) {
    /// @todo do something
  }
}

void freettcn::TE::CTTCNExecutable::Unmap(TriPortId fromPort, TriPortId toPort)
{
  if (triUnmap(&fromPort, &toPort) != TRI_OK) {
    /// @todo do something
  }
}
