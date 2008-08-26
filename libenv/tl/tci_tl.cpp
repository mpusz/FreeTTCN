//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcnenv (Free TTCN Environment) library.

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


extern "C" {
#include <freettcn/ttcn3/tci_tl.h>
}
#include "freettcn/tl/tl.h"


void tliTcExecute(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TciTestCaseIdType tcId,
                  TciParameterListType tciPars,
                  TriTimerDuration dur)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcExecute(am, ts, src, line, c, tcId, tciPars, dur);
}


void tliTcStart(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TciTestCaseIdType tcId,
                TciParameterListType tciPars,
                TriTimerDuration dur)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcStart(am, ts, src, line, c, tcId, tciPars, dur);
}


void tliTcStop(String am,
               int ts,
               String src,
               int line,
               TriComponentId c)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcStop(am, ts, src, line, c);
}


void tliTcStarted(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TciTestCaseIdType tcId,
                  TciParameterListType tciPars,
                  TriTimerDuration dur)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcStarted(am, ts, src, line, c, tcId, tciPars, dur);
}


void tliTcTerminated(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TciTestCaseIdType tcId,
                     TciParameterListType tciPars,
                     VerdictValue verdict)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TcTerminated(am, ts, src, line, c, tcId, tciPars, verdict);
}


void tliCtrlStart(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CtrlStart(am, ts, src, line, c);
}


void tliCtrlStop(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CtrlStop(am, ts, src, line, c);
}


void tliCtrlTerminated(String am,
                       int ts,
                       String src,
                       int line,
                       TriComponentId c)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CtrlTerminated(am, ts, src, line, c);
}


void tliMSend_m(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TriPortId at,
                TriPortId to,
                Value msgValue,
                Value addrValue,
                TciStatus encoderFailure,
                TriMessage msg,
                TriAddress address,
                TriStatus transmissionFailure)
{
}


void tliMSend_m_BC(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId at,
                   TriPortId to,
                   Value msgValue,
                   TciStatus encoderFailure,
                   TriMessage msg,
                   TriStatus transmissionFailure)
{
}


void tliMSend_m_MC(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId at,
                   TriPortId to,
                   Value msgValue,
                   TciValueList addrValues,
                   TciStatus encoderFailure,
                   TriMessage msg,
                   TriAddressList addresses,
                   TriStatus transmissionFailure)
{
}


void tliMSend_c(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TriPortId at,
                TriPortId to,
                Value msgValue,
                TriStatus transmissionFailure)
{
}


void tliMSend_c_BC(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId at,
                   TriPortIdList to,
                   Value msgValue,
                   TriStatus transmissionFailure)
{
}


void tliMSend_c_MC(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId at,
                   TriPortIdList to,
                   Value msgValue,
                   TriStatus transmissionFailure)
{
}


void tliMDetected_m(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    TriPortId from,
                    TriMessage msg,
                    TriAddress address)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.MDetected_m(am, ts, src, line, c, at, from, msg, address);
}


void tliMDetected_c(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    TriPortId from,
                    Value msgValue)
{
}


void tliMMismatch_m(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    Value msgValue,
                    TciValueTemplate msgTmpl,
                    TciValueDifferenceList diffs,
                    Value addrValue,
                    TciValueTemplate addressTmpl)
{
}


void tliMMismatch_c(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    Value msgValue,
                    TciValueTemplate msgTmpl,
                    TciValueDifferenceList diffs,
                    TriComponentId from,
                    TciNonValueTemplate fromTmpl)
{
}


void tliMReceive_m(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId at,
                   Value msgValue,
                   TciValueTemplate msgTmpl,
                   Value addrValue,
                   TciValueTemplate addressTmpl)
{
}


void tliMReceive_c(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   TriPortId at,
                   Value msgValue,
                   TciValueTemplate msgTmpl,
                   TriComponentId from,
                   TciNonValueTemplate fromTmpl)
{
}


