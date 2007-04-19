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
 * @file   tci_te_tm.cpp
 * @author Mateusz Pusz
 * @date   Sat Apr  7 16:39:01 2007
 * 
 * @brief  
 * 
 * 
 */


extern "C" {
#include "freettcn/tci_te_tm.h"
}
#include "tm.h"
#include <iostream>
#include <assert.h>


void tciTestCaseStarted(TciTestCaseIdType testCaseId,
                        TciParameterListType parameterList,
                        double timer)
{
  freettcn::TM::CTestManagement &tm = freettcn::TM::CTestManagement::Instance();
  return tm.TestCaseStarted(testCaseId, parameterList, timer);
}


void tciTestCaseTerminated(TciVerdictValue verdict,
                           TciParameterListType parameterlist)
{
  freettcn::TM::CTestManagement &tm = freettcn::TM::CTestManagement::Instance();
  return tm.TestCaseTerminated(verdict, parameterlist);
}


void tciControlTerminated()
{
  freettcn::TM::CTestManagement &tm = freettcn::TM::CTestManagement::Instance();
  return tm.ControlTerminated();
}


TciValue tciGetModulePar(TciModuleParameterIdType parameterId)
{
  freettcn::TM::CTestManagement &tm = freettcn::TM::CTestManagement::Instance();
  return tm.ModuleParameterGet(parameterId);
}


void tciError(String message)
{
  freettcn::TM::CTestManagement &tm = freettcn::TM::CTestManagement::Instance();
  tm.Error(message);
}


void tciLog(TriComponentId testComponentId, String message)
{
  freettcn::TM::CTestManagement &tm = freettcn::TM::CTestManagement::Instance();
  tm.Log(testComponentId, message);
}
