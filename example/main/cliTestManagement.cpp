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


#include "cliTestManagement.h"
#include <iostream>


CCLITestManagement::CCLITestManagement(CMainLoop &mainLoop):
  _mainLoop(mainLoop)
{
}


void CCLITestManagement::TestCasesPrint() const
{
  const freettcn::TM::CTestManagement::TTCList &tcList = TCList();
  for(TTCList::const_iterator it=tcList.begin(); it != tcList.end(); ++it) {
    TciTestCaseIdType id = (*it)->Id();
    std::cout << " - " << id.moduleName << "." << id.objectName << std::endl;
  }
}


void CCLITestManagement::TestCasesInfoPrint(const std::string &testCaseId) const throw(freettcn::ENotFound)
{
  CTestCase &tc = TestCaseGet(testCaseId);
  
  // obtain test case parameters
  //     TciParameterTypeListType parList = tc.Parameters();
  
  // obtain Test System Interfaces used by the test case 
  TriPortIdList portList = tc.Interface();
  
  std::cout << "Test System Interface:" << std::endl;
  for(int i=0; i<portList.length; i++) {
    std::cout << " - " <<
      portList.portIdList[i]->compInst.compName <<
      " <" << portList.portIdList[i]->compInst.compType.moduleName << "." <<
      portList.portIdList[i]->compInst.compType.objectName << "> " <<
      portList.portIdList[i]->portName << "[" <<
      portList.portIdList[i]->portIndex << "] <" <<
      portList.portIdList[i]->portType.moduleName << "." <<
      portList.portIdList[i]->portType.objectName << ">" <<
      std::endl;
  }
}


void CCLITestManagement::TestCaseStart(const std::string &testCaseId, const TciParameterListType &parameterlist) throw(freettcn::ENotFound)
{
  freettcn::TM::CTestManagement::TestCaseStart(testCaseId, parameterlist);
  _mainLoop.Start();
}


void CCLITestManagement::TestCaseTerminated(TciVerdictValue verdict, const TciParameterListType &parameterlist)
{
  TStatus status = Status();
  freettcn::TM::CTestManagement::TestCaseTerminated(verdict, parameterlist);
  if (status == RUNNING_TEST_CASE)
    _mainLoop.Stop();
}


void CCLITestManagement::TestCaseStop() throw(freettcn::EOperationFailed)
{
  TStatus status = Status();
  freettcn::TM::CTestManagement::TestCaseStop();
  if (status == RUNNING_TEST_CASE)
    _mainLoop.Stop();
}




void CCLITestManagement::ControlStart()
{
  freettcn::TM::CTestManagement::ControlStart();
  _mainLoop.Start();
}


void CCLITestManagement::ControlStop() throw(freettcn::EOperationFailed)
{
  freettcn::TM::CTestManagement::ControlStop();
  _mainLoop.Stop();
}


void CCLITestManagement::ControlTerminated()
{
  freettcn::TM::CTestManagement::ControlTerminated();
  _mainLoop.Stop();
}





CCLITestManagement::CMainLoop::~CMainLoop()
{
}
