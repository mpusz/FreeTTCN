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
 * @file   tci_te_ch.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:55:08 2007
 * 
 * @brief  TTCN-3 Executable TE => CH operation interface (TCI-CH provided)
 * 
 * This header specifies the operations the CH shall provide to the TE.
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 *
 */

#ifndef __TCI_TE_CH_H__
#define __TCI_TE_CH_H__

#include <freettcn/ttcn3/tci.h>
#include <freettcn/ttcn3/tri.h>


/**
 * @addtogroup Tci TCI
 * @{
 */

/**
 * @addtogroup TciInterface Interface
 * @{
 */

/**
 * @addtogroup TciInterfaceCH The TCI-CH interface
 * @{
 */

/**
 * @defgroup TciInterfaceCHProvided TCI-CH provided
 * @{
 */


/** 
 * @brief Sends an asynchronous transmission only to the receiver component.
 * 
 * Sends an asynchronous transmission only to the given receiver component. CH transmits the
 * message to the remote TE on which receiver is being executed and enqueues the data in the
 * remote TE.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 unicast send operation on a
 * component port, which has been connected to another component port.
 * 
 * @param sender Port identifier at the sending component via which the message is sent.
 * @param receiver Identifier of the receiving component.
 * @param sendMessage The message to be send.
 */
void tciSendConnected(TriPortId sender,
                      TriComponentId receiver,
                      Value sendMessage);


/** 
 * @brief Sends an asynchronous transmission to all components being connected to this port.
 * 
 * Sends an asynchronous transmission to all components being connected to this port. CH transmits
 * the message to all remote TEs on which receivers are being executed and enqueues the data in
 * the remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 broadcast send operation on a
 * component port, which has been connected to other component ports.
 * 
 * @param sender Port identifier at the sending component via which the message is sent.
 * @param sendMessage The message to be send.
 */
void tciSendConnectedBC(TriPortId sender,
                        Value sendMessage);


/** 
 * @brief Sends an asynchronous transmission to all given receiver components.
 * 
 * Sends an asynchronous transmission to all given receiver components. CH transmits the message
 * to all remote TEs on which receivers are being executed and enqueues the data in the remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 multicast send operation on a
 * component port, which has been connected to other component ports.
 * 
 * @param sender Port identifier at the sending component via which the message is sent.
 * @param receivers Identifiers of the receiving components.
 * @param sendMessage The message to be send.
 */
void tciSendConnectedMC(TriPortId sender,
                        TriComponentIdList receivers,
                        Value sendMessage);


/** 
 * @brief The TE can initiate the procedure call at the called component receiver.
 * 
 * On invocation of this operation the TE can initiate the procedure call corresponding to the signature
 * identifier @p signature at the called component receiver. The tciCallConnected() operation shall
 * return without waiting for the return of the issued procedure call. Note that an optional timeout
 * value, which can be specified in the TTCN-3 ATS for a call operation, is not included in the
 * tciCallConnected() operation signature. The TE is responsible to address this issue by starting
 * a timer for the TTCN-3 call operation in the PA with a separate TRI operation call, i.e.
 * triStartTimer(). CH transmits the call to the remote TE on which @p receiver is being executed
 * and enqueues the call in the remote TE.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 unicast call operation on a
 * component port, which has been connected to another component port. All @e in and @e inout procedure
 * parameters contain values. All @e out procedure parameters shall contain the distinct value of @c null
 * because they are only of relevance in a reply to the procedure call but not in the procedure call
 * itself. The procedure parameters are the parameters specified in the TTCN-3 signature template.
 * 
 * @param sender Port identifier at the sending component via which the message is sent.
 * @param receiver Identifier of the receiving component.
 * @param signature Identifier of the signature of the procedure call.
 * @param parameterList A list of value parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 */
void tciCallConnected(TriPortId sender,
                      TriComponentId receiver,
                      TriSignatureId signature,
                      TciParameterListType parameterList);


/** 
 * @brief The TE can initiate the procedure call at the called component receiver.
 * 
 * On invocation of this operation the TE can initiate the procedure call corresponding to the signature
 * identifier @p signature at the called component receiver. The tciCallConnectedBC() operation shall
 * return without waiting for the return of the issued procedure call. Note that an optional timeout value,
 * which can be specified in the TTCN-3 ATS for a call operation, is not included in the
 * tciCallConnectedBC() operation signature. The TE is responsible to address this issue by starting a
 * timer for the TTCN-3 call operation in the PA with a separate TRI operation call, i.e.
 * triStartTimer(). CH transmits the call to all remote TEs on which @p receiver is being executed
 * and enqueues the call in the remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 broadcast call operation on a
 * component port, which has been connected to other component ports. All @e in and @e inout procedure
 * parameters contain values. All @e out procedure parameters shall contain the distinct value of @c null
 * because they are only of relevance in a reply to the procedure call but not in the procedure call itself.
 * The procedure parameters are the parameters specified in the TTCN-3 signature template.
 * 
 * @param sender Port identifier at the sending component via which the message is sent.
 * @param signature Identifier of the signature of the procedure call.
 * @param parameterList A list of value parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 */
