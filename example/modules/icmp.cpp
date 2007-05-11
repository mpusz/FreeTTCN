//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) usage example.

// This example is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This example is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this example; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   ip.cpp
 * @author Mateusz Pusz
 * @date   Sun Apr  8 19:33:57 2007
 * 
 * @brief  
 * 
 * 
 */

#include <freettcn/te/module.h>
#include <freettcn/te/testComponent.h>
#include <freettcn/te/testCase.h>
#include <freettcn/te/behavior.h>
#include <freettcn/te/port.h>
#include <freettcn/te/command.h>
#include <freettcn/te/sourceData.h>


namespace freettcn {
  
  namespace icmp {

//     // ********** TYPES ***********
    
//     class CICMPPingDataType {
//     public:
//       int id;
//       int seqNumber;
//       std::string *data;
//       CICMPPingDataType(): data(0) {};
//       virtual ~CICMPPingDataType()
//       {
//         if (data)
//           delete data;
//       }
//     };
    
//     class CICMPDataType {
//     public:
//       enum Selector {
//         SELECTOR_ping
//       };
//       Selector _selector;
      
//       union {
//         CICMPPingDataType *ping;
//       };
//       CICMPDataType(): ping(0) {};
//       virtual ~CICMPDataType()
//       {
//         if (ping)
//           delete ping;
//       }
//     };
    
//     class CICMPMsg {
//     public:
//       int msgType;
//       int code;
//       int *crc;
//       CICMPDataType data;
//       CICMPMsg(): crc(0) {};
//       virtual ~CICMPMsg()
//       {
//         if (crc)
//           delete crc;
//       }
//     };
    
    
    // ************************* P O R T S *****************************
    
    class CICMPPortType : public freettcn::TE::CPortType {
    public:
      class CInstance : public freettcn::TE::CPortType::CInstance {
        virtual void Initialize();
      public:
        CInstance(const freettcn::TE::CTestComponentType::CInstance &component,
                  const char *name);
        ~CInstance();
      };
      
    public:
      CICMPPortType(const freettcn::TE::CModule &module) :
        freettcn::TE::CPortType(module, "ICMPPort") {};
    };
    
    
    
    
    
    
    // ******************** C O M P O N E N T S ************************
    
    class CICMPComponentType : public freettcn::TE::CTestComponentType {
    public:
      class CInstance : public freettcn::TE::CTestComponentType::CInstance {
        virtual void Initialize();
      public:
        CICMPPortType::CInstance *icmpPort;
        CInstance(const freettcn::TE::CType &type);
        ~CInstance();
      };
      
    public:
      CICMPComponentType(const freettcn::TE::CModule &module);
      virtual CInstance *InstanceCreate(bool omit = false) const { return new CInstance(*this); }
    };
    
    
    class CIPStackType : public freettcn::TE::CTestComponentType {
    public:
      class CInstance : public freettcn::TE::CTestComponentType::CInstance {
        virtual void Initialize();
      public:
        CICMPPortType::CInstance *icmpPort;
        CInstance(const freettcn::TE::CType &type);
        ~CInstance();
      };
      
