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
 * @file   tl.h
 * @author Mateusz Pusz
 * @date   Fri Apr 20 08:12:18 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TL_H__
#define __TL_H__

extern "C" {
#include <freettcn/ttcn3/tci.h>
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/tools/entity.h>
#include <vector>
#include <string>


namespace freettcn {
  
  class CTimeStampMgr;
    
  namespace TL {

    class CLogger {
    public:
      class CData {
        struct TLineData {
          std::string _title;
          std::string _value;
        };
        
        int _ts;
        std::string _src;
        int _line;
        std::string _am;
        CEntity::TType _entity;
        unsigned short _logIdx;
        std::string _title;
        
        typedef std::vector<TLineData> CLineArray;
        CLineArray lines;
      public:
        CData(int ts, const char *src, int line, const char *am, CEntity::TType entity, unsigned short logIdx, const char *title);
        
        int TimeStamp() const;
        const std::string &Source() const;
        int SourceLine() const;
        const std::string &AdditionalMessage() const;
        CEntity::TType Entity() const;
        unsigned short LogIdx() const;
        const std::string &Title() const;
        
        void LineAdd(const char *title, const char *value);
        unsigned short LineNum() const;
        const std::string &LineTitle(unsigned short lineIdx) const;
        const std::string &LineValue(unsigned short lineIdx) const;
      };
      
    private:
      freettcn::CTimeStampMgr &_ts;
      
    protected:
      freettcn::CTimeStampMgr &TimeStampMgr() const;
      
    public:
      CLogger(freettcn::CTimeStampMgr &ts);
      virtual ~CLogger();
      
      virtual void Push(const CData *data);
    };
    
    
    class CTestLogging {
      static CTestLogging *_instance;
      
      CLogger &_logger;

      CTestLogging& operator=(CTestLogging&);  // Disallowed
      CTestLogging(const CTestLogging&);       // Disallowed
      
    protected:
      CLogger &Logger() const;
      
    public:
      static CTestLogging &Instance();
      
      CTestLogging(CLogger &logger);
      virtual ~CTestLogging();
      
      virtual const char *Buffer2String(const BinaryString &binStr, char *str) const;
      virtual const char *InstanceId2String(const BinaryString &inst, char *str) const;
      virtual const char *TriPortId2String(const TriPortId &port, char *str) const;
      virtual const char *TriComponentId2String(const TriComponentId &comp, char *str) const;

      virtual void TcExecute(const char *am, int ts, const char *src, int line,
                             const TriComponentId &c,
                             const TciTestCaseIdType &tcId,
                             const TciParameterListType &pars,
                             TriTimerDuration dur) const;
      virtual void TcStart(const char *am, int ts, const char *src, int line,
                           const TriComponentId &c,
                           const TciTestCaseIdType &tcId,
                           const TciParameterListType &pars,
                           TriTimerDuration dur) const;
      virtual void TcStop(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c) const;
      virtual void TcStarted(const char *am, int ts, const char *src, int line,
                             const TriComponentId &c,
                             const TciTestCaseIdType &tcId,
                             const TciParameterListType &tciPars,
                             TriTimerDuration dur) const;
      virtual void TcTerminated(const char *am, int ts, const char *src, int line,
                                const TriComponentId &c,
                                const TciTestCaseIdType &tcId,
                                const TciParameterListType &tciPars,
                                const VerdictValue &verdict) const;
      
      virtual void CtrlStart(const char *am, int ts, const char *src, int line,
                             const TriComponentId &c) const;
      virtual void CtrlStop(const char *am, int ts, const char *src, int line,
                            const TriComponentId &c) const;
      virtual void CtrlTerminated(const char *am, int ts, const char *src, int line,
                                  const TriComponentId &c) const;
      
      virtual void MDetected_m(const char *am, int ts, const char *src, int line,
                               const TriComponentId &c,
                               const TriPortId &at,
                               const TriPortId &from,
                               const TriMessage &msg,
                               const TriAddress &address) const;
      
      virtual void CCreate(const char *am, int ts, const char *src, int line,
                           const TriComponentId &c,
                           const TriComponentId &comp,
                           const char *name,
                           bool alive) const;
      virtual void CStart(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c,
                          const TriComponentId &comp,
                          const TciBehaviourIdType &name,
                          const TciParameterListType &tciPars) const;
      virtual void CKilled(const char *am, int ts, const char *src, int line,
                           const TriComponentId &c,
                           const TciNonValueTemplate &compTmpl) const;
      virtual void CTerminated(const char *am, int ts, const char *src, int line,
                               const TriComponentId &c,
                               const VerdictValue &verdict) const;

      virtual void PConnect(const char *am, int ts, const char *src, int line,
                            const TriComponentId &c,
                            const TriPortId &port1,
                            const TriPortId &port2) const;
      virtual void PDisconnect(const char *am, int ts, const char *src, int line,
                               const TriComponentId &c,
                               const TriComponentId &c1,
                               const TriPortId &port1,
                               const TriComponentId &c2,
                               const TriPortId &port2) const;
      virtual void PMap(const char *am, int ts, const char *src, int line,
                        const TriComponentId &c,
                        const TriPortId &port1,
                        const TriPortId &port2) const;
      virtual void PUnmap(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c,
                          const TriComponentId &c1,
                          const TriPortId &port1,
                          const TriComponentId &c2,
                          const TriPortId &port2) const;
      
      virtual void Encode(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c,
                          const Value &val,
                          TriStatus encoderFailure,
                          const TriMessage &msg,
                          const char *codec) const;
      
      virtual void TTimeoutDetected(const char *am, int ts, const char *src, int line,
                                    const TriComponentId &c,
                                    const TriTimerId &timer) const;
      virtual void TStart(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c,
                          const TriTimerId &timer,
                          TriTimerDuration dur) const;
      virtual void TStop(const char *am, int ts, const char *src, int line,
                         const TriComponentId &c,
                         const TriTimerId &timer,
                         TriTimerDuration dur) const;
      virtual void TRead(const char *am, int ts, const char *src, int line,
                         const TriComponentId &c,
                         const TriTimerId &timer,
                         TriTimerDuration elapsed) const;
      virtual void TRunning(const char *am, int ts, const char *src, int line,
                            const TriComponentId &c,
                            const TriTimerId &timer,
                            TimerStatus status) const;

      virtual void SEnter(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c,
                          const QualifiedName &name,
                          const TciParameterListType &tciPars,
                          const char *kind) const;
      virtual void SLeave(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c,
                          const QualifiedName &name,
                          const TciParameterListType &tciPars,
                          const Value &returnValue,
                          const char *kind) const;
      
      virtual void VerdictSet(const char *am, int ts, const char *src, int line,
                              const TriComponentId &c,
                              const VerdictValue &verdict) const;
    };
    
  } // namespace TL
  
} // namespace freettcn



#endif /* __TL_H__ */