void tciCallConnectedBC(TriPortId sender,
                        TriSignatureId signature,
                        TciParameterListType parameterList);


/** 
 * @brief The TE can initiate the procedure call at the called component receiver.
 * 
 * On invocation of this operation the TE can initiate the procedure call corresponding to the signature
 * identifier @p signature at the called component receiver. The tciCallConnectedMC() operation shall
 * return without waiting for the return of the issued procedure call. Note that an optional timeout value,
 * which can be specified in the TTCN-3 ATS for a call operation, is not included in the
 * tciCallConnectedMC() operation signature. The TE is responsible to address this issue by starting a
 * timer for the TTCN-3 call operation in the PA with a separate TRI operation call, i.e.
 * triStartTimer(). CH transmits the call to all remote TEs on which @p receiver is being executed
 * and enqueues the call in the remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 multicast call operation on a
 * component port, which has been connected to other component ports. All @e in and @e inout procedure
 * parameters contain values. All @e out procedure parameters shall contain the distinct value of @c null
 * because they are only of relevance in a reply to the procedure call but not in the procedure call itself.
 * The procedure parameters are the parameters specified in the TTCN-3 signature template.
 * 
 * @param sender  Port identifier at the sending component via which the message is sent.
 * @param receivers Identifier of the receiving components.
 * @param signature Identifier of the signature of the procedure call.
 * @param parameterList A list of value parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 */
void tciCallConnectedMC(TriPortId sender,
                        TriComponentIdList receivers,
                        TriSignatureId signature,
                        TciParameterListType parameterList);


/** 
 * @brief The CH can issue the reply to a procedure call on component receiver.
 * 
 * On invocation of this operation the CH can issue the reply to a procedure call corresponding to the
 * signature identifier @p signature and component identifier @p receiver. CH transmits the reply to the
 * remote TE on which @p receiver is being executed and enqueues the reply in the remote TE.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 unicast reply operation on a
 * component port which has been connected to another component port.
 * All @e out and @e inout procedure parameters and the return value contain values. All @e in procedure
 * parameters shall contain the distinct value of @c null since they are only of relevance to the procedure
 * call but not in the reply to the call. The @p parameterList contains procedure call parameters. These
 * parameters are the parameters specified in the TTCN-3 signature template. If no return type has
 * been defined for the procedure signature in the TTCN-3 ATS, the distinct value @c null shall be
 * passed for the return value.
 *
 * @param sender Identifier of the port sending the reply.
 * @param receiver Identifier of the component receiving the reply.
 * @param signature Identifier of the signature of the procedure call.
 * @param parameterList A list of encoded parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 * @param returnValue (Optional) return value of the procedure call.
 *
 * @todo TriSignatureIdType type redefined as TriSignatureId
 */
void tciReplyConnected(TriPortId sender,
                       TriComponentId receiver,
                       TriSignatureId signature,
                       TciParameterListType parameterList,
                       Value returnValue);


/** 
 * @brief The CH can issue the reply to a procedure call on all components connected to sender.
 * 
 * On invocation of this operation the CH can issue the reply to a procedure call corresponding to the
 * signature identifier @p signature and all components connected to @p sender. CH transmits the
 * exception to all remote TEs on which receivers are being executed and enqueues the exception in
 * the remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 broadcast reply operation on a
 * component port which has been connected to other component ports.
 * All @e out and @e inout procedure parameters and the return value contain values. All @e in procedure
 * parameters shall contain the distinct value of @c null since they are only of relevance to the
 * procedure call but not in the reply to the call. The @p parameterList contains procedure call
 * parameters. These parameters are the parameters specified in the TTCN-3 signature template. If
 * no return type has been defined for the procedure signature in the TTCN-3 ATS, the distinct value
 * @c null shall be passed for the return value.
 * 
 * @param sender Identifier of the port sending the reply.
 * @param signature Identifier of the signature of the procedure call.
 * @param parameterList A list of encoded parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 * @param returnValue (Optional) return value of the procedure call.
 *
 * @todo TriSignatureIdType type redefined as TriSignatureId
 */