    public:
      CIPStackType(const freettcn::TE::CModule &module);
      virtual CInstance *InstanceCreate(bool omit = false) const { return new CInstance(*this); }
    };
    
        
    
    
//     // ********** TEMPLATES ***********
    
//     class Ct_EchoRequest : public CICMPMsg {
//     public:
//       Ct_EchoRequest()
//       {
//         msgType = 8;
//         code = 0;
//         crc = new int(0);
//         data._selector = CICMPDataType::SELECTOR_ping;
//         data.ping = new CICMPPingDataType;
//         data.ping->id = 1234;
//       }
      
//       const Ct_EchoRequest &Template(const int &seqNum)
//       {
//         data.ping->seqNumber = seqNum;
//         return *this;
//       }
//     };
    
//     Ct_EchoRequest t_EchoRequest;
    
//     class Ct_EchoReply : public CICMPMsg {
//     public:
//       Ct_EchoReply()
//       {
//         msgType = 0;
//         code = 0;
//       }
      
//       const Ct_EchoReply &Template(const Ct_EchoRequest &echoReq)
//       {
//         data = echoReq.data;
//         return *this;
//       }
//     };
    
//     Ct_EchoReply t_EchoReply;
    
    

//     class CTestCase_ICMP_Ping_1_Scope_1 {
//     public:
//       CIPStack system;
//       CICMPComponent mtc;
//       freettcn::TE::CTimer *t;
//       int count;
      
//       CTestCase_ICMP_Ping_1_Scope_1() : t(0), count(0) {};
//       ~CTestCase_ICMP_Ping_1_Scope_1()
//       {
//         if (t)
//           delete t;
//       }
//     };
    
//     class CTestCase_ICMP_Ping_1_Command_1 : public freettcn::TE::CCommand {
//       freettcn::TE::CTestComponent &_comp;
//       CTestCase_ICMP_Ping_1_Scope_1 &_scope;
      
//     public:
//       void Run()
//       {
//         _comp.Map(_scope.mtc.icmpPort, _scope.system.icmpPort);
        
//         _comp.Verdict(freettcn::TE::VERDICT_FAIL);
        
//         _scope.t = new freettcn::TE::CTimer(1.0);
        
//         _scope.mtc.icmpPort.Send(t_EchoRequest.Template(_scope.count));
//       }
//     };
    
    
    
    
    
    // ******************** T E S T   C A S E S ************************
    
    class CTC_ICMPPing_1 : public freettcn::TE::CTestCase {
      class CBehavior : public freettcn::TE::CBehavior {
      public:
        CBehavior(freettcn::TE::CModule &module);
        virtual void Enqueue(freettcn::TE::CTestComponentType::CInstance &comp) const;
      };
      
      virtual void Initialize();
    public:
      CTC_ICMPPing_1(freettcn::TE::CModule &module);
    };
    
    class CTC_ICMPPing_2 : public freettcn::TE::CTestCase {
      class CBehavior : public freettcn::TE::CBehavior {
      public:
        CBehavior(freettcn::TE::CModule &module);
        virtual void Enqueue(freettcn::TE::CTestComponentType::CInstance &comp) const;
      };
      
      virtual void Initialize();
    public:
      CTC_ICMPPing_2(freettcn::TE::CModule &module);
    };
    
    
    
    
    // ************************ M O D U L E ****************************
    
    class CModule : public freettcn::TE::CModule {
    public:
      class CType {
        static CType *_instance;
        
        const CICMPPortType *_icmpPort;
        const CICMPComponentType *_icmpComponent;
        const CIPStackType *_ipStack;
        CTC_ICMPPing_1 *_tc_ICMPPing_1;
        CTC_ICMPPing_2 *_tc_ICMPPing_2;
        
        CType();
        CType& operator=(CType&);  // Disallowed
        CType(const CType&);       // Disallowed
        
      public:
        static CType &Instance();
        
        ~CType();
        void Init();
        
        const CICMPPortType &ICMPPort() const { return *_icmpPort; }
        const CICMPComponentType &ICMPComponent() const { return *_icmpComponent; }
        const CIPStackType &IPStack() const { return *_ipStack; }
        CTC_ICMPPing_1 &TC_ICMPPing_1() const { return *_tc_ICMPPing_1; }
        CTC_ICMPPing_2 &TC_ICMPPing_2() const { return *_tc_ICMPPing_2; }
      };
      
      class CBehavior : public freettcn::TE::CBehavior {
      public:
        CBehavior(freettcn::TE::CModule &module);
        virtual void Enqueue(freettcn::TE::CTestComponentType::CInstance &comp) const;
      };
      
    private:
      static CModule _instance;
      
