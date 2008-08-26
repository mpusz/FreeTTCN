//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) usage example.

// This example is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This example is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this example; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


/**
 * @file   glibPlatformAdaptor.h
 * @author Mateusz Pusz
 * @date   Mon May  7 14:27:15 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __GLIBPLATFORMADAPTOR_H__
#define __GLIBPLATFORMADAPTOR_H__

#include <freettcn/pa/pa.h>
#include <freettcn/pa/timer.h>
#include <glib.h>


namespace freettcn {
  
  namespace example {
    
    class CGlibPlatformAdaptor : public freettcn::PA::CPlatformAdaptor {
      class CTimer : public freettcn::PA::CTimer {
        enum TState {
          STOPPED,
          STARTED
        };
    
        guint _id;
        TState _state;
    
        static gboolean CallbackFunc(gpointer data);
    
        TState State() const;
        void State(TState state);
    
      public:
        CTimer(const TriTimerId &timerId);
        ~CTimer();
    
        virtual void Start(TriTimerDuration duration);
        virtual void Stop();
        virtual TriTimerDuration Read() const;
        virtual bool Running() const;
      };
  
      virtual CTimer *TimerCreate(const TriTimerId &timerId) const;
    };

  } // namespace example
  
} // namespace freettcn

#endif /* __GLIBPLATFORMADAPTOR_H__ */
