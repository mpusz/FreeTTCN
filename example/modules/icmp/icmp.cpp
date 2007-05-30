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
 * @file   icmp.cpp
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
#include <freettcn/te/record.h>
#include <freettcn/te/template.h>
#include <freettcn/te/timer.h>
#include <freettcn/te/basicTypes.h>
#include <freettcn/te/sourceData.h>
#include <iostream>


#define MY_CAST         dynamic_cast

namespace freettcn {
  
  namespace icmp {

    // ************************* T Y P E S *****************************
    
    class CICMPPingDataType : public freettcn::TE::CRecordType {
    public:
      enum {
        FIELD_id,
        FIELD_seqNumber,
        FIELD_data
      };
      CICMPPingDataType(const freettcn::TE::CModule &module);
    };
    
    /// @todo should be an union
    class CICMPDataType : public freettcn::TE::CRecordType {
    public:
      enum {
        FIELD_ping
      };
      CICMPDataType(const freettcn::TE::CModule &module);
    };
    
    class CICMPMsg : public freettcn::TE::CRecordType {
    public:
      enum {
        FIELD_msgType,
        FIELD_code,
        FIELD_crc,
        FIELD_data
      };
      CICMPMsg(const freettcn::TE::CModule &module);
    };
    
    
    
    // ************************* P O R T S *****************************
    
    class CICMPPortType : public freettcn::TE::CPortType {
    public:
      CICMPPortType(const freettcn::TE::CModule &module);
    };
    
    
    
    
    // ******************** C O M P O N E N T S ************************
    
    class CICMPComponentType : public freettcn::TE::CTestComponentType {
    public:
      enum {
        PORT_icmpPort_0
      };
      
      class CInstance : public freettcn::TE::CTestComponentType::CInstanceLocal {
        virtual void Initialize();
      public:
        CInstance(const freettcn::TE::CType &type);
      };
      
    public:
      CICMPComponentType(const freettcn::TE::CModule &module);
      virtual CInstance *InstanceCreate() const { return new CInstance(*this); }
    };
    
    
    class CIPStackType : public freettcn::TE::CTestComponentType {
    public:
      enum {
        PORT_icmpPort_0
      };
      
      class CInstance : public freettcn::TE::CTestComponentType::CInstanceLocal {
        virtual void Initialize();
      public:
        CInstance(const freettcn::TE::CType &type);
      };
      
    public:
      CIPStackType(const freettcn::TE::CModule &module);
      virtual CInstance *InstanceCreate() const { return new CInstance(*this); }
    };
    
    
    
    
    // ********************* T E M P L A T E S *************************

    class Ct_EchoRequest : public freettcn::TE::CTemplate {
    public:
      Ct_EchoRequest(const freettcn::TE::CModule &module, freettcn::TE::CIntegerType::CInstance &seqNum);
    };
    
    class Ct_EchoReply : public freettcn::TE::CTemplate {
    public:
      Ct_EchoReply(const freettcn::TE::CModule &module, CICMPMsg::CInstance &echoReq);
    };
    

    
    // ******************** T E S T   C A S E S ************************
    
    class CTC_ICMPPing_1 : public freettcn::TE::CTestCase {
    public:
      class CBehavior : public freettcn::TE::CBehavior {
        enum{
          SCOPE1_count
        };
        enum {
          SCOPE1_t
        };
        
      public:
        CBehavior(freettcn::TE::CModule &module);
        int Run(freettcn::TE::CTestComponentType::CInstanceLocal &comp, unsigned int offset) const;
      };
      
    public:
      CTC_ICMPPing_1(freettcn::TE::CModule &module);
    };
    
    class CTC_ICMPPing_2 : public freettcn::TE::CTestCase {
    public:
      class CBehavior : public freettcn::TE::CBehavior {
        enum {
          SCOPE1_t1
        };
        enum {
          OFFSET_1 = freettcn::TE::CBehavior::OFFSET_START + 1,
        };
        
      public:
        CBehavior(freettcn::TE::CModule &module);
        int Run(freettcn::TE::CTestComponentType::CInstanceLocal &comp, unsigned int offset) const;
      };
      
