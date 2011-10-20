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
 * @file   t3rts.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:04:58 2007
 * 
 * @brief  
 * 
 * 
 */


#include "freettcn/te/t3rts.h"
#include "freettcn/te/teEnv.h"
#include "freettcn/te/ets.h"
#include "freettcn/etsi/TriCommunicationSA.h"
#include "freettcn/etsi/TriPlatformPA.h"
#include "freettcn/etsi/TciTmProvided.h"
#include "freettcn/te/module.h"
// #include "freettcn/ttcn3/triTimerDuration.h"
// #include "freettcn/te/modulesContainer.h"
// #include "freettcn/te/component.h"
// #include "freettcn/te/port.h"
// #include "freettcn/te/testCase.h"
// #include "freettcn/tools/exception.h"



freettcn::TE::CTTCN3RuntimeSystem::CTTCN3RuntimeSystem(const CExecutableTestSuite &ets):
  _env(nullptr), _ets(ets),
  _rootModule(nullptr), _ctrlRunning(false), _activeTestCase(nullptr)
{
}


bool freettcn::TE::CTTCN3RuntimeSystem::Running() const
{
  return _ctrlRunning || _activeTestCase;
}


void freettcn::TE::CTTCN3RuntimeSystem::Reset()
{
  if(Running()) {
    if(_activeTestCase) {
      _activeTestCase = nullptr;
      
      // reset SA only if test case is running
      _env->SA().triSAReset();
    }
    
    _ctrlRunning = false;
    
    // delete all local test components but not Control component
    /// @todo Kill components
    
    // reset PA
    _env->PA().triPAReset();
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::RootModule(const TciModuleId &moduleName)
{
  // check if TTCN Executable is running test case or control part
  if(Running()) {
    _env->TM().tciError("Cannot set TTCN Root Module while tests are running");
    return;
  }
  
  // obtain requested module and set it as active one
  _rootModule = &_ets.Module(moduleName);
  
  // init module
  _rootModule->Init();
}


freettcn::TE::CModule &freettcn::TE::CTTCN3RuntimeSystem::RootModule() const
{
  if(_rootModule)
    return *_rootModule;
  throw ENotFound(E_DATA, "TTCN Root Module is not set");
}


const freettcn::TE::CTestCase &freettcn::TE::CTTCN3RuntimeSystem::ActiveTestCase() const
{
  if(_activeTestCase)
    return *_activeTestCase;
  throw ENotFound(E_DATA, "Test Case not running");
}



const ORG_ETSI_TTCN3_TCI::TciModuleIdList *freettcn::TE::CTTCN3RuntimeSystem::getImportedModules() const
{
  try {
    throw ENotImplemented(E_DATA, "Module imports are not supported yet");
    return &RootModule().ImportedModules();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TciModuleParameterList *freettcn::TE::CTTCN3RuntimeSystem::tciGetModuleParameters(const TciModuleId *moduleName)
{
  try {
    assert(moduleName);
    RootModule();
    return &CModulesContainer::Instance().Get(*moduleName).Parameters();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TciTestCaseIdList *freettcn::TE::CTTCN3RuntimeSystem::tciGetTestCases() const
{
  try {
    return &RootModule().TestCases();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TciParameterTypeList *freettcn::TE::CTTCN3RuntimeSystem::tciGetTestCaseParameters(const TciTestCaseId *testCaseId) const
{
  try {
    assert(testCaseId);
    return &RootModule().TestCase(*testCaseId).Parameters();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TriPortIdList *freettcn::TE::CTTCN3RuntimeSystem::tciGetTestCaseTSI(const TciTestCaseId &testCaseId) const
{
  try {
    return &RootModule().TestCase(testCaseId).SystemInterface();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciStartTestCase(const TciTestCaseId *testCaseId,
                                                     const TciParameterList *parameterList)
{
  try {
    assert(testCaseId);
    
    CModule &module = RootModule();
    CTestCase &tc = module.TestCase(*testCaseId);
    
    // obtain module parameters
    module.ParametersObtain();
    
    // set as current test case
    _activeTestCase = &tc;
    
    // start test case
    _activeTestCase->Start("", 0, nullptr, parameterList, 0);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciStopTestCase()
{
  try {
    CModule &module = RootModule();
    if(module.Running())
      ActiveTestCase().Stop();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


const ORG_ETSI_TTCN3_TRI::TriComponentId *freettcn::TE::CTTCN3RuntimeSystem::tciStartControl()
{
  try {
    freettcn::TE::CModule &module = RootModule();
    
    // obtain module parameters
    module.ParametersObtain();
    
    return &module.ControlStart();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciStopControl()
{
  try {
    freettcn::TE::CModule &module = RootModule();
    if(module.Running())
      module.ControlStop();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}




// CH requests

void freettcn::TE::CTTCN3RuntimeSystem::tciEnqueueMsgConnected(const TriPortId *sender,
                                                           const TriComponentId *receiver,
                                                           const TciValue *rcvdMessage)
{
  try {
    assert(sender);
    assert(receiver);
    assert(rcvdMessage);
    
    std::unique_ptr<const TciValue> msg(rcvdMessage->clone());
    
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "EnqueMsg is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciEnqueueCallConnected(const TriPortId *sender,
                                                            const TriComponentId *receiver,
                                                            const TriSignatureId *signature,
                                                            const TciParameterList *parameterList)
{
  try {
    assert(sender);
    assert(receiver);
    assert(signature);
    assert(parameterList);
    
    std::unique_ptr<const TciParameterList> msg(parameterList->clone());
    
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "EnqueCall is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciEnqueueReplyConnected(const TriPortId *sender,
                                                             const TriComponentId *receiver,
                                                             const TriSignatureId *signature,
                                                             const TciParameterList *parameterList,
                                                             const TciValue *returnValue)
{
  try {
    assert(sender);
    assert(receiver);
    assert(signature);
    assert(parameterList);
    
    std::unique_ptr<const TciParameterList> msg(parameterList->clone());
    
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "EnqueReply is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciEnqueueRaiseConnected(const TriPortId *sender,
                                                             const TriComponentId *receiver,
                                                             const TriSignatureId *signature,
                                                             const TciValue *exception)
{
  try {
    assert(sender);
    assert(receiver);
    assert(signature);
    assert(exception);
    
    std::unique_ptr<const TciValue> msg(exception->clone());
    
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "EnqueRaise is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


const ORG_ETSI_TTCN3_TRI::TriComponentId *freettcn::TE::CTTCN3RuntimeSystem::tciCreateTestComponent(const TciTestComponentKind *kind,
                                                                                                const TciType *componentType,
                                                                                                const Tstring *name)
{
  try {
    assert(kind);
    
    // check condition from spec
    if(*kind == CTRL_COMP && componentType)
      throw EOperationFailed(E_DATA, "'componentType' provided for Control component in 'tciCreateTestComponent()'");
    
    // get component type
    std::shared_ptr<const CTypeComponent> type;
    if(componentType) {
      if(componentType->getTypeClass() != TCI_COMPONENT)
        throw EOperationFailed(E_DATA, "Type of class '" + Convert(componentType->getTypeClass()) + "' provided as 'componentType' in 'tciCreateTestComponent()'");
      CModule &module = CModulesContainer::Instance().Get(componentType->getDefiningModule());
      type = module.ComponentType(*componentType);
    }
    else if(*kind == CTRL_COMP)
      type.reset(new CTypeComponentControl());
    else
      throw EOperationFailed(E_DATA, "'componentType' not provided in 'tciCreateTestComponent()'");
    
    // create component instance
    std::unique_ptr<CComponent> comp;
    if(*kind == MTC_COMP)
      comp.reset(new CComponentMTC(type, *kind, name));
    else if(*kind == PTC_ALIVE_COMP)
      comp.reset(new CComponentAlive(type, *kind, name));
    else
      comp.reset(new CComponentPTC(type, *kind, name));
    
    // store handler
    const TriComponentId &id = *comp->Id();
    _componentMap[&id] = std::move(comp);
    // if(kind == CTRL_COMP)
    //   // store control component
    //   _ctrlComponent = cInstance;
    
    return &id;
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciStartTestComponent(const TriComponentId *component,
                                                          const TciBehaviourId *behaviour,
                                                          const TciParameterList *parameterList)
{
  try {
    assert(component);
    assert(behaviour);
    CModule &module = CModulesContainer::Instance().Get(behaviour->getName().getModuleName());
    Component(*component).Start(module.Behaviour(*behaviour), parameterList);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciStopTestComponent(const TriComponentId *component)
{
  try {
    assert(component);
    Component(*component).Stop();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciConnect(const TriPortId *fromPort,
                                               const TriPortId *toPort)
{
  try {
    assert(fromPort);
    assert(toPort);
    CComponent *comp1 = ComponentCheck(fromPort->getComponent());
    CComponent *comp2 = ComponentCheck(toPort->getComponent());
    if(!comp1 && !comp2)
      throw EOperationFailed(E_DATA, "Component to connect not found");
    if(comp1)
      comp1->Port(*fromPort).Connect(*toPort);
    if(comp2)
      comp2->Port(*toPort).Connect(*fromPort);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciDisconnect(const TriPortId *fromPort,
                                                  const TriPortId *toPort)
{
  try {
    assert(fromPort);
    assert(toPort);
    CComponent *comp1 = ComponentCheck(fromPort->getComponent());
    CComponent *comp2 = ComponentCheck(toPort->getComponent());
    if(!comp1 && !comp2)
      throw EOperationFailed(E_DATA, "Component to disconnect not found");
    if(comp1)
      comp1->Port(*fromPort).Disconnect(*toPort);
    if(comp2)
      comp2->Port(*toPort).Disconnect(*fromPort);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciMap(const TriPortId *fromPort,
                                           const TriPortId *toPort)
{
  try {
    assert(fromPort);
    assert(toPort);
    CComponent *comp1 = ComponentCheck(fromPort->getComponent());
    CComponent *comp2 = ComponentCheck(toPort->getComponent());
    if(!comp1 && !comp2)
      throw EOperationFailed(E_DATA, "Component to map not found");
    if(comp1)
      comp1->Port(*fromPort).Map(*toPort);
    if(comp2)
      comp2->Port(*toPort).Map(*fromPort);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciUnmap(const TriPortId *fromPort,
                                             const TriPortId *toPort)
{
  try {
    assert(fromPort);
    assert(toPort);
    CComponent *comp1 = ComponentCheck(fromPort->getComponent());
    CComponent *comp2 = ComponentCheck(toPort->getComponent());
    if(!comp1 && !comp2)
      throw EOperationFailed(E_DATA, "Component to unmap not found");
    if(comp1)
      comp1->Port(*fromPort).Unmap(*toPort);
    if(comp2)
      comp2->Port(*toPort).Unmap(*fromPort);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciTestComponentTerminated(const TriComponentId *component,
                                                               const VerdictValue *verdict) const
{
  try {
    assert(component);
    assert(verdict);
    TestComponentTerminated(*component, *verdict);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


Tboolean freettcn::TE::CTTCN3RuntimeSystem::tciTestComponentRunning(const TriComponentId *component) const
{
  try {
    assert(component);
    return TestComponentRunning(*component);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return false;
  }
}


Tboolean freettcn::TE::CTTCN3RuntimeSystem::tciTestComponentDone(const TriComponentId *comp) const
{
  try {
    assert(comp);
    return TestComponentDone(*comp);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return false;
  }
}


const ORG_ETSI_TTCN3_TRI::TriComponentId *freettcn::TE::CTTCN3RuntimeSystem::tciGetMTC() const
{
  try {
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
    return TestCase(*testCaseId).Mtc();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullPtr;
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciExecuteTestCase(const TciTestCaseId *testCaseId,
                                                       const TriPortIdList *tsiPortList)
{
  try {
    assert(testCaseId);
    
    // set as current test case
    CModule &module = CModulesContainer::Instance().Get(testCaseId->getName().getModuleName());
    _activeTestCase = &module.TestCase(*testCaseId);
    
    // prepare test case
    _activeTestCase->Execute(*testCaseId, tsiPortList);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::tciKillTestComponent(const TriComponentId *comp)
{
  try {
    assert(comp);
    TestComponentKill(&comp);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


Tboolean freettcn::TE::CTTCN3RuntimeSystem::tciTestComponentAlive(const TriComponentId *comp) const
{
  try {
    assert(comp);
    return TestComponentAlive(*comp);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return false;
  }
}


Tboolean freettcn::TE::CTTCN3RuntimeSystem::tciTestComponentKilled(const TriComponentId *comp) const
{
  try {
    return TestComponentKilled(*comp);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return false;
  }
}



// CD requests

const ORG_ETSI_TTCN3_TCI::TciType *freettcn::TE::CTTCN3RuntimeSystem::getTypeForName(const Tstring typeName) const
{
  try {
    if(typeName == "anytype" || typeName == "address")
      // special meaning of "anytype" "address"
      /// @todo enqueue new message
      throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
    
    if(typeName == "integer")
      return *CBuiltInTypes::Integer();
    else if(typeName == "float")
      throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
    else if(typeName == "bitstring")
      throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
    else if(typeName == "hexstring")
      throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
    else if(typeName == "octetstring")
      return *CBuiltInTypes::Octetstring();
    else if(typeName == "charstring")
      throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
    else if(typeName == "universal charstring")
      throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
    else if(typeName == "boolean")
      return *CBuiltInTypes::Boolean();
    else if(typeName == "verdicttype")
      return *CBuiltInTypes::Verdict();
    else {
      // read qualified name
      std::Tstring::size_type pos = typeName.find_first_of(".");
      if(pos == std::Tstring::npos)
        throw EOperationFailed(E_DATA, "'" + typeName + "' is not a fully qualified type name");
      std::Tstring::size_type pos2 = typeName.find_last_of(".");
      if(pos != pos2)
        throw EOperationFailed(E_DATA, "'" + typeName + "' is not a fully qualified type name");
      
      std::Tstring module(typeName, 0, pos);
      std::Tstring type(typeName, pos + 1);
      return CModulesContainer::Instance().Get(module).Type(type).get();
    }
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullPtr;
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getInteger() const
{
  return *CBuiltInTypes::Integer();
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getFloat() const
{
  try {
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *CBuiltInTypes::Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getBoolean() const
{
  return *CBuiltInTypes::Boolean();
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getCharstring() const
{
  try {
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *CBuiltInTypes::Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getUniversalCharstring() const
{
  try {
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *CBuiltInTypes::Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getHexstring() const
{
  try {
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *CBuiltInTypes::Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getBitstring() const
{
  try {
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *CBuiltInTypes::Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getOctetstring() const
{
  return *CBuiltInTypes::Octetstring();
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3RuntimeSystem::getVerdict() const
{
  return *CBuiltInTypes::Verdict();
}


void freettcn::TE::CTTCN3RuntimeSystem::tciErrorReq(const Tstring message)
{
  _env->TM().tciError(message);
}


// PA requests

void freettcn::TE::CTTCN3RuntimeSystem::triTimeout(const TriTimerId *timerId)
{
  try {
    assert(timerId);
    freettcn::TE::CIdObject &object = CIdObject::Get(*timerId);
    try {
      dynamic_cast<freettcn::TE::CTimer &>(object).Timeout();
    }
    catch(std::exception &ex) {
      throw EOperationFailed(E_DATA, "'timerId' does not point to Timer type!!!");
    }
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


// SA requests

void freettcn::TE::CTTCN3RuntimeSystem::triEnqueueMsg(const TriPortId *tsiPortId,
                                                  const TriAddress *SUTaddress,
                                                  const TriComponentId *componentId,
                                                  const TriMessage *receivedMessage)
{
  try {
    assert(tsiPortId);
    assert(componentId);
    assert(receivedMessage);
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::triEnqueueCall(const TriPortId *tsiPortId,
                                                   const TriAddress *SUTaddress,
                                                   const TriComponentId *componentId,
                                                   const TriSignatureId *signatureId,
                                                   const TriParameterList *parameterList)
{
  try {
    assert(tsiPortId);
    assert(componentId);
    assert(signatureId);
    assert(parameterList);
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::triEnqueueReply(const TriPortId *tsiPortId,
                                                    const TriAddress *SUTaddress,
                                                    const TriComponentId *componentId,
                                                    const TriSignatureId *signatureId,
                                                    const TriParameterList *parameterList,
                                                    const TriParameter *returnValue)
{
  try {
    assert(tsiPortId);
    assert(componentId);
    assert(signatureId);
    assert(parameterList);
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3RuntimeSystem::triEnqueueException(const TriPortId *tsiPortId,
                                                        const TriAddress *SUTaddress,
                                                        const TriComponentId *componentId,
                                                        const TriSignatureId *signatureId,
                                                        const TriException *exc)
{
  try {
    assert(tsiPortId);
    assert(componentId);
    assert(signatureId);
    assert(exc);
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}
