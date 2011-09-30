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


#include "glibMainLoop.h"
#include "glibPlatformAdaptor.h"

#include "../modules/icmp/include/icmp_cd.h"

#include <freettcn/tl/tl.h>
#include <freettcn/ch/ch.h>
#include <freettcn/cd/cd.h>
#include <freettcn/pa/paLogMask.h>
#include <freettcn/sa/sa.h>
#include <freettcn/te/te.h>
#include <freettcn/te/teLogMask.h>
#include <freettcn/te/module.h>
#include <freettcn/te/modulesContainer.h>
#include <freettcn/tools/timeStampMgrSeconds.h>

#include <iostream>
#include <getopt.h>
#include <cstdio>


namespace freettcn {

  namespace example {

    void Usage();
    void Start(CCLITestManagement &tm, const std::string &testCase);

  } // namespace example

} // namespace freettcn


void freettcn::example::Usage()
{
  using namespace std;
  cout << "Usage:" << endl;
  cout << " -m, --module      Select module" << endl;
  cout << " -t, --testcase    Select testcase of specified module" << endl;
  cout << " -l, --list        List modules/testcases" << endl;
  cout << " -i, --info        Print module/testcase information" << endl;
  cout << " -h, --help        Print that usage" << endl;
  cout << endl;
  cout << endl;
  cout << "Examples:" << endl;
  cout << " - list modules:" << endl;
  cout << "    ./ttcn_example -l" << endl;
  cout << endl;
  cout << " - print specified module information:" << endl;
  cout << "    ./ttcn_example -m <module_name> -i" << endl;
  cout << endl;
  cout << " - run control part of specified module:" << endl;
  cout << "    ./ttcn_example -m <module_name>" << endl;
  cout << endl;
  cout << " - list test cases of specified module:" << endl;
  cout << "    ./ttcn_example -m <module_name> -l" << endl;
  cout << endl;
  cout << " - print specified test case information:" << endl;
  cout << "    ./ttcn_example -m <module_name> -t <testcase_id> -i" << endl;
  cout << endl;
  cout << " - run specified test case:" << endl;
  cout << "    ./ttcn_example -m <module_name> -t <testcase_id>" << endl;
}


void freettcn::example::Start(CCLITestManagement &tm, const std::string &testCase)
{
  // set module parameters
  tm.ParametersSet();
  
  // init timestamping
  CTimeStampMgrSeconds ts(4);
  
  // init logger
  TL::CLogger logger(ts);
    
  // get TE
  TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
    
  // initiate all entities
  CH::CComponentHandler ch;
  CD::CCodingDecoding cd;
  CGlibPlatformAdaptor pa;
  SA::CSUTAdaptor sa;
  TL::CTestLogging tl(logger);
    
  // create log masks for all entities
  TE::CLogMask teLogMask(true);
  TM::CLogMask tmLogMask(true);
  CH::CLogMask chLogMask(true);
  CD::CLogMask cdLogMask(true);
  PA::CLogMask paLogMask(true);
  SA::CLogMask saLogMask(true);
    
  // set logging in all entities
  te.LogEnable(ts, teLogMask);
  tm.LogEnable(ts, tmLogMask);
  ch.LogEnable(ts, chLogMask);
  cd.LogEnable(ts, cdLogMask);
  pa.LogEnable(ts, paLogMask);
  sa.LogEnable(ts, saLogMask);
  
  // register module specific codecs
  icmp::CCodec *icmpCodec = new freettcn::icmp::CCodec;
  cd.Register(icmpCodec);
  
  // run
  if (testCase != "") {
    // run specified test case
    TciParameterListType parameterlist;
    parameterlist.length = 0;
    parameterlist.parList = 0;
      
    try {
      tm.TestCaseStart(testCase, parameterlist);
      //      tm.TestCaseStop();
    }
    catch(Exception &) {
      std::cerr << "Error: Could not init test case '" << testCase << "'" << std::endl;
      exit(EXIT_SUCCESS);
    }
  }
  else {
    // run control part
    tm.ControlStart();
    //      tm.ControlStop();
  }
}



int main (int argc, char **argv)
{
  std::string module;
  std::string testCase;
  bool list = false;
  bool info = false;
  bool help = false;
  
  // get options
  while (1) {
    int c;
    int option_index = 0;
    static struct option long_options[] = {
      {"module",   1, 0, 'm'},
      {"testcase", 1, 0, 't'},
      {"list",     0, 0, 'l'},
      {"info",     0, 0, 'i'},
      {"help",     0, 0, 'h'},
      {0, 0, 0, 0}
    };
    
    c = getopt_long(argc, argv, "m:t:lih", long_options, &option_index);
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
      
    case 'i':
      info = true;
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
    std::cerr << "Error: Non-option ARGV-elements: ";
    while (optind < argc)
      std::cerr << argv[optind++] << " ";
    std::cerr << std::endl;
    
    exit(EXIT_SUCCESS);
  }
  
  if (help) {
    freettcn::example::Usage();
    exit(EXIT_SUCCESS);
  }
  
  if (list && module == "") {
    // list modules
    freettcn::TE::CModulesContainer &modules = freettcn::TE::CModulesContainer::Instance();
    const freettcn::TE::CModulesContainer::CModuleList &list = modules.List();

    for(auto &m : list)
      std::cout << " - " << m->Id().moduleName << std::endl;
    
    exit(EXIT_SUCCESS);
  }
  
  if (module == "") {
    std::cerr << "Error: Module name not given" << std::endl;
    exit(EXIT_SUCCESS);
  }
  
  // init test management
  freettcn::example::CGlibMainLoop mainLoop;
  freettcn::example::CCLITestManagement tm(mainLoop);
  
  try {
    // init module
    tm.Init(module.c_str());
  }
  catch(freettcn::Exception &) {
    std::cerr << "Error: Could not init module '" << module << "'" << std::endl;
    exit(EXIT_SUCCESS);
  }
  
  if (list) {
    // list test cases
    tm.TestCasesPrint();
    exit(EXIT_SUCCESS);
  }

  if (info) {
    if (testCase == "") {
      tm.ModuleInfoPrint();
    }
    else {
      // init specified test cases
      try {
        tm.TestCasesInfoPrint(testCase);
      }
      catch(freettcn::Exception &) {
        std::cerr << "Error: Could not init test case '" << testCase << "'" << std::endl;
      }      
    }
    
    exit(EXIT_SUCCESS);
  }
  
  try {
    // start TTCN module
    freettcn::example::Start(tm, testCase);
  }
  catch(freettcn::Exception &ex) {
    std::cerr << "Error: Unhandled freettcn library exception: " << ex.what() << " caught!!!" << std::endl;
  }
  catch(std::exception &ex) {
    std::cerr << "Error: Unhandled system exception: " << ex.what() << " caught!!!" << std::endl;
  }
  
  exit(EXIT_SUCCESS);
}
