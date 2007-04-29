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
 * @file   tri_te_sa.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 11:31:15 2007
 * 
 * @brief  TTCN-3 Executable TRI communication interface operations TE=>SA
 * 
 */

#ifndef __TRI_TE_SA_H__
#define __TRI_TE_SA_H__

#include <freettcn/ttcn3/tri.h>


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
 * @addtogroup TriConnHandling Connection handling
 * @{
 */

/**
 * @defgroup TriConnHandling_TE_SA TE => SA
 * @{
 */

/** 
 * @brief Called by the TE before the execution of any test case
 * 
 * The SA can set up any static connections to the SUT and initialize any communication means for
 * TSI ports. @n
 * @n
 * This operation is called by the TE immediately before the execution of any test case. The test case
 * that is going to be executed is indicated by the @p testCaseId. @p tsiPortList contains all ports that
 * have been declared in the definition of the system component for the test case, i.e. the TSI ports. If a
 * system component has not been explicitly defined for the test case in the TTCN-3 ATS then the
 * @p tsiPortList contains all communication ports of the MTC test component. The ports in
 * @p tsiPortList are ordered as they appear in the respective TTCN-3 component declaration. @n
 * @n
 * The triExecuteTestCase() operation returns @c TRI_OK in case the operation has been successfully
 * performed, @c TRI_Error otherwise.
 * 
 * @param testCaseId identifier of the test case that is going to be executed
 * @param tsiPortList a list of test system interface ports defined for the test system
 * 
 * @return The return status of the triExecuteTestCase() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triExecuteTestCase(const TriTestCaseId* testCaseId,
                             const TriPortIdList* tsiPortList);


/** 
 * @brief The SA can establish a dynamic connection to the SUT for the referenced TSI port.
 * 
 * The SA can establish a dynamic connection to the SUT for the referenced TSI port. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 map operation. @n
 * @n
 * The triMap() operation returns @c TRI_Error in case a connection could not be established successfully,
 * @c TRI_OK otherwise. The operation should return @c TRI_OK in case no dynamic connection needs to be
 * established by the test system.
 * 
 * @param compPortId identifier of the test component port to be mapped
 * @param tsiPortId identifier of the test system interface port to be mapped
 * 
 * @return The return status of the triMap() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triMap(const TriPortId* compPortId,
                 const TriPortId* tsiPortId);


/** 
 * @brief The SA shall close a dynamic connection to the SUT for the referenced TSI port.
 * 
 * The SA shall close a dynamic connection to the SUT for the referenced TSI port. @n
 * @n
 * This operation is called by the TE when it executes any TTCN-3 unmap operation. @n
 * @n
 * The triUnmap() operation returns @c TRI_Error in case a connection could not be closed successfully or
 * no such connection has been established previously, @c TRI_OK otherwise. The operation should return
 * @c TRI_OK in case no dynamic connections have to be established by the test system.
 * 
 * @param compPortId identifier of the test component port to be unmapped
 * @param tsiPortId identifier of the test system interface port to be unmapped
 * 
 * @return The return status of the triUnmap() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triUnmap(const TriPortId* compPortId,
                   const TriPortId* tsiPortId);


/** 
 * @brief The SA can free resources.
 * 
 * The SA can free resources, cease communication at system ports and to test components. @n
 * @n
 * This operation is called by the TE immediately after the execution of any test case. @n
 * @n
 * The triEndTestCase() operation returns @c TRI_OK in case the operation has been successfully
 * performed, @c TRI_Error otherwise.
 * 
 * @return The return status of the triEndTestCase() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triEndTestCase();

/// @} TriConnHandling_TE_SA

/// @} TriConnHandling


/**
 * @addtogroup TriMsgCommunication Message based communication
 * @{
 */

/**
 * @defgroup TriMsgCommunication_TE_SA TE => SA
 * @{
 */

/** 
 * @brief The SA can send the message to the SUT.
 * 
 * The SA can send the message to the SUT. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 unicast send operation on a component
 * port, which has been mapped to a TSI port. This operation is called by the TE for all TTCN-3 send
 * operations if no system component has been specified for a test case, i.e. only a MTC test component
 * is created for a test case.
 * The encoding of @p sendMessage has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triSend() operation returns @c TRI_OK in case it has been completed successfully. Otherwise
 * @c TRI_Error shall be returned. Notice that the return value @c TRI_OK does not imply that the SUT has
 * received @p sendMessage.
 * 
 * @param componentId identifier of the sending test component
 * @param tsiPortId identifier of the test system interface port via which the message is sent to the SUT Adapter
 * @param sutAddress (optional) destination address within the SUT
 * @param sendMessage the encoded message to be sent
 * 
 * @return The return status of the triSend operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triSend(const TriComponentId* componentId,
                  const TriPortId* tsiPortId,
                  const TriAddress* sutAddress,
                  const TriMessage* sendMessage);


/** 
 * @brief The SA can broadcast the message to the SUT.
 * 
 * The SA can broadcast the message to the SUT. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 broadcast send operation on a
 * component port, which has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 send operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * The encoding of @p sendMessage has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triSendBC() operation returns @c TRI_OK in case it has been completed successfully. Otherwise
 * @c TRI_Error shall be returned. Notice that the return value @c TRI_OK does not imply that the SUT has
 * received @p sendMessage.
 * 
 * @param componentId identifier of the sending test component
 * @param tsiPortId identifier of the test system interface port via which the message is sent to the SUT Adapter
 * @param sendMessage the encoded message to be sent
 * 
 * @return The return status of the triSend() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triSendBC(const TriComponentId* componentId,
                    const TriPortId* tsiPortId,
                    const TriMessage* sendMessage);



/** 
 * @brief The SA can multicast the message to the SUT.
 * 
 * The SA can multicast the message to the SUT. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 multicast send operation on a
 * component port, which has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 send operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * The encoding of @p sendMessage has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triSendMC() operation returns @c TRI_OK in case it has been completed successfully. Otherwise
 * @c TRI_Error shall be returned. Notice that the return value @c TRI_OK does not imply that the SUT has
 * received @p sendMessage.
 * 
 * @param componentId identifier of the sending test component
 * @param tsiPortId identifier of the test system interface port via which the message is sent to the SUT Adapter
 * @param sutAddresses destination addresses within the SUT
 * @param sendMessage the encoded message to be sent
 * 
 * @return The return status of the triSend operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triSendMC(const TriComponentId* componentId,
                    const TriPortId* tsiPortId,
                    const TriAddressList* sutAddresses,
                    const TriMessage* sendMessage);

/// @} TriMsgCommunication_TE_SA

/// @} TriMsgCommunication


/**
 * @addtogroup TriProcCommunication Procedure based communication
 * @{
 */

/**
 * @defgroup TriProcCommunication_TE_SA TE => SA
 * @{
 */


/** 
 * @brief The SA can initiate the procedure call.
 * 
 * On invocation of this operation the SA can initiate the procedure call corresponding to the signature
 * identifier @p signatureId and the TSI port @p tsiPortId. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 unicast call operation on a component
 * port, which has been mapped to a TSI port. This operation is called by the TE for all TTCN-3 call
 * operations if no system component has been specified for a test case, i.e. only a MTC test
 * component is created for a test case.
 * All in and inout procedure parameters contain encoded values.
 * The procedure parameters are the parameters specified in the TTCN-3 signature template. Their
 * encoding has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triCall() operation shall return without waiting for the return of the issued procedure call (see
 * note). This TRI operation returns @c TRI_OK on successful initiation of the procedure call, @c TRI_Error
 * otherwise. No error shall be indicated by the SA in case the value of any out parameter is non-null.
 * Notice that the return value of this TRI operation does not make any statement about the success or
 * failure of the procedure call.
 * Note that an optional timeout value, which can be specified in the TTCN-3 ATS for a call operation, is
 * not included in the triCall() operation signature. The TE is responsible to address this issue by
 * starting a timer for the TTCN-3 call operation in the PA with a separate TRI operation call,
 * i.e. triStartTimer().
 *
 * @note This might be achieved for example by spawning a new thread or process. This handling of 
 *       this procedure call is, however, dependent on implementation of the TE.
 * 
 * @param componentId identifier of the test component issuing the procedure call
 * @param tsiPortId identifier of the test system interface port via which the procedure call is
 *                  sent to the SUT Adapter
 * @param sutAddress (optional) destination address within the SUT
 * @param signatureId identifier of the signature of the procedure call
 * @param parameterList a list of encoded parameters which are part of the indicated signature.
 *                      The parameters in parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration
 * 
 * @return The return status of the triCall() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triCall(const TriComponentId* componentId,
                  const TriPortId* tsiPortId,
                  const TriAddress* sutAddress,
                  const TriSignatureId* signatureId,
                  const TriParameterList* parameterList);



/** 
 * @brief The SA can initiate and broadcast the procedure call.
 * 
 * On invocation of this operation the SA can initiate and broadcast the procedure call corresponding to
 * the signature identifier @p signatureId and the TSI port @p tsiPortId. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 broadcast call operation on a
 * component port, which has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 call operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * All in and inout procedure parameters contain encoded values.
 * The procedure parameters are the parameters specified in the TTCN-3 signature template. Their
 * encoding has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triCallBC() operation shall return without waiting for the return of the issued procedure call (see
 * note). This TRI operation returns @c TRI_OK on successful initiation of the procedure call, @c TRI_Error
 * otherwise. No error shall be indicated by the SA in case the value of any out parameter is non-null.
 * Notice that the return value of this TRI operation does not make any statement about the success or
 * failure of the procedure call.
 * Note that an optional timeout value, which can be specified in the TTCN-3 ATS for a call operation, is
 * not included in the triCallBC() operation signature. The TE is responsible to address this issue by
 * starting a timer for the TTCN-3 call operation in the PA with a separate TRI operation call,
 * i.e. triStartTimer().
 * 
 * @note This might be achieved for example by spawning a new thread or process. This handling of this 
 *       procedure call is, however, dependent on implementation of the TE.
 * 
 * @param componentId identifier of the test component issuing the procedure call
 * @param tsiPortId identifier of the test system interface port via which the procedure call is sent
 *                  to the SUT Adapter
 * @param signatureId identifier of the signature of the procedure call
 * @param parameterList a list of encoded parameters which are part of the indicated signature.
 *                      The parameters in parameterList are ordered as they appear in the TTCN-3 signature
 *                      declaration
 * 
 * @return The return status of the triCallBC() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triCallBC(const TriComponentId* componentId,
                    const TriPortId* tsiPortId,
                    const TriSignatureId* signatureId,
                    const TriParameterList* parameterList);


/** 
 * @brief The SA can initiate and multicast the procedure call.
 * 
 * On invocation of this operation the SA can initiate and multicast the procedure call corresponding to
 * the signature identifier @p signatureId and the TSI port @p tsiPortId. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 multicast call operation on a
 * component port, which has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 call operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * All in and inout procedure parameters contain encoded values.
 * The procedure parameters are the parameters specified in the TTCN-3 signature template. Their
 * encoding has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triCallMC() operation shall return without waiting for the return of the issued procedure call (see
 * note). This TRI operation returns @c TRI_OK on successful initiation of the procedure call, @c TRI_Error
 * otherwise. No error shall be indicated by the SA in case the value of any out parameter is non-null.
 * Notice that the return value of this TRI operation does not make any statement about the success or
 * failure of the procedure call.
 * Note that an optional timeout value, which can be specified in the TTCN-3 ATS for a call operation, is
 * not included in the triCallMC() operation signature. The TE is responsible to address this issue by
 * starting a timer for the TTCN-3 call operation in the PA with a separate TRI operation call,
 * i.e. triStartTimer().
 *
 * @note This might be achieved for example by spawning a new thread or process. This handling of this 
 *       procedure call is, however, dependent on implementation of the TE.
 * 
 * @param componentId identifier of the test component issuing the procedure call
 * @param tsiPortId identifier of the test system interface port via which the procedure call is sent
 *                  to the SUT Adapter
 * @param sutAddresses destination addresses within the SUT
 * @param signatureId identifier of the signature of the procedure call
 * @param parameterList a list of encoded parameters which are part of the indicated signature.
 *                      The parameters in parameterList are ordered as they appear in the TTCN-3 signature
 *                      declaration.
 * 
 * @return The return status of the triCallMC() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triCallMC(const TriComponentId* componentId,
                    const TriPortId* tsiPortId,
                    const TriAddressList* sutAddresses,
                    const TriSignatureId* signatureId,
                    const TriParameterList* parameterList);


/** 
 * @brief The SA can issue the reply to a procedure call.
 * 
 * On invocation of this operation the SA can issue the reply to a procedure call corresponding to the
 * signature identifier @p signatureId and the TSI port @p tsiPortId. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 unicast reply operation on a
 * component port that has been mapped to a TSI port. This operation is called by the TE for all TTCN-3
 * reply operations if no system component has been specified for a test case, i.e. only a MTC test
 * component is created for a test case.
 * All out and inout procedure parameters and the return value contain encoded values.
 * The @p parameterList contains procedure call parameters. These parameters are the parameters
 * specified in the TTCN-3 signature template. Their encoding has to be done in the TE prior to this TRI
 * operation call.
 * If no return type has been defined for the procedure signature in the TTCN-3 ATS, the distinct value
 * @c null shall be passed for the return value. @n
 * @n
 * The triReply() operation will return @c TRI_OK on successful execution of this operation, @c TRI_Error
 * otherwise. The SA shall indicate no error in case the value of any in parameter or an undefined return
 * value is different from @c null.
 * 
 * @param componentId identifier of the replying test component
 * @param tsiPortId identifier of the test system interface port via which the reply is sent to the SUT Adapter
 * @param sutAddress (optional) destination address within the SUT
 * @param signatureId identifier of the signature of the procedure call
 * @param parameterList a list of encoded parameters which are part of the indicated signature.
 *                      The parameters in parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 * @param returnValue (optional) encoded return value of the procedure call
 * 
 * @return The return status of the triReply() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triReply(const TriComponentId* componentId,
                   const TriPortId* tsiPortId,
                   const TriAddress* sutAddress,
                   const TriSignatureId* signatureId,
                   const TriParameterList* parameterList,
                   const TriParameter* returnValue);


/** 
 * @brief The SA can broadcast the reply to procedure calls.
 * 
 * On invocation of this operation the SA can broadcast the reply to procedure calls corresponding to
 * the signature identifier @p signatureId and the TSI port @p tsiPortId. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 broadcast reply operation on a
 * component port that has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 reply operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * All out and inout procedure parameters and the return value contain encoded values.
 * The @p parameterList contains procedure call parameters. These parameters are the parameters
 * specified in the TTCN-3 signature template. Their encoding has to be done in the TE prior to this TRI
 * operation call.
 * If no return type has been defined for the procedure signature in the TTCN-3 ATS, the distinct value
 * @c null shall be passed for the return value. @n
 * @n
 * The triReplyBC() operation will return @c TRI_OK on successful execution of this operation, @c TRI_Error
 * otherwise. The SA shall indicate no error in case the value of any in parameter or an undefined return
 * value is different from @c null.
 * 
 * @param componentId identifier of the replying test component
 * @param tsiPortId identifier of the test system interface port via which the reply is sent to the SUT Adapter
 * @param signatureId identifier of the signature of the procedure call
 * @param parameterList a list of encoded parameters which are part of the indicated signature.
 *                      The parameters in parameterList are ordered as they appear in the TTCN-3 signature
 *                      declaration.
 * @param returnValue (optional) encoded return value of the procedure call
 * 
 * @return The return status of the triReplyBC() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triReplyBC(const TriComponentId* componentId,
                     const TriPortId* tsiPortId,
                     const TriSignatureId* signatureId,
                     const TriParameterList* parameterList,
                     const TriParameter* returnValue);



/** 
 * @brief The SA can multicast the reply to procedure calls.
 * 
 * On invocation of this operation the SA can multicast the reply to procedure calls corresponding to the
 * signature identifier @p signatureId and the TSI port @p tsiPortId.
 *
 * This operation is called by the TE when it executes a TTCN-3 multicast reply operation on a
 * component port that has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 reply operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * All out and inout procedure parameters and the return value contain encoded values.
 * The @p parameterList contains procedure call parameters. These parameters are the parameters
 * specified in the TTCN-3 signature template. Their encoding has to be done in the TE prior to this TRI
 * operation call.
 * If no return type has been defined for the procedure signature in the TTCN-3 ATS, the distinct value
 * @c null shall be passed for the return value. @n
 * @n
 * The triReplyMC() operation will return @c TRI_OK on successful execution of this operation, @c TRI_Error
 * otherwise. The SA shall indicate no error in case the value of any in parameter or an undefined return
 * value is different from @c null.
 * 
 * @param componentId identifier of the replying test component
 * @param tsiPortId identifier of the test system interface port via which the reply is sent to the SUT Adapter
 * @param sutAddresses destination addresses within the SUT
 * @param signatureId identifier of the signature of the procedure call
 * @param parameterList a list of encoded parameters which are part of the indicated signature.
 *                      The parameters in parameterList are ordered as they appear in the TTCN-3 signature
 *                      declaration.
 * @param returnValue (optional) encoded return value of the procedure call
 * 
 * @return The return status of the triReplyMC() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triReplyMC(const TriComponentId* componentId,
                     const TriPortId* tsiPortId,
                     const TriAddressList* sutAddresses,
                     const TriSignatureId* signatureId,
                     const TriParameterList* parameterList,
                     const TriParameter* returnValue);


/** 
 * @brief The SA can raise an exception to a procedure call.
 * 
 * On invocation of this operation the SA can raise an exception to a procedure call corresponding to
 * the signature identifier @p signatureId and the TSI port @p tsiPortId. @n
 *
 * This operation is called by the TE when it executes a TTCN-3 unicast raise operation on a
 * component port that has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 raise operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * The encoding of the exception has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triRaise() operation returns @c TRI_OK on successful execution of the operation, @c TRI_Error
 * otherwise.
 * 
 * @param componentId identifier of the test component raising the exception
 * @param tsiPortId identifier of the test system interface port via which the exception is sent to the SUT Adapter
 * @param sutAddress (optional) destination address within the SUT
 * @param signatureId identifier of the signature of the procedure call which the exception is associated with
 * @param exception the encoded exception
 * 
 * @return The return status of the triRaise() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triRaise(const TriComponentId* componentId,
                   const TriPortId* tsiPortId,
                   const TriAddress* sutAddress,
                   const TriSignatureId* signatureId,
                   const TriException* exception);


/** 
 * @brief The SA can raise and broadcast an exception to procedure calls.
 * 
 * On invocation of this operation the SA can raise and broadcast an exception to procedure calls
 * corresponding to the signature identifier @p signatureId and the TSI port @p tsiPortId. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 broadcast raise operation on a
 * component port that has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 raise operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * The encoding of the exception has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triRaiseBC() operation returns @c TRI_OK on successful execution of the operation, @c TRI_Error
 * otherwise.
 * 
 * @param componentId identifier of the test component raising the exception
 * @param tsiPortId identifier of the test system interface port via which the exception is sent to the SUT Adapter
 * @param signatureId identifier of the signature of the procedure call which the exception is associated with
 * @param exception the encoded exception
 * 
 * @return The return status of the triRaiseBC() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triRaiseBC(const TriComponentId* componentId,
                     const TriPortId* tsiPortId,
                     const TriSignatureId* signatureId,
                     const TriException* exception);


/** 
 * @brief The SA can raise and multicast an exception to a procedure calls.
 * 
 * On invocation of this operation the SA can raise and multicast an exception to a procedure calls
 * corresponding to the signature identifier @p signatureId and the TSI port @p tsiPortId. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 multicast raise operation on a
 * component port that has been mapped to a TSI port. This operation is called by the TE for all
 * TTCN-3 raise operations if no system component has been specified for a test case, i.e. only a MTC
 * test component is created for a test case.
 * The encoding of the exception has to be done in the TE prior to this TRI operation call. @n
 * @n
 * The triRaiseMC() operation returns @c TRI_OK on successful execution of the operation, @c TRI_Error
 * otherwise.
 * 
 * @param componentId identifier of the test component raising the exception
 * @param tsiPortId identifier of the test system interface port via which the exception is sent to the SUT Adapter
 * @param sutAddresses destination addresses within the SUT
 * @param signatureId identifier of the signature of the procedure call which the exception is associated with
 * @param exception the encoded exception
 * 
 * @return The return status of the triRaiseMC() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triRaiseMC(const TriComponentId* componentId,
                     const TriPortId* tsiPortId,
                     const TriAddressList* sutAddresses,
                     const TriSignatureId* signatureId,
                     const TriException* exception);


/// @} TriProcCommunication_TE_SA

/// @} TriProcCommunication


/**
 * @defgroup TriIfaceCommunicationMisc Miscellaneous
 * @{
 */

/**
 * @defgroup TriIfaceCommunicationMisc_TE_SA TE => SA
 * @{
 */

/** 
 * @brief The SA shall reset communication
 * 
 * The SA shall reset all communication means that it is maintaining, e.g. reset static connections to the
 * SUT, close dynamic connections to the SUT, discard any pending messages or procedure calls. @n
 * @n
 * This operation can be called by the TE at any time to reset the SA. @n
 * @n
 * The triSAReset() operation returns @c TRI_OK in case the operation has been successfully performed,
 * @c TRI_Error otherwise.
 * 
 * @return The return status of the triSAReset() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triSAReset();


/** 
 * @brief The SA shall initiate the described actions to be taken on the SUT.
 * 
 * On invocation of this operation the SA shall initiate the described actions to be taken on the SUT,
 * e.g. turn on, initialize, or send a message to the SUT. @n
 * @n
 * This operation is called by the TE when it executes a TTCN-3 SUT action operation, which only
 * contains a string. @n
 * @n
 * The triSUTactionInformal() operation returns @c TRI_OK on successful execution of the operation,
 * @c TRI_Error otherwise. Notice that the return value of this TRI operation does not make any statement
 * about the success or failure of the actions to be taken on the SUT.
 * 
 * @param description an informal description of an action to be taken on the SUT
 * 
 * @return The return status of the triSUTactionInformal() operation.
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triSUTActionInformal(const char* description);


/// @} TriIfaceCommunicationMisc_TE_SA

/// @} TriIfaceCommunicationMisc

/// @} TriIfaceCommunication

/// @} TriIface

/// @} Tri

#endif /* __TRI_TE_SA_H__ */
