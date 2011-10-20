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
#include "freettcn/te/teEnv.h"
#include "freettcn/te/t3rts.h"
#include "freettcn/te/eds.h"
#include "freettcn/te/ets.h"
#include "freettcn/etsi/TciTmProvided.h"
#include "freettcn/te/module.h"
#include "freettcn/te/testCase.h"
#include "freettcn/te/component.h"
#include "freettcn/ttcn3/integer.h"
#include "freettcn/ttcn3/boolean.h"
#include "freettcn/ttcn3/verdict.h"
#include "freettcn/ttcn3/octetstring.h"
#include "freettcn/tools/exception.h"
#include <cassert>


freettcn::TE::CTTCN3Executable::CTTCN3Executable():
  _t3rts(_ets)
{
}


void freettcn::TE::CTTCN3Executable::Environment(std::unique_ptr<const CEnvironment> env)
{ 
  _env = std::move(env); 
  _t3rts.Environment(*env);
}


// TM requests

void freettcn::TE::CTTCN3Executable::tciRootModule(const TciModuleId *moduleName)
{
  try {
    assert(moduleName);
    _t3rts.RootModule(*moduleName);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


const ORG_ETSI_TTCN3_TCI::TciModuleIdList *freettcn::TE::CTTCN3Executable::getImportedModules() const
{
  try {
    throw ENotImplemented(E_DATA, "Module imports are not supported yet");
    return &_t3rts.RootModule().ImportedModules();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TciModuleParameterList *freettcn::TE::CTTCN3Executable::tciGetModuleParameters(const TciModuleId *moduleName)
{
  try {
    assert(moduleName);
    _t3rts.RootModule();
    return &_ets.Module(*moduleName).Parameters();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TciTestCaseIdList *freettcn::TE::CTTCN3Executable::tciGetTestCases() const
{
  try {
    return &_t3rts.RootModule().TestCases();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TciParameterTypeList *freettcn::TE::CTTCN3Executable::tciGetTestCaseParameters(const TciTestCaseId *testCaseId) const
{
  try {
    assert(testCaseId);
    return &_t3rts.RootModule().TestCase(*testCaseId).Parameters();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TriPortIdList *freettcn::TE::CTTCN3Executable::tciGetTestCaseTSI(const TciTestCaseId &testCaseId) const
{
  try {
    return &_t3rts.RootModule().TestCase(testCaseId).SystemInterface();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


void freettcn::TE::CTTCN3Executable::tciStartTestCase(const TciTestCaseId *testCaseId,
                                                      const TciParameterList *parameterList)
{
  try {
    assert(testCaseId);
    _t3rts.TestCaseStart(*testCaseId, parameterList);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciStopTestCase()
{
  try {
    _t3rts.TestCaseStop();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


const ORG_ETSI_TTCN3_TRI::TriComponentId *freettcn::TE::CTTCN3Executable::tciStartControl()
{
  try {
    return _t3rts.ControlStart();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


void freettcn::TE::CTTCN3Executable::tciStopControl()
{
  try {
    _t3rts.ControlStop();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}




// CH requests

void freettcn::TE::CTTCN3Executable::tciEnqueueMsgConnected(const TriPortId *sender,
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


void freettcn::TE::CTTCN3Executable::tciEnqueueCallConnected(const TriPortId *sender,
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


void freettcn::TE::CTTCN3Executable::tciEnqueueReplyConnected(const TriPortId *sender,
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


void freettcn::TE::CTTCN3Executable::tciEnqueueRaiseConnected(const TriPortId *sender,
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


const ORG_ETSI_TTCN3_TRI::TriComponentId *freettcn::TE::CTTCN3Executable::tciCreateTestComponent(const TciTestComponentKind *kind,
                                                                                                const TciType *componentType,
                                                                                                const Tstring *name)
{
  try {
    assert(kind);
    return _t3rts.TestComponentCreate(*kind, componentType, name);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


void freettcn::TE::CTTCN3Executable::tciStartTestComponent(const TriComponentId *component,
                                                           const TciBehaviourId *behaviour,
                                                           const TciParameterList *parameterList)
{
  try {
    assert(component);
    assert(behaviour);
    const CModule &module = _ets.Module(behaviour->getModuleName());
    _t3rts.TestComponentStart(*component, module.Behaviour(*behaviour), parameterList);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciStopTestComponent(const TriComponentId *component)
{
  try {
    assert(component);
    _t3rts.TestComponentStop(*component);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciConnect(const TriPortId *fromPort,
                                                const TriPortId *toPort)
{
  try {
    assert(fromPort);
    assert(toPort);
    _t3rts.Connect(*fromPort, *toPort);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciDisconnect(const TriPortId *fromPort,
                                                  const TriPortId *toPort)
{
  try {
    assert(fromPort);
    assert(toPort);
    _t3rts.Disconnect(*fromPort, *toPort);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciMap(const TriPortId *fromPort,
                                           const TriPortId *toPort)
{
  try {
    assert(fromPort);
    assert(toPort);
    _t3rts.Map(*fromPort, *toPort);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciUnmap(const TriPortId *fromPort,
                                             const TriPortId *toPort)
{
  try {
    assert(fromPort);
    assert(toPort);
    _t3rts.Unmap(*fromPort, *toPort);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciTestComponentTerminated(const TriComponentId *component,
                                                               const VerdictValue *verdict) const
{
  try {
    assert(component);
    assert(verdict);
    _t3rts.TestComponentTerminated(*component, *verdict);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


Tboolean freettcn::TE::CTTCN3Executable::tciTestComponentRunning(const TriComponentId *component) const
{
  try {
    assert(component);
    return _t3rts.Component(*component).Running();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return false;
  }
}


Tboolean freettcn::TE::CTTCN3Executable::tciTestComponentDone(const TriComponentId *comp) const
{
  try {
    assert(comp);
    return _t3rts.Component(*comp).Done();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return false;
  }
}


const ORG_ETSI_TTCN3_TRI::TriComponentId *freettcn::TE::CTTCN3Executable::tciGetMTC() const
{
  try {
    return _t3rts.MTC();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


void freettcn::TE::CTTCN3Executable::tciExecuteTestCase(const TciTestCaseId *testCaseId,
                                                        const TriPortIdList *tsiPortList)
{
  try {
    assert(testCaseId);
    _t3rts.TestCaseExecute(*testCaseId, tsiPortList);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciReset()
{
  try {
    _t3rts.Reset();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


void freettcn::TE::CTTCN3Executable::tciKillTestComponent(const TriComponentId *comp)
{
  try {
    assert(comp);
    _t3rts.TestComponentKill(*comp);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


Tboolean freettcn::TE::CTTCN3Executable::tciTestComponentAlive(const TriComponentId *comp) const
{
  try {
    assert(comp);
    return _t3rts.Component(*comp).Alive();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return false;
  }
}


Tboolean freettcn::TE::CTTCN3Executable::tciTestComponentKilled(const TriComponentId *comp) const
{
  try {
    return _t3rts.Component(*comp).Killed();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return false;
  }
}



// CD requests

const ORG_ETSI_TTCN3_TCI::TciType *freettcn::TE::CTTCN3Executable::getTypeForName(const Tstring typeName) const
{
  try {
    return _ets.Type(typeName).get();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return nullptr;
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getInteger() const
{
  try {
    return *_ets.TypeTTCN3().Integer();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getFloat() const
{
  try {
    throw ENotImplemented(E_DATA, "Float type not implemented yet");
    //    return *_ets.TypeTTCN3().Float();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getBoolean() const
{
  try {
    return *_ets.TypeTTCN3().Boolean();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getCharstring() const
{
  try {
    throw ENotImplemented(E_DATA, "Charstring type not implemented yet");
    //    return *_ets.TypeTTCN3().Charstring();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getUniversalCharstring() const
{
  try {
    throw ENotImplemented(E_DATA, "UniversalCharstring type not implemented yet");
    //    return *_ets.TypeTTCN3().UniversalCharstring();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getHexstring() const
{
  try {
    throw ENotImplemented(E_DATA, "Hexstring type not implemented yet");
    //    return *_ets.TypeTTCN3().Hexstring();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getBitstring() const
{
  try {
    throw ENotImplemented(E_DATA, "Bitstring type not implemented yet");
    //    return *_ets.TypeTTCN3().Bitstring();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getOctetstring() const
{
  try {
    return *_ets.TypeTTCN3().Octetstring();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


const ORG_ETSI_TTCN3_TCI::TciType &freettcn::TE::CTTCN3Executable::getVerdict() const
{
  try {
    return *_ets.TypeTTCN3().Verdict();
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
    return *_ets.TypeTTCN3().Integer();
  }
}


void freettcn::TE::CTTCN3Executable::tciErrorReq(const Tstring message)
{
  _env->TM().tciError(message);
}


// PA requests

void freettcn::TE::CTTCN3Executable::triTimeout(const TriTimerId *timerId)
{
  try {
    assert(timerId);
    _t3rts.Timeout(*timerId);
  }
  catch(std::exception &ex) {
    _env->TM().tciError(ex.what());
  }
}


// SA requests

void freettcn::TE::CTTCN3Executable::triEnqueueMsg(const TriPortId *tsiPortId,
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


void freettcn::TE::CTTCN3Executable::triEnqueueCall(const TriPortId *tsiPortId,
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


void freettcn::TE::CTTCN3Executable::triEnqueueReply(const TriPortId *tsiPortId,
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


void freettcn::TE::CTTCN3Executable::triEnqueueException(const TriPortId *tsiPortId,
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
