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
#include <freettcn/te/verdict.h>
#include <freettcn/te/idObject.h>
#include <freettcn/tools/exception.h>
#include <freettcn/tools/tools.h>
#include <string>
#include <vector>
#include <list>

namespace freettcn {
  
  namespace TE {
    
    class CBehavior;
    class CPortType;
    class CTimer;
    class CSourceData;
    class CTestCase;
    class CScope;
    
    class CTestComponentType : public CType {
    public:
      class CInstance : public CType::CInstance, public CIdObject {
      public:
        enum TStatus {
          NOT_INITED,                             /**< created but Init() not run */
          ACTIVE,
          SNAPSHOT,                               /**< active but in the evaluation phase of a snapshot */
          REPEAT,                                 /**< active and in an 'alt' statement that should be
                                                     reevaluated due to a 'repeat' statement */
          BLOCKED                                 /**< module control is blocked during the execution of
                                                     the test case;
                                                     test components are blocked during the creation of
                                                     other test components, and when they wait for being
                                                     started */
        };
        
        class ENotInited : public freettcn::EOperationFailed {};
        class ENotStarted : public freettcn::EOperationFailed {};
        
        class CScope {
          CScope * const _up;
        public:
          CScope(CTestComponentType::CInstance &comp, CScope *up);
          CScope *Up() const;
        };
        
      private:
        typedef std::list<const CTimer *> TTimerList;
        
        CModule *_module;
        TciTestComponentKindType _kind;
        TriComponentId _id;
        CTimer *_startTimer;
        
        // test comopnent dynamic state
        TStatus _status;                          /**< describes the status of test component */
//         CCommandQueue _controlStack;              /**< a stack of flow graph node references; the top element is the flow graph node that has to be interpreted next */
//         TDefaultList _defaultList;                /**< a list of activated defaults; a list of pointers to the start nodes of activated defaults; the list in reverse order of activation */
        // DEFAULT_POINTER (next default that has to be evaluated if the actual default terminates unsuccessfully)
        // VALUE_STACK (CStack) (not used)
        CVerdictType::CInstance _verdict;         /**< actual local verdict of a test component;
                                                     ignored if an entity state represents the module control */
        // TIMER_GUARD (special timer which is necessary to guard the execution time of test cases and the duration of call operations; modelled as a timer binding)
        // DATA_STATE (CList) (list of list of variable bindings)
        // TIMER_STATE (wtf ???)
        // PORT_REF (wtf ???)
        // SNAP_ALIVE (supports snapshot semantics of test component; when a snapshot is taken, a copy of the ALL_ENTITY_STATES list of module state will be assigned)
        // SNAP_DONE (supports snapshot semantics of test component; when a snapshot is taken, a copy of the DONE list of module state will be assigned)
        // SNAP_KILLED (supports snapshot semantics of test component; when a snapshot is taken, a copy of the KILLED list of module state will be assigned)
        // KEEP_ALIVE (indicated wheter the entity can be restarted after its termination or not; 'true' if the entity can be restarted)
        TTimerList _explicitTimers;
        TTimerList _implicitTimers;
        const CBehavior *_behavior;
        CScope *_scope;
        int _behaviorOffset;
        
        virtual void Initialize() = 0;
        
      protected:
        CModule &Module() const throw(ENotInited);
        
      public:
        CInstance(const CType &type);
        ~CInstance();
        
        TStatus Status() const;
        void Status(TStatus status);
        
        void Init(CModule &module, TciTestComponentKindType kind, const char *name);
        const TriComponentId &Id() const throw(ENotInited);
        TciTestComponentKindType Kind() const throw(ENotInited);
        
        virtual void Start(const CBehavior &behavior, TciParameterListType parameterList) throw(ENotInited);
        void Execute(const char *src, int line, CTestCase &testCase, TriTimerDuration duration, int returnOffset);
        void Run(int offset) throw(ENotStarted);
        void Stop(const char *src, int line);
        
        void TimerAdd(const CTimer &timer, bool implicit = false);
        void TimerRemove(const CTimer &timer, bool implicit = false) throw(ENotFound);
        
        //       void Map(const CPort &fromPort, const CPort &toPort) throw(ENotInited);
        void Verdict(const char *src, int line, TVerdict verdict);
        
        CScope *Scope() const;
        void ScopePush(CScope &scope);
        void ScopePop() throw(EOperationFailed);
      };

      
    private:
      // types
      typedef std::vector<const TriPortId *> TPortIdList;
      
      // info
      TPortIdList _portIdList;
      
      // temporary variables
      mutable TriPortId **__portIdList;
      
    protected:
      void Register(const CPortType &portType, const char *name, int portIdx = -1);
      
    public:
      CTestComponentType(const CModule *module, const char *name);
      ~CTestComponentType();
      
      TriPortIdList Ports() const;
    };
    
    
    class CControlComponentType : public CTestComponentType {
      class CInstance : public CTestComponentType::CInstance {
        virtual void Initialize();
      public:
        CInstance(const CType &type);
      };
      
    public:
      CControlComponentType();
      virtual CInstance *InstanceCreate(bool omit = false) const;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TESTCOMPONENT_H__ */
