//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcnenv (Free TTCN Environment) library.

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
 * @file   pa/timer.h
 * @author Mateusz Pusz
 * @date   Mon May  7 13:19:21 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <freettcn/tools/exception.h>
extern "C" {
#include <freettcn/ttcn3/tri.h>
}

namespace freettcn {
  
  namespace PA {
    
    class CTimer {
      const TriTimerId &_id;
      
    protected:
      void Timeout() const;
      
    public:
      CTimer(const TriTimerId &timerId);
      virtual ~CTimer();
      
      const TriTimerId &Id() const;
      
      virtual void Start(TriTimerDuration duration) throw(EOperationFailed) = 0;
      virtual void Stop() throw(EOperationFailed) = 0;
      virtual TriTimerDuration Read() const throw(EOperationFailed) = 0;
      virtual bool Running() const throw(EOperationFailed) = 0;
    };
    
  } // namespace PA
  
} // namespace freettcn


#endif /* __TIMER_H__ */
