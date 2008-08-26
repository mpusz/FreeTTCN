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
 * @file   tci_tm_te.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:57:37 2007
 * 
 * @brief  TTCN-3 Executable TM => TE operation interface (TCI-TM required)
 *
 * This header specifies the operations the TM requires from the TE. In addition to the
 * operations specified in this file, a test management requires the operations as required
 * at the TCI-CD interface.
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 *
 */

#ifndef __TCI_TM_TE_H__
#define __TCI_TM_TE_H__

#include <freettcn/ttcn3/tci.h>
#include <freettcn/ttcn3/tri.h>


/**
 * @addtogroup Tci TCI
 * @{
 */

/**
 * @addtogroup TciInterface Interface
 * @{
 */

/**
 * @addtogroup TciInterfaceTM The TCI-TM interface
 * @{
 */

/**
 * @defgroup TciInterfaceTMRequired TCI-TM required
 * @{
 */


/** 
 * @brief Selects the module for execution
 * 
 * tciRootModule() selects the indicated module for execution through a subsequent call using
 * tciStartTestCase() or tciStartControl(). A tciError() will be issued by the TE if no such
 * module exists.
 * 
 * @remarks Shall be used only if neither the control part nor a test case is currently being executed.
 * 
 * @param moduleId The moduleName denotes the module identifiers as defined in TTCN-3.
 */
void tciRootModule(String moduleId);


/**
 * TciModuleIdListType getImportedModules()
 * A list of all imported modules of the root module. The modules are ordered as they appear in
 * the TTCN-3 module. If no imported modules exist, an empty module list is returned.
 * Shall be used only if a root module has been set before.
 * The TE provides to the management a list of imported modules of the root module. If no
 * imported module exist, an empty module list is returned. If the TE cannot provide a list, the
 * distinct null value shall be returned.
 */
TciModuleIdListType tciGetImportedModules();


/** 
 * @brief The TE provides a list of module parameters of the identified module.
 * 
 * The TE provides to the management a list of module parameters of the identified module. If no
 * module parameters exist, an empty module parameter list is returned. If the TE cannot provide a list,
 * the distinct @c null value shall be returned.
 * 
 * @remarks Shall be used only if a root module has been set before.
 * 
 * @param moduleName The moduleName denotes the module identifiers for which the module parameters should be retrieved.
 * 
 * @return A list of all module parameters of the identified module. The parameters are ordered as they appear
 *         in the TTCN-3 module. If no parameters exist, an empty module parameter list is returned.
 */
TciModuleParameterListType tciGetModuleParameters(TciModuleIdType moduleName);


/** 
 * @brief The TE provides a list of test cases.
 * 
 * The TE provides to the management a list of test cases. If no test cases exist, an empty test
 * case list is returned. If the TE cannot provide a list, the distinct @c null value shall be returned.
 * 
 * @remarks Shall be used only if a root module has been set before.
 * 
 * @return A list of all test cases that are either defined in or imported into the root module.
 */
TciTestCaseIdListType tciGetTestCases();


/** 
 * @brief The TE provides a list of parameter types of the given test case.
 * 
 * The TE provides to the management a list of parameter types of the given test case. If no test case
 * parameters exist, an empty parameter type list is returned. If the TE cannot provide a list, the distinct
 * @c null value shall be returned.
 * 
 * @remarks Shall be used only if a root module has been set before.
 * 
 * @param testCaseId A test case identifier as defined in the TTCN-3 module.
 * 
 * @return A list of all parameter types of the given test case. The parameter types are ordered as they appear
 *         in the TTCN-3 signature of the test case. If no parameters exist, an empty parameter type list is
 *         returned.
 */
TciParameterTypeListType tciGetTestCaseParameters(TciTestCaseIdType testCaseId);


