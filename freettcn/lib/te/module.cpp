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


#include "freettcn/te/module.h"
#include "freettcn/te/modulesContainer.h"
#include "freettcn/te/te.h"
#include "freettcn/te/behavior.h"
#include "freettcn/te/testCase.h"
#include "freettcn/te/sourceData.h"
#include "freettcn/te/basicTypes.h"
#include "freettcn/tools/tools.h"
#include "freettcn/tools/logMask.h"
#include "freettcn/tools/timeStamp.h"
extern "C" {
#include "freettcn/ttcn3/tci_te_tm.h"
#include "freettcn/ttcn3/tci_te_ch.h"
#include "freettcn/ttcn3/tri_te_sa.h"
#include "freettcn/ttcn3/tri_te_pa.h"
#include "freettcn/ttcn3/tci_tl.h"
#include "freettcn/ttcn3/tci_value.h"
}
#include <iostream>




/* ********************************** P A R A M E T E R ********************************* */

freettcn::TE::CModule::CParameter::CParameter(const char *name, const CType::CInstance *defaultValue) throw(EOperationFailed):
  _defaultValue(defaultValue), _value(0)
{
  if (!_defaultValue)
    throw EOperationFailed();
  _id = const_cast<char *>(name);
}

freettcn::TE::CModule::CParameter::~CParameter()
{
  if (_defaultValue)
    delete _defaultValue;
  if (_value)
    delete _value;
}

const TciModuleParameterIdType &freettcn::TE::CModule::CParameter::Id() const
{
  return _id;
}

const freettcn::TE::CType::CInstance &freettcn::TE::CModule::CParameter::DefaultValue() const
{
  return *_defaultValue;
}

void freettcn::TE::CModule::CParameter::Value(const CType::CInstance *value)
{
  if (_value)
    delete _value;
  
  _value = value;
}

const freettcn::TE::CType::CInstance &freettcn::TE::CModule::CParameter::Value() const throw(EOperationFailed)
{
  if (_value) {
    if (!_value->Omit())
      return *_value;
    
    std::cout << "ERROR: Value is set to omit!!!" << std::endl;
    throw EOperationFailed();
  }
  else {
    if (!_defaultValue->Omit())
      return *_defaultValue;
    
    std::cout << "ERROR: Default value is set to omit!!!" << std::endl;
    throw EOperationFailed();
  }
}




/* ********************** T E S T   C O M P O N E N T   D A T A************************** */

freettcn::TE::CModule::CTestComponentData::CTestComponentData(const TriComponentId &id, TciTestComponentKindType kind):
  _id(id), _kind(kind)
{
}

const freettcn::TE::CTriComponentId &freettcn::TE::CModule::CTestComponentData::Id() const
{
  return _id;
}

TciTestComponentKindType freettcn::TE::CModule::CTestComponentData::Kind() const
{
  return _kind;
}

bool freettcn::TE::CModule::CTestComponentData::operator==(const TriComponentId &id) const
{
  const TriComponentId &localId = _id.Id();
  
  return (id.compInst.bits == localId.compInst.bits) &&
    !memcmp(id.compInst.data, localId.compInst.data, id.compInst.bits / 8);
}




/* ************************************* M O D U L E ************************************ */

freettcn::TE::CModule::CModule(const char *name):
  _ctrlBehavior(0), _ctrlSrcData(0),
  //_ctrlCompType(*this), 
  _ctrlRunning(false), _activeTestCase(0), __modParList(0), __testCaseIdList(0)
{
  freettcn::TE::CModulesContainer &modContainer = freettcn::TE::CModulesContainer::Instance();
  modContainer.Register(*this);
  
  _id.moduleName = const_cast<char *>(name);
  _id.objectName = _id.moduleName;
  _id.aux = this;
}

