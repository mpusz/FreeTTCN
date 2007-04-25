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
 * @file   testCase.h
 * @author Mateusz Pusz
 * @date   Wed Apr 25 10:49:25 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TESTCASE_H__
#define __TESTCASE_H__


extern "C" {
#include "freettcn/tci.h"
#include "freettcn/tri.h"
}
#include "initObject.h"
#include "exception.h"


namespace freettcn {

  namespace TE {
    
    class CModule;
    class CBehavior;
    
    class CTestCase : public CInitObject {
      class CState {
        // ALL_PORT_STATES - a list of states of different ports
        // MTC - MTC reference
        // TC_VERDICT - actual global test verdict of a test case, updated after every test component termination
      };
      
      TriComponentId _mtcId;
      CBehavior *_behavior;
      CModule *_module;
      
    public:
      CTestCase(const std::string &name);
      virtual ~CTestCase();
      
      void Register(CBehavior *behavior);
      
      void Module(CModule &module);
      CModule &Module() const throw(EOperationFailed);
      
      TciParameterTypeListType Parameters() const;
      TriPortIdList Ports() const;
      
      void Start(TciParameterListType parameterlist);
      void Execute(TciTestCaseIdType testCaseId, TriPortIdList tsiPortList);
      void Stop();
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TESTCASE_H__ */
