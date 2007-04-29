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
#include <freettcn/tools/tools.h>
#include <string>
//#include <vector>


namespace freettcn {
  
  namespace TL {
    
    class CLogger {
    public:
      class CData {
        struct LineData {
          std::string _title;
          std::string _value;
        };
        
        int _ts;
        std::string _src;
        int _line;
        std::string _am;
        TTCNEntity _entity;
        unsigned short _logIdx;
        std::string _title;
        
        std::vector<LineData> lines;
      public:
        CData(int ts, const char *src, int line, const char *am, TTCNEntity entity, unsigned short logIdx, const char *title);
        
        int TimeStamp() const;
        const std::string &Source() const;
        int SourceLine() const;
        const std::string &AdditionalMessage() const;
        TTCNEntity Entity() const;
        unsigned short LogIdx() const;
        const std::string &Title() const;
        
        void LineAdd(const char *title, const char *value);
        unsigned short LineNum() const;
        const std::string &LineTitle(unsigned short lineIdx) const;
        const std::string &LineValue(unsigned short lineIdx) const;
      };
      
    private:
      freettcn::CTimeStamp &_ts;
      
    protected:
      freettcn::CTimeStamp &TimeStamp() const;
      
    public:
      CLogger(freettcn::CTimeStamp &ts);
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
      static CTestLogging &Instance() throw(ENotFound);
      
      CTestLogging(CLogger &logger);
      virtual ~CTestLogging();
      
      virtual void TcExecute(const char *am, int ts, const char *src, int line,
                             const TriComponentId &c,
                             const TciTestCaseIdType &tcId,
                             const TriParameterList &pars,
                             TriTimerDuration dur) const;
      virtual void TcStart(const char *am, int ts, const char *src, int line,
                           const TriComponentId &c,
                           const TciTestCaseIdType &tcId,
                           const TriParameterList &pars,
                           TriTimerDuration dur) const;
      virtual void TcStop(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c) const;
      virtual void TcStarted(const char *am, int ts, const char *src, int line,
                             const TriComponentId &c,
                             const TciTestCaseIdType &tcId,
                             const TriParameterList &pars,
                             TriTimerDuration dur) const;
      virtual void TcTerminated(const char *am, int ts, const char *src, int line,
                                const TriComponentId &c,
                                const TciTestCaseIdType &tcId,
                                const TriParameterList &pars,
                                TciVerdictValue outcome) const;
      
      virtual void CtrlStart(const char *am, int ts, const char *src, int line,
                             const TriComponentId &c) const;
      virtual void CtrlStop(const char *am, int ts, const char *src, int line,
                            const TriComponentId &c) const;
      virtual void CtrlTerminated(const char *am, int ts, const char *src, int line,
                                  const TriComponentId &c) const;
      
      virtual void MDetected_m(const char *am, int ts, const char *src, int line,
                               const TriComponentId &c,
                               const TriPortId &port,
                               const TriMessage &msg,
                               const TriAddress &address) const;
      
      virtual void CCreate(const char *am, int ts, const char *src, int line,
                           const TriComponentId &c,
                           const TriComponentId &comp,
                           const char *name) const;
      virtual void CStart(const char *am, int ts, const char *src, int line,
                          const TriComponentId &c,
                          const TriComponentId &comp,
                          const TciBehaviourIdType &name,
                          const TciParameterListType &parsValue) const;
      virtual void CTerminated(const char *am, int ts, const char *src, int line,
                               const TriComponentId &c,
                               TciVerdictValue verdict) const;

    };
    
  } // namespace TL
  
} // namespace freettcn



#endif /* __TL_H__ */