    public:
      CTC_ICMPPing_2(freettcn::TE::CModule &module);
    };
    
    
    
    
    // ************************ M O D U L E ****************************
    
    class CModule : public freettcn::TE::CModule {
    public:
      enum {
        TYPE_ICMPPingDataType,
        TYPE_ICMPDataType,
        TYPE_ICMPMsg,
        TYPE_ICMPComponentType,
        TYPE_IPStackType
      };
      
      enum {
        PAR_long,
        PAR_count,
      };
      
      enum {
        PORT_TYPE_ICMPPortType
      };
      
      enum {
        TESTCASE_ICMPPing_1,
        TESTCASE_ICMPPing_2
      };
      
      class CBehavior : public freettcn::TE::CBehavior {
      private:
        enum {
          SCOPE1_i
        };
        enum {
          SCOPE1_t1
        };

        enum {
          OFFSET_1 = freettcn::TE::CBehavior::OFFSET_START + 1,
          OFFSET_2,
          OFFSET_3,
          OFFSET_4,
          OFFSET_5,
          OFFSET_6
        };
        
      public:
        CBehavior(freettcn::TE::CModule &module);
        int Run(freettcn::TE::CTestComponentType::CInstanceLocal &comp, unsigned int offset) const;
      };
      
    private:
      static CModule _instance;
      
      CModule();
      virtual void Initialize();
      virtual void Cleanup();
      
    public:
      static CModule &Instance() { return _instance; }
    };
    
    
    
    
    
    // ************************ S T A T I C ****************************
    
    CModule CModule::_instance;
    
    
    

    // ************************* T Y P E S *****************************
    
    CICMPPingDataType::CICMPPingDataType(const freettcn::TE::CModule &module):
      freettcn::TE::CRecordType(module, "ICMPPingDataType", "", "", "")
    {
      Register(freettcn::TE::CBasicTypes::Integer(), "id");
      Register(freettcn::TE::CBasicTypes::Integer(), "seqNumber");
      Register(freettcn::TE::CBasicTypes::Octetstring(), "data", true);
      Init();
    }
    
    /// @todo should be of union type
    CICMPDataType::CICMPDataType(const freettcn::TE::CModule &module):
      freettcn::TE::CRecordType(module, "ICMPDataType", "", "", "")
    {
      Register(module.Type(CModule::TYPE_ICMPPingDataType), "ping");
      Init();
    }
    
    CICMPMsg::CICMPMsg(const freettcn::TE::CModule &module):
      freettcn::TE::CRecordType(module, "ICMPMsg", "", "", "")
    {
      Register(freettcn::TE::CBasicTypes::Integer(), "msgType");
      Register(freettcn::TE::CBasicTypes::Integer(), "code");
      Register(freettcn::TE::CBasicTypes::Integer(), "crc");
      Register(module.Type(CModule::TYPE_ICMPDataType), "data");
      Init();
    }
    
    
    
    // ************************* P O R T S *****************************
    
    CICMPPortType::CICMPPortType(const freettcn::TE::CModule &module):
      freettcn::TE::CPortType(module, "ICMPPort", freettcn::TE::CPortType::MESSAGE)
    {
      TypeAdd(module.Type(CModule::TYPE_ICMPMsg), freettcn::TE::CPortType::INOUT);
    }

    
    
    // ******************** C O M P O N E N T S ************************
    
    // ICMPComponent
    CICMPComponentType::CICMPComponentType(const freettcn::TE::CModule &module):
      freettcn::TE::CTestComponentType(&module, "ICMPComponent")
    {
      PortInfoAdd(module.PortType(CModule::PORT_TYPE_ICMPPortType), "icmpPort", 0);
    }
    
    CICMPComponentType::CInstance::CInstance(const freettcn::TE::CType &type):
      freettcn::TE::CTestComponentType::CInstanceLocal(type)
    {
    }
    
    void CICMPComponentType::CInstance::Initialize()
    {
      // constant definition
      
      // variable declaration
      
      // timer declaration
    }
    
    
    
