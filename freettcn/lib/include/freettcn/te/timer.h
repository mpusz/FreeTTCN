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

#include <freettcn/te/testComponent.h>
extern "C" {
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/tools/exception.h>


namespace freettcn {
  
  namespace TE {
    
    class CTimer : public CIdObject {
    public:
      enum TStatus {
        IDLE,
        RUNNING,
        TIMEOUT
      };

    private:
      typedef std::vector<unsigned int> TOffsetList;
      
      CTestComponentType::CInstanceLocal &_component;
      const bool _implicit;
      
      // timer dynamic state
      TStatus _status;                            /**< denotes whether a timer is active, inactive or has timed out */
      const bool _defaultDurationValid;           /**< specifies if default duration have been given during timer declaration */
      TriTimerDuration _defaultDuration;          /**< default duration of a timer */
      TriTimerDuration _activeDuration;           /**< stores the actual duration with which a running timer has been started */
      // TIME_LEFT - describes the actual duration that a running timer has to run before it times out (0.0 - if timer is stopped or timed out)
      // SNAP_VALUE - when taking a snapshot it gets the actual value of ACT_DURATION - TIME_LEFT
      // SNAP_STATUS - when taking a snapshot it gets the same value as STATUS
      
      TOffsetList _offsetList;
      
    public:
      CTimer(CTestComponentType::CInstanceLocal &comp, bool implicit);
      CTimer(CTestComponentType::CInstanceLocal &comp, bool implicit, TriTimerDuration defaultDuration) throw(EOperationFailed);
      ~CTimer();
      
      const TriTimerId &Id() const;
      
      void Start() throw(EOperationFailed);
      void Start(TriTimerDuration duration) throw(EOperationFailed);
      void Stop() throw(EOperationFailed);
      TriTimerDuration Read() const throw(EOperationFailed);
      bool Running() const throw(EOperationFailed);
      
      void HandlerAdd(unsigned int behavoiorOffset);
      void HandlerRemove(unsigned int behavoiorOffset);
      
      void Timeout();
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TIMER_H__ */
