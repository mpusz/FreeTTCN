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
#include "freettcn/tci.h"
#include "freettcn/tri.h"
}
#include "exception.h"
#include <string>
#include <vector>


namespace freettcn {

  class CList {
  public:
//     void Add(item)
//     {
// //       push_front();
//     }
    
//     void Add(sublist)
//     {
// //       push_front();
//     }
    
//     void Append(item)
//     {
// //       push_back();
//     }

//     void Append(sublist)
//     {
// //       push_back();
//     }

//     void Delete(item)
//     {
//     }
    
//     bool Member(item) const
//     {
//     }
    
//     Item &First() const
//     {
//     }
    
//     Item &Last() const
//     {
//     }
    
//     unsigned Length() const
//     {
//     }
    
//     Item &Next(item) const throw
//     {
//     }

    // for 'all' and 'any' support
//     Item *Random(BoolCondition) const {
//     }
    
//     void Change(Operation) {
//     }
  };
  
  class CStack {
  public:
//     void Push(item);
//     void Pop();
//     Item *Top() const;
//     void Clear();
//     void ClearUntil(item);
  };
  
  
  class CQueue {
  public:
    void Enqueue(item);
    void Dequeue();
    Item *First() const;
    void Clear();
  };

  namespace TE {
    
    class CTimer {
      class CState {
        // STATUS:
        //  - IDLE
        //  - RUNNING
        //  - TIMEOUT
        // DEF_DURATION - default duration of a timer (undefined if not inited during declaration)
        // ACT_DURATION - stores the actual duration with which a running timer has been started (0.0 - if timer is stopped or timed out) (if a timer is started without duration, DEF_DURATION is copied) - error if no value defined when starting;
        // TIME_LEFT - describes the actual duration that a running timer has to run before it times out (0.0 - if timer is stopped or timed out)
        // SNAP_VALUE - when taking a snapshot it gets the actual value of ACT_DURATION - TIME_LEFT
        // SNAP_STATUS - when taking a snapshot it gets the same value as STATUS
      };
    };
    
    class CPort {
      class CState {
        // STATUS
        //  - STARTED
        //  - STOPPED
        // CONNECTIONS_LIST - keeps track of connections between the different ports in the test system
        // VALUE_QUEUE - not yet consumed messages, calls, replies and exceptions
        // SNAP_VALUE - when a snapshot is taken the first element from VALUE_QUEUE is copied (NULL if VALUE_QUEUE is empty or STATUS = STOPPED)
      }
    };
    
    class CBehavior {
    public:
      enum VerdictType_t {
        VERDICT_NONE,
        VERDICT_PASS,
        VERDICT_INCONC,
        VERDICT_FAIL,
        VERDICT_ERROR
      };
      
    private:
      VerdictType_t _verdict;
      
    public:
      CBehavior();
      virtual ~CBehavior();
      
      virtual VerdictType_t Run() = 0;
    };
    
    class CTestComponent {
      class CState {
        // STATUS:
        // - ACTIVE
        // - SNAPSHOT (active but in the evaluation phase of a snapshot)
        // - REPEAT (active and in an 'alt' statement that should be reevaluated due to a 'repeat' statement)
        // - BLOCKED (module control is blocked during the execution of the test case; test components are blocked during the creation of other test components, and when they wait for being started)
        // CONTROL_STACK (CStack) (a stack of flow graph node references; the top element is the flow graph node that has to be interpreted next)
        // DEFAULT_LIST (CList) (a list of activated defaults; a list of pointers to the start nodes of activated defaults; the list in reverse order of activation)
        // DEFAULT_POINTER (next default that has to be evaluated if the actual default terminates unsuccessfully)
        // VALUE_STACK (CStack) (not used)
        // E_VERDICT (actual local verdict of a test component; ignored if an entity state represents the module control)
        // TIMER_GUARD (special timer which is necessary to guard the execution time of test cases and the duration of call operations; modelled as a timer binding)
        // DATA_STATE (CList) (list of list of variable bindings)
        // TIMER_STATE (wtf ???)
        // PORT_REF (wtf ???)
        // SNAP_ALIVE (supports snapshot semantics of test component; when a snapshot is taken, a copy of the ALL_ENTITY_STATES list of module state will be assigned)
        // SNAP_DONE (supports snapshot semantics of test component; when a snapshot is taken, a copy of the DONE list of module state will be assigned)
        // SNAP_KILLED (supports snapshot semantics of test component; when a snapshot is taken, a copy of the KILLED list of module state will be assigned)
        // KEEP_ALIVE (indicated wheter the entity can be restarted after its termination or not; 'true' if the entity can be restarted)
      };
      
