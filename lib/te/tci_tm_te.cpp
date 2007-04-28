//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) library.

// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   tci_tm_te.cpp
 * @author Mateusz Pusz
 * @date   Sat Apr  7 20:23:44 2007
 * 
 * @brief  
 * 
 * 
 */


extern "C" {
#include "freettcn/tci_tm_te.h"
}
#include "te.h"


void tciRootModule(String moduleId)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.RootModule(moduleId);
}


TciModuleParameterListType tciGetModuleParameters(TciModuleIdType moduleName)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  return te.ModuleParametersGet(moduleName);
}


TciTestCaseIdListType tciGetTestCases()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  return te.TestCasesGet();
}


TciParameterTypeListType tciGetTestCaseParameters(TciTestCaseIdType testCaseId)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  return te.TestCaseParametersGet(testCaseId);
}


TriPortIdList tciGetTestCaseTSI(TciTestCaseIdType testCaseId)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  return te.TestCaseTSIGet(testCaseId);
}


void tciStartTestCase(TciTestCaseIdType testCaseId, TciParameterListType parameterlist)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.TestCaseStart(testCaseId, parameterlist);
}


void tciStopTestCase()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.TestCaseStop();
}


TriComponentId tciStartControl()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  return te.ControlStart();
}


void tciStopControl()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.ControlStop();
}
