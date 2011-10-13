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
 * @file   TciChRequired.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:50:45 2007
 * 
 * @brief  TTCN-3 Executable TCI types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 * 
 */

#ifndef __TCI_CH_REQUIRED_H__
#define __TCI_CH_REQUIRED_H__

#include <freettcn/etsi/tci.h>
#include <freettcn/etsi/tri.h>

namespace ORG_ETSI_TTCN3_TCI {
  
  using namespace ORG_ETSI_TTCN3_TRI;
  
  class TciChRequired {
  public:
    //Default destructor
    virtual ~TciChRequired();
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciSendConnected has been called
    virtual void tciEnqueueMsgConnected(const TriPortId *sender, const TriComponentId *receiver,
                                        const TciValue *rcvdMessage) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciCallConnected has been called
    virtual void tciEnqueueCallConnected(const TriPortId *sender, const TriComponentId *receiver,
                                         const TriSignatureId *signature, const TciParameterList *parameterList) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciReplyConnected has been called
    virtual void tciEnqueueReplyConnected(const TriPortId *sender, const TriComponentId *receiver,
                                          const TriSignatureId *signature, const TciParameterList *parameterList,
                                          const TciValue *returnValue) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciRaiseConnected has been called
    virtual void tciEnqueueRaiseConnected(const TriPortId *sender, const TriComponentId *receiver,
                                          const TriSignatureId *signature, const TciValue *exception) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciCreateTestComponentReq has been called
    virtual const TriComponentId *tciCreateTestComponent(const TciTestComponentKind *kind,
                                                         const TciType *componentType, const Tstring *name) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciStartTestComponentReq has been called
    virtual void tciStartTestComponent(const TriComponentId *component, const TciBehaviourId *behaviour,
                                       const TciParameterList *parameterList) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciStopTestComponentReq has been called
    virtual void tciStopTestComponent(const TriComponentId *component) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided tciConnect
    //has been called
    virtual void tciConnect(const TriPortId *fromPort, const TriPortId *toPort) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciDisconnect has been called
    virtual void tciDisconnect(const TriPortId *fromPort, const TriPortId *toPort) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided tciMapReq
    //has been called
    virtual void tciMap(const TriPortId *fromPort, const TriPortId *toPort) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided tciUnmapReq
    //has been called
    virtual void tciUnmap(const TriPortId *fromPort, const TriPortId *toPort) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided tciUnmapReq
    //has been called
    virtual void tciTestComponentTerminated(const TriComponentId *component, const VerdictValue *verdict) const = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciTestComponentRunningReq has been called
    virtual Tboolean tciTestComponentRunning(const TriComponentId *component) const = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciTestComponentDoneReq has been called
    virtual Tboolean tciTestComponentDone(const TriComponentId *comp) const = 0;
    //This operation can be called by the CH at the appropriate local TE when at a remote TE a
    //provided tciGetMTCReq has been called
    virtual const TriComponentId *tciGetMTC() const = 0;
    //This operation is called by the CH at the appropriate local TE when at a remote TE a provided
    //tciExecuteTestCaseReq has been called
    virtual void tciExecuteTestCase(const TciTestCaseId *testCaseId, const TriPortIdList *tsiPortList) = 0;
    //This operation is called by the CH at appropriate local TEs when at a remote TE a provided
    //tciResetReq has been called
    virtual void tciReset() = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciKillTestComponentReq has been called
    virtual void tciKillTestComponent(const TriComponentId *comp) = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciTestComponentAliveReq has been called
    virtual Tboolean tciTestComponentAlive(const TriComponentId *comp) const = 0;
    //This operation is called by the CH at the local TE when at a remote TE a provided
    //tciTestComponentKilledReq has been called
    virtual Tboolean tciTestComponentKilled(const TriComponentId *comp) const = 0;
  };
  
} // namespace ORG_ETSI_TTCN3_TCI

#endif /* __TCI_CH_REQUIRED_H__ */
