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


#include <freettcn/tl/tl.h>
#include <freettcn/ch/ch.h>
#include <freettcn/tm/tm.h>
#include <freettcn/pa/pa.h>
#include <freettcn/sa/sa.h>
#include <freettcn/te/te.h>
#include <freettcn/te/log.h>
#include <freettcn/tools/exception.h>
#include <iostream>
#include <getopt.h>


using namespace std;


void Run(const std::string &testCase)
{
  try {
    freettcn::TM::CTestManagement &tm = freettcn::TM::CTestManagement::Instance();
    
    if (testCase != "") {
      // init specified test cases
      try {
        tm.TestCaseInit(testCase);
      }
      catch(freettcn::Exception) {
        std::cout << "Error: Could not init test case '" << testCase << "'" << std::endl;
        exit(0);
      }
    }
    
    // init timestamping
    freettcn::CTimeStamp ts(4);
    
    // init logger
    freettcn::TL::CLogger logger(ts);
    
    // get TE
    freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
    
    // initiate all entities
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
    
    if (testCase != "") {
      // run specified test case
      TciParameterListType parameterlist;
      parameterlist.length = 0;
      parameterlist.parList = 0;
      
      tm.TestCaseStart(testCase, parameterlist);
      //      tm.TestCaseStop();
    }
    else {
      // run control part
      tm.ControlInit();
      tm.ControlStart();
      //      tm.ControlStop();
    }
  }
  catch(freettcn::Exception &ex) {
    std::cout << "Error: Unhandled freettcn library exception: " << ex.what() << " caught!!!" << std::endl;
  }
  catch(exception &ex) {
    std::cout << "Error: Unhandled system exception: " << ex.what() << " caught!!!" << std::endl;
  }
}



int main (int argc, char **argv)
{
  std::string module;
  std::string testCase;
  bool list = false;
  bool help = false;
  
  // get options
  while (1) {
    int c;
    int option_index = 0;
    static struct option long_options[] = {
      {"module",   1, 0, 'm'},
      {"testcase", 1, 0, 't'},
      {"list",     0, 0, 'l'},
      {"help",     0, 0, 'h'},
      {0, 0, 0, 0}
    };
    
    c = getopt_long(argc, argv, "m:t:lh", long_options, &option_index);
    if (c == -1)
      break;
    
    switch (c) {
    case 'm':
      module = optarg;
      break;
      
    case 't':
      testCase = optarg;
      break;
      
    case 'l':
      list = true;
      break;
      
    case 'h':
      help = true;
      break;
      
    case '?':
      break;
      
    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
    }
  }
  if (optind < argc) {
    std::cout << "Error: Non-option ARGV-elements: ";
    while (optind < argc)
      std::cout << argv[optind++] << " ";
    std::cout << std::endl;
    
    exit(0);
  }
  
  if (help) {
    std::cout << "Usage:" << std::endl;
    exit(0);
  }
  
  if (list && module == "") {
    // list modules
    exit(0);
  }
  
  if (module == "") {
    std::cout << "Error: Module name not given" << std::endl;
    exit(0);
  }
  
  // init test management
  freettcn::TM::CTestManagement tm;
  
  try {
    // init module
    tm.Init(module.c_str());
  }
  catch(freettcn::Exception) {
    std::cout << "Error: Could not init module '" << module << "'" << std::endl;
    exit(0);
  }
  
  if (list) {
    // list test cases
    
    exit(0);
  }
  
  // run TTCN module
  Run(testCase);
}


// void freettcn::TM::CTestManagement::TestCasesPrint() const
// {
//   std::cout << "Test cases:" << std::endl;
//   for(TCList::const_iterator it=_tcList.begin(); it != _tcList.end(); ++it) {
//     std::cout << " - ";
//     (*it)->Print();
//   }
// }
