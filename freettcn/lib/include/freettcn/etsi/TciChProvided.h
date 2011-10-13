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
 * @file   TciChProvided.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:50:45 2007
 * 
 * @brief  TTCN-3 Executable TCI types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 * 
 */

#ifndef __TCI_CH_PROVIDED_H__
#define __TCI_CH_PROVIDED_H__

#include <freettcn/etsi/tci.h>

namespace ORG_ETSI_TTCN3_TCI {
  
  class TciChProvided {
  public:
    //Destructor
    virtual ~TciChProvided();
    //Called by the TE when it executes a TTCN-3 unicast send operation on a component port
    virtual void tciSendConnected(const TriPortId *sender, const TriComponentId *receiver,
                                  const TciValue *sendMessage) = 0;
    //Called by the TE when it executes a TTCN-3 broadcast send operation on a component port
    virtual void tciSendConnectedBC(const TriPortId *sender, const TciValue *sendMessage) = 0;
    //Called by the TE when it executes a TTCN-3 multicast send operation on a component port
    virtual void tciSendConnectedMC(const TriPortId *sender, const TriComponentIdList *receivers,
                                    const TciValue *sendMessage) = 0;
    //Called by the TE when it executes a TTCN-3 unicast call operation on a component port
    virtual void tciCallConnected(const TriPortId *sender, const TriComponentId *receiver,
                                  const TriSignatureId *signature, const TciParameterList *parameterList) = 0;
    //Called by the TE when it executes a TTCN-3 broadcast call operation on a component port
    virtual void tciCallConnectedBC(const TriPortId *sender, const TriSignatureId *signature,
                                    const TciParameterList *parameterList) = 0;
    //Called by the TE when it executes a TTCN-3 multicast call operation on a component port
    virtual void tciCallConnectedMC(const TriPortId *sender, const TriComponentIdList *receivers,
                                    const TriSignatureId *signature, const TciParameterList *parameterList) = 0;
    //Called by the TE when it executes a TTCN-3 unicast reply operation on a component port
    virtual void tciReplyConnected(const TriPortId *sender, const TriComponentId *receiver,
                                   const TriSignatureId *signature, const TciParameterList *parameterList,
                                   const TciValue *returnValue) = 0;
    //Called by the TE when it executes a TTCN-3 broadcast reply operation on a component port
    virtual void tciReplyConnectedBC(const TriPortId *sender, const TriSignatureId *signature,
                                     const TciParameterList *parameterList, const TciValue *returnValue) = 0;
    //Called by the TE when it executes a TTCN-3 multicast reply operation on a component
    virtual void tciReplyConnectedMC(const TriPortId *sender, const TriComponentIdList *receivers,
                                     const TriSignatureId *signature, const TciParameterList *parameterList,
                                     const TciValue *returnValue) = 0;
    //Called by the TE when it executes a TTCN-3 unicast raise operation on a component port
    virtual void tciRaiseConnected(const TriPortId *sender, const TriComponentId *receiver,
                                   const TriSignatureId *signature, const TciValue *exception) = 0;
    //Called by the TE when it executes a TTCN-3 broadcast raise operation on a component portvirtual
    void tciRaiseConnectedBC(const TriPortId *sender, const TriSignatureId *signature,
                             const TciValue *exception) = 0;
    //Called by the TE when it executes a TTCN-3 multicast raise operation on a component
    virtual void tciRaiseConnectedMC(const TriPortId *sender, const TriComponentIdList *receiver,
                                     const TriSignatureId *signature, const TciValue *exception) = 0;
    //Called from the TE when a component has to be created
    virtual const TriComponentId *tciCreateTestComponentReq(const TciTestComponentKind *kind,
                                                            const QualifiedName *componentType,
                                                            const Tstring &name, const TciValue *hostId) = 0;
    //Called by the TE when it executes the TTCN-3 start operation
    virtual void tciStartTestComponentReq(const TriComponentId *component, const TciBehaviourId *behaviour,
                                          const TciParameterList *parameterList) = 0;
    //Called by the TE when it executes the TTCN-3 stop operation
    virtual void tciStopTestComponentReq(const TriComponentId *component) = 0;
    //Called by the TE when it executes a TTCN-3 connect operation
    virtual void tciConnectReq(const TriPortId *fromPort, const TriPortId *toPort) = 0;
    //Called by the TE when it executes a TTCN-3 disconnect operation
    virtual void tciDisconnectReq(const TriPortId *fromPort, const TriPortId *toPort) = 0;
    //Called by the TE when it executes a TTCN-3 map operation
    virtual void tciMapReq(const TriPortId *fromPort, const TriPortId *toPort) = 0;
    //Called by the TE when it executes a TTCN-3 unmap operation
    virtual void tciUnmapReq(const TriPortId *fromPort, const TriPortId *toPort) = 0;
    //Called by the TE when a test component terminates execution
    virtual void tciTestComponentTerminatedReq(const TriComponentId *component, const VerdictValue *verdict) = 0;
    //Called by the TE when it executes a TTCN-3 running operation
    virtual Tboolean tciTestComponentRunningReq(const TriComponentId *component) const = 0;
      //Called by the TE when it executes a TTCN-3 done operation
    virtual Tboolean tciTestComponentDoneReq(const TriComponentId *comp) const = 0;
      //Called by the TE when it executes a TTCN-3 mtc operation
    virtual const TriComponentId * tciGetMTCReq() const = 0;
    //Called by the TE immediately before it starts the test case behaviour on the MTC
    virtual void tciExecuteTestCaseReq(const TciTestCaseId *testCaseId, const TriPortIdList *tsiPortList) = 0;
    //Called by the TE at any time to reset the test system
    virtual void tciResetReq() = 0;
    //Called by the TE when it executes the TTCN-3 kill operation
    virtual void tciKillTestComponentReq(const TriComponentId *comp) = 0;
    //Called by the TE when it executes the TTCN-3 alive operation
    virtual Tboolean tciTestComponentAliveReq(const TriComponentId *comp) const = 0;
    //Called by the TE when it executes the TTCN-3 killed operation
    virtual Tboolean tciTestComponentKilledReq(const TriComponentId *comp) const = 0;
  };
  
} // namespace ORG_ETSI_TTCN3_TCI

#endif /* __TCI_CH_PROVIDED_H__ */
