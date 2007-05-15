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
 * @file   cliTestManagement.h
 * @author Mateusz Pusz
 * @date   Mon May  7 14:05:49 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __CLITESTMANAGEMENT_H__
#define __CLITESTMANAGEMENT_H__

#include <freettcn/tm/tm.h>


class CCLITestManagement : public freettcn::TM::CTestManagement {
public:
  class CMainLoop {
  public:
    virtual ~CMainLoop() = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
  };
  
private:
  CMainLoop &_mainLoop;
  
public:
  CCLITestManagement(CMainLoop &mainLoop);
  
  void ModuleInfoPrint() const;
  
  void TestCasesPrint() const;
  void TestCasesInfoPrint(const std::string &testCaseId) const throw(freettcn::ENotFound);
  
  virtual void ParametersSet() const;
  
  virtual void TestCaseStart(const std::string &testCaseId, const TciParameterListType &parameterlist) throw(freettcn::ENotFound);
  virtual void TestCaseTerminated(TciVerdictValue verdict, const TciParameterListType &parameterlist);
  virtual void TestCaseStop() throw(freettcn::EOperationFailed);
  
  virtual void ControlStart();
  virtual void ControlStop() throw(freettcn::EOperationFailed);
  virtual void ControlTerminated();
};

#endif /* __CLITESTMANAGEMENT_H__ */
