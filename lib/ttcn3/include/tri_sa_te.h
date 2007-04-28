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
 * @file   tri_sa_te.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 12:55:34 2007
 * 
 * @brief  TTCN-3 Executable TRI communication interface operations SA=>TE
 * 
 */

#ifndef __TRI_SA_TE_H__
#define __TRI_SA_TE_H__

#include "freettcn/tri.h"


/**
 * @addtogroup Tri TRI
 * @{
 */

/**
 * @addtogroup TriIface Interface
 * @{
 */

/**
 * @addtogroup TriIfaceCommunication Communication
 * @{
 */

/**
 * @addtogroup TriMsgCommunication Message based communication
 * @{
 */

/**
 * @defgroup TriMsgCommunication_SA_TE SA => TE
 * @{
 */


/** 
 * @brief This operation shall pass the message to the TE
 * 
 * This operation shall pass the message to the TE indicating the component @p componentId to which the
 * TSI port @p tsiPortId is mapped. @n
 * @n
 * This operation is called by the SA after it has received a message from the SUT. It can only be used
 * when @p tsiPortId has been either previously mapped to a port of componentId or has been referenced in
 * the previous triExecuteTestCase() statement.
 * In the invocation of a triEnqueueMsg() operation @p receivedMessage shall contain an encoded value. @n
 * The decoding of @p receivedMessage has to be done in the TE.
 * 
 * @param tsiPortId identifier of the test system interface port via which the message is enqueued
 *                  by the SUT Adapter
 * @param sutAddress (optional) source address within the SUT
 * @param componentId identifier of the receiving test component
 * @param receivedMessage the encoded received message
 */
void triEnqueueMsg(const TriPortId* tsiPortId,
                   const TriAddress* sutAddress,
                   const TriComponentId* componentId,
                   const TriMessage* receivedMessage);


/// @} TriMsgCommunication_SA_TE

/// @} TriMsgCommunication


/**
 * @addtogroup TriProcCommunication Procedure based communication
 * @{
 */

/**
 * @defgroup TriProcCommunication_SA_TE SA => TE
 * @{
 */

/** 
 * @brief Called by the SA after it has received a procedure call from the SUT.
 * 
 * The TE can enqueue this procedure call with the signature identifier @p signatureId at the port of the
 * component @p componentId to which the TSI port @p tsiPortId is mapped. The decoding of procedure
 * parameters has to be done in the TE. @n
 * @n
 * This operation can be called by the SA after it has received a procedure call from the SUT. It can
 * only be used when @p tsiPortId has been either previously mapped to a port of @p componentId or
 * referenced in the previous triExecuteTestCase() statement.
 * In the invocation of a triEnqueueCall() operation all in and inout procedure parameters contain
 * encoded values. The TE shall indicate no error in case the value of any out parameter is different
 * from @c null.
 * 
 * @param tsiPortId identifier of the test system interface port via which the procedure call is enqueued
 *                  by the SUT Adapter
 * @param sutAddress (optional) source address within the SUT
 * @param componentId identifier of the receiving test component
 * @param signatureId identifier of the signature of the procedure call
 * @param parameterList a list of encoded parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3 signature
 *                      declaration. Description of data passed as parameters to the operation from the
 *                      calling entity to the called entity.
 */
void triEnqueueCall(const TriPortId* tsiPortId,
                    const TriAddress* sutAddress,
                    const TriComponentId* componentId,
                    const TriSignatureId* signatureId,
                    const TriParameterList* parameterList);


/** 
 * @brief Reply to the procedure call.
 * 
 * The TE can enqueue this reply to the procedure call with the signature identifier @p signatureId at
 * the port of the component @p componentId to which the TSI port @p tsiPortId is mapped. The
 * decoding of the procedure parameters has to be done within the TE. @n
 * @n
 * This operation can be called by the SA after it has received a reply from the SUT. It can only be used
 * when @p tsiPortId has been either previously mapped to a port of @p componentId or referenced in the
 * previous triExecuteTestCase() statement.
 * In the invocation of a triEnqueueReply() operation all out and inout procedure parameters and the
 * return value contain encoded values.
 * If no return type has been defined for the procedure signature in the TTCN-3 ATS, the distinct value
 * @c null shall be used for the return value.
 * The TE shall indicate no error in case the value of any in parameter or an undefined return value is
 * different from @c null.
 * 
 * @param tsiPortId identifier of the test system interface port via which the reply is enqueued
 *                  by the SUT Adapter
 * @param sutAddress (optional) source address within the SUT
 * @param componentId identifier of the receiving test component
 * @param signatureId identifier of the signature of the procedure call
 * @param parameterList a list of encoded parameters which are part of the indicated signature.
 *                      The parameters in parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 * @param returnValue (optional) encoded return value of the procedure call
 */
void triEnqueueReply(const TriPortId* tsiPortId,
                     const TriAddress* sutAddress,
                     const TriComponentId* componentId,
                     const TriSignatureId* signatureId,
                     const TriParameterList* parameterList,
                     const TriParameter* returnValue);


/** 
 * @brief Exception for the procedure call.
 * 
 * The TE can enqueue this exception for the procedure call with the signature identifier @p signatureId
 * at the port of the component @p componentId to which the TSI port @p tsiPortId is mapped.
 * The decoding of the exception has to be done within the TE. @n
 * @n
 * This operation can be called by the SA after it has received a reply from the SUT. It can only be
 * used when @p tsiPortId has been either previously mapped to a port of @p componentId or referenced in
 * the previous triExecuteTestCase() statement.
 * In the invocation of a triEnqueueException() operation exception shall contain an encoded value.
 * 
 * @param tsiPortId identifier for the test system interface port via which the exception is enqueued by
 *                  the SUT Adapter
 * @param sutAddress (optional) source address within the SUT
 * @param componentId identifier of the receiving test component
 * @param signatureId identifier of the signature of the procedure call which the exception is associated with
 * @param exception the encoded exception
 */
void triEnqueueException(const TriPortId* tsiPortId,
                         const TriAddress* sutAddress,
                         const TriComponentId* componentId,
                         const TriSignatureId* signatureId,
                         const TriException* exception);

/// @} TriProcCommunication_SA_TE

/// @} TriProcCommunication

/// @} TriIfaceCommunication

/// @} TriIface

/// @} Tri

#endif /* __TRI_SA_TE_H__ */
