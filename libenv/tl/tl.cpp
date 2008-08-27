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

/**
 * @file   tl.cpp
 * @author Mateusz Pusz
 * @date   Fri Apr 20 08:11:42 2007
 * 
 * @brief  
 * 
 * 
 */


#include "freettcn/tl/tl.h"
#include <freettcn/tools/tciValueDumper.h>
#include <freettcn/tools/logMask.h>
#include <freettcn/tools/timeStampMgr.h>
#include <freettcn/tools/exception.h>
extern "C" {
#include "freettcn/ttcn3/tci_value.h"
}
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>


using namespace std;


freettcn::TL::CLogger::CData::CData(int ts, const char *src, int line, const char *am, freettcn::CEntity::TType entity, unsigned short logIdx, const char *title):
  _ts(ts), _src(src ? src : ""), _line(line), _am(am ? am : ""), _entity(entity), _logIdx(logIdx), _title(title)
{
}


int freettcn::TL::CLogger::CData::TimeStamp() const
{
  return _ts;
}

const std::string &freettcn::TL::CLogger::CData::Source() const
{
  return _src;
}

int freettcn::TL::CLogger::CData::SourceLine() const
{
  return _line;
}

const std::string &freettcn::TL::CLogger::CData::AdditionalMessage() const
{
  return _am;
}

freettcn::CEntity::TType freettcn::TL::CLogger::CData::Entity() const
{
  return _entity;
}

unsigned short freettcn::TL::CLogger::CData::LogIdx() const
{
  return _logIdx;
}

const std::string &freettcn::TL::CLogger::CData::Title() const
{
  return _title;
}


void freettcn::TL::CLogger::CData::LineAdd(const char *title, const char *value)
{
  TLineData data;
  data._title = title;
  data._value = value;
  
  lines.push_back(data);
}


unsigned short freettcn::TL::CLogger::CData::LineNum() const
{
  return lines.size();
}


const std::string &freettcn::TL::CLogger::CData::LineTitle(unsigned short lineIdx) const
{
  return lines[lineIdx]._title;
}


const std::string &freettcn::TL::CLogger::CData::LineValue(unsigned short lineIdx) const
{
  return lines[lineIdx]._value;
}




freettcn::TL::CLogger::CLogger(freettcn::CTimeStampMgr &ts):
  _ts(ts)
{
}

freettcn::TL::CLogger::~CLogger()
{
}

freettcn::CTimeStampMgr &freettcn::TL::CLogger::TimeStampMgr() const
{
  return _ts;
}

void freettcn::TL::CLogger::Push(const freettcn::TL::CLogger::CData *data)
{
  const unsigned short width = 15;
  const char *entityStr[] = {
    "TE",
    "TM",
    "CH",
    "CD",
    "SA",
    "PA",
    "TL"
  };
  ostringstream ostring;
  
  ostring.setf(ios::left, ios::adjustfield);
  ostring << "[" << TimeStampMgr().String(data->TimeStamp()) << "][" << entityStr[data->Entity()] << "] " << data->Title() << ":" << endl;
  if (data->Source() != "") {
    ostring << "  - " << setw(width) << "Source" << ": " << data->Source() << ":" << data->SourceLine() << endl;
  }
  for(unsigned short i=0; i<data->LineNum(); i++)
    ostring << "  - " << setw(width) << data->LineTitle(i) << ": " << data->LineValue(i) << endl;
  
  cout << ostring.str() << endl;
  
  delete data;                                    /**< can be stored for further logging/filtering purposes */
}



freettcn::TL::CTestLogging *freettcn::TL::CTestLogging::_instance = 0;

freettcn::TL::CTestLogging &freettcn::TL::CTestLogging::Instance()
{
  if (_instance)
    return *_instance;
  
  throw ENotInitialized(E_DATA, "TL instance not initialized!!!");
}

freettcn::TL::CTestLogging::CTestLogging(CLogger &logger):
  _logger(logger)
{
  _instance = this;
}

freettcn::TL::CTestLogging::~CTestLogging()
{
  _instance = 0;
}


freettcn::TL::CLogger &freettcn::TL::CTestLogging::Logger() const
{
  return _logger;
}




