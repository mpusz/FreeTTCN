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
 * @file   tri_te_pa.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 14:59:32 2007
 * 
 * @brief  TTCN-3 Executable TRI platform interface operations TE=>PA
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-5: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 5: TTCN-3 Runtime Interface (TRI)"
 * 
 */

#ifndef __TRI_TE_PA_H__
#define __TRI_TE_PA_H__

#include <freettcn/ttcn3/tri.h>


/**
 * @addtogroup Tri TRI
 * @{
 */

/**
 * @addtogroup TriIface Interface
 * @{
 */

/**
 * @addtogroup TriIfacePlatform Platform
 * @{
 */

/**
 * @addtogroup TriIfacePlatformTimer Timer operations
 * @{
 */

/**
 * @defgroup TriIfacePlatformTimer_TE_PA TE => PA
 * @{
 */


/** 
 * @brief The PA shall start the timer.
 * 
 * On invocation of this operation the PA shall start the indicated timer with the indicated duration. The
 * timer runs from the value zero (0.0) up to the maximum specified by @p timerDuration. Should the timer
 * indicated by @p timerId already be running it is to be restarted. When the timer expires the PA will call
 * the triTimeout() operation with @p timerId.
 * 
 * @remarks This operation is called by the TE when a timer needs to be started.
 *
 * @param timerId identifier of the timer instance
 * @param timerDuration duration of the timer in seconds
 * 
 * @return The triStartTimer() operation returns @p TRI_OK if the timer has been started successfully, @p TRI_Error
 * otherwise.
 *
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triStartTimer(const TriTimerId *timerId,
                        TriTimerDuration timerDuration);



/** 
 * @brief The PA shall stop the indicated timer instance.
 * 
 * On invocation of this operation the PA shall use the @p timerId to stop the indicated timer instance. The
 * stopping of an inactive timer, i.e. a timer which has not been started or has already expired, should
 * have no effect.
 * 
 * @remarks This operation is called by the TE when a timer is to be stopped.
 * 
 * @param timerId identifier of the timer instance
 * 
 * @return The triStopTimer() operation returns @c TRI_OK if the operation has been performed successfully,
 * @c TRI_Error otherwise. Notice that stopping an inactive timer is a valid operation. In this case @c TRI_OK
 * shall be returned.
 *
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triStopTimer(const TriTimerId *timerId);



/** 
 * @brief The PA shall access the time that elapsed since the timer was started.
 * 
 * On invocation of this operation the PA shall use the @p timerId to access the time that elapsed since
 * this timer was started. The return value @p elapsedTime shall be provided in seconds. The reading of an
 * inactive timer, i.e. a timer which has not been started or already expired, shall return an elapsed time
 * value of zero.
 * 
 * @remarks This operation may be called by the TE when a TTCN-3 read timer operation is to be executed on the
 * indicated timer (see clause 5.3.1).
 * 
 * @param timerId identifier of the timer instance
 * @param elapsedTime value of the time elapsed since the timer has been started in seconds
 * 
 * @return The triReadTimer() operation returns @c TRI_OK if the operation has been performed successfully,
 * @c TRI_Error otherwise.
 *
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triReadTimer(const TriTimerId *timerId,
                       TriTimerDuration *elapsedTime);


/** 
 * @brief The PA shall access the status of the timer.
 * 
 * On invocation of this operation the PA shall use the @p timerId to access the status of the timer. The
 * operation sets @p running to the boolean value @c true if and only if the timer is currently running.
 * 
 * @remarks This operation may be called by the TE when a TTCN-3 running timer operation is to be executed on
 * the indicated timer (see clause 5.3.1).
 * 
 * @param timerId identifier of the timer instance
 * @param running status of the timer
 * 
 * @return The triTimerRunning() operation returns @c TRI_OK if the status of the timer has been successfully
 * determined, @c TRI_Error otherwise
 *
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triTimerRunning(const TriTimerId *timerId,
                          unsigned char *running);


/// @} TriIfacePlatformTimer_TE_PA

/// @} TriIfacePlatformTimer


/**
 * @defgroup TriIfacePlatformMisc Miscellaneous
 * @{
 */

/**
 * @defgroup TriIfacePlatformMisc_TE_PA TE => PA
 * @{
 */

/** 
 * @brief The PA shall reset all timing activities which it is currently performing.
 * 
 * The PA shall reset all timing activities which it is currently performing, e.g. stop all running timers,
 * discard any pending timeouts of expired timers.
 * 
 * @remarks This operation can be called by the TE at any time to reset the PA.
 * 
 * @return The triPAReset() operation returns @c TRI_OK in case the operation has been performed successfully,
 * @c TRI_Error otherwise.
 *
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triPAReset();


/** 
 * @brief The PA shall invoke the function indicated by the identifier.
 * 
 * For each external function specified in the TTCN-3 ATS the PA shall implement the behaviour. On
 * invocation of this operation the PA shall invoke the function indicated by the identifier @p functionId. It
 * shall access the specified in and inout function parameters in @p parameterList, evaluate the external
 * function using the values of these parameters, and compute values for inout and out parameters in
 * @p parameterList. The operation shall then return encoded values for all inout and out function
 * parameters and the encoded return value of the external function.
 * If no return type has been defined for this external function in the TTCN-3 ATS, the distinct value
 * null shall be used for the latter.
 * 
 * @remarks This operation is called by the TE when it executes a function which is defined to be TTCN-3 external
 * (i.e. all non-external functions are implemented within the TE).
 * In the invocation of a triExternalFunction() operation by the TE all in and inout function parameters
 * contain encoded values. No error shall be indicated by the PA in case the value of any out parameter
 * is non-null.
 * 
 * @note Note that whereas all other TRI operations are considered to be non-blocking, the
 * triExternalFunction() operation is considered to be blocking. That means that the operation shall
 * not return before the indicated external function has been fully evaluated. External functions have to
 * be implemented carefully as they could cause deadlock of test component execution or even the
 * entire test system implementation.
 * 
 * @param functionId Identifier of the external function
 * @param parameterList a list of encoded parameters for the indicated function. The parameters in parameterList are ordered as they appear in the TTCN-3 function declaration.
 * @param returnValue (optional) encoded return value
 * 
 * @return The triExternalFunction() operation returns @c TRI_OK if the PA completes the evaluation of the
 * external function successfully, @c TRI_Error otherwise.
 *
 * @retval TRI_OK success
 * @retval TRI_Error failure
 */
TriStatus triExternalFunction(const TriFunctionId *functionId,
                              TriParameterList *parameterList,
                              TriParameter *returnValue);

/// @} TriIfacePlatformMisc_TE_SA

/// @} TriIfacePlatformMisc

/// @} TriIfacePlatform

/// @} TriIface

/// @} Tri

#endif /* __TRI_TE_PA_H__ */
