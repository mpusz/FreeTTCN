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
#include "freettcn/tci.h"
#include "freettcn/tri.h"
}
#include "initObject.h"
#include "testComponent.h"
#include "exception.h"
#include <vector>
#include <list>


namespace freettcn {

  
//   class CQualifiedName {
//     QualifiedName _name;
//   public:
//     CQualifiedName(String moduleName, String objectName, void *aux);
//     const QualifiedName &Get() const;
//   };

//   class CModule {
//     const CQualifiedName _id;
//   public:
//     CModule(const CQualifiedName &id);
//     const TciModuleIdType &Id() const;
//   };


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
      class CState {
        // ALL_ENTITY_STATES - (CList) list of all entities that was used in a test case - M-CONTROL (must be the first), MTC, PTCs
        // current test case pointer
        // DONE - (CList) a list of all currently stopped test components during test case execution (filled when TC is stopped or killed, removed when TC is started)
        // KILLED - (CList) a list of all terminated test components during test case execution (filled when TC is killed)
      };
      
      // module types
      typedef std::vector<CParameter *> ParameterList;
      typedef std::vector<CTestCase *> TestCaseList;
      typedef std::list<CTestComponent *> TestCompList;
      typedef std::list<CBehavior *> BehaviorList;
      
      // module info
      CBehavior * _ctrlBehavior;
      const CSourceData * _ctrlSrcData;
      CControlComponentType _ctrlCompType;
      TciModuleIdType _id;
      ParameterList _parameterList;
      TestCaseList _testCaseList;
      BehaviorList _behaviorList;
      
      // module state
      bool _ctrlRunning;
      TestCompList _allEntityStates;
      CTestCase *_currTestCase;
      TestCompList _done;
      TestCompList _killed;
      
      // temporary variables
      mutable TciModuleParameterType *__modParList;
      mutable TciTestCaseIdType *__testCaseIdList;
      
    protected:
      void Register(CParameter *parameter);
      void Register(CTestCase *tc);
      void Register(CBehavior *ctrlBehavior, const CSourceData *ctrlSrcData);
      
      void ParametersSet() throw(freettcn::EOperationFailed);
    public:
      CModule(const char *name);
      virtual ~CModule() = 0;
      
      const TciModuleIdType &Id() const;
      TriComponentId ModuleComponentId() const;
      const CControlComponentType &ControlComponentType() const;
      
      bool Running() const;
      void Reset();
      
      TciModuleParameterListType Parameters() const;
      
      TciTestCaseIdListType TestCases() const;
      CTestCase &TestCase(const char *tcId) const throw(ENotFound);
      void TestCase(CTestCase *tc);
      CTestCase *TestCase() const;
      
      const CBehavior &ControlBehavior() const throw(ENotFound);
      TriComponentId ControlStart();
      void ControlStop() throw(EOperationFailed);
      
      void BehaviorAdd(CBehavior *behavior);
      const CBehavior &Behavior(const TciBehaviourIdType &behavior) const throw(ENotFound);
      
      void TestComponentAdd(CTestComponent &component);
      CTestComponent &TestComponent(const TriComponentId &component) const throw(ENotFound);
    };
    
    
    /**
     * Singleton design pattern
     */
    class CModulesContainer {
      typedef std::vector<CModule *> ModuleList;
      ModuleList _modList;
      
      CModulesContainer();
      CModulesContainer &operator=(CModulesContainer &);  // Disallowed
      CModulesContainer(const CModulesContainer &);       // Disallowed
    public:
      static CModulesContainer &Instance();
      
      void Register(CModule &module);
      void Deregister(const CModule &module);
      CModule &Get(const std::string &moduleId) const throw(ENotFound);
    };

  } // namespace TE
  
} // namespace freettcn


#endif /* __MODULE_H__ */
