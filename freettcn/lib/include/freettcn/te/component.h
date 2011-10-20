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
 * @file   component.h
 * @author Mateusz Pusz
 * @date   Wed Apr 25 10:55:15 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __COMPONENT_H__
#define __COMPONENT_H__


#include <freettcn/etsi/tri.h>
#include <freettcn/ttcn3/tciType.h>
#include <freettcn/tools/nonCopyable.h>
// #include <freettcn/ttcn3/ttcnArray.h>
// #include <freettcn/ttcn3/verdict.h>
// #include <freettcn/te/initObject.h>
// #include <freettcn/tools/tools.h>
// #include <list>

namespace freettcn {
  
  namespace TE {

    using namespace ORG_ETSI_TTCN3_TCI;
    using namespace ORG_ETSI_TTCN3_TRI;

    class CBehaviour;
    class CPort;
    // class CPortType;
    // class CTimer;
    // class CTestCase;
    
    class CTypeComponent : public CType {
    public:
       // private:
    //   std::shared_ptr<CTriPortIdArray> _portIdArray;
      
    // protected:
    //   void Register(std::shared_ptr<CTriPortId> id);
    //   void Init();
      
    protected:
      CTypeComponent(const CTypeComponent &) = default;

    public:
      CTypeComponent(const std::shared_ptr<const TciModuleId> &moduleId,
                     const Tstring &name);
      CTypeComponent(CTypeComponent &&) = default;
      ~CTypeComponent();
      
      TciType *clone() const override  { return new CTypeComponent(*this); }
      TciValue *newInstance() override;
      
    //   const CTriPortIdArray &Ports() const;
    //   unsigned int PortInfoNum() const;
    //   const CPortInfo &PortInfo(unsigned int idx) const;
    };
    
    
    class CTypeComponentControl : public CTypeComponent {
    //   class CInstance : public CTestComponentType::CInstanceLocal {
    //     virtual void Initialize();
    //   public:
    //     CInstance(const CType &type);
    //   };
    protected:
      CTypeComponentControl(const CTypeComponentControl &) = default;
    public:
      CTypeComponentControl();
      CTypeComponentControl(CTypeComponentControl &&) = default;
      ~CTypeComponentControl() = default;
      TciValue *newInstance() override;
    };
    
    
    class CComponent : CNonCopyable {
      std::shared_ptr<const TriComponentId> _id;
      
      // // not allowed
      // const Tstring &getValueEncoding() const override;
      // const Tstring &getValueEncodingVariant() const override;
      // Tboolean notPresent() const override;
    public:
      CComponent(const std::shared_ptr<const TciType> &type,
                 TciTestComponentKind kind,
                 const Tstring *name);
      CComponent(CComponent &&) = default;
      ~CComponent() = default;
      
      const std::shared_ptr<const TriComponentId> &Id() const { return _id; }
      
      void Start(const CBehaviour &behavior, const TciParameterList *parameterList);
      void Stop();
      CPort &Port(const TriPortId &id);

      Tboolean Running() const;
      Tboolean Done() const;
      Tboolean Alive() const;
      Tboolean Killed() const;
      
      //   CInstance(const CType &type);
      //   ~CInstance();
        
      //   virtual const TriComponentId &Id() const  = 0;
      //   virtual TciTestComponentKind Kind() const  = 0;
        
      //   virtual void Start(const CBehavior &behavior, TciParameterListType parameterList) = 0;
      //   virtual void Stop() = 0;
      //   virtual void Kill() = 0;
        
      //   const TriPortId &PortId(const char *name, int idx) const;
    };
      

    class CComponentMTC : public CComponent {
    public:
      CComponentMTC(const std::shared_ptr<const TciType> &type,
                    TciTestComponentKind kind,
                    const Tstring *name);
      CComponentMTC(CComponentMTC &&) = default;
      ~CComponentMTC() = default;
    };


    class CComponentPTC : public CComponent {
    public:
      CComponentPTC(const std::shared_ptr<const TciType> &type,
                    TciTestComponentKind kind,
                    const Tstring *name);
      CComponentPTC(CComponentPTC &&) = default;
      ~CComponentPTC() = default;
    };


    class CComponentAlive : public CComponentPTC {
    public:
      CComponentAlive(const std::shared_ptr<const TciType> &type,
                      TciTestComponentKind kind,
                      const Tstring *name);
      CComponentAlive(CComponentAlive &&) = default;
      ~CComponentAlive() = default;
    };


      // class CInstanceRemote : public CInstance {
      // // public:
      // //   enum TStatus {
      // //     IDLE,
      // //     ACTIVE,
      // //     TERMINATED,
      // //     KILLED
      // //   };
        
      // // private:
      // //   const TciTestComponentKind _kind;
      // //   TStatus _status;
      // public:
      //   CInstanceRemote(const std::shared_ptr<const TciType> &type);

      // //   CInstanceRemote(const CType &type, const TriComponentId &id, TciTestComponentKindType kind);
        
      // //   virtual TciTestComponentKind Kind() const;
        
      // //   virtual void Start(const CBehavior &behavior, TciParameterListType parameterList);
      // //   virtual void Stop();
      // //   virtual void Kill();
        
