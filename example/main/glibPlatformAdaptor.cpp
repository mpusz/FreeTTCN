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


#include "glibPlatformAdaptor.h"
#include <iostream>
#include <cmath>


CTimer::CTimer(const TriTimerId &timerId):
  freettcn::PA::CTimer(timerId), _state(STOPPED)
{
}


CTimer::~CTimer()
{
//   if (gSource)
//     ;
}


gboolean CTimer::CallbackFunc(gpointer data)
{
  CTimer *timer = static_cast<CTimer *>(data);
  timer->Timeout();
  timer->State(STOPPED);
  
  return FALSE;
}


CTimer::TState CTimer::State() const
{
  return _state;
}


void CTimer::State(CTimer::TState state)
{
  _state = state;
}


void CTimer::Start(TriTimerDuration duration) throw(freettcn::EOperationFailed)
{
  _id = g_timeout_add_full(G_PRIORITY_HIGH, static_cast<guint>(round(duration * 1000)),
                           CallbackFunc, this, 0);
  _state = STARTED;
}


void CTimer::Stop() throw(freettcn::EOperationFailed)
{
  if (!g_source_remove(_id))
    throw freettcn::EOperationFailed();
  _state = STOPPED;
}


TriTimerDuration CTimer::Read() const throw(freettcn::EOperationFailed)
{
  return 0;
}


bool CTimer::Running() const throw(freettcn::EOperationFailed)
{
  return _state == STARTED;
}




CTimer *CPlatformAdaptor::TimerCreate(const TriTimerId &timerId) const
{
  return new CTimer(timerId);
}
