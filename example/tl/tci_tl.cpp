//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) usage example.

// This example is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This example is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this example; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


extern "C" {
#include "freettcn/tci_tl.h"
}
#include "tl.h"


/** 
 * @brief TE logs the execute test case request.
 * 
 * Shall be called by TE to log the execute test case request.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param tcId The testcase to be executed.
 * @param pars The list of parameters required by the testcase.
 * @param dur Duration of the execution.
 */
void tliTcExecute(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TciTestCaseIdType tcId,
                  TriParameterList pars,
                  TriTimerDuration dur)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcExecute(am, ts, src, line, c, tcId, pars, dur);
}


/** 
 * @brief TE logs the start of a testcase.
 * 
 * Shall be called by TE to log the start of a testcase. This event occurs before the testcase is started.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param tcId The testcase to be executed.
 * @param pars The list of parameters required by the testcase.
 * @param dur Duration of the execution.
 */
void tliTcStart(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TciTestCaseIdType tcId,
                TriParameterList pars,
                TriTimerDuration dur)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcStart(am, ts, src, line, c, tcId, pars, dur);
}


/** 
 * @brief TE logs the stop of a testcase.
 * 
 * Shall be called by TE to log the stop of a testcase.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliTcStop(String am,
               int ts,
               String src,
               int line,
               TriComponentId c)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcStop(am, ts, src, line, c);
}


/** 
 * @brief TM logs the start of a testcase.
 * 
 * Shall be called by TM to log the start of a testcase. This event occurs after the testcase was started.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c  The component which produces this event.
 * @param tcId The testcase to be executed.
 * @param pars The list of parameters required by the testcase.
 * @param dur Duration of the execution.
 */
void tliTcStarted(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TciTestCaseIdType tcId,
                  TriParameterList pars,
                  TriTimerDuration dur)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcStarted(am, ts, src, line, c, tcId, pars, dur);
}


/** 
 * @brief TM logs the termination of a testcase.
 * 
 * Shall be called by TM to log the termination of a testcase. This event occurs after the testcase
 * terminated.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param tcId The testcase to be executed.
 * @param pars The list of parameters required by the testcase.
 * @param outcome The verdict of the testcase.
 * 
 * @todo VerdictValue type redefined as TciVerdictValue
 */
void tliTcTerminated(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TciTestCaseIdType tcId,
                     TriParameterList pars,
                     TciVerdictValue outcome)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcTerminated(am, ts, src, line, c, tcId, pars, outcome);
}


/** 
 * @brief TE logs the start of the control part.
 * 
 * Shall be called by TE to log the start of the control part. This event occurs before the control is
 * started. If the control is not represented by a TRI component, @p c is @c null.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliCtrlStart(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CtrlStart(am, ts, src, line, c);
}


/** 
 * @brief TE logs the stop of the control part.
 * 
 * Shall be called by TE to log the stop of the control part. This event occurs before the control is
 * stopped. If the control is not represented by a TRI component, @p c is @c null.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliCtrlStop(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CtrlStop(am, ts, src, line, c);
}


/** 
 * @brief TM logs the termination of the control part.
 * 
 * Shall be called by TM to log the termination of the control part. This event occurs after the control
 * has terminated. If the control is not represented by a TRI component, @p c is @c null.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliCtrlTerminated(String am,
                       int ts,
                       String src,
                       int line,
                       TriComponentId c)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CtrlTerminated(am, ts, src, line, c);
}


/** 
 * @brief SA logs a unicast send operation.
 * 
 * Shall be called by SA to log a unicast send operation. This event occurs after sending. This event is
 * used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is sent.
 * @param msgValue The value to be encoded and sent.
 * @param address The address of the destination within the SUT.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param msg The encoded message.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliMSend_m(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TriPortId port,
                TciValue msgValue,
                TriAddress address,
                TriStatus encoderFailure,
                TriMessage msg,
                TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs a broadcast send operation.
 * 
 * Shall be called by SA to log a broadcast send operation. This event occurs after sending. This
 * event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is sent.
 * @param msgValue The value to be encoded and sent.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param msg  The encoded message.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliMSend_m_BC(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId port,
                   TciValue msgValue,
                   TriStatus encoderFailure,
                   TriMessage msg,
                   TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs a multicast send operation.
 * 
 * Shall be called by SA to log a multicast send operation. This event occurs after sending. This event
 * is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is sent.
 * @param msgValue The value to be encoded and sent.
 * @param addresses The addresses of the destinations within the SUT.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param msg The encoded message.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliMSend_m_MC(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId port,
                   TciValue msgValue,
                   TriAddressList addresses,
                   TriStatus encoderFailure,
                   TriMessage msg,
                   TriStatus transmissionFailure)
{
}


/**
 * @brief CH logs a unicast send operation.
 * 
 * Shall be called by CH to log a unicast send operation. This event occurs after sending. This event is
 * used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is sent.
 * @param msgValue The value to be encoded and sent.
 * @param to The component which will receive the message.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliMSend_c(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TriPortId port,
                TciValue msgValue,
                TriComponentId to,
                TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a broadcast send operation.
 * 
 * Shall be called by CH to log a broadcast send operation. This event occurs after sending. This
 * event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is sent.
 * @param msgValue The value to be encoded and sent.
 * @param transmissionFailure  The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliMSend_c_BC(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId port,
                   TciValue msgValue,
                   TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a multicast send operation.
 * 
 * Shall be called by CH to log a multicast send operation. This event occurs after sending. This event
 * is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is sent.
 * @param msgValue The value to be encoded and sent.
 * @param toList The components which will receive the message.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliMSend_c_MC(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId port,
                   TciValue msgValue,
                   TriComponentIdList toList,
                   TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs the enqueuing of a message.
 * 
 * Shall be called by SA to log the enqueuing of a message. This event occurs after the message is
 * enqueued. This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is received.
 * @param msg The received encoded message.
 * @param address The address of the source within the SUT.
 */