void tliPrCall_m(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriPortId at,
                 TriSignatureId signature,
                 TciParameterListType tciPars,
                 Value addrValue,
                 TriStatus encoderFailure,
                 TriParameterList triPars,
                 TriAddress address,
                 TciStatus transmissionFailure)
{
}


void tliPrCall_m_BC(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    TriPortId to,
                    TriSignatureId signature,
                    TciParameterListType tciPars,
                    TciStatus encoderFailure,
                    TriParameterList triPars,
                    TriStatus transmissionFailure)
{
}


void tliPrCall_m_MC(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    TriPortId to,
                    TriSignatureId signature,
                    TciParameterListType tciPars,
                    TciValueList addrValues,
                    TciStatus encoderFailure,
                    TriParameterList triPars,
                    TriAddressList addresses,
                    TriStatus transmissionFailure)
{
}


void tliPrCall_c(String am,
                 int ts,String src,
                 int line,
                 TriComponentId c,
                 TriPortId at,
                 TriSignatureId signature,
                 TciParameterListType tciPars,
                 TriStatus transmissionFailure)
{
}


void tliPrCall_c_BC(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    TriPortIdList to,
                    TriSignatureId signature,
                    TciParameterListType tciPars,
                    TriStatus transmissionFailure)
{
}


void tliPrCall_c_MC(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    TriPortIdList to,
                    TriSignatureId signature,
                    TciParameterListType tciPars,
                    TriStatus transmissionFailure)
{
}


void tliPrGetCallDetected_m(String am,
                            int ts,
                            String src,
                            int line,
                            TriComponentId c,
                            TriPortId at,
                            TriPortId from,
                            TriSignatureId signature,
                            TriParameterList triPars,
                            TriAddress address)
{
}


void tliPrGetCallDetected_c(String am,
                            int ts,
                            String src,
                            int line,
                            TriComponentId c,
                            TriPortId at,
                            TriPortId from,
                            TriSignatureId signature,
                            TciParameterListType tciPars)
{
}


void tliPrGetCallMismatch_m(String am,
                            int ts,
                            String src,
                            int line,
                            TriComponentId c,
                            TriPortId at,
                            TriSignatureId signature,
                            TciParameterListType tciPars,
                            TciValueTemplate parsTmpl,
                            TciValueDifferenceList diffs,
                            Value addrValue,
                            TciValueTemplate addressTmpl)
{
}


void tliPrGetCallMismatch_c(String am,
                            int ts,
                            String src,
                            int line,
                            TriComponentId c,
                            TriPortId at,
                            TriSignatureId signature,
                            TciParameterListType tciPars,
                            TciValueTemplate parsTmpl,
                            TciValueDifferenceList diffs,
                            TriComponentId from,
                            TciNonValueTemplate fromTmpl)
{
}


void tliPrGetCall_m(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    TriSignatureId signature,
                    TciParameterListType tciPars,
                    TciValueTemplate parsTmpl,
                    Value addrValue,
                    TciValueTemplate addressTmpl)
{
}


void tliPrGetCall_c(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId at,
                    TriSignatureId signature,
                    TciParameterListType tciPars,
                    TciValueTemplate parsTmpl,
                    TriComponentId from,
                    TciNonValueTemplate fromTmpl)
{
}


void tliPrReply_m(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId at,
                  TriPortId to,
                  TriSignatureId signature,
                  TciParameterListType tciPars,
                  Value replValue,
                  Value addrValue,
                  TciStatus encoderFailure,
                  TriParameterList triPars,
                  TriParameter repl,
                  TriAddress address,
                  TriStatus transmissionFailure)
{
}


void tliPrReply_m_BC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriPortId to,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     Value replValue,
                     TciStatus encoderFailure,
                     TriParameterList triPars,
                     TriParameter repl,
                     TriStatus transmissionFailure)
{
}


void tliPrReply_m_MC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriPortId to,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     Value replValue,
                     TciValueList addrValues,
                     TriStatus encoderFailure,
                     TriParameterList triPars,
                     TriParameter repl,
                     TriAddressList addresses,
                     TciStatus transmissionFailure)
{
}


