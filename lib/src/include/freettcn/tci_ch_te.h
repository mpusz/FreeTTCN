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
 * @file   tci_ch_te.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:52:28 2007
 * 
 * @brief  TTCN-3 Executable CH => TE operation interface (TCI-CH required)
 * 
 * This header specifies the operations the CH requires from the TE. In addition to the operations
 * specified in this file, all @e required operation of the TCI-CD interface are also required.
 */

#ifndef __TCI_CH_TE_H__
#define __TCI_CH_TE_H__

#include "freettcn/tci.h"
#include "freettcn/tri.h"


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
 * @defgroup TciInterfaceCHRequired TCI-CH required
 * @{
 */


/** 
 * @brief The TE enqueues the value into the local port queue of the receiver component.
 * 
 * The TE enqueues the received value into the local port queue of the indicated receiver component. @n
 * @n
 * This operation shall be called by the CH at the local TE when at remote TE a @p provided
 * tciSendConnected() has been called.
 * 
 * @param sender Port identifier at the sending component via which the message is sent.
 * @param receiver Identifier of the receiving component.
 * @param rcvdMessage The value to be enqueued.
 */
void tciEnqueueMsgConnected(TriPortId sender,
                            TriComponentId receiver,
                            TciValue rcvdMessage);


/** 
 * @brief The TE enqueues the calls at the local port queue of the receiver component.
 * 
 * The TE enqueues the calls at the local port queue of the indicated receiver component. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciCallConnected() has been called. All @e in and @e inout procedure parameters contain values. All
 * @e out procedure parameters shall contain the distinct value of @c null because they are only of
 * relevance in a reply to the procedure call but not in the procedure call itself. The procedure
 * parameters are the parameters specified in the TTCN-3 signature template.
 * 
 * @param sender Port identifier at the sending component via which the message is sent.
 * @param receiver Identifier of the receiving component.
 * @param signature Identifier of the signature of the procedure call.
 * @param parameterList A list of value parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
*/
void tciEnqueueCallConnected(TriPortId sender,
                             TriComponentId receiver,
                             TriSignatureId signature,
                             TciParameterListType parameterList);


/** 
 * @brief The TE enqueues the reply at the local port queue of the receiver component.
 * 
 * The TE enqueues the reply at the local port queue of the indicated receiver component. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciReplyConnected() has been called. All @e out and @e inout procedure parameters and the @p return
 * value contain values. All @e in procedure parameters shall contain the distinct value of @c null since they
 * are only of relevance to the procedure call but not in the reply to the call. The @p parameterList
 * contains procedure call parameters. These parameters are the parameters specified in the TTCN-3
 * signature template. If no return type has been defined for the procedure signature in the TTCN-3
 * ATS, the distinct value @c null shall be passed for the @p returnValue.
 * 
 * @param sender Identifier of the port sending the reply.
 * @param receiver Identifier of the component receiving the reply.
 * @param signature Identifier of the signature of the procedure call.
 * @param parameterList A list of value parameters which are part of the indicated signature. The
 *                      parameters in @p parameterList are ordered as they appear in the TTCN-3
 *                      signature declaration.
 * @param returnValue (Optional) return value of the procedure call.
 */
void tciEnqueueReplyConnected(TriPortId sender,
                              TriComponentId receiver,
                              TriSignatureId signature,
                              TciParameterListType parameterList,
                              TciValue returnValue);


/** 
 * @brief The TE enqueues the exception at the local port queue of the receiver component.
 * 
 * The TE enqueues the exception at the local port queue of the indicated receiver component. @n
 * 
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciRaiseConnected() has been called.
 * 
 * @param sender Identifier of the port sending the reply.
 * @param receiver Identifier of the component receiving the reply.
 * @param signature Identifier of the signature of the procedure call.
 * @param exception The exception.
 *
 * @todo TriSignatureIdType type redefied as TriSignatureId
 */
void tciEnqueueRaiseConnected(TriPortId sender,
                              TriComponentId receiver,
                              TriSignatureId signature,
                              TciValue exception);


/** 
 * @brief The TE creates a TTCN-3 test component.
 * 
 * The TE creates a TTCN-3 test component of the @p componentType and passes a
 * @c TriComponentIdType reference back to the CH. The CH communicates the reference back to
 * the remote TE. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciCreateTestComponentReq() has been called. @p componentType shall be set to the distinct value
 * @c null if a test component of kind @c control shall be created. @p name shall be set to the distinct
 * value @c null if no name is given in the TTCN-3 create statement.
 * 
 * @param kind The kind of component that shall be created, either @c MTC, @c PTC or @c CONTROL.
 * @param componentType Identifier of the TTCN-3 component type that shall be created.
 * @param name Name of the component that shall be created
 * 
 * @return A @c TriComponentIdType value for the created component.
 */
TriComponentId tciCreateTestComponent(TciTestComponentKindType kind,
                                      TciType componentType,
                                      String name);


/** 
 * @brief The TE shall start the indicated behaviour on the indicated component.
 * 
 * The TE shall start the indicated behaviour on the indicated component. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a provided
 * tciStartTestComponentReq() has been called. Since only @e in parameters are allowed for
 * functions being started (ES 201 873-1 [2]), @p parameterList contains only @e in parameters.
 * 
 * @param component Identifier of the component to be started. Refers to an identifier
 *                  previously created by a call of tciCreateTestComponent()
 * @param behavior Identifier of the behaviour to be started on the component.
 * @param parameterList A list of Values where each value defines a parameter from the
 *                      parameter list as defined in the TTCN-3 function declaration of
 *                      the function being started. The parameters in @p parameterList
 *                      are ordered as they appear in the TTCN-3 signature of the test
 *                      case. If no parameters have to be passed either the @c null value
 *                      or an empty @p parameterList, i.e. a list of length zero shall be
 *                      passed.
 *
 * @todo TciParamaterListType type redefined as TciParameterListType
 */
void tciStartTestComponent(TriComponentId component,
                           TciBehaviourIdType behavior,
                           TciParameterListType parameterList);


/** 
 * @brief The TE shall stop the indicated component.
 * 
 * The TE shall stop the indicated behaviour on the indicated component. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciStopTestComponentReq() has been called.
 * 
 * @param component Identifier of the component to be stopped.
 */
void tciStopTestComponent(TriComponentId component);


/** 
 * @brief The TE shall connect the indicated ports to one another.
 * 
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciConnect() has been called.
 * 
 * @param fromPort Identifier of the test component port to be connected from.
 * @param toPort Identifier of the test component port to be connected to.
 */
void tciConnect(TriPortId fromPort,
                TriPortId toPort);


/** 
 * @brief The TE shall disconnect the indicated ports.
 * 
 * The TE shall disconnect the indicated ports. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciDisconnect() has been called.
 * 
 * @param fromPort Identifier of the test component port to be disconnected.
 * @param toPort Identifier of the test component port to be disconnected.
 */
void tciDisconnect(TriPortId fromPort,
                   TriPortId toPort);


/** 
 * @brief The TE shall map the indicated ports to one another.
 * 
 * The TE shall map the indicated ports to one another. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciMapReq() has been called.
 * 
 * @param fromPort Identifier of the test component port to be mapped from.
 * @param toPort Identifier of the test component port to be mapped to.
 */
void tciMap(TriPortId fromPort,
            TriPortId toPort);


/** 
 * @brief The TE shall unmap the indicated ports.
 * 
 * The TE shall unmap the indicated ports. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciUnmapReq() has been called.
 * 
 * @param fromPort Identifier of the test component port to be unmapped.
 * @param toPort Identifier of the test component port to be unmapped.
 */
void tciUnmap(TriPortId fromPort,
              TriPortId toPort);


/** 
 * @brief The TE is notified of the termination of the test component.
 * 
 * The local TE is notified of the termination of the indicated test component on a remote TE.
 * Since a function being executed on a test component can only have @e in parameters
 * (ES 201 873-1 [2]), the tciTestComponentTerminated() operation does not have a
 * @p parameterList parameter. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciTestComponentTerminatedReq() has been called.
 * 
 * @param component Identifier of the component that has terminated.
 * @param verdict Verdict after termination of the component.
 */
void tciTestComponentTerminated(TriComponentId component,
                                TciVerdictValue verdict);


/** 
 * @brief The local TE determines whether the indicated component is executing a test behaviour.
 * 
 * The local TE determines whether the indicated component is executing a test behaviour. If the
 * component is executing a behaviour @c true will be returned. In any other case, e.g. test
 * component has finished execution, or test component has not been started, etc. @c false will be
 * returned. After the operation returns, the CH will communicate the value back to the remote TE. @n
 * @n
 * @param component Identifier of the component to be checked for running.
 * 
 * @return Component running status.
 * @retval true if the indicated component is still executing a behaviour
 * @retval false otherwise
 */
Boolean tciTestComponentRunning(TriComponentId component);


/** 
 * @brief The TE determines whether the component has completed executing its test behaviour.
 * 
 * The local TE determines whether the indicated component has completed executing its test
 * behaviour. If the component has completed its behaviour @c true will be returned. In any other case,
 * e.g. test component has not been started, or test component is still executing, @c false will be
 * returned. After the operation returns, the CH will communicate the value back to the remote TE. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciTestComponentDoneReq() has been called.
 * 
 * @param component Identifier of the component to be checked for done.
 * 
 * @return Component executing status.
 * @retval true if the indicated component has completed executing its behaviour
 * @retval false otherwise
 */
Boolean tciTestComponentDone(TriComponentId component);


/** 
 * @brief Returns the component id of the MTC.
 * 
 * The local TE determines whether the MTC is executing on the local TE. If the MTC executes on
 * the local TE the component id of the MTC is being returned. If the MTC is not executed on the
 * local TE the distinct value @c null will be returned. The operation will have no effect on the execution
 * of the MTC. After the operation returns, the CH will communicate the value back to the remote TE. @n
 * @n
 * This operation can be called by the CH at the appropriate local TE when at a remote TE a @e provided
 * tciGetMTCReq() has been called.
 * 
 * @return A @c TriComponentIdType value of the MTC if the MTC executes on the local TE, the distinct value
 *         @c null otherwise.
 */
TriComponentId tciGetMTC();


/** 
 * @brief The TE determines whether static connections and the initialization of TSI ports should be done.
 * 
 * The local TE determines whether static connections to the SUT and the initialization of
 * communication means for TSI ports should be done. @n
 * @n
 * This operation shall be called by the CH at the appropriate local TE when at a remote TE a @e provided
 * tciExecuteTestCaseReq() has been called.
 * 
 * @param testCaseId A test case identifier as defined in the TTCN-3 module.
 * @param tsiPortList Contains all ports that have been declared in the definition of the system
 *                    component for the test case, i.e. the TSI ports. If a system component has not
 *                    been explicitly defined for the test case, then the @p tsiPortList contains all
 *                    communication ports of the MTC. The ports in @p tsiPortList are ordered as they
 *                    appear in the respective TTCN-3 component type declaration. If no ports have to
 *                    be passed either the @c null value or an empty @p tsiPortList, i.e. a list of length
 *                    zero shall be passed.
 */
void tciExecuteTestCase(TciTestCaseIdType testCaseId,
                        TriPortIdList tsiPortList);


/** 
 * @brief The TE can reset the test system locally.
 * 
 * The TE can decide to take any means to reset the test system locally. @n
 * @n
 * This operation shall be called by the CH at appropriate local TEs when at a remote TE a
 * @e provided tciResetReq() has been called.
 */
void tciReset();


/** 
 * @brief The TE stops the behaviour on the indicated component.
 * 
 * The TE stops the behaviour on the indicated component if necessary and transfers it into the
 * killed state. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciKillTestComponentReq() has been called.
 *
 * @param component Identifier of the component to be killed.
 */
void tciKillTestComponent(TriComponentId component);


/** 
 * @brief The local TE determines whether the indicated component is alive.
 * 
 * The local TE determines whether the indicated component is alive. After the operation returns,
 * the CH will communicate the value back to the remote TE. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciTestComponentAliveReq() has been called.
 * 
 * @param component Identifier of the component to be checked for being alive.
 * 
 * @return Living status on the component.
 * @retval true if the indicated component is alive
 * @retval false otherwise
 */
Boolean tciTestComponentAlive(TriComponentId component);


/** 
 * @brief The local TE determines whether the indicated component is in the killed state.
 * 
 * The local TE determines whether the indicated component is in the killed state. If it is, @c true
 * will be returned. In any other case, @c false will be returned. After the operation returns, the CH
 * will communicate the value back to the remote TE. @n
 * @n
 * This operation shall be called by the CH at the local TE when at a remote TE a @e provided
 * tciTestComponentKilledReq() has been called.
 * 
 * @param component Identifier of the component to be checked for being killed.
 * 
 * @return Killed status of the component.
 * @retval true if the indicated component has been killed.
 * @retval false otherwise
 */
Boolean tciTestComponentKilled(TriComponentId component);


/// @} TciInterfaceCHRequired

/// @} TciInterfaceCH

/// @} TciInterface

/// @} Tci


#endif /* __TCI_CH_TE_H__ */
