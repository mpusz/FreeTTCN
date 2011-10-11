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
 * @file   TciTmRequired.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:50:45 2007
 * 
 * @brief  TTCN-3 Executable TCI types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 * 
 */

#ifndef __TCI_TM_REQUIRED_H__
#define __TCI_TM_REQUIRED_H__

#include <freettcn/ttcn3/tci.h>

namespace ORG_ETSI_TTCN3_TCI {

  class TciTmRequired {
  public:
    //Destructor
    virtual ~TciTmRequired();
    //Selects the indicated module for execution
    virtual void tciRootModule(const TciModuleId *moduleName) = 0;
    //The TE provides to the management a list of imported modules of the root module
    virtual const TciModuleIdList *getImportedModules() const = 0;
    //The TE provides to the management a list of module parameters of the identified module
    virtual const TciModuleParameterList *tciGetModuleParameters(const TciModuleId *moduleName) = 0;
    //The TE provides to the management a list of test cases
    virtual const TciTestCaseIdList *tciGetTestCases() const = 0;
    //The TE provides to the management a list of parameter types of the given test case
    virtual const TciParameterTypeList *tciGetTestCaseParameters(const TciTestCaseId *testCaseId) const = 0;
    //The TE provides to the management a list of system ports of the given test case
    virtual const TriPortIdList *tciGetTestCaseTSI (const TciTestCaseId &testCaseId) const = 0;
    //Starts a testcase in the currently selected module with the given parameters
    virtual void tciStartTestCase(const TciTestCaseId *testCaseId, const TciParameterList *parameterList) = 0;
    //Stops the testcase currently being executed
    virtual void tciStopTestCase() = 0;
    //Starts the control part of the selected module
    virtual const TriComponentId *tciStartControl() = 0;
    //Stops execution of the control part
    virtual void tciStopControl() = 0;
  };

} // namespace ORG_ETSI_TTCN3_TCI

#endif /* __TCI_TM_REQUIRED_H__ */