      CType *_types;
      
      CModule();
      virtual void Initialize();
      virtual void Cleanup();
    public:
      static CModule &Instance() { return _instance; }
    };
    
    
    
    
    
    // ************************ S T A T I C ****************************
    
    CModule CModule::_instance;
    CModule::CType *CModule::CType::_instance = 0;
    
    
    
    
    
    
    // ************************* P O R T S *****************************
    
    CICMPPortType::CInstance::CInstance(const freettcn::TE::CTestComponentType::CInstance &component,
                                        const char *name):
      freettcn::TE::CPortType::CInstance(CModule::CType::Instance().ICMPPort(), component, name)
    {
    }
    
    CICMPPortType::CInstance::~CInstance()
    {
    }

    void CICMPPortType::CInstance::Initialize()
    {
    }
    
    
    
    
    // ******************** C O M P O N E N T S ************************
    
    // ICMPComponent
    
    CICMPComponentType::CICMPComponentType(const freettcn::TE::CModule &module):
      freettcn::TE::CTestComponentType(&module, "ICMPComponent")
    {
      Register(CModule::CType::Instance().ICMPPort(), "icmpPort");
    }
    
    CICMPComponentType::CInstance::CInstance(const freettcn::TE::CType &type):
      freettcn::TE::CTestComponentType::CInstance(type),
      icmpPort(0)
    {
    }
    
    CICMPComponentType::CInstance::~CInstance()
    {
    }
    
    void CICMPComponentType::CInstance::Initialize()
    {
      // ports declaration
      icmpPort = new CICMPPortType::CInstance(*this, "icmpPort");
      Module().TestCase()->Register(icmpPort);
      
      // constant definition
      
      // variable declaration
      
      // timer declaration
    }
    
    
    
    // IPStack
    
    CIPStackType::CIPStackType(const freettcn::TE::CModule &module):
      freettcn::TE::CTestComponentType(&module, "IPStack")
    {
      Register(CModule::CType::Instance().ICMPPort(), "icmpPort");
    }
    
    CIPStackType::CInstance::CInstance(const freettcn::TE::CType &type):
      freettcn::TE::CTestComponentType::CInstance(type),
      icmpPort(0)
    {
    }
    
    CIPStackType::CInstance::~CInstance()
    {
      if (icmpPort)
        delete icmpPort;
    }
    
    void CIPStackType::CInstance::Initialize()
    {
      icmpPort = new CICMPPortType::CInstance(*this, "icmpPort");
      Module().TestCase()->Register(icmpPort);
    }
    
    

    
    
    
    // ******************** T E S T   C A S E S ************************
    
    // ICMP_Ping_1
    
    CTC_ICMPPing_1::CTC_ICMPPing_1(freettcn::TE::CModule &module):
      freettcn::TE::CTestCase(module, "TC_ICMPPing_1", new freettcn::TE::CSourceData("icmp.ttcn", 76),
                              CModule::CType::Instance().ICMPComponent(), new CBehavior(module),
                              &CModule::CType::Instance().IPStack())
    {
    }
    
    void CTC_ICMPPing_1::Initialize()
    {
      // register test case parameters
    }
    
    
    
    CTC_ICMPPing_1::CBehavior::CBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "TC_ICMPPing_1")
    {
    }
    
    void CTC_ICMPPing_1::CBehavior::Enqueue(freettcn::TE::CTestComponentType::CInstance &comp) const
    {
//       comp.CmdQueue().Enqueue(new CCmdInitScopeWithRunsOn(comp));
      
      // <parameter-handling>
      
      // <statement-block>
      
      // add automatically if 'self.stop' not included in *.ttcn file
      comp.Enqueue(new freettcn::TE::CCmdStopMTC(comp, new freettcn::TE::CSourceData("icmp.ttcn", 115)));
    }
    
    
    
    // ICMP_Ping_2
    
