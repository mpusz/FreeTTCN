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
 * @file   timer.h
 * @author Mateusz Pusz
 * @date   Wed Apr 25 10:59:31 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TIMER_H__
#define __TIMER_H__

extern "C" {
// #include "freettcn/tci.h"
// #include "freettcn/tri.h"
}
// #include "tools.h"
// #include "ttcn_values.h"
// #include <string>
// #include <vector>


namespace freettcn {

  namespace TE {
    
//     enum VerdictType_t {
//       VERDICT_NONE,
//       VERDICT_PASS,
//       VERDICT_INCONC,
//       VERDICT_FAIL,
//       VERDICT_ERROR
//     };
    
    class CTimer {
      class CState {
        // STATUS:
        //  - IDLE
        //  - RUNNING
        //  - TIMEOUT
        // DEF_DURATION - default duration of a timer (undefined if not inited during declaration)
        // ACT_DURATION - stores the actual duration with which a running timer has been started (0.0 - if timer is stopped or timed out) (if a timer is started without duration, DEF_DURATION is copied) - error if no value defined when starting;
        // TIME_LEFT - describes the actual duration that a running timer has to run before it times out (0.0 - if timer is stopped or timed out)
        // SNAP_VALUE - when taking a snapshot it gets the actual value of ACT_DURATION - TIME_LEFT
        // SNAP_STATUS - when taking a snapshot it gets the same value as STATUS
      };
    public:
      CTimer();
      CTimer(double val);
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TIMER_H__ */