/* ********************** L O G   F U N C T I O N S *********************************** */

const char *freettcn::TL::CTestLogging::Buffer2String(const BinaryString &binStr, char *str) const
{
  str[0] = 0;
  
  for(int i=0; i<ceil(binStr.bits / 8.0); i++) {
    if (!(i % 8)) {
      if (!(i % 16))
        sprintf(str, "%s\n", str);
      else
        sprintf(str, "%s ", str);
    }
    else
      sprintf(str, "%s ", str);
    sprintf(str, "%s %02x", str, static_cast<unsigned short>(binStr.data[i]));
  }
  
  return str;
}


const char *freettcn::TL::CTestLogging::InstanceId2String(const BinaryString &inst, char *str) const
{
  str[0] = 0;
  
  if (inst.bits)
    for(int i=0; i<inst.bits / 8; i++)
      sprintf(str, "%s%s%02x", str, i ? "" : "0x", static_cast<unsigned short>(inst.data[i]));
  
  return str;
}


const char *freettcn::TL::CTestLogging::TriComponentId2String(const TriComponentId &comp, char *str) const
{
  char str1[256];
  char str2[256];
  
  if (strcmp(comp.compName, ""))
    sprintf(str2, " '%s'", comp.compName);
  else
    str2[0] = 0;
  
  sprintf(str, "<%s.%s> %s%s", comp.compType.moduleName, comp.compType.objectName,
          InstanceId2String(comp.compInst, str1), str2);
  
  return str;
}


const char *freettcn::TL::CTestLogging::TriPortId2String(const TriPortId &port, char *str) const
{
  char str1[256];
  sprintf(str, "[%s]:%s", TriComponentId2String(port.compInst, str1), port.portName);
  if (port.portIndex)
    sprintf(str, "%s[%li]", str, port.portIndex);
  return str;
}


void freettcn::TL::CTestLogging::TcExecute(const char *am, int ts, const char *src, int line,
                                           const TriComponentId &c,
                                           const TciTestCaseIdType &tcId,
                                           const TciParameterListType &pars,
                                           TriTimerDuration dur) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_TC_EXECUTE,
                                                                        "Testcase execute request");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  sprintf(str, "%s.%s", tcId.moduleName, tcId.objectName);
  data->LineAdd("Testcase Id", str);
  
//   std::vector<std::string> params(pars.length);
//   for(unsigned short i=0; i<pars.length; i++) {
//     sprintf(str, "[%5s] %s.%s: %u", pars.parList[i].mode == TRI_IN ? "IN" : pars.parList[i].mode == TRI_OUT ? "OUT" : "INOUT",
//             pars.parList[i].par.);
//     params[i] = str;
//   }
//   data->LineAdd("Parameters", params);

  sprintf(str, "%f", dur);
  data->LineAdd("Duration", str);
  
  Logger().Push(data);
}  


void freettcn::TL::CTestLogging::TcStart(const char *am, int ts, const char *src, int line,
                                         const TriComponentId &c,
                                         const TciTestCaseIdType &tcId,
                                         const TciParameterListType &pars,
                                         TriTimerDuration dur) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_TC_START,
                                                                        "Testcase START");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  sprintf(str, "%s.%s", tcId.moduleName, tcId.objectName);
  data->LineAdd("Testcase Id", str);
  
//   std::vector<std::string> params(pars.length);
//   for(unsigned short i=0; i<pars.length; i++) {
//     sprintf(str, "[%5s] %s.%s: %u", pars.parList[i].mode == TRI_IN ? "IN" : pars.parList[i].mode == TRI_OUT ? "OUT" : "INOUT",
//             pars.parList[i].par.);
//     params[i] = str;
//   }
//   data->LineAdd("Parameters", params);
  
  sprintf(str, "%f", dur);
  data->LineAdd("Duration", str);
  
  Logger().Push(data);
} 


void freettcn::TL::CTestLogging::TcStop(const char *am, int ts, const char *src, int line,
                                        const TriComponentId &c) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_TC_STOP,
                                                                        "Testcase STOP");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  Logger().Push(data);
} 