      // //   TStatus Status() const;
      // };
      
      
      // class CInstanceLocal : public CInstance { //, public CInitObject {
      // // public:
      // //   enum TStatus {
      // //     NOT_INITED,                               /**< created but Init() not run */
      // //     ACTIVE,
      // //     SNAPSHOT,                                 /**< active but in the evaluation phase of a snapshot */
      // //     REPEAT,                                   /**< active and in an 'alt' statement that should be
      // //                                                  reevaluated due to a 'repeat' statement */
      // //     BLOCKED                                   /**< module control is blocked during the execution of
      // //                                                  the test case;
      // //                                                  test components are blocked during the creation of
      // //                                                  other test components, and when they wait for being
      // //                                                  started */
      // //   };
        
      // //   class ENotStarted : public freettcn::EOperationFailed {};
        
      // //   class CScope {
      // //     typedef std::vector<CType::CInstance *> CValueArray;
      // //     typedef std::vector<CTimer *> CTimerArray;
          
      // //     const char *_kind;
      // //     CScope * const _up;
      // //     CValueArray _valueArray;
      // //     CTimerArray _timerArray;
      // //   public:
      // //     CScope(const char *kind, CScope *up);
      // //     ~CScope();
      // //     const char *Kind() const;
      // //     CScope *Up() const;;
          
      // //     void Register(CType::CInstance *value);
      // //     void Register(CTimer *timer);
      // //     CType::CInstance &Value(unsigned int valueIdx) const;
      // //     CTimer &Timer(unsigned int timerIdx) const;
      // //   };
        
      // // private:
      // //   typedef std::vector<CPort *> CPortArray;
      // //   typedef std::list<const CTimer *> CTimerList;
        
      // //   // test componnent info
      // //   TciTestComponentKind _kind;
      // //   CModule *_module;
      // //   CPortArray _portArray;
      // //   CTimer *_startTimer;
        
      // //   // test component dynamic state
      // //   TStatus _status;                          /**< describes the status of test component */
      // //   //         CCommandQueue _controlStack;              /**< a stack of flow graph node references; the top element is the flow graph node that has to be interpreted next */
      // //   //         TDefaultList _defaultList;                /**< a list of activated defaults; a list of pointers to the start nodes of activated defaults; the list in reverse order of activation */
      // //   // DEFAULT_POINTER (next default that has to be evaluated if the actual default terminates unsuccessfully)
      // //   // VALUE_STACK (CStack) (not used)
      // //   CTypeVerdict::CValue _verdict;         /**< actual local verdict of a test component;
      // //                                                ignored if an entity state represents the module control */
      // //   CTimer *_guardTimer;                      /**< special timer which is necessary to guard the execution time of test cases and the duration of call operations */
      // //   // DATA_STATE (CList) (list of list of variable bindings)
      // //   // TIMER_STATE (wtf ???)
      // //   // PORT_REF (wtf ???)
      // //   // SNAP_ALIVE (supports snapshot semantics of test component; when a snapshot is taken, a copy of the ALL_ENTITY_STATES list of module state will be assigned)
      // //   // SNAP_DONE (supports snapshot semantics of test component; when a snapshot is taken, a copy of the DONE list of module state will be assigned)
      // //   // SNAP_KILLED (supports snapshot semantics of test component; when a snapshot is taken, a copy of the KILLED list of module state will be assigned)
      // //   // KEEP_ALIVE (indicated wheter the entity can be restarted after its termination or not; 'true' if the entity can be restarted)
      // //   CTimerList _explicitTimers;
      // //   CTimerList _implicitTimers;
      // //   const CBehavior *_behavior;
      // //   CScope *_scope;
      // //   unsigned int _behaviorOffset;
        
      // //   void ScopePush(const char *kind);
      // //   void ScopePop();
        
      // public:
      //   CInstanceLocal(const std::shared_ptr<const TciType> &type);
        
      // //   CInstanceLocal(const CType &type);
      // //   ~CInstanceLocal();
        
      // //   virtual TciTestComponentKind Kind() const;
        
      // //   virtual void Start(const CBehavior &behavior, TciParameterListType parameterList);
      // //   virtual void Stop();
      // //   virtual void Kill();
        
      // //   TStatus Status() const;
      // //   void Status(TStatus status);
      // //   CModule &Module() const;
        
      // //   void Init(CModule &module, TciTestComponentKind kind, const char *name);
      // //   void Reset();
        
      // //   void Verdict(const char *src, int line, TVerdict verdict);
        
      // //   CPort &Port(const char *name, int idx) const;
        
      // //   void Run(unsigned int offset);
      // //   void Execute(const char *src, int line, CTestCase &testCase, TriTimerDuration duration, int returnOffset);
        
      // //   void TimerAdd(const CTimer &timer, bool implicit = false);
      // //   void TimerRemove(const CTimer &timer, bool implicit = false);
        
      // //   //       void Map(const CPort &fromPort, const CPort &toPort);
        
      // //   void ScopeEnter(const char *src, int line, const char *kind);
      // //   CScope &Scope() const;
      // //   void ScopeLeave(const char *src, int line);
        
      // //   void StopReq(const char *src, int line, CInstanceRemote *comp = 0);
      // //   void StopAllReq(const char *src, int line);
        
      // //   void ConnectReq(const TriPortId &port1, const TriPortId &port2);
      // //   void DisconnectReq(const TriPortId &port1, const TriPortId &port2);
      // //   void MapReq(const TriPortId &port1, const TriPortId &port2);
      // //   void UnmapReq(const TriPortId &port1, const TriPortId &port2);
      // };

    
  } // namespace TE
  
} // namespace freettcn


#endif /* __COMPONENT_H__ */
