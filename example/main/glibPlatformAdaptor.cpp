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
#include <freettcn/tools/exception.h>
#include <cmath>


freettcn::example::CGlibPlatformAdaptor::CTimer::CTimer(const TriTimerId &timerId):
  freettcn::PA::CTimer(timerId), _state(STOPPED)
{
}


freettcn::example::CGlibPlatformAdaptor::CTimer::~CTimer()
{
//   if (gSource)
//     ;
}


gboolean freettcn::example::CGlibPlatformAdaptor::CTimer::CallbackFunc(gpointer data)
{
  CTimer *timer = static_cast<CTimer *>(data);
  timer->Timeout();
  timer->State(STOPPED);
  
  return FALSE;
}


freettcn::example::CGlibPlatformAdaptor::CTimer::TState freettcn::example::CGlibPlatformAdaptor::CTimer::State() const
{
  return _state;
}


void freettcn::example::CGlibPlatformAdaptor::CTimer::State(TState state)
{
  _state = state;
}


void freettcn::example::CGlibPlatformAdaptor::CTimer::Start(TriTimerDuration duration)
{
  _id = g_timeout_add_full(G_PRIORITY_HIGH, static_cast<guint>(round(duration * 1000)),
                           CallbackFunc, this, 0);
  _state = STARTED;
}


void freettcn::example::CGlibPlatformAdaptor::CTimer::Stop()
{
  if (!g_source_remove(_id))
    throw EOperationFailed(E_DATA, "Removing of a timer failed!!!");
  _state = STOPPED;
}


TriTimerDuration freettcn::example::CGlibPlatformAdaptor::CTimer::Read() const
{
  return 0;
}


bool freettcn::example::CGlibPlatformAdaptor::CTimer::Running() const
{
  return _state == STARTED;
}




freettcn::example::CGlibPlatformAdaptor::CTimer *freettcn::example::CGlibPlatformAdaptor::TimerCreate(const TriTimerId &timerId) const
{
  return new CTimer(timerId);
}
