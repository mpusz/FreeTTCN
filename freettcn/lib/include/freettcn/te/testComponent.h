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
#include <freettcn/te/idObject.h>
#include <freettcn/te/verdict.h>
#include <freettcn/te/initObject.h>
#include <freettcn/tools/ttcnWrappers.h>
#include <freettcn/tools/tools.h>
#include <vector>
#include <list>

namespace freettcn {
  
  namespace TE {
    
    class CBehavior;
    class CPortType;
    class CTimer;
    class CTestCase;
    class CPort;
    class CPortInfo;
    
    class CTestComponentType : public CType {
    public:
      class CInstance : public CType::CInstance {
        typedef std::vector<TriPortId *> TPortIdArray;
        
        TPortIdArray _portIdArray;
        
        // not allowed
        bool Omit() const;
        void Omit(bool omit);
        const char *Encoding() const;
        const char *EncodingVariant() const;
        const char *Extension() const;
        
      protected:
        void PortIdArrayCreate();
        
      public:
        CInstance(const CType &type);
        ~CInstance();
        
        virtual const TriComponentId &Id() const  = 0;
        virtual TciTestComponentKindType Kind() const  = 0;
        
        virtual void Start(const CBehavior &behavior, TciParameterListType parameterList) = 0;
        virtual void Stop() = 0;
        virtual void Kill() = 0;
        
        const TriPortId &Port(const char *name, int idx) throw(ENotFound);
      };
      
      
      class CInstanceRemote : public CInstance {
      public:
        enum TStatus {
          IDLE,
          ACTIVE,
          TERMINATED,
          KILLED
        };
        
      private:
        const CTriComponentId _id;
        const TciTestComponentKindType _kind;
        TStatus _status;
      public:
        CInstanceRemote(const CType &type, const TriComponentId &id, TciTestComponentKindType kind);
        
        virtual const TriComponentId &Id() const;
        virtual TciTestComponentKindType Kind() const;
        
        virtual void Start(const CBehavior &behavior, TciParameterListType parameterList);
        virtual void Stop();
        virtual void Kill();
        
        bool operator==(const TriComponentId &id) const;
        TStatus Status() const;
      };
      
      
      class CInstanceLocal : public CInstance, public CIdObject, public CInitObject {
      public:
        enum TStatus {
          NOT_INITED,                               /**< created but Init() not run */
          ACTIVE,
          SNAPSHOT,                                 /**< active but in the evaluation phase of a snapshot */
          REPEAT,                                   /**< active and in an 'alt' statement that should be
                                                       reevaluated due to a 'repeat' statement */
          BLOCKED                                   /**< module control is blocked during the execution of
                                                       the test case;
                                                       test components are blocked during the creation of
                                                       other test components, and when they wait for being
                                                       started */
        };
        
        class ENotStarted : public freettcn::EOperationFailed {};
        
        class CScope {
          typedef std::vector<CType::CInstance *> TValueArray;
          typedef std::vector<CTimer *> TTimerArray;
          
          const char *_kind;
          CScope * const _up;
          TValueArray _valueArray;
          TTimerArray _timerArray;
        public:
          CScope(const char *kind, CScope *up);
          ~CScope();
          const char *Kind() const;
          CScope *Up() const;;
          
          void Register(CType::CInstance *value);
          void Register(CTimer *timer);
          CType::CInstance &Value(unsigned int valueIdx) const throw(ENotFound);
          CTimer &Timer(unsigned int timerIdx) const throw(ENotFound);
        };
        
      private:
        typedef std::vector<CPort *> TPortArray;
        typedef std::list<const CTimer *> TTimerList;
        
        // test componnent info
        TriComponentId _id;
        TciTestComponentKindType _kind;
        CModule *_module;
        TPortArray _portArray;
        CTimer *_startTimer;
        
        // test component dynamic state
        TStatus _status;                          /**< describes the status of test component */
        //         CCommandQueue _controlStack;              /**< a stack of flow graph node references; the top element is the flow graph node that has to be interpreted next */
        //         TDefaultList _defaultList;                /**< a list of activated defaults; a list of pointers to the start nodes of activated defaults; the list in reverse order of activation */
        // DEFAULT_POINTER (next default that has to be evaluated if the actual default terminates unsuccessfully)
        // VALUE_STACK (CStack) (not used)
        CVerdictType::CInstance _verdict;         /**< actual local verdict of a test component;
                                                     ignored if an entity state represents the module control */
        CTimer *_guardTimer;                      /**< special timer which is necessary to guard the execution time of test cases and the duration of call operations */
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
        unsigned int _behaviorOffset;
        
        void ScopePush(const char *kind);
        void ScopePop();
        
      public:
        CInstanceLocal(const CType &type);
        ~CInstanceLocal();
        
        virtual const TriComponentId &Id() const;
        virtual TciTestComponentKindType Kind() const;
        
        virtual void Start(const CBehavior &behavior, TciParameterListType parameterList);
        virtual void Stop();
        virtual void Kill();
        
        TStatus Status() const;
        void Status(TStatus status);
        CModule &Module() const throw(ENotInited);
        
        void Init(CModule &module, TciTestComponentKindType kind, const char *name);
        void Reset();
        
        void Verdict(const char *src, int line, TVerdict verdict);
        
        void Run(unsigned int offset) throw(ENotStarted);
        void Execute(const char *src, int line, CTestCase &testCase, TriTimerDuration duration, int returnOffset);
        
        void TimerAdd(const CTimer &timer, bool implicit = false);
        void TimerRemove(const CTimer &timer, bool implicit = false) throw(ENotFound);
        
        //       void Map(const CPort &fromPort, const CPort &toPort) throw(ENotInited);
        
        void ScopeEnter(const char *src, int line, const char *kind);
        CScope &Scope() const throw(ENotFound);
        void ScopeLeave(const char *src, int line);
        
        void StopReq(const char *src, int line, CInstanceRemote *comp = 0);
        void StopAllReq(const char *src, int line) throw(EOperationFailed);
        
        void ConnectReq(const TriPortId &port1, const TriPortId &port2) throw(EOperationFailed);
        void DisconnectReq(const TriPortId &port1, const TriPortId &port2) throw(ENotFound);
        void MapReq(const TriPortId &port1, const TriPortId &port2) throw(EOperationFailed);
        void UnmapReq(const TriPortId &port1, const TriPortId &port2) throw(ENotFound);
      };
      
      
    private:
      // types
      typedef std::vector<const CPortInfo *> TPortInfoArray;
      
      // info
      TPortInfoArray _portInfoArray;
      TriPortIdList _portList;
      
    protected:
      void PortInfoAdd(const CPortType &portType, const char *name, int portIdx);
      void Init();
      
    public:
      CTestComponentType(const CModule *module, const char *name);
      ~CTestComponentType();
      
      TriPortIdList Ports() const;
      unsigned int PortInfoNum() const;
      const CPortInfo &PortInfo(unsigned int idx) const throw(ENotFound);
    };
    
    
    
    
    class CControlComponentType : public CTestComponentType {
      class CInstance : public CTestComponentType::CInstanceLocal {
        virtual void Initialize();
      public:
        CInstance(const CType &type);
      };
      
    public:
      CControlComponentType();
      virtual CInstance *InstanceCreate() const;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TESTCOMPONENT_H__ */