void freettcn::TL::CTestLogging::TcStarted(const char *am, int ts, const char *src, int line,
                                           const TriComponentId &c,
                                           const TciTestCaseIdType &tcId,
                                           const TciParameterListType &pars,
                                           TriTimerDuration dur) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TM,
                                                                        freettcn::CLogMask::CMD_TM_TC_STARTED,
                                                                        "Testcase STARTED");
  
  char str[256];
  
//   sprintf(str, "%s [%s.%s]", c.compName, c.compType.moduleName, c.compType.objectName);
//   data->LineAdd("From", str);
  
  sprintf(str, "%s.%s", tcId.moduleName, tcId.objectName);
  data->LineAdd("Testcase Id", str);
  
//   std::vector<std::string> params(pars.length);
//   for(unsigned short i=0; i<pars.length; i++) {
//     sprintf(str, "[%5s] %s.%s: %u", pars.parList[i].mode == TRI_IN ? "IN" : pars.parList[i].mode == TRI_OUT ? "OUT" : "INOUT",
//             pars.parList[i].par.);
//     params[i] = str;
//   }
//   data->LineAdd("Parameters", params);
  
  sprintf(str, "%f", dur);
  data->LineAdd("Duration", str);
  
  Logger().Push(data);
} 


void freettcn::TL::CTestLogging::TcTerminated(const char *am, int ts, const char *src, int line,
                                              const TriComponentId &c,
                                              const TciTestCaseIdType &tcId,
                                              const TciParameterListType &pars,
                                              const VerdictValue &outcome) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TM,
                                                                        freettcn::CLogMask::CMD_TM_TC_STARTED,
                                                                        "Testcase TERMINATED");
  
  char str[256];
  
//   sprintf(str, "%s [%s.%s]", c.compName, c.compType.moduleName, c.compType.objectName);
//   data->LineAdd("From", str);
  
  sprintf(str, "%s.%s", tcId.moduleName, tcId.objectName);
  data->LineAdd("Testcase Id", str);
  
//   std::vector<std::string> params(pars.length);
//   for(unsigned short i=0; i<pars.length; i++) {
//     sprintf(str, "[%5s] %s.%s: %u", pars.parList[i].mode == TRI_IN ? "IN" : pars.parList[i].mode == TRI_OUT ? "OUT" : "INOUT",
//             pars.parList[i].par.);
//     params[i] = str;
//   }
//   data->LineAdd("Parameters", params);
  
  sprintf(str, "%s", CTciValueDumper::Verdict2String(outcome));
  data->LineAdd("Outcome", str);
  
  Logger().Push(data);
} 


void freettcn::TL::CTestLogging::CtrlStart(const char *am, int ts, const char *src, int line,
                                           const TriComponentId &c) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_CTRL_START,
                                                                        "Control START");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  Logger().Push(data);
}
      

void freettcn::TL::CTestLogging::CtrlStop(const char *am, int ts, const char *src, int line,
                                          const TriComponentId &c) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_CTRL_STOP,
                                                                        "Control STOP");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::CtrlTerminated(const char *am, int ts, const char *src, int line,
                                                const TriComponentId &c) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TM,
                                                                        freettcn::CLogMask::CMD_TM_CTRL_TERMINATED,
                                                                        "Control TERMINATED");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::MDetected_m(const char *am, int ts, const char *src, int line,
                                             const TriComponentId &c,
                                             const TriPortId &at,
                                             const TriPortId &from,
                                             const TriMessage &msg,
                                             const TriAddress &address) const
{
//   using namespace std;
  
//   cout << "[" << ts << "][SA] New message detected";
//   if (*src)
//     cout << " [" << src << ":" << line << "]";
//   cout << ":" << endl;
//   if (*am)
//     cout << "[SA] - Note: " << am << endl;
//   cout << "[SA] - To: " << port.compInst.compName << "." << port.portName << ":" << port.portIndex
//        << " [" << port.compInst.compType.moduleName << "." << port.compInst.compType.objectName << "]" << endl;
//   cout << "[SA] - From: " << c.compName
//        << " [" << c.compType.moduleName << "." << c.compType.objectName << "]" << endl;
//   cout << "[SA] - Data:";

//   int oldFill=cout.fill('0');
//   for(int i=0; i<msg.bits / 8; i++) {
//     if (!(i % 8)) {
//       if (!(i % 16))
//         cout << endl << "       ";
//       else
//         cout << "  ";
//     }
//     else
//       cout << " ";
//     cout << hex << setw(2) << static_cast<unsigned short>(msg.data[i]);
//   }
//   cout.fill(oldFill);
//   cout << endl;
}