void tliPrReply_c(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId at,
                  TriPortId to,
                  TriSignatureId signature,
                  TciParameterListType tciPars,
                  Value replValue,
                  TriStatus transmissionFailure)
{
}


void tliPrReply_c_BC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriPortIdList to,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     Value replValue,
                     TriStatus transmissionFailure)
{
}


void tliPrReply_c_MC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriPortIdList to,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     Value replValue,
                     TriStatus transmissionFailure)
{
}


void tliPrGetReplyDetected_m(String am,
                             int ts,
                             String src,
                             int line,
                             TriComponentId c,
                             TriPortId at,
                             TriPortId from,
                             TriSignatureId signature,
                             TriParameterList triPars,
                             TriParameter repl,
                             TriAddress address)
{
}


void tliPrGetReplyDetected_c(String am,
                             int ts,
                             String src,
                             int line,
                             TriComponentId c,
                             TriPortId at,
                             TriPortId from,
                             TriSignatureId signature,
                             TciParameterListType tciPars,
                             Value replValue)
{
}


void tliPrGetReplyMismatch_m(String am,
                             int ts,
                             String src,
                             int line,
                             TriComponentId c,
                             TriPortId at,
                             TriSignatureId signature,
                             TciParameterListType tciPars,
                             TciValueTemplate parsTmpl,
                             Value replValue,
                             TciValueTemplate replyTmpl,
                             TciValueDifferenceList diffs,
                             Value addrValue,
                             TciValueTemplate addressTmpl)
{
}


void tliPrGetReplyMismatch_c(String am,
                             int ts,
                             String src,
                             int line,
                             TriComponentId c,
                             TriPortId at,
                             TriSignatureId signature,
                             TciParameterListType tciPars,
                             TciValueTemplate parsTmpl,
                             Value replValue,
                             TciValueTemplate replyTmpl,
                             TciValueDifferenceList diffs,
                             TriComponentId from,
                             TciNonValueTemplate fromTmpl)
{
}


void tliPrGetReply_m(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     TciValueTemplate parsTmpl,
                     Value replValue,
                     TciValueTemplate replyTmpl,
                     Value addrValue,
                     TciValueTemplate addressTmpl)
{
}


void tliPrGetReply_c(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     TciValueTemplate parsTmpl,
                     Value replValue,
                     TciValueTemplate replyTmpl,
                     TriComponentId from,
                     TciNonValueTemplate fromTmpl)
{
}


void tliPrRaise_m(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId at,
                  TriPortId to,
                  TriSignatureId signature,
                  TciParameterListType tciPars,
                  Value excValue,
                  Value addrValue,
                  TciStatus encoderFailure,
                  TriException exc,
                  TriAddress address,
                  TriStatus transmissionFailure)
{
}


void tliPrRaise_m_BC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriPortId to,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     Value excValue,
                     TciStatus encoderFailure,
                     TriException exc,
                     TriStatus transmissionFailure)
{
}


void tliPrRaise_m_MC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriPortId to,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     Value excValue,
                     TciValueList addrValues,
                     TciStatus encoderFailure,
                     TriException exc,
                     TriAddressList addresses,
                     TriStatus transmissionFailure)
{
}


void tliPrRaise_c(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId at,
                  TriPortId to,
                  TriSignatureId signature,
                  TciParameterListType tciPars,
                  Value excValue,
                  TriStatus transmissionFailure)
{
}


void tliPrRaise_c_BC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriPortIdList to,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     Value excValue,
                     TriStatus transmissionFailure)
{
}


void tliPrRaise_c_MC(String am,
                     int ts,
                     String src,
                     int line,
                     TriComponentId c,
                     TriPortId at,
                     TriPortIdList to,
                     TriSignatureId signature,
                     TciParameterListType tciPars,
                     Value excValue,
                     TriStatus transmissionFailure)
{
}


void tliPrCatchDetected_m(String am,
                          int ts,
                          String src,
                          int line,
                          TriComponentId c,
                          TriPortId at,
                          TriPortId from,
                          TriSignatureId signature,
                          TriException exc,
                          TriAddress address)
{
}