freettcn::TE::CModule::~CModule()
{
  Cleanup();
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


void freettcn::TE::CModule::Cleanup()
{
  Purge(_typeArray);
  Purge(_parameterArray);
  Purge(_allEntityStates);
  Purge(_behaviorList);
  Purge(_testCaseArray);
  Purge(_portTypeArray);
  
  if (_ctrlSrcData)
    delete _ctrlSrcData;
  
  // delete temporary variables
  if (__modParList)
    delete[] __modParList;
  if (__testCaseIdList)
    delete[] __testCaseIdList;
}


bool freettcn::TE::CModule::Running() const
{
  return _ctrlRunning || _activeTestCase;
}


void freettcn::TE::CModule::Reset()
{
  if (Running()) {
    if (_activeTestCase) {
      _activeTestCase->Reset();
      _activeTestCase = 0;
      
      // reset SA only if test case is running
      triSAReset();
    }
    
    _ctrlRunning = false;
    
    // delete all local test components but not Control component
    while (_localTestComponents.size()) {
      TLocalTestCompList::reverse_iterator it = _localTestComponents.rbegin();
      if ((*it)->Kind() == TCI_CTRL_COMP) {
        // unblock Control component
        (*it)->Status(CTestComponentType::CInstance::ACTIVE);
        (*it)->Run(CBehavior::OFFSET_AUTO);
        break;
      }
      else
        delete *it;
    }
    
    // reset PA
    triPAReset();
  }
}


void freettcn::TE::CModule::Register(const CType *type)
{
  _typeArray.push_back(type);
}


void freettcn::TE::CModule::Register(CParameter *parameter)
{
  _parameterArray.push_back(parameter);
}


void freettcn::TE::CModule::Register(const CBehavior *ctrlBehavior, const CSourceData *ctrlSrcData)
{
  _ctrlBehavior = ctrlBehavior;
  _ctrlSrcData = ctrlSrcData;
}


void freettcn::TE::CModule::Register(CTestCase *testCase)
{
  _testCaseArray.push_back(testCase);
}


void freettcn::TE::CModule::Register(CPortType *portType)
{
  _portTypeArray.push_back(portType);
}


// void freettcn::TE::CModule::ParametersSet() throw(freettcn::EOperationFailed)
// {
//   // obtain and set module parameters values
//   for(TParameterList::iterator it=_parameterArray.begin(); it != _parameterArray.end(); ++it) {
//     TciValue val = tciGetModulePar((*it)->Id());
// //     if (!val && (*it)->DefaultValue())
// //       val = new((*it)->DefaultValue());
    
//     if (!val)
//       throw freettcn::EOperationFailed();
    
//     (*it)->Value(val);
//   }
// }


TciModuleParameterListType freettcn::TE::CModule::Parameters() const
{
  TciModuleParameterListType modParList;
  modParList.length = _parameterArray.size();
  if (!__modParList) {
    __modParList = new TciModuleParameterType[modParList.length];
    
    for(unsigned int i=0; i<_parameterArray.size(); i++) {
      __modParList[i].parName = _parameterArray[i]->Id();
      __modParList[i].defaultValue = const_cast<void *>(static_cast<const void *>(&_parameterArray[i]->DefaultValue()));
    }
  }
  modParList.modParList = __modParList;
  
  return modParList;
}


const freettcn::TE::CType &freettcn::TE::CModule::Type(const char *typeName) const throw(ENotFound)
{
  for(unsigned int i=0; i<_typeArray.size(); i++)
    if (!strcmp(_typeArray[i]->Name(), typeName))
      return *_typeArray[i];
  
  std::cout << "ERROR: " << __FUNCTION__ << ":" << __LINE__ <<
    " Requested type: '" << typeName << "'not found" << std::endl;
  throw ENotFound();
}


const freettcn::TE::CType &freettcn::TE::CModule::Type(unsigned int typeIdx) const throw(ENotFound)
{
  if (typeIdx < _typeArray.size())
    return *_typeArray[typeIdx];
  
  std::cout << "ERROR: Type index: " << typeIdx << " too big (size: " << _typeArray.size() << ")" << std::endl;
  throw ENotFound();
}


const freettcn::TE::CPortType &freettcn::TE::CModule::PortType(unsigned int portTypeIdx) const throw(ENotFound)
{
  if (portTypeIdx < _portTypeArray.size())
    return *_portTypeArray[portTypeIdx];
  
  std::cout << "ERROR: Port Type index: " << portTypeIdx << " too big (size: " << _portTypeArray.size() << ")" << std::endl;
  throw ENotFound();
}


TciTestCaseIdListType freettcn::TE::CModule::TestCases() const
{
  TciTestCaseIdListType tcList;
  tcList.length = _testCaseArray.size();
  if (!__testCaseIdList) {
    __testCaseIdList = new TciTestCaseIdType[tcList.length];
    for(unsigned int i=0; i<_testCaseArray.size(); i++)
      __testCaseIdList[i] = _testCaseArray[i]->Id();
  }
  tcList.idList = __testCaseIdList;
  
  return tcList;
}


freettcn::TE::CTestCase &freettcn::TE::CModule::TestCase(const char *tcId) const throw(ENotFound)
{
  for(unsigned int i=0; i<_testCaseArray.size(); i++)
    if (!strcmp(_testCaseArray[i]->Id().objectName, tcId))
      return *_testCaseArray[i];
  std::cout << "ERROR: Test Case not found" << std::endl;
  throw freettcn::ENotFound();
}

freettcn::TE::CTestCase &freettcn::TE::CModule::TestCase(unsigned int tcIdx) const throw(ENotFound)
{
  if (tcIdx < _testCaseArray.size())
    return *_testCaseArray[tcIdx];
  
  std::cout << "ERROR: Type index: " << tcIdx << " too big (size: " << _testCaseArray.size() << ")" << std::endl;
  throw ENotFound();
}


void freettcn::TE::CModule::ActiveTestCase(freettcn::TE::CTestCase &tc)
{
  _activeTestCase = &tc;
}


freettcn::TE::CTestCase &freettcn::TE::CModule::ActiveTestCase() const throw(ENotFound)
{
  if (_activeTestCase)
    return *_activeTestCase;
  
  std::cout << "ERROR: Test Case not running!!!" << std::endl;
  throw ENotFound();
}


const freettcn::TE::CTriComponentId &freettcn::TE::CModule::ControlStart()
{
  // obtain module parameters
//   ParametersSet();

  _ctrlRunning = true;
  
  return TestComponentCreateReq(_ctrlSrcData->Source(), _ctrlSrcData->Line(), ModuleComponentId(), TCI_CTRL_COMP, 0, "CONTROL");
}


void freettcn::TE::CModule::ControlStop() throw(EOperationFailed)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(freettcn::CLogMask::CMD_TE_CTRL_STOP))
    // log
    tliCtrlStop(0, te.TimeStamp().Get(), 0, 0, ModuleComponentId());
  
  if (_activeTestCase)
    _activeTestCase->Stop();
  
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
  for(TBehaviorList::const_iterator it=_behaviorList.begin(); it!=_behaviorList.end(); ++it) {
    TciBehaviourIdType id = (*it)->Id();
    if (!strcmp(behavior.objectName, id.objectName))
      return *(*it);
  }
  
  std::cout << "ERROR!!! Behavior not found" << std::endl;
  throw freettcn::ENotFound();
}