void freettcn::TL::CTestLogging::CCreate(const char *am, int ts, const char *src, int line,
                                         const TriComponentId &c,
                                         const TriComponentId &comp,
                                         const char *name,
                                         bool alive) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_C_CREATE,
                                                                        "Component CREATE");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  data->LineAdd("Component", TriComponentId2String(comp, str));
  data->LineAdd("Alive", alive ? "TRUE" : "FALSE");
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::CStart(const char *am, int ts, const char *src, int line,
                                        const TriComponentId &c,
                                        const TriComponentId &comp,
                                        const TciBehaviourIdType &name,
                                        const TciParameterListType &parsValue) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_C_START,
                                                                        "Component START");
  
  char str[256];
  
  data->LineAdd("From", TriComponentId2String(c, str));
  data->LineAdd("Component", TriComponentId2String(comp, str));

  sprintf(str, "%s.%s", name.moduleName, name.objectName);
  data->LineAdd("Behaviour", str);
  
  /// @todo print parameters
  sprintf(str, "num: %li", parsValue.length);
  data->LineAdd("Parameters", str);
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::CKilled(const char *am, int ts, const char *src, int line,
                                         const TriComponentId &c,
                                         const TciNonValueTemplate &compTmpl) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_C_KILLED,
                                                                        "Component KILLED");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  sprintf(str, "%p", compTmpl);                   /**< @todo Print template */
  data->LineAdd("Template", str);
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::CTerminated(const char *am, int ts, const char *src, int line,
                                             const TriComponentId &c,
                                             const VerdictValue &verdict) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_C_TERMINATED,
                                                                        "Component TERMINATED");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  sprintf(str, "%s", CTciValueDumper::Verdict2String(verdict));
  data->LineAdd("Verdict", str);
  
  Logger().Push(data);
}




void freettcn::TL::CTestLogging::PConnect(const char *am, int ts, const char *src, int line,
                                          const TriComponentId &c,
                                          const TriPortId &port1,
                                          const TriPortId &port2) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_CH,
                                                                        freettcn::CLogMask::CMD_CH_P_CONNECT,
                                                                        "Port CONNECT");
  
  char str[256];
  data->LineAdd("From", TriPortId2String(port1, str));
  data->LineAdd("To", TriPortId2String(port2, str));
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::PDisconnect(const char *am, int ts, const char *src, int line,
                                             const TriComponentId &c,
                                             const TriComponentId &c1,
                                             const TriPortId &port1,
                                             const TriComponentId &c2,
                                             const TriPortId &port2) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_CH,
                                                                        freettcn::CLogMask::CMD_CH_P_DISCONNECT,
                                                                        "Port DISCONNECT");
  
  char str[256];
  data->LineAdd("From", TriPortId2String(port1, str));
  data->LineAdd("To", TriPortId2String(port2, str));
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::PMap(const char *am, int ts, const char *src, int line,
                                      const TriComponentId &c,
                                      const TriPortId &port1,
                                      const TriPortId &port2) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_SA,
                                                                        freettcn::CLogMask::CMD_SA_P_MAP,
                                                                        "Port MAP");
  
  char str[256];
  data->LineAdd("From", TriPortId2String(port1, str));
  data->LineAdd("To", TriPortId2String(port2, str));
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::PUnmap(const char *am, int ts, const char *src, int line,
                                        const TriComponentId &c,
                                        const TriComponentId &c1,
                                        const TriPortId &port1,
                                        const TriComponentId &c2,
                                        const TriPortId &port2) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_SA,
                                                                        freettcn::CLogMask::CMD_SA_P_UNMAP,
                                                                        "Port UNMAP");
  
  char str[256];
  data->LineAdd("From", TriPortId2String(port1, str));
  data->LineAdd("To", TriPortId2String(port2, str));
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::Encode(const char *am, int ts, const char *src, int line,
                                        const TriComponentId &c,
                                        const Value &val,
                                        TriStatus encoderFailure,
                                        const TriMessage &msg,
                                        const char *codec) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_CD,
                                                                        freettcn::CLogMask::CMD_CD_ENCODE,
                                                                        "ENCODE");
  
  char str[256];
  sprintf(str, "%p", val);
  data->LineAdd("Value", str);

  char long_str1[1024];
  char long_str2[1024];
  sprintf(long_str1, "bits: %li%s", msg.bits, Buffer2String(msg, long_str2));
  data->LineAdd("Message", long_str1);
  
  data->LineAdd("Codec", codec);
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::TTimeoutDetected(const char *am, int ts, const char *src, int line,
                                                  const TriComponentId &c,
                                                  const TriTimerId &timer) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_PA,
                                                                        freettcn::CLogMask::CMD_PA_T_TIMEOUT_DETECTED,
                                                                        "Timeout Detected");
  
  char str[256];
  data->LineAdd("Timer Id", InstanceId2String(timer, str));
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::TStart(const char *am, int ts, const char *src, int line,
                                        const TriComponentId &c,
                                        const TriTimerId &timer,
                                        TriTimerDuration dur) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_PA,
                                                                        freettcn::CLogMask::CMD_PA_T_START,
                                                                        "Timer START");
  
  char str[256];
  data->LineAdd("Timer Id", InstanceId2String(timer, str));
  
  sprintf(str, "%f", dur);
  data->LineAdd("Duration", str);
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::TStop(const char *am, int ts, const char *src, int line,
                                       const TriComponentId &c,
                                       const TriTimerId &timer,
                                       TriTimerDuration dur) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_PA,
                                                                        freettcn::CLogMask::CMD_PA_T_STOP,
                                                                        "Timer STOP");
  
  char str[256];
  data->LineAdd("Timer Id", InstanceId2String(timer, str));
  
  sprintf(str, "%f", dur);
  data->LineAdd("Duration", str);

  Logger().Push(data);
}


