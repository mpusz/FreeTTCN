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

#include "te.h"


namespace freettcn {
  
  namespace IP {
    
    // ********** TYPES ***********
    
    class CICMPPingDataType {
    public:
      int id;
      int seqNum;
      std::string *data;
      CICMPPingDataType(): data(0) {}
      virtual ~CICMPPingDataType()
      {
        if (data)
          delete data;
      }
    };
    
    class CICMPDataType {
    public:
      enum Selector {
        SELECTOR_ping
      };
      Selector _selector;
      
      union {
        CICMPPingDataType ping
      } u;
      virtual ~CICMPDataType();
    };
    
    class CICMPMsg {
    public:
      int msgType;
      int code;
      int *crc;
      CICMPDataType data;
      CICMPMsg(): crc(0) {}
      virtual ~CICMPMsg() = 0 {
        if (crc)
          delete crc;
      }
    };
    
    
    // ********** PORTS ***********

    class CICMPPort : public CPort {
    };
    
    class CICMPComponent : public CComponent {
    public:
      CICMPPort icmpPort;
    };
    
    class CIPStack : public CComponent {
    public:
      CICMPPort icmpPort;
    };
    
    
    
    // ********** TEMPLATES ***********
    
    class Ct_EchoRequest : public CICMPMsg {
    public:
      Ct_EchoRequest()
      {
        msgType = 8;
        code = 0;
        crc = new int(0);
        data._selector = SELECTOR_ping;
        data.u.ping.id = 1234;
      }
      
      const Ct_EchoRequest &Template(const int &seqNum)
      {
        data.u.ping.seqNumber = seqNum;
        return *this;
      }
    };
    
    class Ct_EchoReply : public CICMPMsg {
    public:
      Ct_EchoReply()
      {
        msgType = 0;
        code = 0;
      }
      
      const Ct_EchoRequest &Template(const Ct_EchoRequest &echoReq)
      {
        data = echoReq.data;
        return *this;
      }
    };
    
    

    class CTestCase_ICMP_Ping_1_Scope_1 {
    public:
      CIPStack system;
      CICMPComponent mtc;
      freettcn::TE::CTimer *t;
      integer count;
      
      CTestCase_ICMP_Ping_1_Scope_1() : t(0), count(0) {};
      ~CTestCase_ICMP_Ping_1_Scope_1()
      {
        if (t)
          delete t;
      }
    };
    
    class CTestCase_ICMP_Ping_1_Command_1 : public freettcn::TE::CCommand {
      freettcn::TE::CTestComponent &_comp;
      CTestCase_ICMP_Ping_1_Scope_1 &_scope;
      
    public:
      void Run()
      {
        _comp.Map(_scope.mtc.icmpPort, _scope.system.icmpPort);
        
        _comp.Verdict(VERDICT_FAIL);
        
        _scope.t = new freettcn::TE::CTimer(1.0);
        
        _scope.mtc.icmpPort.Send()
      }
    };
    
    
    class CTestCase_ICMP_Ping_1_Behavior : public freettcn::TE::CBehavior {
    public:
      freettcn::TE::CTimer t;
      
      CTestCase_ICMP_Ping_1_Behavior():
        t(3.0);
      {
      }
      
      void Run()
      {
        
        
        t
      }
    };

    
    class CTestCase_ICMP_Ping_1 : public freettcn::TE::CTestCase {
      virtual void Initialize();
    public:
      CTestCase_ICMP_Ping_1();
    };
    
    class CControlBehavior : public freettcn::TE::CBehavior {
    };

    class CModule : public freettcn::TE::CModule {
      static CModule _module;
      
      virtual void Initialize();
    public:
      CModule();
    };
    
    
    CTestCase_ICMP_Ping_1::CTestCase_ICMP_Ping_1():
      freettcn::TE::CTestCase("ICMP_Ping_1")
    {
    }
    
    void CTestCase_ICMP_Ping_1::Initialize()
    {
      
    }
    
    
    CModule CModule::_module;
    
    CModule::CModule():
      freettcn::TE::CModule("IP")
    {
    }
    
    void CModule::Initialize()
    {
      Register(new CTestCase_ICMP_Ping_1);
    }
    
    
  } // namespace IP

} // namespace freettcn