freettcn::TE::CTestComponentType::CInstance &freettcn::TE::CModule::TestComponent(const TriComponentId &component) const throw(freettcn::ENotFound)
{
  freettcn::TE::CIdObject &object = CIdObject::Get(component.compInst);
  try {
    return dynamic_cast<freettcn::TE::CTestComponentType::CInstance &>(object);
  }
  catch(Exception) {
    throw;
  }
  catch(std::exception &ex) {
    std::cout << "Error: System exception: " << ex.what() << " caught!!!" << std::endl;
    throw freettcn::ENotFound();
  }
}


const freettcn::TE::CTriComponentId &freettcn::TE::CModule::TestComponentCreateReq(const char *src, int line,
                                                                                    const TriComponentId &creatorId,
                                                                                    TciTestComponentKindType kind,
                                                                                    const CTestComponentType *compType,
                                                                                    const char *name)
{
  CTTCNExecutable &te = CTTCNExecutable::Instance();
  if (kind == TCI_CTRL_COMP) {
    if (te.Logging() && te.LogMask().Get(freettcn::CLogMask::CMD_TE_CTRL_START))
      // log
      tliCtrlStart(0, te.TimeStamp().Get(), const_cast<char *>(src), line, creatorId);
  }
  
  TriComponentId compId = tciCreateTestComponentReq(kind, const_cast<void *>(reinterpret_cast<const void*>(compType)), const_cast<char *>(name));
  const CTestComponentData *data = new CTestComponentData(compId, kind);
  _allEntityStates.push_back(data);
  
  if (te.Logging() && te.LogMask().Get(freettcn::CLogMask::CMD_TE_C_CREATE))
    // log
    tliCCreate(0, te.TimeStamp().Get(), const_cast<char *>(src), line, creatorId, compId, const_cast<char *>(name));
  
  if (kind == TCI_CTRL_COMP) {
    // start control test component immediately using default control behavior
    
    // control does not have parameters
    TciParameterListType parameterList;
    parameterList.length = 0;
    parameterList.parList = 0;
    
    TestComponentStartReq(src, line, creatorId, compId, ControlBehavior().Id(), parameterList);
  }
  
  return data->Id();
}