void freettcn::TL::CTestLogging::TRead(const char *am, int ts, const char *src, int line,
                                       const TriComponentId &c,
                                       const TriTimerId &timer,
                                       TriTimerDuration elapsed) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_PA,
                                                                        freettcn::CLogMask::CMD_PA_T_READ,
                                                                        "Timer READ");
  
  char str[256];
  data->LineAdd("Timer Id", InstanceId2String(timer, str));
  
  sprintf(str, "%f", elapsed);
  data->LineAdd("Elapsed", str);
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::TRunning(const char *am, int ts, const char *src, int line,
                                          const TriComponentId &c,
                                          const TriTimerId &timer,
                                          TimerStatus status) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_PA,
                                                                        freettcn::CLogMask::CMD_PA_T_RUNNING,
                                                                        "Timer RUNNING");
  
  char str[256];
  data->LineAdd("Timer Id", InstanceId2String(timer, str));
  
  sprintf(str, "%s", status == runningT ? "RUNNING" : status == inactiveT ? "INACTIVE" : "EXPIRED");
  data->LineAdd("Elapsed", str);
  
  Logger().Push(data);
}



void freettcn::TL::CTestLogging::SEnter(const char *am, int ts, const char *src, int line,
                                        const TriComponentId &c,
                                        const QualifiedName &name,
                                        const TciParameterListType &tciPars,
                                        const char *kind) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_S_ENTER,
                                                                        "Scope ENTER");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  data->LineAdd("Kind", kind);
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::SLeave(const char *am, int ts, const char *src, int line,
                                        const TriComponentId &c,
                                        const QualifiedName &name,
                                        const TciParameterListType &tciPars,
                                        const Value &returnValue,
                                        const char *kind) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_S_LEAVE,
                                                                        "Scope LEAVE");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  data->LineAdd("Kind", kind);
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::VerdictSet(const char *am, int ts, const char *src, int line,
                                            const TriComponentId &c,
                                            const VerdictValue &verdict) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_SET_VERDICT,
                                                                        "Verdict SET");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  sprintf(str, "%s", CTciValueDumper::Verdict2String(verdict));
  data->LineAdd("Verdict", str);
  
  Logger().Push(data);
}
