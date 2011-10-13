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
 * @file   TciTlProvided.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:50:45 2007
 * 
 * @brief  TTCN-3 Executable TCI types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 * 
 */

#ifndef __TCI_TL_PROVIDED_H__
#define __TCI_TL_PROVIDED_H__

#include <freettcn/etsi/tci.h>

namespace ORG_ETSI_TTCN3_TCI {
  
  class TciTlProvided {
  public:
    //Default constructor
    TciTlProvided();
    // Destructor
    virtual ~TciTlProvided ();
    //Called by TE to log the execute test case request
    virtual void tliTcExecute(const Tstring &am, const timeval ts,
                              const Tstring src, const Tinteger line, const TriComponentId *c,
                              const TciTestCaseId *tcId, const TriParameterList *triPars, const TriTimerDuration *dur) = 0;
    //Called by TE to log the start of a testcase. This event occurs before the testcase is started
    virtual void tliTcStart(const Tstring &am, const timeval ts,
                            const Tstring &src, const Tinteger line, const TriComponentId *c,
                            const TciTestCaseId *tcId, const TciParameterList *tciPars, const TriTimerDuration *dur) = 0;
    //Called by TE to log the stop of a testcase
    virtual void tliTcStop(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log the start of a testcase
    virtual void tliTcStarted(const Tstring &am, const timeval ts,
                              const Tstring &src, const Tinteger line, const TriComponentId *c,
                              const TciTestCaseId *tcId, const TciParameterList *tciPars, const TriTimerDuration *dur) = 0;
    //Called by TE to log the termination of a testcase
    virtual void tliTcTerminated(const Tstring &am, const timeval ts,
                                 const Tstring &src, const Tinteger line, const TriComponentId *c,
                                 const TciTestCaseId *tcId, const TciParameterList *tciPars, const VerdictValue *verdict) = 0;
    //Called by TE to log the start of the control part
    virtual void tliCtrlStart(const Tstring &am, const timeval ts,
                              const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log the stop of the control part. This event occurs after the control has
    //stopped. If the control is not represented by TRI component, c is null
    virtual void tliCtrlStop(const Tstring &am, const timeval ts,
                             const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log the termination of the control part
    virtual void tliCtrlTerminated(const Tstring &am, const timeval ts,
                                   const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log a unicast send operation
    virtual void tliMSend_m(const Tstring &am, const timeval ts,
                            const Tstring &src, const Tinteger line, const TriComponentId *c,
                            const TriPortId *at, const TriPortId *to, const TciValue *msgValue,
                            const TriAddress *address, const TciStatus *encoderFailure, const TriMessage *msg,
                            const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a broadcast send operation
    virtual void tliMSend_m_BC(const Tstring &am, const timeval ts,
                               const Tstring &src, const Tinteger line, const TriComponentId *c,
                               const TriPortId *at, const TriPortId *to, const TciValue *msgValue,
                               const TciStatus *encoderFailure, const TriMessage *msg, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a multicast send operation
    virtual void tliMSend_m_MC(const Tstring &am, const timeval ts,
                               const Tstring &src, const Tinteger line, const TriComponentId *c,
                               const TriPortId *at, const TriPortId *to, const TciValue *msgValue,
                               const TriAddressList *addresses, const TciStatus *encoderFailure,
                               const TriMessage *msg, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a unicast send operation
    virtual void tliMSend_c(const Tstring &am, const timeval ts,
                            const Tstring src, const Tinteger line, const TriComponentId *c,
                            const TriPortId *at, const TriPortId *to, const TciValue *msgValue,
                            const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a broadcast send operation
    virtual void tliMSend_c_BC(const Tstring &am, const timeval ts,
                               const Tstring src, const Tinteger line, const TriComponentId *c,
                               const TriPortId *at, const TriPortIdList *to, const TciValue *msgValue,
                               const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a multicast send operation
    virtual void tliMSend_c_MC(const Tstring &am, const timeval ts,
                               const Tstring src, const Tinteger line, const TriComponentId *c,
                               const TriPortId *at, const TriPortIdList *to, const TciValue *msgValue,
                               const TriStatus *transmissionFailure) = 0;
    //Called by TE to log the enqueuing of a message
    virtual void tliMDetected_m(const Tstring &am, const timeval ts,
                                const Tstring &src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TriPortId *from, const TriMessage *msg,
                                const TriAddress *address) = 0;
    //Called by CH to log the enqueuing of a message
    virtual void tliMDetected_c(const Tstring &am, const timeval ts,
                                const Tstring src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TriPortId *from, const TciValue *msgValue) = 0;
    //Called by TE to log the mismatch of a template
    virtual void tliMMismatch_m(const Tstring &am, const timeval ts,
                                const Tstring &src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TciValue *msgValue, const TciValueTemplate *msgTmpl,
                                const TciValueDifferenceList *diffs, const TriAddress *address,
                                const TciValueTemplate *addressTmpl) = 0;
    //Called by TE to log the mismatch of a template
    virtual void tliMMismatch_c(const Tstring &am, const timeval ts,
                                const Tstring &src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TciValue *msgValue, const TciValueTemplate *msgTmpl,
                                const TciValueDifferenceList *diffs, const TriComponentId *from,
                                const TciNonValueTemplate *fromTmpl) = 0;
    // Called by TE to log the receiving of a message
    virtual void tliMRecieve_m(const Tstring &am, const timeval ts,
                               const Tstring &src, const Tinteger line, const TriComponentId *c,
                               const TriPortId *at, const TciValue *msgValue, const TciValueTemplate *msgTmpl,
                               const TriAddress *address, const TciValueTemplate *addressTmpl) = 0;
    //Called by TE to log the mismatch of a template
    virtual void tliMReceive_c(const Tstring &am, const timeval ts,
                               const Tstring &src, const Tinteger line, const TriComponentId *c,
                               const TriPortId *at, const TciValue *msgValue, const TciValueTemplate *msgTmpl,
                               const TriComponentId *fromComp, const TciNonValueTemplate *fromTmpl) = 0;
    //Called by TE to log a unicast call operation
    virtual void tliPrCall_m(const Tstring &am, const timeval ts,
                             const Tstring src, const Tinteger line, const TriComponentId *c,
                             const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                             const TciParameterList *tciPars, const TriAddress *address,
                             const TciStatus *encoderFailure, const TriParameterList *triPars,
                             const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a broadcast call operation
    virtual void tliPrCall_m_BC(const Tstring &am, const timeval ts,
                                const Tstring src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                                const TciParameterList *tciPars, const TciStatus *encoderFailure,
                                const TriParameterList *triPars, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a multicast call operation
    virtual void tliPrCall_m_MC(const Tstring &am, const timeval ts,
                                const Tstring src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                                const TciParameterList *tciPars, const TriAddressList *addresses,
                                const TciStatus *encoderFailure, const TriParameterList *triPars,
                                const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a unicast call operation
    virtual void tliPrCall_c(const Tstring &am, const timeval ts,
                             const Tstring src, const Tinteger line, const TriComponentId *c,
                             const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                             const TciParameterList *tciPars, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a broadcast call operation
    virtual void tliPrCall_c_BC(const Tstring &am, const timeval ts,
                                const Tstring src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TriPortIdList *to, const TriSignatureId *signature,
                                const TciParameterList *tciPars, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a multicast call operation
    virtual void tliPrCall_c_MC(const Tstring &am, const timeval ts,
                                const Tstring src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TriPortIdList *to, const TriSignatureId *signature,
                                const TciParameterList *tciPars, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log the getcall enqueue operation
    virtual void tliPrGetCallDetected_m(const Tstring &am, const timeval ts,
                                        const Tstring src, const Tinteger line, const TriComponentId *c,
                                        const TriPortId *at, const TriPortId *from, const TriSignatureId *signature,
                                        const TriParameterList *triPars, const TriAddress *address) = 0;
    //Called by TE to log the getcall enqueue operation
    virtual void tliPrGetCallDetected_c(const Tstring &am, const timeval ts,
                                        const Tstring src, const Tinteger line, const TriComponentId *c,
                                        const TriPortId *at, const TriPortId *from, const TriSignatureId *signature,
                                        const TciParameterList *tciPars) = 0;
    //Called by TE to log the mismatch of a getcall
    virtual void tliPrGetCallMismatch_m(const Tstring &am, const timeval ts,
                                        const Tstring src, const Tinteger line, const TriComponentId *c,
                                        const TriPortId *at, const TriSignatureId *signature,
                                        const TciParameterList *tciPars, const TciValueTemplate *parsTmpl,
                                        const TciValueDifferenceList *diffs, const TriAddress *address,
                                        const TciValueTemplate *addressTmpl) = 0;
    //Called by TE to log the mismatch of a getcall
    virtual void tliPrGetCallMismatch_c(const Tstring &am, const timeval ts,
                                        const Tstring src, const Tinteger line, const TriComponentId *c,
                                        const TriPortId *at, const TriSignatureId *signature,
                                        const TciParameterList *tciPars, const TciValueTemplate *parsTmpl,
                                        const TciValueDifferenceList *diffs, const TriComponentId *from,
                                        const TciValueTemplate *fromTmpl) = 0;
    //Called by TE to log getting a call
    virtual void tliPrGetCall_m(const Tstring &am, const timeval ts,
                                const Tstring src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TriSignatureId *signature, const TciParameterList *tciPars,
                                const TciValueTemplate *parsTmpl, const TriAddress *address,
                                const TciValueTemplate *addressTmpl) = 0;
    //Called by TE to log getting a call
    virtual void tliPrGetCall_c(const Tstring &am, const timeval ts,
                                const Tstring src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *at, const TriSignatureId *signature, const TciParameterList *tciPars,
                                const TciValueTemplate *parsTmpl, const TriComponentId *from,
                                const TciNonValueTemplate *fromTmpl) = 0;
    //Called by TE to log a unicast reply operation
    virtual void tliPrReply_m(const Tstring &am, const timeval ts,
                              const Tstring src, const Tinteger line, const TriComponentId *c,
                              const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                              const TciParameterList *tciPars, const TciValue *replValue, const TriAddress *address,
                              const TciStatus *encoderFailure, const TriParameterList *triPars, const TriParameter *repl,
                              const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a broadcast reply operation
    virtual void tliPrReply_m_BC(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                                 const TciParameterList *tciPars, const TciValue *replValue,
                                 const TciStatus *encoderFailure, const TriParameterList *triPars,
                                 const TriParameter *repl, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a multicast reply operation
    virtual void tliPrReply_m_MC(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                                 const TciParameterList *tciPars, const TciValue *replValue,
                                 const TriAddressList *addresses, const TciStatus *encoderFailure,
                                 const TriParameterList *triPars, const TriParameter *repl,
                                 const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a unicast reply operation
    virtual void tliPrReply_c(const Tstring &am, const timeval ts,
                              const Tstring src, const Tinteger line, const TriComponentId *c,
                              const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                              const TciValue *parsValue, const TciValue *replValue, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a broadcast reply operation
    virtual void tliPrReply_c_BC(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriPortIdList *to, const TriSignatureId *signature,
                                 const TciValue *parsValue, const TciValue *replValue, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log og a multicast reply operation
    virtual void tliPrReply_c_MC(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriPortIdList *to, const TriSignatureId *signature,
                                 const TciValue *parsValue, const TciValue *replValue, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log the getreply enqueue operation
    virtual void tliPrGetReplyDetected_m(const Tstring &am, const timeval ts,
                                         const Tstring src, const Tinteger line, const TriComponentId *c,
                                         const TriPortId *at, const TriPortId *from, const TriSignatureId *signature,
                                         const TriParameterList *triPars, const TriParameter *repl, const TriAddress *address) = 0;
    //Called by CH to log the getreply enqueue operation
    virtual void tliPrGetReplyDetected_c(const Tstring &am, const timeval ts,
                                         const Tstring src, const Tinteger line, const TriComponentId *c,
                                         const TriPortId *at, const TriPortId *from, const TriSignatureId *signature,
                                         const TciParameterList *tciPars, const TciValue *replValue) = 0;
    //Called by TE to log the mismatch of a getreply operation
    virtual void tliPrGetReplyMismatch_m(const Tstring &am, const timeval ts,
                                         const Tstring src, const Tinteger line, const TriComponentId *c,
                                         const TriPortId *at, const TriSignatureId *signature, const TciParameterList *tciPars,
                                         const TciValueTemplate *parsTmpl, const TciValue *replValue, const TciValueTemplate *replyTmpl,
                                         const TciValueDifferenceList *diffs, const TriAddress *address, const TciValueTemplate *addressTmpl) = 0;
    //Called by TE to log the mismatch of a getreply operation
    virtual void tliPrGetReplyMismatch_c(const Tstring &am, const timeval ts,
                                         const Tstring src, const Tinteger line, const TriComponentId *c,
                                         const TriPortId *at, const TriSignatureId *signature, const TciParameterList *tciPars,
                                         const TciValueTemplate *parsTmpl, const TciValue *replValue, const TciValueTemplate *replyTmpl,
                                         const TciValueDifferenceList *diffs, const TriComponentId *from, const TciNonValueTemplate *fromTmpl) = 0;
    //Called by TE to log getting a reply
    virtual void tliPrGetReply_m(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriSignatureId *signature, const TciParameterList *tciPars,
                                 const TciValueTemplate *parsTmpl, const TciValue *replValue, const TciValueTemplate *replyTmpl,
                                 const TriAddress *address, const TciValueTemplate *addressTmpl) = 0;
    //Called by TE to log getting a reply
    virtual void tliPrGetReply_c(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriSignatureId *signature, const TciParameterList *tciPars,
                                 const TciValueTemplate *parsTmpl, const TciValue *replValue, const TciValueTemplate *replyTmpl,
                                 const TriComponentId *from, const TciNonValueTemplate *fromTmpl) = 0;
    //Called by TE to log a unicast raise operation
    virtual void tliPrRaise_m(const Tstring &am, const timeval ts,
                              const Tstring src, const Tinteger line, const TriComponentId *c,
                              const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                              const TciParameterList *tciPars, const TciValue *excValue, const TriAddress *address,
                              const TriStatus *encoderFailure, const TriException *exc, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a broadcast raise operation
    virtual void tliPrRaise_m_BC(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                                 const TciParameterList *tciPars, const TciValue *excValue, const TriStatus *encoderFailure,
                                 const TriException *exc, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a multicast raise operation
    virtual void tliPrRaise_m_MC(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                                 const TciParameterList *tciPars, const TciValue *excValue, const TriAddressList *addresses,
                                 const TriStatus *encoderFailure, const TriException *exc, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a unicast raise operation
    virtual void tliPrRaise_c(const Tstring &am, const timeval ts,
                              const Tstring src, const Tinteger line, const TriComponentId *c,
                              const TriPortId *at, const TriPortId *to, const TriSignatureId *signature,
                              const TciParameterList *tciPars, const TciValue *excValue, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a broadcast raise operation
    virtual void tliPrRaise_c_BC(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriPortIdList *to, const TriSignatureId *signature,
                                 const TciParameterList *tciPars, const TciValue *excValue, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log a multicast raise operation
    virtual void tliPrRaise_c_MC(const Tstring &am, const timeval ts,
                                 const Tstring src, const Tinteger line, const TriComponentId *c,
                                 const TriPortId *at, const TriPortIdList *to, const TriSignatureId *signature,
                                 const TciParameterList *tciPars, const TciValue *excValue, const TriStatus *transmissionFailure) = 0;
    //Called by TE to log the catch enqueue operation
    virtual void tliPrCatchDetected_m(const Tstring &am, const timeval ts,
                                      const Tstring src, const Tinteger line, const TriComponentId *c,
                                      const TriPortId *at, const TriPortId *from, const TriSignatureId *signature,
                                      const TriException *exc, const TriAddress *address) = 0;
    //Called by TE to log the catch enqueue operation
    virtual void tliPrCatchDetected_c(const Tstring &am, const timeval ts,
                                      const Tstring src, const Tinteger line, const TriComponentId *c,
                                      const TriPortId *at, const TriPortId *from, const TriSignatureId *signature,
                                      const TciValue *excValue) = 0;
    //Called by TE to log the mismatch of a catch operation
    virtual void tliPrCatchMismatch_m(const Tstring &am, const timeval ts,
                                      const Tstring src, const Tinteger line, const TriComponentId *c,
                                      const TriPortId *at, const TriSignatureId *signature, const TciValue *excValue,
                                      const TciValueTemplate *excTmpl, const TciValueDifferenceList *diffs,
                                      const TriAddress *address, const TciValueTemplate *addressTmpl) = 0;
    //Called by TE to log the mismatch of a catch operation
    virtual void tliPrCatchMismatch_c(const Tstring &am, const timeval ts,
                                      const Tstring src, const Tinteger line, const TriComponentId *c,
                                      const TriPortId *at, const TriSignatureId *signature, const TciValue *excValue,
                                      const TciValueTemplate *excTmpl, const TciValueDifferenceList *diffs,
                                      const TriComponentId *from, const TciNonValueTemplate *fromTmpl) = 0;
    //Called by TE to log catching an exception
    virtual void tliPrCatch_m(const Tstring &am, const timeval ts,
                              const Tstring src, const Tinteger line, const TriComponentId *c,
                              const TriPortId *at, const TriSignatureId *signature, const TciValue *excValue,
                              const TciValueTemplate *excTmpl, const TriAddress *address, const TciValueTemplate *addressTmpl) = 0;
    //Called by TE to log catching an exception
    virtual void tliPrCatch_c(const Tstring &am, const timeval ts,
                              const Tstring src, const Tinteger line, const TriComponentId *c,
                              const TriPortId *at, const TriSignatureId *signature, const TciValue *excValue,
                              const TciValueTemplate *excTmpl, const TriComponentId *from, const TciNonValueTemplate *fromTmpl) = 0;
    //Called by TE to log the detection of a catch timeout
    virtual void tliPrCatchTimeoutDetected(const Tstring &am, const timeval ts,
                                           const Tstring src, const Tinteger line, const TriComponentId *c,
                                           const TriPortId *at, const TriSignatureId *signature) = 0;
    //Called by TE to log catching a timeout
    virtual void tliPrCatchTimeout(const Tstring &am, const timeval ts,
                                   const Tstring src, const Tinteger line, const TriComponentId *c,
                                   const TriPortId *at, const TriSignatureId *signature) = 0;
    //Called by TE to log the create component operation
    virtual void tliCCreate(const Tstring &am, const timeval ts,
                            const Tstring src, const Tinteger line, const TriComponentId *c,
                            const TriComponentId *comp, const Tstring &name, const Tboolean alive) = 0;
    //Called by TE to log the start component operation
    virtual void tliCStart(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const TriComponentId *comp, const TciBehaviourId *beh, const TciParameterList *tciPars) = 0;
    //Called by TE to log the running component operation
    virtual void tliCRunning(const Tstring &am, const timeval ts,
                             const Tstring &src, const Tinteger line, const TriComponentId *c,
                             const TriComponentId *comp, const ComponentStatus status) = 0;
    //Called by TE to log the alive component operation
    virtual void tliCAlive(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const TriComponentId *comp, const ComponentStatus status) = 0;
    //Called by TE to log the stop component operation
    virtual void tliCStop(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c,
                          const TriComponentId *comp) = 0;
    //Called by TE to log the kill component operation
    virtual void tliCKill(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c,
                          const TriComponentId *comp) = 0;
    //Called by TE to log the mismatch of a done component operation
    virtual void tliCDoneMismatch(const Tstring &am, const timeval ts,
                                  const Tstring &src, const Tinteger line, const TriComponentId *c,
                                  const TriComponentId *comp, const TciNonValueTemplate *compTmpl) = 0;
    //Called by TE to log the done component operation
    virtual void tliCDone(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c,
                          const TciNonValueTemplate *compTmpl) = 0;
    //Called by TE to log the mismatch of a killed component operation
    virtual void tliCKilledMismatch(const Tstring &am, const timeval ts,
                                    const Tstring &src, const Tinteger line, const TriComponentId *c,
                                    const TciNonValueTemplate *compTmpl) = 0;
    //Called by TE to log the killed component operation
    virtual void tliCKilled(const Tstring &am, const timeval ts,
                            const Tstring &src, const Tinteger line, const TriComponentId *c,
                            const TciNonValueTemplate *compTmpl) = 0;
    //Called by TE to log the termination of a component
    virtual void tliCTerminated(const Tstring &am, const timeval ts,
                                const Tstring &src, const Tinteger line, const TriComponentId *c,
                                const VerdictValue *verdict) = 0;
    //Called by TE to log the connect operation
    virtual void tliPConnect(const Tstring &am, const timeval ts,
                             const Tstring src, const Tinteger line, const TriComponentId *c,
                             const TriPortId *port1, const TriPortId *port2) = 0;
    //Called by TE to log the connect operation
    virtual void tliPDisconnect(const Tstring &am, const timeval ts,
                                const Tstring src, const Tinteger line, const TriComponentId *c,
                                const TriPortId *port1, const TriPortId *port2) = 0;
    //Called by TE to log the map operation
    virtual void tliPMap(const Tstring &am, const timeval ts,
                         const Tstring &src, const Tinteger line, const TriComponentId *c,
                         const TriPortId *port1, const TriPortId *port2) = 0;
    //Called by TE to log the unmap operation
    virtual void tliPUnmap(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const TriPortId *port1, const TriPortId *port2) = 0;
    //Called by TE to log the port clear operation
    virtual void tliPClear(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const TriPortId *port) = 0;
    //Called by TE to log the port start operation
    virtual void tliPStart(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const TriPortId *port) = 0;
    //Called by TE to log the port stop operation
    virtual void tliPStop(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c,
                          const TriPortId *port) = 0;
    //Called by TE to log the port stop operation
    virtual void tliPHalt(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c,
                          const TriPortId *port) = 0;
    //Called by TE to log the encode operation
    virtual void tliEncode(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const TciValue *val, const TciStatus *encoderFailure, const TriMessage *msg,
                           const Tstring &codec) = 0;
    //Called by TE to log the decode operation
    virtual void tliDecode(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const TriMessage *msg, const TciStatus *decoderFailure, const TciValue *val,
                           const Tstring &codec) = 0;
    //Called by TE to log the detection of a timeout
    virtual void tliTTimeoutDetected(const Tstring &am, const timeval ts,
                                     const Tstring &src, const Tinteger line, const TriComponentId *c,
                                     const TriTimerId *timer) = 0;
    //Called by TE to log a timeout mismatch
    virtual void tliTTimeoutMismatch(const Tstring &am, const timeval ts,
                                     const Tstring &src, const Tinteger line, const TriComponentId *c,
                                     const TriTimerId *timer, const TciNonValueTemplate *timerTmpl) = 0;
    //Called by TE to log a timeout match
    virtual void tliTTimeout(const Tstring &am, const timeval ts,
                             const Tstring &src, const Tinteger line, const TriComponentId *c,
                             const TriTimerId *timer, const TciNonValueTemplate *timerTmpl) = 0;
    //Called by TE to log the start of a timer
    virtual void tliTStart(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const TriTimerId *timer, const TriTimerDuration *dur) = 0;
    //Called by TE to log the stop of a timer
    virtual void tliTStop(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c,
                          const TriTimerId *timer, const TriTimerDuration *dur) = 0;
    //Called by TE to log the reading of a timer
    virtual void tliTRead(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c,
                          const TriTimerId *timer, const TriTimerDuration *elapsed) = 0;
    //Called by TE to log the running timer operation
    virtual void tliTRunning(const Tstring &am, const timeval ts,
                             const Tstring &src, const Tinteger line, const TriComponentId *c,
                             const TriTimerId *timer, const TimerStatus status) = 0;
    //Called by TE to log the entering of a scope
    virtual void tliSEnter(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const QualifiedName &name, const TciParameterList *tciPars, const Tstring &kind) = 0;
    //Called by TE to log the leaving of a scope
    virtual void tliSLeave(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const QualifiedName &name, const TciParameterList *tciPars, const TciValue *returnValue,
                           const Tstring &kind) = 0;
    //Called by TE to log the modification of the value of a variable
    virtual void tliVar(const Tstring &am, const timeval ts,
                        const Tstring &src, const Tinteger line, const TriComponentId *c,
                        const QualifiedName &name, const TciValue *varValue) = 0;
    //Called by TE to log the value of a module parameter
    virtual void tliModulePar(const Tstring &am, const timeval ts,
                              const Tstring &src, const Tinteger line, const TriComponentId *c,
                              const QualifiedName &name, const TciValue *parValue) = 0;
    //Called by TE to log the value of a module parameter
    virtual void tliGetVerdict(const Tstring &am, const timeval ts,
                               const Tstring &src, const Tinteger line, const TriComponentId *c,
                               const VerdictValue *verdict) = 0;
    //Called by TE to log the setverdict operation
    virtual void tliSetVerdict(const Tstring &am, const timeval ts,
                               const Tstring &src, const Tinteger line, const TriComponentId *c,
                               const VerdictValue *verdict, const TString &reason) = 0;
    //Called by TE to log the TTCN-3 statement log
    virtual void tliLog(const Tstring &am, const timeval ts,
                        const Tstring &src, const Tinteger line, const TriComponentId *c,
                        const Tstring *log) = 0;
    //Called by TE to log entering an alt
    virtual void tliAEnter(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log leaving an alt
    virtual void tliALeave(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log the nomatch of an alt
    virtual void tliANomatch(const Tstring &am, const timeval ts,
                             const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log repeating an alt
    virtual void tliARepeat(const Tstring &am, const timeval ts,
                            const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log entering the default section
    virtual void tliADefaults(const Tstring &am, const timeval ts,
                              const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log the activation of a default
    virtual void tliAActivate(const Tstring &am, const timeval ts,
                              const Tstring &src, const Tinteger line, const TriComponentId *c,
                              const QualifiedName &name, const TciParameterList *tciPars, const TciValue *ref) = 0;
    //Called by TE to log the deactivation of a default
    virtual void tliADeactivate(const Tstring &am, const timeval ts,
                                const Tstring &src, const Tinteger line, const TriComponentId *c,
                                const TciValue *ref) = 0;
    //Called by TE to log entering an alt
    virtual void tliAWait(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c) = 0;
    //Called by TE to log that the component executed an SUT action
    virtual void tliAction(const Tstring &am, const timeval ts,
                           const Tstring &src, const Tinteger line, const TriComponentId *c,
                           const Tstring &action) = 0;
    //Called by TE to log that the component successfully executed a match operation
    virtual void tliMatch(const Tstring &am, const timeval ts,
                          const Tstring &src, const Tinteger line, const TriComponentId *c,
                          const TciValue &expr, const TciValueTemplate &tmpl) = 0;
    //Called by TE to log that the component executed a match operation, and a mismatch occurred
    virtual void tliMatchMismatch(const Tstring &am, const timeval ts,
                                  const Tstring &src, const Tinteger line, const TriComponentId *c,
                                  const TciValue &expr, const TciValueTemplate &tmpl, const TciValueDifferenceList &diffs) = 0;
    //Can be called by the TE to log additional information during test execution
    virtual void tliInfo(const Tstring &am, const timeval ts,
                         const Tstring &src, const Tinteger line, const TriComponentId *c,
                         const Tinteger level, const Tstring &info) = 0;
  };
  
} // namespace ORG_ETSI_TTCN3_TCI

#endif /* __TCI_TL_PROVIDED_H__ */
