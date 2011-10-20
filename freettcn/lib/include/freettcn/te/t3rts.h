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
 * @file   t3rts.h
 * @author Mateusz Pusz
 * @date   Sat Apr  7 22:10:55 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __T3RTS_H__
#define __T3RTS_H__

#include <freettcn/tools/nonCopyable.h>
#include <freettcn/etsi/tci.h>
#include <freettcn/etsi/tri.h>
#include <freettcn/tools/tools.h>
#include <memory>
#include <map>

namespace freettcn {
  
  namespace TE {
    
    class CEnvironment;
    class CExecutableTestSuite;
    class CModule;
    class CTestCase;
    class CComponent;
    class CBehaviour;
    //    class CTimer;

    using namespace ORG_ETSI_TTCN3_TCI;
    using namespace ORG_ETSI_TTCN3_TRI;
    
    class CTTCN3RuntimeSystem : CNonCopyable
    {
      typedef std::map<const TriComponentId *, std::unique_ptr<CComponent>, CPtrCmp> CComponentMap;
      const CEnvironment *_env;
      const CExecutableTestSuite &_ets;
      
      CModule *_rootModule;
      bool _ctrlRunning;
      const CTestCase *_activeTestCase;
      CComponentMap _componentMap;
      // CComponent *_ctrlComponent;
      
    protected:
      const CTestCase &ActiveTestCase() const;
      CComponent *ComponentCheck(const TriComponentId &component) const;
      
      bool Running() const;
      
    public:
      CTTCN3RuntimeSystem(const CExecutableTestSuite &ets);
      ~CTTCN3RuntimeSystem() = default;
      
      void Environment(const CEnvironment &env) { _env = &env; }
      
      void Reset();
      
      void RootModule(const TciModuleId &moduleName);
      CModule &RootModule() const;
      
      CComponent &Component(const TriComponentId &component) const;
      //      CTimer &Timer(const TriTimerId &timerId) const;
      
      const TriComponentId *ControlStart();
      void ControlStop();
      void TestCaseStart(const TciTestCaseId &testCaseId,
                         const TciParameterList *parameterList);
      void TestCaseExecute(const TciTestCaseId &testCaseId,
                           const TriPortIdList *tsiPortList);
      void TestCaseStop();
      
      const TriComponentId *TestComponentCreate(TciTestComponentKind kind,
                                                const TciType *componentType,
                                                const Tstring *name);
      void TestComponentStart(const TriComponentId &component,
                              const CBehaviour &behaviour,
                              const TciParameterList *parameterList);
      void TestComponentStop(const TriComponentId &component);
      void TestComponentKill(const TriComponentId &component);
      void TestComponentTerminated(const TriComponentId &component,
                                   const VerdictValue &verdict) const;
      
      const TriComponentId *MTC() const;
      
      void Connect(const TriPortId &port1, const TriPortId &port2);
      void Disconnect(const TriPortId &port1, const TriPortId &port2);
      void Map(const TriPortId &port1, const TriPortId &port2);
      void Unmap(const TriPortId &port1, const TriPortId &port2);
      
      void Timeout(const TriTimerId &timerId);
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __T3RTS_H__ */