void tliPrCatchDetected_c(String am,
                          int ts,
                          String src,
                          int line,
                          TriComponentId c,
                          TriPortId at,
                          TriPortId from,
                          TriSignatureId signature,
                          Value excValue)
{
}


void tliPrCatchMismatch_m(String am,
                          int ts,
                          String src,
                          int line,
                          TriComponentId c,
                          TriPortId at,
                          TriSignatureId signature,
                          Value excValue,
                          TciValueTemplate excTmpl,
                          TciValueDifferenceList diffs,
                          Value addrValue,
                          TciValueTemplate addressTmpl)
{
}


void tliPrCatchMismatch_c(String am,
                          int ts,
                          String src,
                          int line,
                          TriComponentId c,
                          TriPortId at,
                          TriSignatureId signature,
                          Value excValue,
                          TciValueTemplate excTmpl,
                          TciValueDifferenceList diffs,
                          TriComponentId from,
                          TciNonValueTemplate fromTmpl)
{
}


void tliPrCatch_m(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId at,
                  TriSignatureId signature,
                  Value excValue,
                  TciValueTemplate excTmpl,
                  Value addrValue,
                  TciValueTemplate addressTmpl)
{
}


void tliPrCatch_c(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  TriPortId at,
                  TriSignatureId signature,
                  Value excValue,
                  TciValueTemplate excTmpl,
                  TriComponentId from,
                  TciNonValueTemplate fromTmpl)
{
}


void tliPrCatchTimeoutDetected(String am,
                               int ts,
                               String src,
                               int line,
                               TriComponentId c,
                               TriPortId at,
                               TriSignatureId signature)
{
}


void tliPrCatchTimeout(String am,
                       int ts,
                       String src,
                       int line,
                       TriComponentId c,
                       TriPortId at,
                       TriSignatureId signature)
{
}


void tliCCreate(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TriComponentId comp,
                String name,
                Boolean alive)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CCreate(am, ts, src, line, c, comp, name, alive);
}


void tliCStart(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriComponentId comp,
               TciBehaviourIdType name,
               TciParameterListType tciPars)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CStart(am, ts, src, line, c, comp, name, tciPars);
}


void tliCRunning(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriComponentId comp,
                 ComponentStatus status)
{
}


void tliCAlive(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriComponentId comp,
               ComponentStatus status)
{
}


void tliCStop(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriComponentId comp)
{
}


/** @todo  Description */
void tliCKill(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriComponentId comp)
{
}


void tliCDoneMismatch(String am,
                      int ts,
                      String src,
                      int line,
                      TriComponentId c,
                      TriComponentId comp,
                      TciNonValueTemplate compTmpl)
{
}


void tliCDone(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TciNonValueTemplate compTmpl)
{
}


void tliCKilledMismatch(String am,
                        int ts,
                        String src,
                        int line,
                        TriComponentId c,
                        TriComponentId comp,
                        TciNonValueTemplate compTmpl)
{
}


void tliCKilled(String am,
                int ts,
                String src,
                int line,
                TriComponentId c,
                TciNonValueTemplate compTmpl)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CKilled(am, ts, src, line, c, compTmpl);
}


void tliCTerminated(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    VerdictValue verdict)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.CTerminated(am, ts, src, line, c, verdict);
}


void tliPConnect(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriPortId port1,
                 TriPortId port2)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.PConnect(am, ts, src, line, c, port1, port2);
}


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
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.PDisconnect(am, ts, src, line, c, c1, port1, c2, port2);
}


void tliPMap(String am,
             int ts,
             String src,
             int line,
             TriComponentId c,
             TriPortId port1,
             TriPortId port2)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.PMap(am, ts, src, line, c, port1, port2);
}


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
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.PUnmap(am, ts, src, line, c, c1, port1, c2, port2);
}


void tliPClear(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriPortId port)
{
}


void tliPStart(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriPortId port)
{
}


void tliPStop(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriPortId port)
{
}