    // IPStack
    CIPStackType::CIPStackType(const freettcn::TE::CModule &module):
      freettcn::TE::CTestComponentType(&module, "IPStack")
    {
      PortInfoAdd(module.PortType(CModule::PORT_TYPE_ICMPPortType), "icmpPort", 0);
    }
    
    CIPStackType::CInstance::CInstance(const freettcn::TE::CType &type):
      freettcn::TE::CTestComponentType::CInstanceLocal(type)
    {
    }
    
    void CIPStackType::CInstance::Initialize()
    {
    }
    
    
    
    
    // ********************* T E M P L A T E S *************************
    
    Ct_EchoRequest::Ct_EchoRequest(const freettcn::TE::CModule &module, freettcn::TE::CIntegerType::CInstance &seqNum):
      freettcn::TE::CTemplate(module.Type(CModule::TYPE_ICMPMsg))
    {
      CICMPMsg::CInstance &value = MY_CAST<CICMPMsg::CInstance &>(Value());
      
      MY_CAST<freettcn::TE::CIntegerType::CInstance &>(value.Field(CICMPMsg::FIELD_msgType)).Value(8);
      MY_CAST<freettcn::TE::CIntegerType::CInstance &>(value.Field(CICMPMsg::FIELD_code)).Value(0);
      MY_CAST<freettcn::TE::CIntegerType::CInstance &>(value.Field(CICMPMsg::FIELD_crc)).Value(0);
      CICMPDataType::CInstance &data = MY_CAST<CICMPDataType::CInstance &>(value.Field(CICMPMsg::FIELD_data));
      //         data._selector = CICMPDataType::SELECTOR_ping;
      CICMPPingDataType::CInstance &ping = MY_CAST<CICMPPingDataType::CInstance &>(data.Field(CICMPDataType::FIELD_ping));
      MY_CAST<freettcn::TE::CIntegerType::CInstance &>(ping.Field(CICMPPingDataType::FIELD_id)).Value(1234);
      MY_CAST<freettcn::TE::CIntegerType::CInstance &>(ping.Field(CICMPPingDataType::FIELD_seqNumber)) = seqNum;
      ping.Field(CICMPPingDataType::FIELD_data).Omit(true);
    }
    
    
    Ct_EchoReply::Ct_EchoReply(const freettcn::TE::CModule &module, CICMPMsg::CInstance &echoReq):
      freettcn::TE::CTemplate(module.Type(CModule::TYPE_ICMPMsg))
    {
      CICMPMsg::CInstance &value = MY_CAST<CICMPMsg::CInstance &>(Value());
      
      MY_CAST<freettcn::TE::CIntegerType::CInstance &>(value.Field(CICMPMsg::FIELD_msgType)).Value(0);
      MY_CAST<freettcn::TE::CIntegerType::CInstance &>(value.Field(CICMPMsg::FIELD_code)).Value(0);
      MY_CAST<freettcn::TE::CIntegerType::CInstance &>(value.Field(CICMPMsg::FIELD_crc)).Omit(true);
      MY_CAST<CICMPDataType::CInstance &>(value.Field(CICMPMsg::FIELD_data)) = MY_CAST<CICMPDataType::CInstance &>(echoReq.Field(CICMPMsg::FIELD_data));
    }
    
    
    
    
    // ******************** T E S T   C A S E S ************************
    