void tliMDetected_m(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TriMessage msg,
                    TriAddress address)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.MDetected_m(am, ts, src, line, c, port, msg, address);
}


/** 
 * @brief CH logs the enqueuing of a message.
 * 
 * Shall be called by CH to log the enqueuing of a message. This event occurs after the message is
 * enqueued. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is received.
 * @param msgValue The received message.
 * @param from The component which sent the message.
 *
 * @todo Value type redefined to TciValue
 */
void tliMDetected_c(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TciValue msgValue,
                    TriComponentId from)
{
}


/**
 * @brief TE logs the mismatch of a template.
 * 
 * Shall be called by TE to log the mismatch of a template. This event occurs after checking a
 * template match. This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is received.
 * @param msgValue The message which is checked against the template.
 * @param msgTmpl The template used to check the message match.
 * @param diffs The difference/the mismatch between message and template
 * @param address The address of the source within the SUT.
 * @param addressTmpl The expected address of the source within the SUT.
 *
 * @todo Value type redefined to TciValue
 */
void tliMMismatch_m(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TciValue msgValue,
                    TciValueTemplate msgTmpl,
                    TciValueDifferenceList diffs,
                    TriAddress address,
                    TciValueTemplate addressTmpl)
{
}


/** 
 * @brief TE logs the mismatch of a template.
 * 
 * Shall be called by TE to log the mismatch of a template. This event occurs after checking a
 * template match. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is received.
 * @param msgValue The message which is checked against the template.
 * @param msgTmpl The template used to check the message match.
 * @param diffs The difference/the mismatch between message and template
 * @param from The component which sent the message.
 * @param fromTmpl The expected sender component.
 *
 * @todo Value type redefined to TciValue
 */
void tliMMismatch_c(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TciValue msgValue,
                    TciValueTemplate msgTmpl,
                    TciValueDifferenceList diffs,
                    TriComponentId from,
                    TciNonValueTemplate fromTmpl)
{
}


/** 
 * @brief TE logs the receive of a message.
 * 
 * Shall be called by TE to log the receive of a message. This event occurs after checking a template
 * match. This event is used for logging the communication with SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is received.
 * @param msgValue The message which is checked against the template.
 * @param msgTmpl The template used to check the message match.
 * @param address The address of the source within the SUT.
 * @param addressTmpl The expected address of the source within the SUT.
 *
 * @todo Value type redefined to TciValue
 */
void tliMReceive_m(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId port,
                   TciValue msgValue,
                   TciValueTemplate msgTmpl,
                   TriAddress address,
                   TciValueTemplate addressTmpl)
{
}


/** 
 * @brief TE logs the receive of a message.
 * 
 * Shall be called by TE to log the receive of a message. This event occurs after checking a template
 * match. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the message is received.
 * @param msgValue The message which is checked against the template.
 * @param msgTmpl The template used to check the message match.
 * @param from The component which sent the message.
 * @param fromTmpl The expected sender component.
 *
 * @todo Value type redefined to TciValue
 */
void tliMReceive_c(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId port,
                   TciValue msgValue,
                   TciValueTemplate msgTmpl,
                   TriComponentId from,
                   TciNonValueTemplate fromTmpl)
{
}


/** 
 * @brief SA logs a unicast call operation.
 * 
 * Shall be called by SA to log a unicast call operation. This event occurs after call execution. This
 * event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src  The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is invoked.
 * @param signature The signature of the called operation.
 * @param parsValue The parameters of the called operation.
 * @param address The address of the destination within the SUT.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param pars The encoded parameters.
 * @param transmissionFailure The failure message which might occur at transmission.
 */
void tliPrCall_m(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriPortId port,
                 TriSignatureId signature,
                 TciParameterListType parsValue,
                 TriAddress address,
                 TriStatus encoderFailure,
                 TriParameterList pars,
                 TriStatus transmissionFailure)
{
}


/**
 * @brief SA logs a broadcast call operation.
 * 
 * Shall be called by SA to log a broadcast call operation. This event occurs after call execution. This
 * event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is invoked.
 * @param signature The signature of the called operation.
 * @param parsValue The parameters of the called operation.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param pars The encoded parameters.
 * @param transmissionFailure 
 */