void tciReplyConnectedBC(TriPortId sender,
                         TriSignatureId signature,
                         TciParameterListType parameterList,
                         Value returnValue);


/** 
 * @brief The CH can issue the reply to a procedure call on one of the component in receivers.
 * 
 * On invocation of this operation the CH can issue the reply to a procedure call corresponding to the
 * signature identifier @p signature and one of the component identifier in @p receivers. CH transmits
 * the reply to the remote TEs on which receivers are being executed and enqueues the reply in
 * the remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 multicast reply operation on a
 * component port which has been connected to other component ports.
 * All @e out and @e inout procedure parameters and the return value contain values. All @e in procedure
 * parameters shall contain the distinct value of @c null since they are only of relevance to the
 * procedure call but not in the reply to the call. The @p parameterList contains procedure call
 * parameters. These parameters are the parameters specified in the TTCN-3 signature template. If
 * no return type has been defined for the procedure signature in the TTCN-3 ATS, the distinct value
 * @c null shall be passed for the return value.
 * 
 * @param sender Identifier of the port sending the reply.
 * @param receivers Identifier of the components receiving the reply.
 * @param signature Identifier of the signature of the procedure call.
 * @param parameterList A list of encoded parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 * @param returnValue (Optional) return value of the procedure call.
 *
 * @todo TriSignatureIdType type redefined as TriSignatureId
 */
void tciReplyConnectedMC(TriPortId sender,
                         TriComponentIdList receivers,
                         TriSignatureId signature,
                         TciParameterListType parameterList,
                         Value returnValue);


/** 
 * @brief The CH can raise an exception to a procedure call on a component receiver.
 * 
 * On invocation of this operation the CH can raise an exception to a procedure call corresponding to
 * the signature identifier @p signature and component identifier @p receiver.
 * CH transmits the exception to the remote TE on which @p receiver is being executed and enqueues
 * the exception in the remote TE.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 unicast raise operation on a
 * component port which has been connected to another component port.
 * 
 * @param sender Identifier of the port sending the reply.
 * @param receiver Identifier of the component receiving the reply.
 * @param signature Identifier of the signature of the procedure call.
 * @param exception The exception value.
 */
void tciRaiseConnected(TriPortId sender,
                       TriComponentId receiver,
                       TriSignatureId signature,
                       Value exception);


/** 
 * @brief The CH can raise an exception to a procedure call on all components connected to sender.
 * 
 * On invocation of this operation the CH can raise an exception to a procedure call corresponding
 * to the signature identifier @p signature and all components connected to @p sender. CH
 * transmits the exception to all remote TEs on which receivers are being executed and enqueues
 * the exception in the remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 broadcast raise operation
 * on a component port which has been connected to other component ports.
 * 
 * @param sender Identifier of the port sending the reply.
 * @param signature Identifier of the signature of the procedure call.
 * @param exception The exception value.
 */
void tciRaiseConnectedBC(TriPortId sender,
                         TriSignatureId signature,
                         Value exception);


/** 
 * @brief The CH can raise an exception to a procedure call on one of the component receivers.
 * 
 * On invocation of this operation the CH can raise an exception to a procedure call corresponding to
 * the signature identifier @p signature and one of the component identifier @p receivers. CH transmits
 * the exception to all remote TEs on which @p receivers are being executed and enqueues the
 * exception in the remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 multicast raise operation on a
 * component port which has been connected to another component port.
 * 
 * @param sender Identifier of the port sending the reply.
 * @param receivers Identifiers of the component receiving the reply.
 * @param signature Identifier of the signature of the procedure call.
 * @param exception The exception value.
 */
void tciRaiseConnectedMC(TriPortId sender,
                         TriComponentIdList receivers,
                         TriSignatureId signature,
                         Value exception);


/** 
 * @brief CH transmits the component creation request to the remote TE.
 * 
 * CH transmits the component creation request to the remote TE and calls there the
 * tciCreateTestComponent() operation to obtain a component identifier for this component.
 * 
 * @remarks This operation shall be called from the TE when a component has to be created, either explicitly
 * when the TTCN-3 create operation is called or implicitly when the master test component (MTC)
 * or a control component has to be created. @p name shall be set to the distinct value @c null if no name
 * is given in the TTCN-3 create statement.
 * 
 * @param kind The kind of component that shall be created, either @c MTC, @c PTC or @c CONTROL.
 * @param componentType Identifier of the TTCN-3 component type that shall be created.
 * @param name Name of the test component to create.
 * 
 * @return A TriComponentIdType value for the created component.
 */