      const TciTestComponentKindType _kind;
      const TciType _componentType;
      const std::string _name;
    public:
      CTestComponent(TciTestComponentKindType kind, TciType componentType, const std::string &name);
      ~CTestComponent();
      
      const std::string &Name() const;
      TriComponentId Id() const;
      
      void Start(TciBehaviourIdType behavior, TciParameterListType parameterList);
      
    };
    
    CTestComponent::CTestComponent(flowGraphNode, bool keepAlive):
      STATUS(ACTIVE), DEFAULT_POINTER(0), E_VERDICT(NONE), TIMER_GUARD(binding("GUARD", IDLE, 0)), KEEP_ALIVE(keepAlive)
    {
      controlStack.push(flowGraphNode);
    }
    
//     CTestComponent::NextControl(bool)
//     {
//       successorNode = controlStack.Next(bool).Top();
//       controlStack.Pop();
//       controlStack.Push(successorNode);
//     }

    class CObject {
      const std::string _name;
      bool _inited;
      
      virtual void Initialize() = 0;
    public:
      CObject(const std::string &name);
      virtual ~CObject();
      
      const std::string &Name() const;
      void Init();
    };
    
    class CModule;
    
    class CTestCase : public CObject {
      class CState {
        // ALL_PORT_STATES - a list of states of different ports
        // MTC - MTC reference
        // TC_VERDICT - actual global test verdict of a test case, updated after every test component termination
      };

      TriComponentId _mtcId;
      CModule *_module;
    public:
      CTestCase(const std::string &name);
      virtual ~CTestCase();
      
      void Register(CModule &module);
      CModule &Module() const throw(EOperationFailed);
      
      TciParameterTypeListType Parameters() const;
      TriPortIdList Ports() const;
      
      void Start(TciParameterListType parameterlist);
      void Execute(TciTestCaseIdType testCaseId, TriPortIdList tsiPortList);
      void Stop();
    };
    
    
    class CModule : public CObject {
    public:
      class CParameter : public CObject {
        TciValue _defaultValue;
        TciValue _value;
      public:
        CParameter(const std::string &name);
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
      
      
      typedef std::vector<CParameter *> ParameterList;
      typedef std::vector<CTestCase *> TCList;
      
      bool _running;
      ParameterList _parameterList;
      TCList _tcList;
      CTestCase *_tc;
      
      // temporary variables
      mutable TciModuleParameterType *__modParList;
      mutable TciTestCaseIdType *__tcIdList;
      
    protected:
      void Register(CParameter *parameter);
      void Register(CTestCase *tc);

      void ParametersSet() throw(freettcn::EOperationFailed);
    public:
      CModule(const std::string &name);
      virtual ~CModule() = 0;
      
      bool Running() const;
      void Reset();
      
      TciModuleParameterListType Parameters() const;
      
      TciTestCaseIdListType TestCases() const;
      CTestCase &TestCase(const std::string &tcId) const throw(ENotFound);
      void TestCase(CTestCase *tc);
      CTestCase &TestCase() const throw(EOperationFailed);
      
      TriComponentId ControlStart();
      void ControlStop() throw(EOperationFailed);
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
    
    
    class CTTCNExecutable {
    private:
      static CTTCNExecutable _instance;
      
      CModule *_rootModule;
      
    public:
      static CTTCNExecutable &Instance();
      
      CTTCNExecutable();
      virtual ~CTTCNExecutable();
      
      void Reset();
      
      void RootModule(CModule &module);
      CModule &RootModule() const throw(ENotFound);
      
      TriComponentId TestComponentCreate(TciTestComponentKindType kind, TciType componentType, String name);
      void TestComponentStart(TriComponentId component, TciBehaviourIdType behavior, TciParameterListType parameterList);
      void TestComponentTerminated(TriComponentId component, TciVerdictValue verdict);

      void Connect(TriPortId fromPort, TriPortId toPort);
      void Disconnect(TriPortId fromPort, TriPortId toPort);
      void Map(TriPortId fromPort, TriPortId toPort);
      void Unmap(TriPortId fromPort, TriPortId toPort);
    };
    
  } // namespace TE
  
} // namespace freettcn



#endif /* __TE_H__ */



