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

#include "module.h"
#include "testComponent.h"
#include "testCase.h"
#include "behavior.h"
#include "port.h"
#include "sourceData.h"


namespace freettcn {
  
  namespace IP {

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
    
    
    // ********** PORTS ***********
    
    class CICMPPort : public freettcn::TE::CPort {
    };

    
    // ********** COMPONENTS ***********
    
    class CICMPComponent : public freettcn::TE::CTestComponent {
    public:
      CICMPPort icmpPort;
      CICMPComponent(const freettcn::TE::CType &type);
    };
    
    class CIPStack : public freettcn::TE::CTestComponent {
    public:
      CICMPPort icmpPort;
      CIPStack(const freettcn::TE::CType &type);
    };

    
    
    // ********** COMPONENTS TYPES ***********
    
    class CICMPComponentType : public freettcn::TE::CTestComponentType {
      static CICMPComponentType _instance;
    public:
      static CICMPComponentType &Instance();
      CICMPComponentType(const freettcn::TE::CModule &module);
      virtual freettcn::TE::CValue *InstanceCreate(bool omit = false) const;
    };
    
    class CIPStackType : public freettcn::TE::CTestComponentType {
      static CIPStackType _instance;
    public:
      static CIPStackType &Instance();
      CIPStackType(const freettcn::TE::CModule &module);
      virtual freettcn::TE::CValue *InstanceCreate(bool omit = false) const;
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
    
    
    
    
    
    // ********************* T E S T   C A S E *************************
    
    class CTestCase_ICMP_Ping_1 : public freettcn::TE::CTestCase {
      class CBehavior : public freettcn::TE::CBehavior {
      public:
        CBehavior(freettcn::TE::CModule &module);
        virtual void Run();
      };
      
      virtual void Initialize();
    public:
      CTestCase_ICMP_Ping_1(freettcn::TE::CModule &module);
    };
    
    class CTestCase_ICMP_Ping_2 : public freettcn::TE::CTestCase {
      class CBehavior : public freettcn::TE::CBehavior {
      public:
        CBehavior(freettcn::TE::CModule &module);
        virtual void Run();
      };
      
      virtual void Initialize();
    public:
      CTestCase_ICMP_Ping_2(freettcn::TE::CModule &module);
    };

    

    
    // *********************** C O N T R O L ***************************
    
    class CControlBehavior : public freettcn::TE::CBehavior {
    public:
      CControlBehavior(freettcn::TE::CModule &module);
      virtual void Run();
    };
    

    
    
    // ************************ M O D U L E ****************************
    
    class CModule : public freettcn::TE::CModule {
      static CModule _instance;
      virtual void Initialize();
    public:
      static CModule &Instance();
      CModule();
    };
    
    
    
    
    
    // ************************ S T A T I C ****************************
    
    CModule CModule::_instance;
    CICMPComponentType CICMPComponentType::_instance(CModule::Instance());
    CIPStackType CIPStackType::_instance(CModule::Instance());
    
    
    
    
    // ********** COMPONENTS ***********
    
    CICMPComponent::CICMPComponent(const freettcn::TE::CType &type):
      freettcn::TE::CTestComponent(type)
    {
    }
    
    CIPStack::CIPStack(const freettcn::TE::CType &type):
      freettcn::TE::CTestComponent(type)
    {
    }
    
    

    // ********** COMPONENTS TYPES ***********

    CICMPComponentType &CICMPComponentType::Instance()
    {
      return _instance;
    }

    CICMPComponentType::CICMPComponentType(const freettcn::TE::CModule &module):
      freettcn::TE::CTestComponentType(&module, "ICMPComponent")
    {
    }
    
    freettcn::TE::CValue *CICMPComponentType::InstanceCreate(bool omit /* false */) const
    {
      return new CICMPComponent(*this);
    }
    
    

    CIPStackType &CIPStackType::Instance()
    {
      return _instance;
    }

    CIPStackType::CIPStackType(const freettcn::TE::CModule &module):
      freettcn::TE::CTestComponentType(&module, "IPStack")
    {
    }
    
    freettcn::TE::CValue *CIPStackType::InstanceCreate(bool omit /* false */) const
    {
      return new CIPStack(*this);
    }
    


    // ********************* T E S T   C A S E *************************

    CTestCase_ICMP_Ping_1::CTestCase_ICMP_Ping_1(freettcn::TE::CModule &module):
      freettcn::TE::CTestCase(module, "ICMP_Ping_1", new freettcn::TE::CSourceData("ip.ttcn", 76),
                              CICMPComponentType::Instance(), new CBehavior(module),
                              &CIPStackType::Instance())
    {
    }
    
    void CTestCase_ICMP_Ping_1::Initialize()
    {
      // register test case parameters
    }
    
    
    
    CTestCase_ICMP_Ping_1::CBehavior::CBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "TC_ICMPPing_1")
    {
    }
    
    void CTestCase_ICMP_Ping_1::CBehavior::Run()
    {
    }

    
    
    CTestCase_ICMP_Ping_2::CTestCase_ICMP_Ping_2(freettcn::TE::CModule &module):
      freettcn::TE::CTestCase(module, "ICMP_Ping_2", new freettcn::TE::CSourceData("ip.ttcn", 109),
                              CICMPComponentType::Instance(), new CBehavior(module))
    {
    }
    
    void CTestCase_ICMP_Ping_2::Initialize()
    {
      // register test case parameters
    }
    
    
    CTestCase_ICMP_Ping_2::CBehavior::CBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "TC_ICMPPing_2")
    {
    }
    
    void CTestCase_ICMP_Ping_2::CBehavior::Run()
    {
    }



    // *********************** C O N T R O L ***************************

    CControlBehavior::CControlBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "_control_")
    {
    }

    void CControlBehavior::Run()
    {
//       _module.TestCase(0).Execute();
//       _module.TestCase(1).Execute(3.0);
    }



    // ************************ M O D U L E ****************************

    CModule &CModule::Instance()
    {
      return _instance;
    }
    
    CModule::CModule():
      freettcn::TE::CModule("IP")
    {
    }
    
    void CModule::Initialize()
    {
      // register module parameters
      
      // register module test cases
      Register(new CTestCase_ICMP_Ping_1(*this));
      Register(new CTestCase_ICMP_Ping_2(*this));
      
      // register control behavior
      Register(new CControlBehavior(*this), new freettcn::TE::CSourceData("ip.ttcn", 115));
    }

    
  } // namespace IP

} // namespace freettcn