TriComponentId tciCreateTestComponentReq(TciTestComponentKindType kind,
                                         Type componentType,
                                         String name);


/** 
 * @brief CH transmits the start component request to the remote TE
 * 
 * CH transmits the start component request to the remote TE and calls there the
 * tciStartTestComponent() operation.
 * 
 * @remarks This operation shall be called by the TE when it executes the TTCN-3 start operation. Since only @e in
 * parameters are allowed for functions being started (ES 201 873-1 [2]), @p parameterList contains
 * only @e in parameters.
 * 
 * @param component Identifier of the component to be started.
 * @param behavior Identifier of the behaviour to be started on the component.
 * @param parameterList A list of Values where each value defines a parameter from the parameter
 *                      list as defined in the TTCN-3 function declaration of the function being
 *                      started. The parameters in @p parameterList are ordered as they appear in
 *                      the TTCN-3 signature of the test case. If no parameters have to be passed
 *                      either the @c null value or an empty @p parameterList, i.e. a list of length
 *                      zero shall be passed.
 *
 * @todo TciParamaterListType type redefined as TciParameterListType
 */
void tciStartTestComponentReq(TriComponentId component,
                              TciBehaviourIdType behavior,
                              TciParameterListType parameterList);


/** 
 * @brief CH transmits the stop component request to the remote TE.
 * 
 * CH transmits the stop component request to the remote TE and calls there the
 * tciStopTestComponent() operation.
 * 
 * @remarks This operation shall be called by the TE when it executes the TTCN-3 stop operation.
 * 
 * @param component Identifier of the component to be stopped.
 */
void tciStopTestComponentReq(TriComponentId component);


/** 
 * @brief CH transmits the connection request to the remote TE.
 * 
 * CH transmits the connection request to the remote TE where it calls the tciConnect() operation to
 * establish a logical connection between the two indicated ports. Note that both ports can be on
 * remote TEs. In this case, the operation returns only after calling the tciConnect() operation on both
 * remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 connect operation.
 * 
 * @param fromPort Identifier of the test component port to be connected from.
 * @param toPort Identifier of the test component port to be connected to.
 */
void tciConnectReq(TriPortId fromPort,
                   TriPortId toPort);


/** 
 * @brief CH transmits the disconnect request to the remote TE.
 * 
 * CH transmits the disconnect request to the remote TE where it calls the tciDisconnect()
 * operation to tear down the logical connection between the two indicated ports. Note that both
 * ports can be on remote TEs. In this case, the operation returns only after calling the
 * tciDisconnect() operation on both remote TEs.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 disconnect operation.
 * 
 * @param fromPort Identifier of the test component port to be disconnected.
 * @param toPort Identifier of the test component port to be disconnected.
 */
void tciDisconnectReq(TriPortId fromPort,
                      TriPortId toPort);


/** 
 * @brief CH transmits the map request to the remote TE.
 * 
 * CH transmits the map request to the remote TE where it calls the tciMap() operation to
 * establish a logical connection between the two indicated ports.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 map operation.
 * 
 * @param fromPort Identifier of the test component port to be mapped from.
 * @param toPort Identifier of the test component port to be mapped to.
 */
void tciMapReq(TriPortId fromPort,
               TriPortId toPort);


/** 
 * @brief CH transmits the unmap request to the remote TE.
 * 
 * CH transmits the unmap request to the remote TE where it calls the tciUnmap() operation to
 * tear down the logical connection between the two indicated ports.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 unmap operation.
 * 
 * @param fromPort Identifier of the test component port to be unmapped.
 * @param toPort Identifier of the test component port to be unmapped.
 */
void tciUnmapReq(TriPortId fromPort,
                 TriPortId toPort);


/** 
 * @brief The CH is notified of the termination of the test component.
 * 
 * The CH is notified of the termination of the indicated test component. Since a function being
 * executed on a test component can only have @e in parameters (ES 201 873-1 [2]), the
 * tciTestComponentTerminateReq() operation does not have a @p parameterList parameter.
 * CH communicates the termination of the indicated component to all participating TEs and to the
 * special TE*, which keeps track of the overall verdict.
 * 
 * @remarks This operation shall be called by the TE when a test component terminates execution, either
 * explicitly with the TTCN-3 stop operation or implicitly, if it has reached the last statement.
 * 
 * @param component Identifier of the component that has terminated.
 * @param verdict Verdict after termination of the component.
 */