void tliPHalt(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriPortId port)
{
}


void tliEncode(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               Value val,
               TciStatus encoderFailure,
               TriMessage msg,
               String codec)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.Encode(am, ts, src, line, c, val, encoderFailure, msg, codec);
}


void tliDecode(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriMessage msg,
               TciStatus decoderFailure,
               Value val,
               String codec)
{
}


void tliTTimeoutDetected(String am,
                         int ts,
                         String src,
                         int line,
                         TriComponentId c,
                         TriTimerId timer)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TTimeoutDetected(am, ts, src, line, c, timer);
}


void tliTTimeoutMismatch(String am,
                         int ts,
                         String src,
                         int line,
                         TriComponentId c,
                         TriTimerId timer,
                         TciNonValueTemplate timerTmpl)
{
}


void tliTTimeout(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriTimerId timer,
                 TciNonValueTemplate timerTmpl)
{
}


void tliTStart(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               TriTimerId timer,
               TriTimerDuration dur)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TStart(am, ts, src, line, c, timer, dur);
}


void tliTStop(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriTimerId timer,
              TriTimerDuration dur)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TStop(am, ts, src, line, c, timer);
}


void tliTRead(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              TriTimerId timer,
              TriTimerDuration elapsed)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TRead(am, ts, src, line, c, timer, elapsed);
}


void tliTRunning(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c,
                 TriTimerId timer,
                 TimerStatus status)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.TRunning(am, ts, src, line, c, timer, status);
}


void tliSEnter(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               QualifiedName name,
               TciParameterListType tciPars,
               String kind)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.SEnter(am, ts, src, line, c, name, tciPars, kind);
}


void tliSLeave(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               QualifiedName name,
               TciParameterListType tciPars,
               Value returnValue,
               String kind)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.SLeave(am, ts, src, line, c, name, tciPars, returnValue, kind);
}


void tliVar(String am,
            int ts,
            String src,
            int line,
            TriComponentId c,
            QualifiedName name,
            Value varValue)
{
}


void tliModulePar(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  QualifiedName name,
                  Value parValue)
{
}


void tliGetVerdict(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   VerdictValue verdict)
{
}


void tliSetVerdict(String am,
                   int ts,
                   String src,
                   int line,
                   TriComponentId c,
                   VerdictValue verdict)
{
  freettcn::TL::CTestLogging &tl = freettcn::TL::CTestLogging::Instance();
  tl.VerdictSet(am, ts, src, line, c, verdict);
}


void tliLog(String am,
            int ts,
            String src,
            int line,
            TriComponentId c,
            String log)
{
}


void tliAEnter(String am,
               int ts,
               String src,
               int line,
               TriComponentId c)
{
}


void tliALeave(String am,
               int ts,
               String src,
               int line,
               TriComponentId c)
{
}


void tliANomatch(String am,
                 int ts,
                 String src,
                 int line,
                 TriComponentId c)
{
}


void tliARepeat(String am,
                int ts,
                String src,
                int line,
                TriComponentId c)
{
}


void tliADefaults(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c)
{
}


void tliAActivate(String am,
                  int ts,
                  String src,
                  int line,
                  TriComponentId c,
                  QualifiedName name,
                  TciParameterListType tciPars,
                  Value ref)
{
}


void tliADeactivate(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    Value ref)
{
}


void tliAWait(String am,
              int ts,
              String src,
              int line,
              TriComponentId c)
{
}


void tliAction(String am,
               int ts,
               String src,
               int line,
               TriComponentId c,
               String action)
{
}


void tliMatch(String am,
              int ts,
              String src,
              int line,
              TriComponentId c,
              Value expr,
              TciValueTemplate tmpl)
{
}


void tliMatchMismatch(String am,
                      int ts,
                      String src,
                      int line,
                      TriComponentId c,
                      Value expr,
                      TciValueTemplate tmpl,
                      TciValueDifferenceList diffs)
{
}


void tliInfo(String am,
             int ts,
             String src,
             int line,
             TriComponentId c,
             int level,
             String info)
{
}
