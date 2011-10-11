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
 * @file   TriPlatformPA.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 11:31:15 2007
 * 
 * @brief  TTCN-3 Executable TRI communication interface operations TE=>SA
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-5: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 5: TTCN-3 Runtime Interface (TRI)"
 * 
 */

#ifndef __TRI_PLATFORM_PA_H__
#define __TRI_PLATFORM_PA_H__

#include <freettcn/ttcn3/tri.h>

namespace ORG_ETSI_TTCN3_TRI {

  class TriPlatformPA {
  public:
    //Destructor.
    virtual ~TriPlatformPA();
    //Reset all timing activities which it is currently performing.
    virtual TriStatus triPAReset() = 0;
    //Start the indicated timer with the indicated duration.
    virtual TriStatus triStartTimer(const TriTimerId *timerId, const TriTimerDuration *timerDuration) = 0;
    //Stop the indicated timer.
    virtual TriStatus triStopTimer(const TriTimerId *timerId) = 0;
    //Use the timerId to access the time that elapsed since this timer was started.
    virtual TriStatus triReadTimer(const TriTimerId *timerId, TriTimerDuration *elapsedTime) = 0;
    //Use the timerId to access the status of the timer.
    virtual TriStatus triTimerRunning(const TriTimerId *timerId, Tboolean * running) = 0;
    //For each external function specified in the TTCN-3 ATS implement the behaviour.
    virtual TriStatus triExternalFunction(const TriFunctionId *functionId, TriParameterList *parameterList,
                                          TriParameter *returnValue) = 0;
  };
  
} // namespace ORG_ETSI_TTCN3_TRI

#endif /* __TRI_PLATFORM_PA_H__ */
