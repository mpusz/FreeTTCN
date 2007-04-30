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
 * @file   pa.h
 * @author Mateusz Pusz
 * @date   Mon Apr 16 18:25:36 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __PA_H__
#define __PA_H__

extern "C" {
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/tools/logMask.h>
#include <freettcn/tools/entity.h>

namespace freettcn {
  
  namespace PA {
    
    class CLogMask : public freettcn::CLogMask {
    public:
      CLogMask(bool enabled = true);
      ~CLogMask();
    };

    
    class CPlatformAdaptor : public freettcn::CEntity {
      static CPlatformAdaptor *_instance;
      
      CPlatformAdaptor& operator=(CPlatformAdaptor&);  // Disallowed
      CPlatformAdaptor(const CPlatformAdaptor&);       // Disallowed
    public:
      static CPlatformAdaptor &Instance() throw(ENotFound);
      
      CPlatformAdaptor();
      virtual ~CPlatformAdaptor();
      
      TriStatus Reset();
    };
    
  } // namespace PA
  
} // namespace freettcn


#endif /* __PA_H__ */


// #include "ttcn3.h"

// extern "C" {
// #include "tri_pa_te.h"
// }


// namespace PA {
  
//   class Timer : public TTCN3::Timer {
//     void Start(double duration) throw(EOperationFailed);
//     void Stop() throw(EOperationFailed);
//     double Read() const throw(EOperationFailed);
//     bool Running() const throw(EOperationFailed);
    
//   public:
//     friend TriStatus triStartTimer(const TriTimerId*, TriTimerDuration);
//     friend TriStatus triStopTimer(const TriTimerId*);
//     friend TriStatus triReadTimer(const TriTimerId*, TriTimerDuration*);
//     friend TriStatus triTimerRunning(const TriTimerId*, unsigned char*);
    
//     void TimeOut() const;
//   };
  
// }


// void PA::Timer::TimeOut() const
// {
//   triTimeout(Id());
// }
