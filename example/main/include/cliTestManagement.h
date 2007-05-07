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


class CTestManagement : public freettcn::TM::CTestManagement {
public:
  void TestCasesPrint() const;
  void TestCasesInfoPrint(const std::string &testCaseId) const throw(freettcn::ENotFound);
};

#endif /* __CLITESTMANAGEMENT_H__ */
