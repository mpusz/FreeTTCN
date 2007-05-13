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
 * @file   module.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __MODULE_H__
#define __MODULE_H__


extern "C" {
#include <freettcn/ttcn3/tci.h>
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/te/initObject.h>
#include <freettcn/te/testComponent.h>
#include <freettcn/te/ttcnWrappers.h>
#include <freettcn/tools/exception.h>
#include <vector>
#include <list>


namespace freettcn {

  namespace TE {

    class CBehavior;
    class CTestCase;
    class CSourceData;
    
    class CModule : public CInitObject {
    public:
      class CParameter : public CInitObject {
        TciValue _defaultValue;
        TciValue _value;
      public:
        CParameter(const char *name);
        virtual ~CParameter();
        
        TciValue DefaultValue() const;
        void Value(TciValue value);
      };
      
    private:
      class CTestComponentData {
        CTestComponentId _id;
        TciTestComponentKindType _kind;
      public:
        CTestComponentData(const TriComponentId &id, TciTestComponentKindType kind);
        const CTestComponentId &Id() const;
        TciTestComponentKindType Kind() const;
        bool operator==(const TriComponentId &id) const;
      };
      
      // types
      typedef std::vector<CParameter *> TParameterList;
      typedef std::list<const CBehavior *> TBehaviorList;
      typedef std::vector<CTestCase *> TTestCaseList;
      typedef std::list<const CTestComponentData *> TTestCompList;
      typedef std::list<CTestComponentType::CInstance *> TLocalTestCompList;
      
      // module info
      const CBehavior * _ctrlBehavior;
      const CSourceData * _ctrlSrcData;
      TciModuleIdType _id;
      TParameterList _parameterList;
      TBehaviorList _behaviorList;
      TTestCaseList _testCaseList;
      
      // module dynamic state
      bool _ctrlRunning;
      TTestCompList _allEntityStates;             /**< list of all entities that was used in a test case - M-CONTROL (must be the first) */
      CTestCase *_currTestCase;                   /**< current test case pointer */
      TTestCompList _done;                         /**< a list of all currently stopped test components during test case execution (filled when TC is stopped or killed, removed when TC is started) */
      TTestCompList _killed;                       /**< a list of all terminated test components during test case execution (filled when TC is killed) */
      
      TLocalTestCompList _localTestComponents;
      
      // temporary variables
      mutable TciModuleParameterType *__modParList;
      mutable TciTestCaseIdType *__testCaseIdList;
      
      CModule& operator=(CModule&);  // Disallowed
      CModule(const CModule&);       // Disallowed
      
      CTestComponentType::CInstance &TestComponent(const TriComponentId &component) const throw(ENotFound);
      const CBehavior &Behavior(const TciBehaviourIdType &behavior) const throw(ENotFound);
      
    protected:
      void Register(CParameter *parameter);
      void Register(const CBehavior *ctrlBehavior, const CSourceData *ctrlSrcData);
      
      void TestCaseAdd(CTestCase &testCase);
      
      void ParametersSet() throw(freettcn::EOperationFailed);
      
      virtual void Cleanup();
      
    public:
      CModule(const char *name);
      virtual ~CModule() = 0;
      
      const TciModuleIdType &Id() const;
      TriComponentId ModuleComponentId() const;
      
      bool Running() const;
      void Reset();
      
      TciModuleParameterListType Parameters() const;
      
      TciTestCaseIdListType TestCases() const;
      CTestCase &TestCase(const char *tcId) const throw(ENotFound);
      void TestCase(CTestCase *tc);
      CTestCase *TestCase() const;
      
      const CTestComponentId &ControlStart();
      void ControlStop() throw(EOperationFailed);
      
      const CBehavior &ControlBehavior() const throw(ENotFound);
      void BehaviorAdd(CBehavior *behavior);
      
      const CTestComponentId &TestComponentCreateReq(const char *src, int line, const TriComponentId &creatorId, TciTestComponentKindType kind, const CTestComponentType *compType, const char *name);
      const TriComponentId &TestComponentCreate(TciTestComponentKindType kind, TciType componentType, const char *name);
      void TestComponentStartReq(const char *src, int line, const TriComponentId &creatorId, const TriComponentId &componentId, const TciBehaviourIdType &behaviorId, const TciParameterListType &parameterList);
      void TestComponentStart(const TriComponentId &componentId, const TciBehaviourIdType &behaviorId, const TciParameterListType &parameterList) throw(ENotFound);
      void TestComponentStop(const TriComponentId &componentId) throw(ENotFound);
      void TestComponentTerminated(const TriComponentId &componentId, TciVerdictValue verdict) throw(ENotFound);
      void TestComponentKill(const TriComponentId &componentId) throw(ENotFound);
      
      void TestComponentLocalAdd(CTestComponentType::CInstance &comp);
      void TestComponentLocalRemove(CTestComponentType::CInstance &comp) throw(ENotFound);
    };

  } // namespace TE
  
} // namespace freettcn


#endif /* __MODULE_H__ */
