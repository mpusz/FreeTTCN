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
 * @file   TriCommunicationSA.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 11:31:15 2007
 * 
 * @brief  TTCN-3 Executable TRI communication interface operations TE=>SA
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-5: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 5: TTCN-3 Runtime Interface (TRI)"
 * 
 */

#ifndef __TRI_COMMUNICATION_SA_H__
#define __TRI_COMMUNICATION_SA_H__

#include <freettcn/etsi/tri.h>

namespace ORG_ETSI_TTCN3_TRI {

  class TriCommunicationSA {
  public:
    //Destructor.
    virtual ~TriCommunicationSA();
    //To reset the System Adaptor
    virtual TriStatus triSAReset() = 0;
    //To execute a test case.
    virtual TriStatus triExecuteTestCase(const TriTestCaseId *testCaseId,
                                         const TriPortIdList *tsiPortList) = 0;
    //To establish a dynamic connection between two ports.
    virtual TriStatus triMap(const TriPortId *comPortId, const TriPortId *tsiPortId) = 0;
    //To close a dynamic connection to the SUT for the referenced TSI port.
    virtual TriStatus triUnmap(const TriPortId *comPortId, const TriPortId *tsiPortId) = 0;
    //To end a test case.
    virtual TriStatus triEndTestCase() = 0;
    //Send operation on a component which has been mapped to a TSI port.
    virtual TriStatus triSend(const TriComponentId *componentId, const TriPortId *tsiPortId,
                              const TriAddress *SUTaddress, const TriMessage *sendMessage) = 0;
    //Send (broadcast) operation on a component which has been mapped to a TSI port.
    virtual TriStatus triSendBC(const TriComponentId *componentId, const TriPortId *tsiPortId,
                                const TriMessage *sendMessage) = 0;
    //Send (multicast) operation on a component which has been mapped to a TSI port.
    virtual TriStatus triSendMC(const TriComponentId *componentId, const TriPortId *tsiPortId,
                                const TriAddressList *SUTaddresses, const TriMessage *sendMessage) = 0;
    //Initiate the procedure call.
    virtual TriStatus triCall(const TriComponentId *componentId, const TriPortId *tsiPortId,
                              const TriAddress *sutAddress, const TriSignatureId *signatureId,
                              const TriParameterList *parameterList) = 0;
    //Initiate and broadcast the procedure call.
    virtual TriStatus triCallBC(const TriComponentId *componentId, const TriPortId *tsiPortId,
                                const TriSignatureId *signatureId, const TriParameterList *parameterList) = 0;
    //Initiate and multicast the procedure call.
    virtual TriStatus triCallMC(const TriComponentId *componentId, const TriPortId *tsiPortId,
                                const TriAddressList *sutAddresses, const TriSignatureId *signatureId,
                                const TriParameterList *parameterList) = 0;
    //Issue the reply to a procedure call.
    virtual TriStatus triReply(const TriComponentId *componentId, const TriPortId *tsiPortId,
                               const TriAddress *sutAddress, const TriSignatureId *signatureId,
                               const TriParameterList *parameterList, const TriParameter *returnValue) = 0;
    //Broadcast the reply to a procedure call.
    virtual TriStatus triReplyBC(const TriComponentId *componentId, const TriPortId *tsiPortId,
                                 const TriSignatureId *signatureId, const TriParameterList *parameterList,
                                 const TriParameter *returnValue) = 0;
    //Multicast the reply to a procedure call.
    virtual TriStatus triReplyMC(const TriComponentId *componentId, const TriPortId *tsiPortId,
                                 const TriAddressList *sutAddresses, const TriSignatureId *signatureId,
                                 const TriParameterList *parameterList, const TriParameter *returnValue) = 0;
    //Raise an exception to a procedure call.
    virtual TriStatus triRaise(const TriComponentId *componentId, const TriPortId *tsiPortId,
                               const TriAddress *sutAddress, const TriSignatureId *signatureId, const TriException *exc) = 0;
    //Raise an broadcast an exception to a procedure call.
    virtual TriStatus triRaiseBC(const TriComponentId *componentId, const TriPortId *tsiPortId,
                                 const TriSignatureId *signatureId, const TriException *exc) = 0;
    //Raise an multicast an exception to a procedure call.
    virtual TriStatus triRaiseMC(const TriComponentId *componentId, const TriPortId *tsiPortId,
                                 const TriAddressList *sutAddresses, const TriSignatureId *signatureId,
                                 const TriException *exc) = 0;
    //Initiate the described actions to be taken on the SUT.
    virtual TriStatus triSUTactionInformal(const Tstring *description) = 0;
  };
  
} // namespace ORG_ETSI_TTCN3_TRI

#endif /* __TRI_COMMUNICATION_SA_H__ */