    // ICMP_Ping_1
    CTC_ICMPPing_1::CTC_ICMPPing_1(freettcn::TE::CModule &module):
      freettcn::TE::CTestCase(module, "TC_ICMPPing_1", new freettcn::TE::CSourceData("icmp.ttcn", 76),
                              MY_CAST<const freettcn::TE::CTestComponentType &>(module.Type(CModule::TYPE_ICMPComponentType)),
                              *new CBehavior(module),
                              &MY_CAST<const freettcn::TE::CTestComponentType &>(module.Type(CModule::TYPE_IPStackType)))
    {
      // register test case parameters
    }
    
    
    CTC_ICMPPing_1::CBehavior::CBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "TC_ICMPPing_1")
    {
    }
    
    
    int CTC_ICMPPing_1::CBehavior::Run(freettcn::TE::CTestComponentType::CInstanceLocal &comp, unsigned int offset) const
    {
      switch(offset) {
      case freettcn::TE::CBehavior::OFFSET_START:
        {
          comp.ScopeEnter("icmp.ttcn", 83, "behavior");
          
          comp.MapReq(comp.Module().ActiveTestCase().MTC().PortId("icmpPort", 0), comp.Module().ActiveTestCase().System().PortId("icmpPort", 0));
          
          comp.Scope().Register(new freettcn::TE::CTimer(comp, false, 1.0));
          comp.Scope().Register(new freettcn::TE::CIntegerType::CInstance(freettcn::TE::CBasicTypes::Integer(), 0));
          
          freettcn::TE::CIntegerType::CInstance &count = MY_CAST<freettcn::TE::CIntegerType::CInstance &>(comp.Scope().Value(SCOPE1_count));
          comp.Port("icmpPort", 0).Send(Ct_EchoRequest(comp.Module(), count).Value());
          comp.Scope().Timer(SCOPE1_t).Start();
          
          /// @todo alt
          
          /// @todo log
          
          /// @todo temporary solution
          comp.Verdict("icmp.ttcn", 94, freettcn::TE::VERDICT_PASS);
          
          comp.UnmapReq(comp.Module().ActiveTestCase().MTC().PortId("icmpPort", 0), comp.Module().ActiveTestCase().System().PortId("icmpPort", 0));
          
          comp.ScopeLeave("icmp.ttcn", 113);
          comp.StopReq("icmp.ttcn", 113);
          return freettcn::TE::CBehavior::END;
        }
    
      default:
        std::cout << "ERROR: Unknown offset: " << offset << std::endl;
      }
      
      return freettcn::TE::CBehavior::ERROR;
    }
    