    CTC_ICMPPing_2::CTC_ICMPPing_2(freettcn::TE::CModule &module):
      freettcn::TE::CTestCase(module, "TC_ICMPPing_2", new freettcn::TE::CSourceData("icmp.ttcn", 109),
                              CModule::CType::Instance().ICMPComponent(), new CBehavior(module))
    {
    }
    
    void CTC_ICMPPing_2::Initialize()
    {
      // register test case parameters
    }
    
    
    CTC_ICMPPing_2::CBehavior::CBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "TC_ICMPPing_2")
    {
    }
    
    void CTC_ICMPPing_2::CBehavior::Enqueue(freettcn::TE::CTestComponentType::CInstance &comp) const
    {
      printf("\n\n@@@@@@@ TEST CASE 2 @@@@@@@@@@\n\n\n");
      
//       self.stop();
    }
    

    
    
    
    
    // ************************ M O D U L E ****************************
    
    CModule::CModule():
      freettcn::TE::CModule("icmp"), _types(0)
    {
    }
    
    void CModule::Initialize()
    {
      // init module types
      _types = &CType::Instance();
      
      // register module parameters
      
      // register control behavior
      Register(new CBehavior(*this), new freettcn::TE::CSourceData("icmp.ttcn", 115));
      
      // add test cases
      TestCaseAdd(CModule::CType::Instance().TC_ICMPPing_1());
      TestCaseAdd(CModule::CType::Instance().TC_ICMPPing_2());
    }
    
    void CModule::Cleanup()
    {
      // cleanup base class
      freettcn::TE::CModule::Cleanup();
      
      // delete module specific types
      if (_types) {
        delete _types;
        _types = 0;
      }
    }
    
    
    
    CModule::CType::CType():
      _icmpPort(0),
      _icmpComponent(0), _ipStack(0),
      _tc_ICMPPing_1(0), _tc_ICMPPing_2(0)
    {
    }
    
    CModule::CType::~CType()
    {
      if (_icmpPort)
        delete _icmpPort;

      if (_icmpComponent)
        delete _icmpComponent;
      if (_ipStack)
        delete _ipStack;

      if (_tc_ICMPPing_1)
        delete _tc_ICMPPing_1;
      if (_tc_ICMPPing_2)
        delete _tc_ICMPPing_2;
      
      _instance = 0;
    }

    CModule::CType &CModule::CType::Instance()
    {
      if (!_instance) {
        _instance = new CModule::CType;
        _instance->Init();
      }
      return *_instance;
    }
    
    void CModule::CType::Init()
    {
      CModule &module = CModule::Instance();
      
      _icmpPort = new CICMPPortType(module);
      _icmpComponent = new CICMPComponentType(module);
      _ipStack = new CIPStackType(module);
      _tc_ICMPPing_1 = new CTC_ICMPPing_1(module);
      _tc_ICMPPing_2 = new CTC_ICMPPing_2(module);
    }
    
    
    CModule::CBehavior::CBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "_control_")
    {
    }
    
    void CModule::CBehavior::Enqueue(freettcn::TE::CTestComponentType::CInstance &comp) const
    {
//       comp.CmdQueue().Enqueue(new CCmdInitComponentScope(comp));
      
//       // <statement-block>
      
//       freettcn::TE::CTestComponentType::CInstance::TStatus status = NOT_INITED;
//       state = comp.Status();
//       comp.Status(freettcn::TE::CTestComponentType::CInstance::BLOCKED);
//       //       CModule::CType::Instance().TC_ICMPPing_1().Start("icmp.ttcn", 116, 0, 0, 0);
//       comp.Status() = status;
      
      // add automatically if 'stop' not included in *.ttcn file
      comp.Enqueue(new freettcn::TE::CCmdStopEntityOp(comp, new freettcn::TE::CSourceData("icmp.ttcn", 115)));
    }
    
  } // namespace icmp

} // namespace freettcn