void tliPrCall_m_BC(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TriSignatureId signature,
                    TciParameterListType parsValue,
                    TriStatus encoderFailure,
                    TriParameterList pars,
                    TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs a multicast call operation.
 * 
 * Shall be called by SA to log a multicast call operation. This event occurs after call execution. This
 * event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is invoked.
 * @param signature The signature of the called operation.
 * @param parsValue The parameters of the called operation.
 * @param addresses The addresses of the destinations within the SUT.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param pars The encoded parameters.
 * @param transmissionFailure The failure message which might occur at transmission.
 */
void tliPrCall_m_MC(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TriSignatureId signature,
                    TciParameterListType parsValue,
                    TriAddressList addresses,
                    TriStatus encoderFailure,
                    TriParameterList pars,
                    TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a unicast call operation.
 * 
 * Shall be called by CH to log a unicast call operation. This event occurs after call execution. This
 * event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is invoked.
 * @param signature The signature of the called operation.
 * @param parsValue The parameters of the called operation.
 * @param to The component which will receive the message.
 * @param transmissionFailure The failure message which might occur at transmission.
 */
void tliPrCall_c(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriPortId port,
                 TriSignatureId signature,
                 TciParameterListType parsValue,
                 TriComponentId to,
                 TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a broadcast call operation.
 * 
 * Shall be called by CH to log a broadcast call operation. This event occurs after call execution. This
 * event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is invoked.
 * @param signature The signature of the called operation.
 * @param parsValue The parameters of the called operation.
 * @param transmissionFailure The failure message which might occur at transmission.
 */
void tliPrCall_c_BC(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TriSignatureId signature,
                    TciParameterListType parsValue,
                    TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a multicast call operation.
 * 
 * Shall be called by CH to log a multicast call operation. This event occurs after call execution. This
 * event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is invoked.
 * @param signature The signature of the called operation.
 * @param parsValue The parameters of the called operation.
 * @param toList The component which will receive the message.
 * @param transmissionFailure The failure message which might occur at transmission.
 */
void tliPrCall_c_MC(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TriSignatureId signature,
                    TciParameterListType parsValue,
                    TriComponentIdList toList,
                    TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs the getcall enqueue operation.
 * 
 * Shall be called by SA to log the getcall enqueue operation. This event occurs after call is enqueued.
 * This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is received.
 * @param signature The signature of the detected call.
 * @param pars The encoded parameters of detected call.
 * @param address The address of the destination within the SUT.
 */
void tliPrGetCallDetected_m(String am,
                            int ts,
                            String src,
                            int line,
                            TriComponentId c,
                            TriPortId port,
                            TriSignatureId signature,
                            TriParameterList pars,
                            TriAddress address)
{
}


/** 
 * @brief CH logs the getcall enqueue operation.
 * 
 * Shall be called by CH to log the getcall enqueue operation. This event occurs after call is enqueued.
 * This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is received.
 * @param signature The signature of the called operation.
 * @param parsValue The encoded parameters of detected call.
 * @param from The component which called the operation.
 *
 * @todo TciParameterList type redefined to TciParameterListType
 */
void tliPrGetCallDetected_c(String am,
                            int ts,
                            String src,
                            int line,
                            TriComponentId c,
                            TriPortId port,
                            TriSignatureId signature,
                            TciParameterListType parsValue,
                            TriComponentId from)
{
}


/** 
 * @brief TE logs the mismatch of a getcall.
 * 
 * Shall be called by TE to log the mismatch of a getcall. This event occurs after getcall is checked
 * against a template. This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is received.
 * @param signature The signature of the detected call.
 * @param parsValue The parameters of detected call.
 * @param parsTmpl The template used to check the parameter match.
 * @param diffs The difference/the mismatch between call and template
 * @param address The address of the source within the SUT.
 * @param addressTmpl The expected address of the source within the SUT.
 */
void tliPrGetCallMismatch_m(String am,
                            int ts,
                            String src,
                            int line,
                            TriComponentId c,
                            TriPortId port,
                            TriSignatureId signature,
                            TciParameterListType parsValue,
                            TciValueTemplate parsTmpl,
                            TciValueDifferenceList diffs,
                            TriAddress address,
                            TciValueTemplate addressTmpl)
{
}


/** 
 * @brief TE logs the mismatch of a getcall.
 * 
 * Shall be called by TE to log the mismatch of a getcall. This event occurs after getcall is checked
 * against a template. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is received.
 * @param signature The signature of the detected call.
 * @param parsValue The parameters of detected call.
 * @param parsTmpl The template used to check the parameter match.
 * @param diffs The difference/the mismatch between message and template
 * @param from The component which called the operation.
 * @param fromTmpl The expected calling component.
 */
void tliPrGetCallMismatch_c(String am,
                            int ts,
                            String src,
                            int line,
                            TriComponentId c,
                            TriPortId port,
                            TriSignatureId signature,
                            TciParameterListType parsValue,
                            TciValueTemplate parsTmpl,
                            TciValueDifferenceList diffs,
                            TriComponentId from,
                            TciNonValueTemplate fromTmpl)
{
}


/** 
 * @brief TE logs getting a call
 * 
 * Shall be called by TE to log getting a call. This event occurs after getcall has matched against a
 * template. This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is received.
 * @param signature The signature of the detected call.
 * @param parsValue The parameters of detected call.
 * @param parsTmpl The template used to check the parameter match.
 * @param address The address of the source within the SUT.
 * @param addressTmpl The expected address of the source within the SUT.
 */
void tliPrGetCall_m(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TriSignatureId signature,
                    TciParameterListType parsValue,
                    TciValueTemplate parsTmpl,
                    TriAddress address,
                    TciValueTemplate addressTmpl)
{
}


/** 
 * @brief TE logs getting a call.
 * 
 * Shall be called by TE to log getting a call. This event occurs after getcall has matched against a
 * template. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the call is received.
 * @param signature The signature of the detected call.
 * @param parsValue The parameters of detected call.
 * @param parsTmpl The template used to check the parameter match.
 * @param from The component which called the operation.
 * @param fromTmpl The expected calling component.
 */
void tliPrGetCall_c(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TriSignatureId signature,
                    TciParameterListType parsValue,
                    TciValueTemplate parsTmpl,
                    TriComponentId from,
                    TciNonValueTemplate fromTmpl)
{
}


/** 
 * @brief SA logs a unicast reply operation.
 * 
 * Shall be called by SA to log a unicast reply operation. This event occurs after reply execution. This
 * event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is sent.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The reply to be sent.
 * @param address The address of the destination within the SUT.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param repl The encoded reply.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo TriSignatureIdType type redefined as TriSignatureId
 *
 * @todo TciParameterList type redefined to TciParameterListType
 *
 * @todo Value type redefined to TciValue
 */
void tliPrReply_m(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId port,
                  TriSignatureId signature,
                  TciParameterListType parsValue,
                  TciValue replValue,
                  TriAddress address,
                  TriStatus encoderFailure,
                  TriParameter repl,
                  TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs a broadcast reply operation.
 * 
 * Shall be called by SA to log a broadcast reply operation. This event occurs after reply execution.
 * This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is sent.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The reply to be sent.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param repl The encoded reply.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo TriSignatureIdType type redefined as TriSignatureId
 *
 * @todo TciParameterList type redefined to TciParameterListType
 *
 * @todo Value type redefined to TciValue
 */
void tliPrReply_m_BC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue replValue,
                     TriStatus encoderFailure,
                     TriParameter repl,
                     TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs a multicast reply operation.
 * 
 * Shall be called by SA to log a multicast reply operation. This event occurs after reply execution.
 * This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is sent.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The reply to be sent.
 * @param addresses The addresses of the destinations within the SUT.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param repl The encoded reply.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo TriSignatureIdType type redefined as TriSignatureId
 *
 * @todo TciParameterList type redefined to TciParameterListType
 *
 * @todo Value type redefined to TciValue
 */
void tliPrReply_m_MC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue replValue,
                     TriAddressList addresses,
                     TriStatus encoderFailure,
                     TriParameter repl,
                     TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a unicast reply operation.
 * 
 * Shall be called by CH to log a unicast reply operation. This event occurs after reply execution. This
 * event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is sent.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The reply to be sent.
 * @param to The component which will receive the reply.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrReply_c(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId port,
                  TriSignatureId signature,
                  TciParameterListType parsValue,
                  TciValue replValue,
                  TriComponentId to,
                  TriStatus transmissionFailure)
{
}


/**
 * @brief CH logs a broadcast reply operation.
 * 
 * Shall be called by CH to log a broadcast reply operation. This event occurs after reply execution. This
 * event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is sent.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The reply to be sent.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrReply_c_BC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue replValue,
                     TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a multicast reply operation.
 * 
 * Shall be called by CH to log a multicast reply operation. This event occurs after reply execution.
 * This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is sent.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The reply to be sent.
 * @param toList The components which will receive the reply.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrReply_c_MC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue replValue,
                     TriComponentIdList toList,
                     TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs the getreply enqueue operation.
 * 
 * Shall be called by SA to log the getreply enqueue operation. This event occurs after getreply is
 * enqueued. This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is received.
 * @param signature The signature relating to the reply.
 * @param repl The received encoded reply.
 * @param address The address of the source within the SUT.
 */
void tliPrGetReplyDetected_m(String am,
                             int ts,
                             String src,
                             int line,
                             TriComponentId c,
                             TriPortId port,
                             TriSignatureId signature,
                             TriParameter repl,
                             TriAddress address)
{
}


/** 
 * @brief CH logs the getreply enqueue operation.
 * 
 * Shall be called by CH to log the getreply enqueue operation. This event occurs after getreply is
 * enqueued. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is received.
 * @param signature The signature relating to the reply.
 * @param replValue The received reply.
 * @param from The component which sent the reply.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrGetReplyDetected_c(String am,
                             int ts,
                             String src,
                             int line,
                             TriComponentId c,
                             TriPortId port,
                             TriSignatureId signature,
                             TciValue replValue,
                             TriComponentId from)
{
}


/** 
 * @brief TE logs the mismatch of a getreply operation.
 * 
 * Shall be called by TE to log the mismatch of a getreply operation. This event occurs after getreply is
 * checked against a template. This event is used for logging the communication with SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is received.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The template used to check the reply match.
 * @param replyTmpl The template used to check the reply match.
 * @param diffs The difference/the mismatch between reply and template
 * @param address The address of the source within the SUT.
 * @param addressTmpl The expected address of the source within the SUT.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrGetReplyMismatch_m(String am,
                             int ts,
                             String src,
                             int line,
                             TriComponentId c,
                             TriPortId port,
                             TriSignatureId signature,
                             TciParameterListType parsValue,
                             TciValue replValue,
                             TciValueTemplate replyTmpl,
                             TciValueDifferenceList diffs,
                             TriAddress address,
                             TciValueTemplate addressTmpl)
{
}


/** 
 * @brief TE logs the mismatch of a getreply operation.
 * 
 * Shall be called by TE to log the mismatch of a getreply operation. This event occurs after getreply is
 * checked against a template. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is received.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The received reply.
 * @param replyTmpl The template used to check the reply match.
 * @param diffs The difference/the mismatch between reply and template.
 * @param from The component which sent the reply.
 * @param fromTmpl The expected replying component.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrGetReplyMismatch_c(String am,
                             int ts,
                             String src,
                             int line,
                             TriComponentId c,
                             TriPortId port,
                             TriSignatureId signature,
                             TciParameterListType parsValue,
                             TciValue replValue,
                             TciValueTemplate replyTmpl,
                             TciValueDifferenceList diffs,
                             TriComponentId from,
                             TciNonValueTemplate fromTmpl)
{
}


/** 
 * @brief TE logs getting a reply.
 * 
 * Shall be called by TE to log getting a reply. This event occurs after getreply is checked against a
 * template. This event is used for logging the communication with SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is received.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The received reply.
 * @param replyTmpl The template used to check the reply match.
 * @param address The address of the source within the SUT.
 * @param addressTmpl The expected address of the source within the SUT.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrGetReply_m(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue replValue,
                     TciValueTemplate replyTmpl,
                     TriAddress address,
                     TciValueTemplate addressTmpl)
{
}


/** 
 * @brief TE logs getting a reply.
 * 
 * Shall be called by TE to log getting a reply. This event occurs after getreply is checked against a
 * template. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the reply is received.
 * @param signature The signature relating to the reply.
 * @param parsValue The signature parameters relating to the reply.
 * @param replValue The received reply.
 * @param replyTmpl The template used to check the reply match.
 * @param from The component which sent the reply.
 * @param fromTmpl The expected replying component.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrGetReply_c(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue replValue,
                     TciValueTemplate replyTmpl,
                     TriComponentId from,
                     TciNonValueTemplate fromTmpl)
{
}


/** 
 * @brief SA logs a unicast raise operation.
 * 
 * Shall be called by SA to log a unicast raise operation. This event occurs after reply execution. This
 * event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is sent.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The exception to be sent.
 * @param address The address of the destination within the SUT.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param exc The encoded exception.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrRaise_m(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId port,
                  TriSignatureId signature,
                  TciParameterListType parsValue,
                  TciValue excValue,
                  TriAddress address,
                  TriStatus encoderFailure,
                  TriException exc,
                  TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs a broadcast raise operation.
 * 
 * Shall be called by SA to log a broadcast raise operation. This event occurs after reply execution. This
 * event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is sent.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The exception to be sent.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param exc The encoded exception.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrRaise_m_BC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue excValue,
                     TriStatus encoderFailure,
                     TriException exc,
                     TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs a multicast raise operation.
 * 
 * Shall be called by SA to log a multicast raise operation. This event occurs after reply execution.
 * This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is sent.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The exception to be sent.
 * @param addresses The addresses of the destinations within the SUT.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param exc The encoded exception.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrRaise_m_MC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue excValue,
                     TriAddressList addresses,
                     TriStatus encoderFailure,
                     TriException exc,
                     TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a unicast raise operation.
 * 
 * Shall be called by CH to log a unicast raise operation. This event occurs after reply execution. This
 * event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is sent.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The exception to be sent.
 * @param to The component which will receive the reply.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrRaise_c(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId port,
                  TriSignatureId signature,
                  TciParameterListType parsValue,
                  TciValue excValue,
                  TriComponentId to,
                  TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a broadcast raise operation.
 * 
 * Shall be called by CH to log a broadcast raise operation. This event occurs after reply execution.
 * This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is sent.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The exception to be sent.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrRaise_c_BC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue excValue,
                     TriStatus transmissionFailure)
{
}


/** 
 * @brief CH logs a multicast raise operation.
 * 
 * Shall be called by CH to log a multicast raise operation. This event occurs after reply execution. This
 * event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is sent.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The exception to be sent.
 * @param toList The components which will receive the reply.
 * @param transmissionFailure The failure message which might occur at transmission.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrRaise_c_MC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId port,
                     TriSignatureId signature,
                     TciParameterListType parsValue,
                     TciValue excValue,
                     TriComponentIdList toList,
                     TriStatus transmissionFailure)
{
}


/** 
 * @brief SA logs the catch enqueue operation.
 * 
 * Shall be called by SA to log the catch enqueue operation. This event occurs after catch is
 * enqueued. This event is used for logging the communication with the SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is received.
 * @param signature The signature relating to the exception.
 * @param exc The catched exception.
 * @param address The address of the source within the SUT.
 */
void tliPrCatchDetected_m(String am,
                          int ts,
                          String src,
                          int line,
                          TriComponentId c,
                          TriPortId port,
                          TriSignatureId signature,
                          TriException exc,
                          TriAddress address)
{
}


/** 
 * @brief CH logs the catch enqueue operation.
 * 
 * Shall be called by CH to log the catch enqueue operation. This event occurs after catch is enqueued.
 * This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is received.
 * @param signature The signature relating to the exception.
 * @param excValue The catched exception.
 * @param from The component which sent the reply.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrCatchDetected_c(String am,
                          int ts,
                          String src,
                          int line,
                          TriComponentId c,
                          TriPortId port,
                          TriSignatureId signature,
                          TciValue excValue,
                          TriComponentId from)
{
}


/** 
 * @brief TE logs the mismatch of a catch operation.
 * 
 * Shall be called by TE to log the mismatch of a catch operation. This event occurs after catch is
 * checked against a template. This event is used for logging the communication with SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is received.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The received exception.
 * @param excTmpl The template used to check the exception match.
 * @param diffs The difference/the mismatch between exception and template
 * @param address The address of the source within the SUT.
 * @param addressTmpl The expected address of the source within the SUT.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrCatchMismatch_m(String am,
                          int ts,
                          String src,
                          int line,
                          TriComponentId c,
                          TriPortId port,
                          TriSignatureId signature,
                          TciParameterListType parsValue,
                          TciValue excValue,
                          TciValueTemplate excTmpl,
                          TciValueDifferenceList diffs,
                          TriAddress address,
                          TciValueTemplate addressTmpl)
{
}


/** 
 * @brief TE logs the mismatch of a catch operation.
 * 
 * Shall be called by TE to log the mismatch of a catch operation. This event occurs after catch is
 * checked against a template. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is received.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The received exception.
 * @param excTmpl The template used to check the exception match.
 * @param diffs The difference/the mismatch between exception and template
 * @param from The component which sent the reply.
 * @param fromTmpl The expected replying component.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrCatchMismatch_c(String am,
                          int ts,
                          String src,
                          int line,
                          TriComponentId c,
                          TriPortId port,
                          TriSignatureId signature,
                          TciParameterListType parsValue,
                          TciValue excValue,
                          TciValueTemplate excTmpl,
                          TciValueDifferenceList diffs,
                          TriComponentId from,
                          TciNonValueTemplate fromTmpl)
{
}


/** 
 * @brief SA logs catching an exception.
 * 
 * Shall be called by SA to log catching an exception. This event occurs after catch is checked against
 * a template. This event is used for logging the communication with SUT.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is received.
 * @param signature The signature relating to the exception.
 * @param parsValue  The signature parameters relating to the exception.
 * @param excValue The received exception.
 * @param excTmpl The template used to check the exception match.
 * @param address The address of the source within the SUT.
 * @param addressTmpl The expected address of the source within the SUT.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrCatch_m(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId port,
                  TriSignatureId signature,
                  TciParameterListType parsValue,
                  TciValue excValue,
                  TciValueTemplate excTmpl,
                  TriAddress address,
                  TciValueTemplate addressTmpl)
{
}


/** 
 * @brief CH logs catching an exception.
 * 
 * Shall be called by CH to log catching an exception. This event occurs after catch is checked against
 * a template. This event is used for logging the intercomponent communication.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is received.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 * @param excValue The received exception.
 * @param excTmpl The template used to check the exception match.
 * @param from The component which sent the reply.
 * @param fromTmpl The expected replying component.
 *
 * @todo Value type redefined to TciValue
 */
void tliPrCatch_c(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId port,
                  TriSignatureId signature,
                  TciParameterListType parsValue,
                  TciValue excValue,
                  TciValueTemplate excTmpl,
                  TriComponentId from,
                  TciNonValueTemplate fromTmpl)
{
}


/** 
 * @brief PA logs the detection of a catch timeout.
 * 
 * Shall be called by PA to log the detection of a catch timeout. This event occurs after the timeout is
 * enqueued.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is received.
 * @param signature The signature relating to the exception.
 */
void tliPrCatchTimeoutDetected(String am,
                               int ts,
                               String src,
                               int line,
                               TriComponentId c,
                               TriPortId port,
                               TriSignatureId signature)
{
}


/** 
 * @brief TE logs catching a timeout.
 * 
 * Shall be called by TE to log catching a timeout. This event occurs after the catch timeout has been
 * performed.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port via which the exception is received.
 * @param signature The signature relating to the exception.
 * @param parsValue The signature parameters relating to the exception.
 */
void tliPrCatchTimeout(String am,
                       int ts,
                       String src,
                       int line,
                       TriComponentId c,
                       TriPortId port,
                       TriSignatureId signature,
                       TciParameterListType parsValue)
{
}


/** 
 * @brief TE logs the create component operation.
 * 
 * Shall be called by TE to log the create component operation. This event occurs after component
 * creation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param comp The component which is created.
 * @param name The name of the component which is created.
 */
void tliCCreate(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TriComponentId comp,
                String name)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CCreate(am, ts, src, line, c, comp, name);
}


/** 
 * @brief TE logs the start component operation.
 * 
 * Shall be called by TE to log the start component operation. This event occurs after component start.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param comp The component which is started.
 * @param name The behaviour being started on the component.
 * @param parsValue The parameters of the started behaviour.
 */
void tliCStart(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriComponentId comp,
               TciBehaviourIdType name,
               TciParameterListType parsValue)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CStart(am, ts, src, line, c, comp, name, parsValue);
}


/**
 * @brief TE logs the running component operation.
 * 
 * Shall be called by TE to log the running component operation. This event occurs after component
 * running.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param comp The component which is checked to be running.
 * @param status The status of this component.
 */
void tliCRunning(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriComponentId comp,
                 ComponentStatus status)
{
}


/** 
 * @brief TE logs the alive component operation.
 * 
 * Shall be called by TE to log the alive component operation. This event occurs after component
 * alive.
 * 
 * @todo Function C declaration not in specification.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param comp The component which is checked to be running.
 * @param status The status of this component.
 */
void tliCAlive(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriComponentId comp,
               ComponentStatus status)
{
}


/** 
 * @brief TE logs the stop component operation.
 * 
 * Shall be called by TE to log the stop component operation. This event occurs after component stop.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param comp The component which is stopped.
 */
void tliCStop(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriComponentId comp)
{
}


/** 
 * @brief TE logs the mismatch of a done component operation.
 * 
 * Shall be called by TE to log the mismatch of a done component operation. This event occurs after
 * done is checked against a template.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param compTmpl The template used to check the done match.
 */
void tliCDoneMismatch(String am,
                      int ts,
                      String src,
                      int line,
                      TriComponentId c,
                      TciNonValueTemplate compTmpl)
{
}


/** 
 * @brief TE logs the done component operation.
 * 
 * Shall be called by TE to log the done component operation. This event occurs after the done
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param compTmpl The template used to check the done match.
 */
void tliCDone(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TciNonValueTemplate compTmpl)
{
}


/** 
 * @brief TE logs the mismatch of a killed component operation.
 * 
 * Shall be called by TE to log the mismatch of a killed component operation. This event occurs after
 * killed is checked against a template.
 * 
 * @todo Function C declaration not in specification.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param compTmpl The template used to check the done match.
 */
void tliCKilledMismatch(String am,
                        int ts,
                        String src,
                        int line,
                        TriComponentId c,
                        TciNonValueTemplate compTmpl)
{
}


/** 
 * @brief TE logs the killed component operation.
 * 
 * Shall be called by TE to log the killed component operation. This event occurs after the killed
 * operation.
 * 
 * @todo Function C declaration not in specification.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param compTmpl The template used to check the done match.
 */
void tliCKilled(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TciNonValueTemplate compTmpl)
{
}


/** 
 * @brief TE logs the termination of a component.
 * 
 * Shall be called by TE to log the termination of a component. This event occurs after the termination
 * of the component.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param verdict The verdict of the component.
 * 
 * @todo VerdictValue type redefined as TciVerdictValue
 */
void tliCTerminated(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TciVerdictValue verdict)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CTerminated(am, ts, src, line, c, verdict);
}


/** 
 * @brief CH logs the connect operation.
 * 
 * Shall be called by CH to log the connect operation. This event occurs after the connect operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param c1 The component of the first port to be connected.
 * @param port1 The first port to be connected.
 * @param c2 The component of the second port to be connected.
 * @param port2 The second port to be connected.
 */
void tliPConnect(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriComponentId c1,
                 TriPortId port1,
                 TriComponentId c2,
                 TriPortId port2)
{
}


/** 
 * @brief CH log the disconnect operation.
 * 
 * Shall be called by CH to log the disconnect operation. This event occurs after the disconnect
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param c1 The component of the first port to be disconnected.
 * @param port1 The first port to be disconnected.
 * @param c2 The component of the second port to be disconnected.
 * @param port2 The second port to be disconnected.
 */
void tliPDisconnect(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriComponentId c1,
                    TriPortId port1,
                    TriComponentId c2,
                    TriPortId port2)
{
}


/** 
 * @brief SA logs the map operation.
 * 
 * Shall be called by SA to log the map operation. This event occurs after the map operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param c1 The component of the first port to be mapped.
 * @param port1 The first port to be mapped.
 * @param c2 The component of the second port to be mapped.
 * @param port2 The second port to be mapped.
 */
void tliPMap(String am,
             int ts,
             String src,
             int line,
             TriComponentId c,
             TriComponentId c1,
             TriPortId port1,
             TriComponentId c2,
             TriPortId port2)
{
}


/** 
 * @brief SA logs the unmap operation.
 * 
 * Shall be called by SA to log the unmap operation. This event occurs after the unmap operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param c1 The component of the first port to be unmapped.
 * @param port1 The first port to be unmapped.
 * @param c2 The component of the second port to be unmapped.
 * @param port2 The second port to be unmapped.
 */
void tliPUnmap(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriComponentId c1,
               TriPortId port1,
               TriComponentId c2,
               TriPortId port2)
{
}


/** 
 * @brief TE logs the port clear operation.
 * 
 * Shall be called by TE to log the port clear operation. This event occurs after the port clear
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port to be cleared.
 */
void tliPClear(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriPortId port)
{
}


/** 
 * @brief TE logs the port start operation.
 * 
 * Shall be called by TE to log the port start operation. This event occurs after the port start operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c  The component which produces this event.
 * @param port The port to be started.
 */
void tliPStart(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriPortId port)
{
}


/** 
 * @brief TE logs the port stop operation.
 * 
 * Shall be called by TE to log the port stop operation. This event occurs after the port stop operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port to be stopped.
 */
void tliPStop(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriPortId port)
{
}


/** 
 * @brief TE logs the port stop operation.
 * 
 * Shall be called by TE to log the port stop operation. This event occurs after the port halt
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param port The port to be stopped.
 */
void tliPHalt(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriPortId port)
{
}


/** 
 * @brief CD logs the encode operation.
 * 
 * Shall be called by CD to log the encode operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param val The value to be encoded.
 * @param encoderFailure The failure message which might occur at encoding.
 * @param msg The encoded value.
 * @param codec The used encoder.
 *
 * @todo Value type redefined to TciValue
 */
void tliEncode(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TciValue val,
               TriStatus encoderFailure,
               TriMessage msg,
               String codec)
{
}


/** 
 * @brief CD logs the decode operation.
 * 
 * Shall be called by CD to log the decode operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param msg The value to be decoded.
 * @param decoderFailure The failure message which might occur at decoding.
 * @param val The decoded value.
 * @param codec The used decoder.
 *
 * @todo Value type redefined to TciValue
 */
void tliDecode(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriMessage msg,
               TriStatus decoderFailure,
               TciValue val,
               String codec)
{
}


/** 
 * @brief PA logs the detection of a timeout.
 * 
 * Shall be called by PA to log the detection of a timeout. This event occurs after timeout is
 * enqueued.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param timer The timer that timed out.
 */
void tliTTimeoutDetected(String am,
                         int ts,
                         String src,
                         int line,
                         TriComponentId c,
                         TriTimerId timer)
{
}


/** 
 * @brief TE logs a timeout mismatch.
 * 
 * Shall be called by TE to log a timeout mismatch. This event occurs after a timeout match failed.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param timerTmpl The timer template that did not match.
 */
void tliTTimeoutMismatch(String am,
                         int ts,
                         String src,
                         int line,
                         TriComponentId c,
                         TciNonValueTemplate timerTmpl)
{
}


/** 
 * @brief TE logs a timeout match.
 * 
 * Shall be called by TE to log a timeout match. This event occurs after a timeout matched.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param timerTmpl The timer template that matched.
 */
void tliTTimeout(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TciNonValueTemplate timerTmpl)
{
}


/** 
 * @brief PA logs the start of a timer.
 * 
 * Shall be called by PA to log the start of a timer. This event occurs after the start timer
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param timer The timer that is started.
 * @param dur The timer duration.
 */
void tliTStart(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriTimerId timer,
               TriTimerDuration dur)
{
}


/** 
 * @brief PA logs the stop of a timer.
 * 
 * Shall be called by PA to log the stop of a timer. This event occurs after the stop timer operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param timer The timer that is stopped.
 */
void tliTStop(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriTimerId timer)
{
}


/** 
 * @brief PA logs the reading of a timer.
 * 
 * Shall be called by PA to log the reading of a timer. This event occurs after the read timer
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param timer The timer that is started.
 * @param elapsed The elapsed time of the timer.
 */
void tliTRead(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriTimerId timer,
              TriTimerDuration elapsed)
{
}


/** 
 * @brief PA logs the running timer operation.
 * 
 * Shall be called by PA to log the running timer operation. This event occurs after the running timer
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param timer The timer which is checked to be running.
 * @param status The status of this component.
 */
void tliTRunning(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriTimerId timer,
                 TimerStatus status)
{
}


/** 
 * @brief TE logs the entering of a scope.
 * 
 * Shall be called by TE to log the entering of a scope. This event occurs after the scoped has been
 * entered.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param name The name of the scope.
 * @param parsValue The parameters of the scope.
 * @param kind The kind of the scope.
 */
void tliSEnter(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               String name,
               TciParameterListType parsValue,
               String kind)
{
}


/** 
 * @brief TE logs the leaving of a scope.
 * 
 * Shall be called by TE to log the leaving of a scope. This event occurs after the scoped has been
 * leaved.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param name The name of the scope.
 * @param returnValue The return value of the scope.
 * @param kind The kind of the scope.
 *
 * @todo Value type redefined to TciValue
 */
void tliSLeave(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               String name,
               TciValue returnValue,
               String kind)
{
}


/** 
 * @brief TE logs the modification of the value of a variable.
 * 
 * Shall be called by TE to log the modification of the value of a variable. This event occurs after the
 * values has been changed.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param name The name of the variable.
 * @param varValue The new value of the variable.
 *
 * @todo Value type redefined to TciValue
 */
void tliVar(String am,
            int ts,
            String src,
            int line,
            TriComponentId c,
            String name,
            TciValue varValue)
{
}


/** 
 * @brief TE logs the value of a module parameter.
 * 
 * Shall be called by TE to log the value of a module parameter. This event occurs after the
 * access to the value of a module parameter.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param name The name of the module parameter.
 * @param parValue The value of the module parameter.
 *
 * @todo Value type redefined to TciValue
 */
void tliModulePar(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  String name,
                  TciValue parValue)
{
}


/** 
 * @brief TE logs the getverdict operation.
 * 
 * Shall be called by TE to log the getverdict operation. This event occurs after the getverdict
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param verdict The current value of the local verdict.
 * 
 * @todo VerdictValue type redefined as TciVerdictValue
 */
void tliGetVerdict(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TciVerdictValue verdict)
{
}


/** 
 * @brief TE logs the setverdict operation.
 * 
 * Shall be called by TE to log the setverdict operation. This event occurs after the setverdict
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param verdict The value to be set to the local verdict.
 * 
 * @todo VerdictValue type redefined as TciVerdictValue
 */
void tliSetVerdict(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TciVerdictValue verdict)
{
}


/** 
 * @brief TM logs the TTCN-3 statement log.
 * 
 * Shall be called by TM to log the TTCN-3 statement log. This event occurs after the TTCN-3 log
 * operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param log The string to be logged.
 *
 * @todo Value type redefined to TciValue
 */
void tliLog(String am,
            int ts,
            String src,
            int line,
            TriComponentId c,
            TciValue log[])
{
}


/** 
 * @brief TE logs entering an alt.
 * 
 * Shall be called by TE to log entering an alt. This event occurs after an alt has been entered.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliAEnter(String am,
               int ts,
               String src,
               int line,
               TriComponentId c)
{
}


/** 
 * @brief TE logs leaving an alt.
 * 
 * Shall be called by TE to log leaving an alt. This event occurs after the alt has been leaved.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliALeave(String am,
               int ts,
               String src,
               int line,
               TriComponentId c)
{
}


/** 
 * @brief TE logs the nomatch of an alt.
 * 
 * Shall be called by TE to log the nomatch of an alt. This event occurs after the alt has not matched.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliANomatch(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c)
{
}


/** 
 * @brief TE logs repeating an alt.
 * 
 * Shall be called by TE to log repeating an alt. This event occurs when the alt is been repeated.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliARepeat(String am,
                int ts,
                String src,
                int line,
                TriComponentId c)
{
}


/** 
 * @brief TE logs entering the default section.
 * 
 * Shall be called by TE to log entering the default section. This event occurs after the default
 * section has been entered.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliADefaults(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c)
{
}


/** 
 * @brief TE logs the activation of a default.
 * 
 * Shall be called by TE to log the activation of a default. This event occurs after the default activation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param name The name of the default.
 * @param pars The parameter of the default.
 * @param ref The resulting default reference.
 *
 * @todo Value type redefined to TciValue
 */
void tliAActivate(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  String name,
                  TciParameterListType pars,
                  TciValue ref)
{
}


/** 
 * @brief TE logs the deactivation of a default.
 * 
 * Shall be called by TE to log the deactivation of a default. This event occurs after the default
 * deactivation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param ref The resulting default reference.
 *
 * @todo Value type redefined to TciValue
 */
void tliADeactivate(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TciValue ref)
{
}


/** 
 * @brief TE logs that the component awaits events for a new snapshot.
 * 
 * Shall be called by TE to log that the component awaits events for a new snapshot.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 */
void tliAWait(String am,
              int ts,
              String src,
              int line,
              TriComponentId c)
{
}


/** 
 * @brief TE logs that the component executed an SUT action.
 * 
 * Shall be called by TE to log that the component executed an SUT action.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param action The action to be performed.
 */
void tliAction(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               String action)
{
}


/** 
 * @brief TE logs that the component successfully executed a match operation.
 * 
 * Shall be called by TE to log that the component successfully executed a match operation.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param expr The expression to be matched with tmpl.
 * @param tmpl The template to be matched with expr.
 */
void tliMatch(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TciValue expr,
              TciValueTemplate tmpl)
{
}


/**
 * @brief TE logs that the component unsuccessfully executed a match operation.
 * 
 * Shall be called by TE to log that the component unsuccessfully executed a match operation
 * - a mismatch occurred.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param expr The expression to be matched with tmpl
 * @param tmpl The template to be matched with expr
 * @param diffs The difference/the mismatch between expr and tmpl
 */
void tliMatchMismatch(String am,
                      int ts,
                      String src,
                      int line,
                      TriComponentId c,
                      TciValue expr,
                      TciValueTemplate tmpl,
                      TciValueDifferenceList diffs)
{
}


/**
 * @brief TE logs additional information during test execution.
 * 
 * Can be called by TE to log additional information during test execution. The generation of this
 * event is tool dependent as well as the usage of the parameters level and info.
 * 
 * @param am An additional message.
 * @param ts The time when the event is produced.
 * @param src The source file of the test specification.
 * @param line The line number where the request is performed.
 * @param c The component which produces this event.
 * @param level The information level.
 * @param info The information.
 */
void tliInfo(String am,
             int ts,
             String src,
             int line,
             TriComponentId c,
             int level,
             String info)
{
}
