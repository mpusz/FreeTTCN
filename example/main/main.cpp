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


//#include "freettcn/tci_value.h"
//#include "ttcn_values.h"
#include "../tl/include/tl.h"
#include "../ch/include/ch.h"
#include "../tm/include/tm.h"
#include "../pa/include/pa.h"
#include "../sa/include/sa.h"
#include "te.h"
#include "log.h"
#include "exception.h"
#include <iostream>


using namespace std;


// void TypePrint(TTCN::CType &type)
// {
//   cout << "Type class: " << tciGetTypeClass(&type) << " name: " << (tciGetDefiningModule(&type).objectName ? tciGetDefiningModule(&type).objectName : "<TTCN-3>") << "." << tciGetName(&type) << endl;
// }


int main()
{
//   TTCN::CBooleanType boolean("", "", "");
  
//   TTCN::CModule ipMod(TTCN::CQualifiedName("", "IP", 0));
//   TTCN::CRecordType ping(&ipMod, "", "", "");
// //   TTCN::CRecordType ping(&ipMod, "PingMsg", TCI_RECORD_TYPE, "", "", "");

//   TypePrint(boolean);
//   TypePrint(ping);

  try {
    // init timestamping
    freettcn::CTimeStamp ts(4);
    
    // init logger
    freettcn::TL::CLogger logger(ts);
    
    // get TE
    freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
    
    // initiate all entities
    freettcn::TM::CTestManagement tm;
    freettcn::CH::CComponentHandler ch;
//     freettcn::CD::CComponentHandler cd;
    freettcn::PA::CPlatformAdaptor pa;
    freettcn::SA::CSUTAdaptor sa;
    freettcn::TL::CTestLogging tl(logger);
    
    // create log masks for all entities
    freettcn::TE::CLogMask teLogMask(true);
    freettcn::TM::CLogMask tmLogMask(true);
    freettcn::CH::CLogMask chLogMask(true);
    freettcn::PA::CLogMask paLogMask(true);
    freettcn::SA::CLogMask saLogMask(true);
    
    // set logging in all entities
    te.LogEnable(ts, teLogMask);
    tm.LogEnable(ts, tmLogMask);
    ch.LogEnable(ts, chLogMask);
    pa.LogEnable(ts, paLogMask);
    sa.LogEnable(ts, saLogMask);
    
    // init module
    tm.Init("IP");
    tm.TestCasesPrint();
    
    // run control part
    tm.ControlInit();
    tm.ControlStart();
    tm.ControlStop();
    
    // run specified test case
    tm.TestCaseInit("ICMP_Ping_1");
    TciParameterListType parameterlist;
    parameterlist.length = 0;
    parameterlist.parList = 0;
    tm.TestCaseStart("ICMP_Ping_1", parameterlist);
    tm.TestCaseStop();
    
    //    MessageReceived();
  }
  catch(freettcn::Exception &ex) {
    std::cout << "Unhandled freettcn library exception: " << ex.what() << " caught!!!" << std::endl;
  }
  catch(exception &ex) {
    std::cout << "Unhandled system exception: " << ex.what() << " caught!!!" << std::endl;
  }
}