    // ICMP_Ping_2
    CTC_ICMPPing_2::CTC_ICMPPing_2(freettcn::TE::CModule &module):
      freettcn::TE::CTestCase(module, "TC_ICMPPing_2", new freettcn::TE::CSourceData("icmp.ttcn", 109),
                              MY_CAST<const freettcn::TE::CTestComponentType &>(module.Type(CModule::TYPE_ICMPComponentType)),
                              *new CBehavior(module))
    {
      // register test case parameters
    }
    
    
    CTC_ICMPPing_2::CBehavior::CBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "TC_ICMPPing_2")
    {
    }
    
    int CTC_ICMPPing_2::CBehavior::Run(freettcn::TE::CTestComponentType::CInstanceLocal &comp, unsigned int offset) const
    {
      switch(offset) {
      case freettcn::TE::CBehavior::OFFSET_START:
        {
          comp.ScopeEnter("icmp.ttcn", 116, "behavior");
          
          comp.Verdict("icmp.ttcn", 117, freettcn::TE::VERDICT_PASS);
          
          comp.Scope().Register(new freettcn::TE::CTimer(comp, false, 5.0));
          comp.Scope().Timer(SCOPE1_t1).Start();
          comp.Scope().Timer(SCOPE1_t1).HandlerAdd(OFFSET_1);
          return freettcn::TE::CBehavior::WAIT;
        }
        
      case OFFSET_1:
        {
          comp.ScopeLeave("icmp.ttcn", 117);
          comp.StopReq("icmp.ttcn", 117);
          return freettcn::TE::CBehavior::END;
        }
        
      default:
        std::cout << "ERROR: Unknown offset: " << offset << std::endl;
      }
      
      return freettcn::TE::CBehavior::ERROR;
    }
    

    
    
    
    
    // ************************ M O D U L E ****************************
    
    CModule::CModule():
      freettcn::TE::CModule("icmp")
    {
    }
    
    void CModule::Initialize()
    {
      // register module types (without components)
      Register(new CICMPPingDataType(*this));
      Register(new CICMPDataType(*this));
      Register(new CICMPMsg(*this));
      
      // register port types
      Register(new CICMPPortType(*this));
      
      // register module components
      Register(new CICMPComponentType(*this));
      Register(new CIPStackType(*this));
      
      // register module parameters
      Register(new CParameter("long", new freettcn::TE::CBooleanType::CInstance(freettcn::TE::CBasicTypes::Boolean(), true)));
      {
        freettcn::TE::CIntegerType::CInstance *value = new freettcn::TE::CIntegerType::CInstance(freettcn::TE::CBasicTypes::Integer());
        value->Omit(true);
        Register(new CParameter("count", value));
      }
      
      // register test cases
      Register(new CTC_ICMPPing_1(*this));
      Register(new CTC_ICMPPing_2(*this));
      
      // register control behavior
      ControlBehavior(*new CBehavior(*this), new freettcn::TE::CSourceData("icmp.ttcn", 115));
    }
    
    void CModule::Cleanup()
    {
      // cleanup base class
      freettcn::TE::CModule::Cleanup();
    }
    
    

    CModule::CBehavior::CBehavior(freettcn::TE::CModule &module):
      freettcn::TE::CBehavior(module, "_control_")
    {
    }
    
    
    int CModule::CBehavior::Run(freettcn::TE::CTestComponentType::CInstanceLocal &comp, unsigned int offset) const
    {
      switch(offset) {
      case freettcn::TE::CBehavior::OFFSET_START:
        {
          comp.ScopeEnter("icmp.ttcn", 122, "control");
          
          comp.ScopeEnter("icmp.ttcn", 123, "if");
          comp.Execute("icmp.ttcn", 123, comp.Module().TestCase(TESTCASE_ICMPPing_1), 0, OFFSET_1);
          return freettcn::TE::CBehavior::WAIT;
        }
        
      case OFFSET_1: // test case termination
        {
          if (comp.Module().TestCase(TESTCASE_ICMPPing_1).Verdict().Value() == freettcn::TE::VERDICT_PASS &&
              MY_CAST<const freettcn::TE::CBooleanType::CInstance &>(comp.Module().Parameter(PAR_long).Value()).Value()) {
            comp.ScopeEnter("icmp.ttcn", 124, "for");
            comp.Scope().Register(new freettcn::TE::CIntegerType::CInstance(freettcn::TE::CBasicTypes::Integer(), 0));
            
            return OFFSET_2;
          }
          return OFFSET_6;
        }
        
      case OFFSET_2: // for loop
        {
          if (MY_CAST<freettcn::TE::CIntegerType::CInstance &>(comp.Scope().Value(SCOPE1_i)).Value() <
              MY_CAST<const freettcn::TE::CIntegerType::CInstance &>(comp.Module().Parameter(PAR_count).Value()).Value()) {
            comp.Execute("icmp.ttcn", 125, comp.Module().TestCase(TESTCASE_ICMPPing_2), 3.0, OFFSET_3);
            return freettcn::TE::CBehavior::WAIT;
          }
          return OFFSET_5;
        }
        
      case OFFSET_3: // test case termination
        {
          // alt for timer
          comp.Scope().Register(new freettcn::TE::CTimer(comp, false, 1.0));
          comp.Scope().Timer(SCOPE1_t1).Start();
          comp.Scope().Timer(SCOPE1_t1).HandlerAdd(OFFSET_4);
          return freettcn::TE::CBehavior::WAIT;
        }        
        
      case OFFSET_4: // alt end
        {
          freettcn::TE::CIntegerType::CInstance &val = MY_CAST<freettcn::TE::CIntegerType::CInstance &>(comp.Scope().Value(SCOPE1_i));
          val.Value(val.Value() + 1);
          return OFFSET_2;
        }
        
      case OFFSET_5: // for end
        {
          comp.ScopeLeave("icmp.ttcn", 129);
          // return OFFSET_6; - !!! ommited !!!
        }
        
      case OFFSET_6: // if end
        {
          comp.ScopeLeave("icmp.ttcn", 130);
          comp.ScopeLeave("icmp.ttcn", 131);
          comp.StopReq("icmp.ttcn", 131);
          return freettcn::TE::CBehavior::END;
        }
        
      default:
        std::cout << "ERROR: Unknown offset: " << offset << std::endl;
      }
      
      return freettcn::TE::CBehavior::ERROR;
    }
    
  } // namespace icmp

} // namespace freettcn
