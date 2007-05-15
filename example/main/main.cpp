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

#include <freettcn/tl/tl.h>
#include <freettcn/ch/ch.h>
#include <freettcn/pa/paLogMask.h>
#include <freettcn/sa/sa.h>
#include <freettcn/te/te.h>
#include <freettcn/te/teLogMask.h>
#include <freettcn/te/module.h>
#include <freettcn/te/modulesContainer.h>
#include <freettcn/tools/timeStamp.h>

#include <iostream>
#include <getopt.h>


using namespace std;


void Usage()
{
  std::cout << "Usage:" << std::endl;
  std::cout << " -m, --module      Select module" << std::endl;
  std::cout << " -t, --testcase    Select testcase of specified module" << std::endl;
  std::cout << " -l, --list        List modules/testcases" << std::endl;
  std::cout << " -i, --info        Print module/testcase information" << std::endl;
  std::cout << " -h, --help        Print that usage" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Examples:" << std::endl;
  std::cout << " - list modules:" << std::endl;
  std::cout << "    ./ttcn_example -l" << std::endl;
  std::cout << "" << std::endl;
  std::cout << " - print specified module information:" << std::endl;
  std::cout << "    ./ttcn_example -m <module_name> -i" << std::endl;
  std::cout << "" << std::endl;
  std::cout << " - run control part of specified module:" << std::endl;
  std::cout << "    ./ttcn_example -m <module_name>" << std::endl;
  std::cout << "" << std::endl;
  std::cout << " - list test cases of specified module:" << std::endl;
  std::cout << "    ./ttcn_example -m <module_name> -l" << std::endl;
  std::cout << "" << std::endl;
  std::cout << " - print specified test case information:" << std::endl;
  std::cout << "    ./ttcn_example -m <module_name> -t <testcase_id> -i" << std::endl;
  std::cout << "" << std::endl;
  std::cout << " - run specified test case:" << std::endl;
  std::cout << "    ./ttcn_example -m <module_name> -t <testcase_id>" << std::endl;
}


void Start(CCLITestManagement &tm, const std::string &testCase)
{
  // init timestamping
  freettcn::CTimeStamp ts(4);
    
  // init logger
  freettcn::TL::CLogger logger(ts);
    
  // get TE
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
    
  // initiate all entities
  freettcn::CH::CComponentHandler ch;
  //     freettcn::CD::CComponentHandler cd;
  CGlibPlatformAdaptor pa;
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
  
  // set module parameters
  tm.ParametersSet();
  
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
    catch(freettcn::Exception) {
      std::cout << "Error: Could not init test case '" << testCase << "'" << std::endl;
      exit(0);
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
    std::cout << "Error: Non-option ARGV-elements: ";
    while (optind < argc)
      std::cout << argv[optind++] << " ";
    std::cout << std::endl;
    
    exit(0);
  }
  
  if (help) {
    Usage();
    exit(0);
  }
  
  if (list && module == "") {
    // list modules
    freettcn::TE::CModulesContainer &modules = freettcn::TE::CModulesContainer::Instance();
    const freettcn::TE::CModulesContainer::TModuleList &list = modules.List();
    
    for(freettcn::TE::CModulesContainer::TModuleList::const_iterator it=list.begin(); it != list.end(); ++it)
      std::cout << " - " << (*it)->Id().moduleName << std::endl;
    
    exit(0);
  }
  
  if (module == "") {
    std::cout << "Error: Module name not given" << std::endl;
    exit(0);
  }
  
  // init test management
  CGlibMainLoop mainLoop;
  CCLITestManagement tm(mainLoop);
  
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
    tm.TestCasesPrint();
    exit(0);
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
      catch(freettcn::Exception) {
        std::cout << "Error: Could not init test case '" << testCase << "'" << std::endl;
      }      
    }
    
    exit(0);
  }
  
  try {
    // start TTCN module
    Start(tm, testCase);
  }
  catch(freettcn::Exception &ex) {
    std::cout << "Error: Unhandled freettcn library exception: " << ex.what() << " caught!!!" << std::endl;
  }
  catch(exception &ex) {
    std::cout << "Error: Unhandled system exception: " << ex.what() << " caught!!!" << std::endl;
  }
}