const TriComponentId &freettcn::TE::CModule::TestComponentCreate(TciTestComponentKindType kind,
                                                                 TciType componentType,
                                                                 const char *name)
{
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
  
  cInstance->Init(*this, kind, name);
  
  return cInstance->Id();
}


void freettcn::TE::CModule::TestComponentStartReq(const char *src, int line,
                                                  const TriComponentId &creatorId,
                                                  const TriComponentId &componentId,
                                                  const TciBehaviourIdType &behaviorId,
                                                  const TciParameterListType &parameterList)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(freettcn::CLogMask::CMD_TE_C_START))
    // log
    tliCStart(0, te.TimeStamp().Get(), const_cast<char *>(src), line, creatorId, componentId, behaviorId, parameterList);
  
  tciStartTestComponentReq(componentId, behaviorId, parameterList);
}


void freettcn::TE::CModule::TestComponentStart(const TriComponentId &componentId,
                                               const TciBehaviourIdType &behaviorId,
                                               const TciParameterListType &parameterList) throw(ENotFound)
{
  TestComponent(componentId).Start(Behavior(behaviorId), parameterList);
}


void freettcn::TE::CModule::TestComponentStop(const TriComponentId &componentId) throw(ENotFound)
{
  TestComponent(componentId).Stop(0, 0);
}


void freettcn::TE::CModule::TestComponentTerminated(const TriComponentId &componentId, TciVerdictValue verdict) throw(ENotFound)
{
  const CTestComponentData *comp = 0;
  
  for(TTestCompList::iterator it=_allEntityStates.begin(); it!=_allEntityStates.end(); ++it) {
    if (*(*it) == componentId) {
      comp = *it;
      _allEntityStates.erase(it);
      break;
    }
  }
  
  if (!comp) {
    std::cout << "ERROR: Test Component not found!!!" << std::endl;
    throw ENotFound();
  }
  
  _done.push_back(comp);
  
  switch (comp->Kind()) {
  case TCI_CTRL_COMP:
    // control terminated
    tciControlTerminated();
    break;
    
  case TCI_MTC_COMP:
    {
      // update testcase verdict
      _activeTestCase->Verdict(static_cast<TVerdict>(tciGetVerdictValue(verdict)));

      // get SYSTEM component
      for(TTestCompList::iterator it=_allEntityStates.begin(); it!=_allEntityStates.end(); ++it) {
        if ((*it)->Kind() == TCI_SYS_COMP) {
          // stop SYSTEM component
          tciStopTestComponentReq((*it)->Id().Id());
          break;
        }
      }
      
      TciParameterListType parms;
      parms.length = 0;
      parms.parList = 0;
      
      // test case terminated
      tciTestCaseTerminated(verdict, parms);
      _activeTestCase->Reset();
      _activeTestCase = 0;
      
      // get control component
      if (_localTestComponents.size()) {
        CTestComponentType::CInstance *ctrlCmp = *_localTestComponents.begin();
        if (ctrlCmp->Kind() == TCI_CTRL_COMP) {
          // unblock Control component
          ctrlCmp->Status(CTestComponentType::CInstance::ACTIVE);
          ctrlCmp->Run(CBehavior::OFFSET_AUTO);
        }
      }
    }
    break;
    
  case TCI_SYS_COMP:
    // do nothing
    break;
    
  case TCI_PTC_COMP:
  case TCI_ALIVE_COMP:
    // update testcase verdict
    _activeTestCase->Verdict(static_cast<TVerdict>(tciGetVerdictValue(verdict)));
      
    /// @todo PTC termination
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
    break;
  }
}


void freettcn::TE::CModule::TestComponentKill(const TriComponentId &componentId) throw(ENotFound)
{
  delete &TestComponent(componentId);
  
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(freettcn::CLogMask::CMD_TE_C_KILLED))
    // log
    tliCKilled(0, te.TimeStamp().Get(), 0, 0, componentId, 0);
}


void freettcn::TE::CModule::TestComponentLocalAdd(CTestComponentType::CInstance &comp)
{
  _localTestComponents.push_back(&comp);
}


void freettcn::TE::CModule::TestComponentLocalRemove(CTestComponentType::CInstance &comp) throw(ENotFound)
{
  for(TLocalTestCompList::iterator it=_localTestComponents.begin(); it!=_localTestComponents.end(); ++it) {
    if (*it == &comp) {
      _localTestComponents.erase(it);
      return;
    }
  }
  
  std::cout << "ERROR: Local test component not found" << std::endl;
  throw ENotFound();
}
