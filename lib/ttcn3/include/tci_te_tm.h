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
 * @file   tci_te_tm.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:56:53 2007
 * 
 * @brief  TTCN-3 Executable TE => TM operation interface (TCI-TM provided)
 * 
 * This header specifies the operations the TM has to provide to the TE.
 */

#ifndef __TCI_TE_TM_H__
#define __TCI_TE_TM_H__


#include "freettcn/tci.h"
#include "freettcn/tri.h"


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
 * @defgroup TciInterfaceTMProvided TCI-TM provided
 * @{
 */



/** 
 * @brief Indicates that a test case has been started.
 * 
 * tciTestCaseStarted() indicates to the TM that a test case with @p testCaseId has been started.
 * It will not be distinguished whether the test case has been started explicitly using the @e required
 * operation tciStartTestCase() or implicitly while executing the control part. @n
 * @n
 * Shall only be called after either the control part of the module or a test case has been started using
 * the @e required operations tciStartControl() or tciStartTestCase().
 * 
 * @param testCaseId A test case identifier as defined in the TTCN-3 module.
 * @param parameterList A list of values that are part of the test case signature. The parameters in
 *                      @p parameterList are ordered as they appear in the TTCN-3 test case
 *                      declaration.
 * @param timer A float value representing the duration of the test case timer.
 */
void tciTestCaseStarted(TciTestCaseIdType testCaseId,
                        TciParameterListType parameterList,
                        double timer);


/** 
 * @brief Indicates that the test case has terminated.
 * 
 * This operation will be called by the TE to indicate the test management that the test case that has
 * been currently executed on the MTC has terminated and that the final verdict was @p verdict. On the
 * invocation of a tciTestCaseTerminated() operation all @e out and @e inout test case parameters
 * contain Values. All @e in test case parameters contain the distinct value of @c null because they are
 * only of relevance to the test case start but not in the reply to the call. @n
 * @n
 * Shall only be called after either the control part of the module or a test cases has been started
 * using the @e required operations tciStartControl() or tciStartTestCase().
 * 
 * @param verdict The final verdict of the test case.
 * @param parameterlist A list of values that are part of the test case signature. The parameters in
 *                      @p parameterList are ordered as they appear in the TTCN-3 test case
 *                      declaration.
 */
void tciTestCaseTerminated(TciVerdictValue verdict,
                           TciParameterListType parameterlist);


/** 
 * @brief Indicate that the control part has just terminated execution.
 * 
 * This operation will be called by the TE to indicate the test management that the control part of
 * the selected module has just terminated execution. @n
 * @n
 * Shall only be called when the module execution has been started using the
 * tciStartControl() operation.
 * 
 */
void tciControlTerminated();


/** 
 * @brief Provides a value for the indicated parameter.
 * 
 * The management provides to the TE a Value for the indicated @p parameterId. Every call of
 * tciGetModulePar() will return the same value throughout the execution of an explicitly
 * started test case or throughout the execution of a control part. If the management cannot
 * provide a TTCN-3 value, the distinct @c null value shall be returned. @n
 * @n
 * This operation shall be called whenever the TE needs to access the value of a module
 * parameter. Every accessed module parameter will be resolved only once between a
 * tciStartTestCase() and tciTestCaseTerminated() pair if a test case has been started
 * explicitly or between a tciStartControl() and tciControlTerminated() pair if the control
 * part of a module has been started.
 * 
 * @param parameterId  The identifier of the module parameter as defined in TTCN-3.
 * 
 * @return A value.
 *
 * @todo tciValue type redefiened as TciValue
 */
TciValue tciGetModulePar(TciModuleParameterIdType parameterId);


/** 
 * @brief The TE indicates the occurrence of an unrecoverable error situation.
 * 
 * The TE indicates the occurrence of an unrecoverable error situation. @p message contains a
 * reason phrase that might be communicated to the test system user. It is up to the test
 * management to terminate execution of test cases or control parts if running. The test
 * management has to take explicit measures to terminate test execution immediately. @n
 * @n
 * Can be called at any time by the TE to indicate an unrecoverable error situation. This error
 * situation could either be indicated by the CH or the CD or could occur within the TE.
 * 
 * @param message A string value, i.e. the message error
 */
void tciError(String message);


/**
 * @todo No description in the TTCN-3 specification
 * @todo In C mappings defined as: void tciLog(String message);
 */
void tciLog(TriComponentId testComponentId, String message);


/// @} TciInterfaceTMProvided

/// @} TciInterfaceTM

/// @} TciInterface

/// @} Tci



#endif /* __TCI_TE_TM_H__ */