void tciTestComponentTerminatedReq(TriComponentId component,
                                   VerdictValue verdict);


/** 
 * @brief CH transmits the running request to the remote TE.
 * 
 * CH transmits the running request to the remote TE having the test component to be checked,
 * where it calls the tciTestComponentRunning() operation to check the execution status of the
 * indicated test component.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 running operation.
 * 
 * @param component Identifier of the component to be checked for running.
 * 
 * @return Running status of the test component.
 * @retval true if the indicated component is still executing a behaviour
 * @retval false otherwise
 */
Boolean tciTestComponentRunningReq(TriComponentId component);


/** 
 * @brief CH transmits the done request to the remote TE.
 * 
 * CH transmits the done request to the remote TE having the test component to be checked, where
 * it calls the tciTestComponentDone() operation to check the status of the indicated test
 * component.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 done operation.
 * 
 * @param component Identifier of the component to be checked for done.
 * 
 * @return Done status of the test component.
 * @retval true if the indicated component has completed executing its behaviour
 * @retval false otherwise
 */
Boolean tciTestComponentDoneReq(TriComponentId component);


/** 
 * @brief The CH determines the component id of the MTC.
 * 
 * The CH determines the component id of the MTC.
 * 
 * @remarks This operation shall be called by the TE when it executes a TTCN-3 mtc operation.
 * 
 * @return A TriComponentIdType value of the MTC.
 */
TriComponentId tciGetMTCReq();


/** 
 * @brief CH transmits the execute test case request to the remote TEs.
 * 
 * CH transmits the execute test case request to the remote TEs having system ports of the indicated
 * test case. Static connections to the SUT and the initialization of communication means for TSI ports
 * can be set up.
 * 
 * @remarks This operation can be called by the TE immediately before it starts the test case behaviour on the
 * MTC (in course of a TTCN-3 execute operation).
 * 
 * @param testCaseId A test case identifier as defined in the TTCN-3 module.
 * @param tsiPortList tsiPortList contains all ports that have been declared in the definition of
 *                    the system component for the test case, i.e. the TSI ports. If a system
 *                    component has not been explicitly defined for the test case, then the
 *                    @p tsiPortList contains all communication ports of the MTC. The ports in
 *                    @p tsiPortList are ordered as they appear in the respective TTCN-3
 *                    component type declaration.
 *                    If no ports have to be passed either the @c null value or an empty @p tsiPortList,
 *                    i.e. a list of length zero shall be passed.
 */
void tciExecuteTestCaseReq(TciTestCaseIdType testCaseId, TriPortIdList tsiPortList);


/** 
 * @brief CH transmits the reset request to all involved TEs.
 * 
 * CH transmits the reset request to all involved TEs.
 * 
 * @remarks This operation can be called by the TE at any time to reset the test system.
 * 
 */
void tciResetReq();


/** 
 * @brief CH transmits the kill component request to the remote TE.
 * 
 * CH transmits the kill component request to the remote TE and calls there the
 * tciKillTestComponent() operation.
 * 
 * @remarks This operation shall be called by the TE when it executes the TTCN-3 kill operation.
 * 
 * @param component Identifier of the component to be killed.
 */
void tciKillTestComponentReq(TriComponentId component);


/** 
 * @brief CH transmits the request to the remote TE.
 * 
 * CH transmits the request to the remote TE that created the test component in question, where it
 * calls the tciTestComponentAlive() operation to check the status of the indicated test
 * component.
 * 
 * @remarks This operation shall be called by the TE when it executes the TTCN-3 alive operation.
 * 
 * @param component Identifier of the component to be checked for being alive.
 * 
 * @return Alive status of the test component.
 * @retval true if the indicated component is alive
 * @retval false otherwise
 */
Boolean tciTestComponentAliveReq(TriComponentId component);


/** 
 * @brief CH transmits the request to the remote TE.
 * 
 * CH transmits the request to the remote TE that created the test component in question, where it calls
 * the tciTestComponentKilled() operation to check the status of the indicated test component.
 * 
 * @remarks This operation shall be called by the TE when it executes the TTCN-3 killed operation.
 * 
 * @param component Identifier of the component to be checked for being killed.
 * 
 * @return Killed status of the test component.
 * @retval true if the indicated component has been killed
 * @retval false otherwise
 */
Boolean tciTestComponentKilledReq(TriComponentId component);


/// @} TciInterfaceCHProvided

/// @} TciInterfaceCH

/// @} TciInterface

/// @} Tci


#endif /* __TCI_TE_CH_H__ */
