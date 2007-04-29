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
 * @file   testComponent.h
 * @author Mateusz Pusz
 * @date   Wed Apr 25 10:55:15 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TESTCOMPONENT_H__
#define __TESTCOMPONENT_H__


extern "C" {
#include <freettcn/ttcn3/tci.h>
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/te/value.h>
#include <freettcn/te/type.h>
#include <string>


namespace freettcn {
  
  namespace TE {
    
    enum VerdictType_t {
      VERDICT_NONE,
      VERDICT_PASS,
      VERDICT_INCONC,
      VERDICT_FAIL,
      VERDICT_ERROR
    };
    
    class CBehavior;
//     class CPort;
    
    class CTestComponent : public CValue {
    public:
      class ENotInited : public freettcn::EOperationFailed {};
      
    private:
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
      
      bool _inited;
      CModule *_module;
      TciTestComponentKindType _kind;
      TriComponentId _id;
    public:
      CTestComponent(const CType &type);
      ~CTestComponent();
      
      void Init(CModule &module, TciTestComponentKindType kind, String name);
      const TriComponentId &Id() const throw(ENotInited);
      
      virtual void Start(const CBehavior &behavior, TciParameterListType parameterList) throw(ENotInited);
      
//       void Map(const CPort &fromPort, const CPort &toPort) throw(ENotInited);
//       void Verdict(VerdictType_t value);
    };
    
    
//     CTestComponent::CTestComponent(flowGraphNode, bool keepAlive):
//       STATUS(ACTIVE), DEFAULT_POINTER(0), E_VERDICT(NONE), TIMER_GUARD(binding("GUARD", IDLE, 0)), KEEP_ALIVE(keepAlive)
//     {
//       controlStack.push(flowGraphNode);
//     }
    
//     CTestComponent::NextControl(bool)
//     {
//       successorNode = controlStack.Next(bool).Top();
//       controlStack.Pop();
//       controlStack.Push(successorNode);
//     }

  } // namespace TE
  
} // namespace freettcn


#endif /* __TESTCOMPONENT_H__ */
