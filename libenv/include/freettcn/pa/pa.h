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
#include <freettcn/tools/entity.h>
#include <list>


namespace freettcn {
  
  namespace PA {
    
    class CTimer;
    
    class CPlatformAdaptor : public freettcn::CEntity {
      typedef std::list<CTimer *> TTimerList;
      
      static CPlatformAdaptor *_instance;
      
      CTimer &TimerGet(const TriTimerId &timerId) const throw(ENotFound);
      virtual CTimer *TimerCreate(const TriTimerId &timerId) const = 0;

    protected:
      TTimerList _timerList;
      
      CPlatformAdaptor& operator=(CPlatformAdaptor&);  // Disallowed
      CPlatformAdaptor(const CPlatformAdaptor&);       // Disallowed
    public:
      static CPlatformAdaptor &Instance() throw(ENotFound);
      
      CPlatformAdaptor();
      virtual ~CPlatformAdaptor();
      
      TriStatus Reset();
      
      TriStatus TimerStart(const TriTimerId *timerId, TriTimerDuration timerDuration);
      TriStatus TimerStop(const TriTimerId *timerId);
      TriStatus TimerRead(const TriTimerId* timerId, TriTimerDuration* elapsedTime);
      TriStatus TimerRunning(const TriTimerId* timerId, unsigned char* running);
      
      TriStatus ExternalFunction(const TriFunctionId* functionId,
                                 TriParameterList* parameterList,
                                 TriParameter* returnValue);
    };
    
  } // namespace PA
  
} // namespace freettcn


#endif /* __PA_H__ */
