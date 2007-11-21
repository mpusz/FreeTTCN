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
      // types
      typedef std::vector<const CType *> CTypeArray;
      typedef std::vector<CParameter *> CParameterArray;
      typedef std::list<const CBehavior *> CBehaviorList;
      typedef std::vector<CTestCase *> CTestCaseArray;
      typedef std::list<CTestComponentType::CInstanceRemote *> CTestCompList;
      typedef std::vector<CPortType *> CPortTypeArray;
      
      // module info
      TciModuleIdType _id;
      CTypeArray _typeArray;
      CParameterArray _parameterArray;
      CBehaviorList _behaviorList;
      CTestCaseArray _testCaseArray;
      CPortTypeArray _portTypeArray;
      const CBehavior *_ctrlBehavior;
      const CSourceData *_ctrlSrcData;
      
      // module dynamic state
      bool _ctrlRunning;
      CTestComponentType::CInstanceLocal *_ctrlComponent;
      CTestCase *_activeTestCase;                 /**< current test case pointer */
      CTestCompList _allEntityStates;             /**< list of all entities that
                                                     was used in a test case
                                                     - M-CONTROL (must be the
                                                     first) */
      CTestCompList _done;                        /**< a list of all currently
                                                     stopped test components during
                                                     test case execution (filled when
                                                     TC is stopped or killed, removed
                                                     when TC is started) */
      CTestCompList _killed;                      /**< a list of all terminated test
                                                     components during test case
                                                     execution (filled when TC is
                                                     killed) */
      
      // temporary variables
      mutable TciModuleParameterType *__modParList;
      mutable TciTestCaseIdType *__testCaseIdList;
      
      CModule& operator=(CModule&);  // Disallowed
      CModule(const CModule&);       // Disallowed
      
      CTestComponentType::CInstanceLocal &TestComponent(const TriComponentId &component) const throw(ENotFound);
      const CBehavior &Behavior(const TciBehaviourIdType &behavior) const throw(ENotFound);
      
    protected:
      void Register(const CType *type);
      void Register(CParameter *parameter);
      void Register(CTestCase *testCase);
      void Register(CPortType *portType);
      
      void ControlBehavior(const CBehavior &ctrlBehavior, const CSourceData *ctrlSrcData);
      
      virtual void Cleanup();
      
    public:
      CModule(const char *name);
      virtual ~CModule() = 0;
      
      const TciModuleIdType &Id() const;
      bool Running() const;
      void Reset();
      
      TriComponentId ModuleComponentId() const;

      TciModuleParameterListType Parameters() const;
      void ParametersGet() const throw(EOperationFailed);
      const CParameter &Parameter(unsigned int parameterIdx) const throw(ENotFound);
      
      const CType &Type(const char *typeName) const throw(ENotFound);
      const CType &Type(unsigned int typeIdx) const throw(ENotFound);
      
      const CPortType &PortType(unsigned int portTypeIdx) const throw(ENotFound);
      
      TciTestCaseIdListType TestCases() const;
      CTestCase &TestCase(const char *tcId) const throw(ENotFound);
      CTestCase &TestCase(unsigned int tcIdx) const throw(ENotFound);
      void ActiveTestCase(CTestCase &tc);
      CTestCase &ActiveTestCase() const throw(ENotFound);
      
      const TriComponentId &ControlStart();
      void ControlStop() throw(EOperationFailed);
      
      const CBehavior &ControlBehavior() const throw(ENotFound);
      void BehaviorAdd(CBehavior *behavior);
      
      CTestComponentType::CInstanceRemote &TestComponentCreateReq(const char *src, int line, const TriComponentId &creatorId, TciTestComponentKindType kind, const CTestComponentType &compType, const char *name);
      const TriComponentId &TestComponentCreate(TciTestComponentKindType kind, TciType componentType, const char *name);
      void TestComponentStartReq(const char *src, int line, const TriComponentId &creatorId, CTestComponentType::CInstanceRemote &component, const CBehavior &behavior, const TciParameterListType &parameterList) throw(EOperationFailed);
      void TestComponentStart(const TriComponentId &componentId, const TciBehaviourIdType &behaviorId, const TciParameterListType &parameterList) const throw(ENotFound);
      void TestComponentStop(const TriComponentId &componentId) const throw(ENotFound);
      void TestComponentTerminated(const TriComponentId &componentId, TciVerdictValue verdict) throw(ENotFound);
      void TestComponentKill(const TriComponentId &componentId) const throw(ENotFound);
      
      void TestComponentAllStop(const char *src, int line, CTestComponentType::CInstanceLocal &comp) const;
      void TestComponentAllKill(const char *src, int line, CTestComponentType::CInstanceLocal &comp);
      
      void Connect(const TriPortId &fromPort, const TriPortId &toPort) const throw(ENotFound);
      void Disconnect(const TriPortId &fromPort, const TriPortId &toPort) const throw(ENotFound);
      void Map(const TriPortId &fromPort, const TriPortId &toPort) const throw(ENotFound, EOperationFailed);
      void Unmap(const TriPortId &fromPort, const TriPortId &toPort) const throw(ENotFound, EOperationFailed);
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __MODULE_H__ */
