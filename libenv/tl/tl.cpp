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
#include <freettcn/tools/logMask.h>
#include <freettcn/tools/timeStamp.h>
#include <iostream>
#include <sstream>
#include <iomanip>


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




freettcn::TL::CLogger::CLogger(freettcn::CTimeStamp &ts):
  _ts(ts)
{
}

freettcn::TL::CLogger::~CLogger()
{
}

freettcn::CTimeStamp &freettcn::TL::CLogger::TimeStamp() const
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
  ostring << "[" << TimeStamp().String(data->TimeStamp()) << "][" << entityStr[data->Entity()] << "] " << data->Title() << ":" << endl;
  if (data->Source() != "") {
    ostring << "  - " << setw(width) << "Source" << ": " << data->Source() << ":" << data->SourceLine() << endl;
  }
  for(unsigned short i=0; i<data->LineNum(); i++)
    ostring << "  - " << setw(width) << data->LineTitle(i) << ": " << data->LineValue(i) << endl;
  
  cout << ostring.str() << endl;
  
  delete data;                                    /**< can be stored for further logging/filtering purposes */
}



freettcn::TL::CTestLogging *freettcn::TL::CTestLogging::_instance = 0;

freettcn::TL::CTestLogging &freettcn::TL::CTestLogging::Instance() throw(ENotFound)
{
  if (_instance)
    return *_instance;
  
  throw ENotFound();
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

const char *freettcn::TL::CTestLogging::BinaryString2String(const BinaryString &binStr, char *str) const
{
  str[0] = 0;
  
  for(int i=0; i<binStr.bits / 8; i++) {
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


const char *freettcn::TL::CTestLogging::TriComponentId2String(const TriComponentId &comp, char *str) const
{
  sprintf(str, "<%s.%s>", comp.compType.moduleName, comp.compType.objectName);
  
  if (comp.compInst.bits) {
    for(int i=0; i<comp.compInst.bits / 8; i++)
      sprintf(str, "%s%s%02x", str, i ? "" : " 0x", static_cast<unsigned short>(comp.compInst.data[i]));
  }
  
  if (strcmp(comp.compName, ""))
    sprintf(str, "%s ('%s')", str, comp.compName);
  
  return str;
}


void freettcn::TL::CTestLogging::TcExecute(const char *am, int ts, const char *src, int line,
                                           const TriComponentId &c,
                                           const TciTestCaseIdType &tcId,
                                           const TriParameterList &pars,
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
                                         const TriParameterList &pars,
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
                                           const TriParameterList &pars,
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
                                              const TriParameterList &pars,
                                              TciVerdictValue outcome) const
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
  
  sprintf(str, "%p", outcome);                    /**< @todo Obtain verdict value */
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
                                             const TriPortId &port,
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
                                         const char *name) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_C_CREATE,
                                                                        "Component CREATE");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  data->LineAdd("Component", TriComponentId2String(comp, str));
  
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


void freettcn::TL::CTestLogging::CTerminated(const char *am, int ts, const char *src, int line,
                                             const TriComponentId &c,
                                             TciVerdictValue verdict) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_TE,
                                                                        freettcn::CLogMask::CMD_TE_C_START,
                                                                        "Component START");
  
  char str[256];
  data->LineAdd("From", TriComponentId2String(c, str));
  
  sprintf(str, "%p", verdict);                    /**< @todo Obtain verdict value */
  data->LineAdd("Verdict", str);
  
  Logger().Push(data);
}






void freettcn::TL::CTestLogging::TTimeoutDetected(const char *am, int ts, const char *src, int line,
                                                  const TriComponentId &c,
                                                  const TriTimerId &timer) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_PA,
                                                                        freettcn::CLogMask::CMD_PA_T_TIMEOUT_DETECTED,
                                                                        "Timeout Detected");
  
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
  
//   char str[256];
//   if (comp.compInst.bits) {
//     for(int i=0; i<comp.compInst.bits / 8; i++)
//       sprintf(str, "%s%s%02x", str, i ? "" : " 0x", static_cast<unsigned short>(comp.compInst.data[i]));
//   }
  

//   data->LineAdd("From", TriComponentId2String(c, str));
  
//   sprintf(str, "%p", verdict);                    /**< @todo Obtain verdict value */
//   data->LineAdd("Verdict", str);
  
  Logger().Push(data);
}


void freettcn::TL::CTestLogging::TStop(const char *am, int ts, const char *src, int line,
                                       const TriComponentId &c,
                                       const TriTimerId &timer) const
{
  freettcn::TL::CLogger::CData *data = new freettcn::TL::CLogger::CData(ts, src, line, am, freettcn::CEntity::TYPE_PA,
                                                                        freettcn::CLogMask::CMD_PA_T_STOP,
                                                                        "Timer STOP");
  
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
  
  Logger().Push(data);
}