/** 
 * @brief The TE provides a list of system ports of the given test case.
 * 
 * The TE provides to the management a list of system ports of the given test case. If no system ports
 * exist, an empty port list is returned. If the TE cannot provide a list, the distinct @c null value shall be
 * returned.
 * 
 * @remarks Shall be used only if a root module has been set before.
 * 
 * @param testCaseId A test case identifier as defined in the TTCN-3 module.
 * 
 * @return A list of all system ports of the given test case that have been declared in the definition of the system
 *         component for the test case, i.e. the TSI ports. If a system component has not been explicitly defined
 *         for the test case, then the list contains all communication ports of the MTC test component. The ports
 *         are ordered as they appear in the respective TTCN-3 component type declaration. If no system ports
 *         exist, an empty list, i.e. a list of length zero is returned.
 */
TriPortIdList tciGetTestCaseTSI(TciTestCaseIdType testCaseId);


/** 
 * @brief Starts a testcase in the currently selected module.
 * 
 * tciStartTestCase() starts a testcase in the currently selected module with the given parameters.
 * A tciError() will be issued by the TE if no such test case exists.
 * All @e in and @e inout test case parameters in @p parameterList contain Value. All @e out test case
 * parameters in @p parameterList shall contain the distinct value of @c null since they are only of
 * relevance when the test case terminates.
 * 
 * @remarks Shall be called only if a module has been selected before. Only @p testCaseIds for test cases that
 * are declared in the currently selected TTCN-3 module shall be passed. Test cases that are
 * imported in a referenced module can not be started. To start imported test cases the referenced
 * (imported) module must be selected first using the tciRootModule() operation.
 * 
 * @param testCaseId A test case identifier as defined in the TTCN-3 module.
 * @param parameterlist A list of Values where each value defines a parameter from the parameter list
 *                      as defined in the TTCN-3 test case definition. The parameters in
 *                      @p parameterList are ordered as they appear in the TTCN-3 signature of the
 *                      test case. If no parameters have to be passed either the @c null value or an
 *                      empty @p parameterList, i.e. a list of length zero shall be passed.
 */
void tciStartTestCase(TciTestCaseIdType testCaseId,
                      TciParameterListType parameterlist);


/** 
 * @brief Stops the testcase currently being executed.
 * 
 * tciStopTestCase() stops the testcase currently being executed. If the TE is not executing a test case,
 * the operation will be ignored. If the control part is being executed, tciStopTestCase() will stop
 * execution of the currently executed test case, i.e. the execution of the test case that has recently
 * been indicated using the @e provided operation tciTestCaseStarted(). A possible executing control
 * part will continue execution as if the test case has stopped normally and returned with verdict
 * @c ERROR.
 * 
 * @remarks Shall be called only if a module has been selected before.
 */
void tciStopTestCase();


/** 
 * @brief Starts the control part of the selected module.
 * 
 * Starts the control part of the selected module. The control part will start TTCN-3 test cases as
 * described in TTCN-3. While executing the control part the TE will call the @e provided operation
 * tciTestCaseStarted() and tciTestCaseTerminated() for every test case that has been
 * started and that has terminated. After termination of the control part the TE will call the @e provided
 * operation tciControlPartTerminated().
 * 
 * @remarks Shall be called only if a module has been selected before.
 * 
 * @return A @c TriComponentId that represents the test component the module control part is executed on. If
 *         the TE cannot start control part of the selected module the distinct value @c null will be returned.
 */
TriComponentId tciStartControl();


/** 
 * @brief Stops execution of the control part.
 * 
 * tciStopControl() stops execution of the control part. If no control part is currently being executed
 * the operation will be ignored. If a test case has been started directly this will stop execution of the
 * current test case as if tciStopTestCase() has been called.
 * 
 * @remarks Shall only be called if a module has been selected before.
 */
void tciStopControl();


/// @} TciInterfaceTMRequired

/// @} TciInterfaceTM

/// @} TciInterface

/// @} Tci

// Telelogic extension
// TciType tciGetModuleParType
// (TciModuleParameterIdType parameterId);

#endif /* __TCI_TM_TE_H__ */
