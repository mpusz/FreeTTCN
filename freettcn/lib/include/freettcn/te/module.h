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
#include <freettcn/te/testComponent.h>
#include <freettcn/te/ttcnWrappers.h>
#include <vector>
#include <list>


namespace freettcn {

  namespace TE {
    
    class CType;
    class CBehavior;
    class CTestCase;
    class CSourceData;
    
    class CModule : public CInitObject {
    public:
      class CParameter {
        TciModuleParameterIdType _id;
        CType::CInstance const * const _defaultValue;
        const CType::CInstance *_value;
      public:
        CParameter(const char *name, const CType::CInstance *defaultValue) throw(EOperationFailed);
        ~CParameter();
        const TciModuleParameterIdType &Id() const;
        const CType::CInstance &DefaultValue() const;
        void Value(const CType::CInstance *value);
        const CType::CInstance &Value() const throw(EOperationFailed);
      };
      
    private:
      class CTestComponentData {
        CTriComponentId _id;
        TciTestComponentKindType _kind;
      public:
        CTestComponentData(const TriComponentId &id, TciTestComponentKindType kind);
        const CTriComponentId &Id() const;
        TciTestComponentKindType Kind() const;
        bool operator==(const TriComponentId &id) const;
      };
      
      // types
      typedef std::vector<const CType *> TTypeArray;
      typedef std::vector<CParameter *> TParameterArray;
      typedef std::list<const CBehavior *> TBehaviorList;
      typedef std::vector<CTestCase *> TTestCaseArray;
      typedef std::list<const CTestComponentData *> TTestCompList;
      typedef std::list<CTestComponentType::CInstance *> TLocalTestCompList;
      typedef std::vector<CPortType *> TPortTypeArray;
      
      // module info
      TciModuleIdType _id;
      TTypeArray _typeArray;
      TParameterArray _parameterArray;
      TBehaviorList _behaviorList;
      TTestCaseArray _testCaseArray;
      TPortTypeArray _portTypeArray;
      const CBehavior * _ctrlBehavior;
      const CSourceData * _ctrlSrcData;
      
      // module dynamic state
      bool _ctrlRunning;
      TTestCompList _allEntityStates;             /**< list of all entities that was used in a test case - M-CONTROL (must be the first) */
      CTestCase *_activeTestCase;                 /**< current test case pointer */
      TTestCompList _done;                        /**< a list of all currently stopped test components during test case execution (filled when TC is stopped or killed, removed when TC is started) */
      TTestCompList _killed;                      /**< a list of all terminated test components during test case execution (filled when TC is killed) */
      
      TLocalTestCompList _localTestComponents;
      
      // temporary variables
      mutable TciModuleParameterType *__modParList;
      mutable TciTestCaseIdType *__testCaseIdList;
      
      CModule& operator=(CModule&);  // Disallowed
      CModule(const CModule&);       // Disallowed
      
      CTestComponentType::CInstance &TestComponent(const TriComponentId &component) const throw(ENotFound);
      const CBehavior &Behavior(const TciBehaviourIdType &behavior) const throw(ENotFound);
      
    protected:
      void Register(const CType *type);
      void Register(CParameter *parameter);
      void Register(const CBehavior *ctrlBehavior, const CSourceData *ctrlSrcData);
      void Register(CTestCase *testCase);
      void Register(CPortType *portType);
      
//       void ParametersSet() throw(freettcn::EOperationFailed);
      
      virtual void Cleanup();
      
    public:
      CModule(const char *name);
      virtual ~CModule() = 0;
      
      const TciModuleIdType &Id() const;
      bool Running() const;
      void Reset();
      
      TriComponentId ModuleComponentId() const;
      TciModuleParameterListType Parameters() const;
      
      const CType &Type(const char *typeName) const throw(ENotFound);
      const CType &Type(unsigned int typeIdx) const throw(ENotFound);
      
      const CPortType &PortType(unsigned int portTypeIdx) const throw(ENotFound);
      
      TciTestCaseIdListType TestCases() const;
      CTestCase &TestCase(const char *tcId) const throw(ENotFound);
      CTestCase &TestCase(unsigned int tcIdx) const throw(ENotFound);
      void ActiveTestCase(CTestCase &tc);
      CTestCase &ActiveTestCase() const throw(ENotFound);
      
      const CTriComponentId &ControlStart();
      void ControlStop() throw(EOperationFailed);
      
      const CBehavior &ControlBehavior() const throw(ENotFound);
      void BehaviorAdd(CBehavior *behavior);
      
      const CTriComponentId &TestComponentCreateReq(const char *src, int line, const TriComponentId &creatorId, TciTestComponentKindType kind, const CTestComponentType *compType, const char *name);
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
