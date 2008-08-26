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
 * @file   te.h
 * @author Mateusz Pusz
 * @date   Sat Apr  7 22:10:55 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TE_H__
#define __TE_H__


extern "C" {
#include <freettcn/ttcn3/tci.h>
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/tools/entity.h>


namespace freettcn {

  namespace TE {
    
    class CModule;
    
    class CTTCNExecutable : public freettcn::CEntity {
      static CTTCNExecutable _instance;
      
      CModule *_rootModule;
      
      CTTCNExecutable();
      virtual ~CTTCNExecutable();
      CTTCNExecutable& operator=(CTTCNExecutable&);  // Disallowed
      CTTCNExecutable(const CTTCNExecutable&);       // Disallowed
    protected:
      CModule &RootModule() const;
      
    public:
      static CTTCNExecutable &Instance();
      
      // TM requests
      void RootModule(String moduleId);
      TciModuleParameterListType ModuleParametersGet(const TciModuleIdType &moduleName) const;
      TciTestCaseIdListType TestCasesGet() const;
      TciParameterTypeListType TestCaseParametersGet(const TciTestCaseIdType &testCaseId) const;
      TriPortIdList TestCaseTSIGet(const TciTestCaseIdType &testCaseId) const;
      void TestCaseStart(const TciTestCaseIdType &testCaseId, const TciParameterListType &parameterlist) const;
      void TestCaseStop() const;
      const TriComponentId &ControlStart() const;
      void ControlStop() const;
      
      // CH requests
      void ConnectedMsgEnqueue(const TriPortId &sender, const TriComponentId &receiver, const Value &rcvdMessage) const;
      const TriComponentId &TestComponentCreate(TciTestComponentKindType kind, const Type &componentType, String name) const;
      void TestComponentStart(const TriComponentId &componentId, const TciBehaviourIdType &behaviorId, const TciParameterListType &parameterList) const;
      void TestComponentStop(const TriComponentId &componentId) const;
      void TestComponentKill(const TriComponentId &component) const;
      void Connect(const TriPortId &fromPort, const TriPortId &toPort) const;
      void Disconnect(const TriPortId &fromPort, const TriPortId &toPort) const;
      void Map(const TriPortId &fromPort, const TriPortId &toPort) const;
      void Unmap(const TriPortId &fromPort, const TriPortId &toPort) const;
      void TestComponentTerminated(const TriComponentId &componentId, const VerdictValue &verdict) const;
      void TestCaseExecute(const TciTestCaseIdType &testCaseId, const TriPortIdList &tsiPortList) const;
      void Reset() const;
      
      // PA requests
      void Timeout(const TriTimerId* timerId);
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TE_H__ */
