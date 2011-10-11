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
 * @file   TriCommunicationTE.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 11:31:15 2007
 * 
 * @brief  TTCN-3 Executable TRI communication interface operations TE=>SA
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-5: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 5: TTCN-3 Runtime Interface (TRI)"
 * 
 */

#ifndef __TRI_COMMUNICATION_TE_H__
#define __TRI_COMMUNICATION_TE_H__

#include <freettcn/ttcn3/tri.h>

namespace ORG_ETSI_TTCN3_TRI {

  class TriCommunicationTE {
  public:
    //Destructor.
    virtual ~TriCommunicationTE();
    //Called by SA after it has received a message from the SUT.
    virtual void triEnqueueMsg(const TriPortId *tsiPortId, const TriAddress *SUTaddress,
                               const TriComponentId *componentId, const TriMessage *receivedMessage) = 0;
    //Called by SA after it has received a procedure call from the SUT.
    virtual void triEnqueueCall(const TriPortId *tsiPortId, const TriAddress *SUTaddress,
                                const TriComponentId *componentId, const TriSignatureId *signatureId,
                                const TriParameterList *parameterList) = 0;
    //Called by SA after it has received a reply from the SUT.
    virtual void triEnqueueReply(const TriPortId *tsiPortId, const TriAddress *SUTaddress,
                                 const TriComponentId *componentId, const TriSignatureId *signatureId,
                                 const TriParameterList *parameterList, const TriParameter *returnValue) = 0;
    //Called by SA after it has received an exception from the SUT.
    virtual void triEnqueueException(const TriPortId *tsiPortId, const TriAddress *SUTaddress,
                                     const TriComponentId *componentId, const TriSignatureId *signatureId,
                                     const TriException *exc) = 0;
  };
  
} // namespace ORG_ETSI_TTCN3_TRI

#endif /* __TRI_COMMUNICATION_TE_H__ */
