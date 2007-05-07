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


extern "C" {
#include <freettcn/ttcn3/tri_te_pa.h>
}
#include "freettcn/pa/pa.h"



TriStatus triStartTimer(const TriTimerId* timerId,
                        TriTimerDuration timerDuration)
{
  freettcn::PA::CPlatformAdaptor &pa = freettcn::PA::CPlatformAdaptor::Instance();
  return pa.TimerStart(timerId, timerDuration);
}


TriStatus triStopTimer(const TriTimerId* timerId)
{
  freettcn::PA::CPlatformAdaptor &pa = freettcn::PA::CPlatformAdaptor::Instance();
  return pa.TimerStop(timerId);
}


TriStatus triReadTimer(const TriTimerId* timerId,
                       TriTimerDuration* elapsedTime)
{
  freettcn::PA::CPlatformAdaptor &pa = freettcn::PA::CPlatformAdaptor::Instance();
  return pa.TimerRead(timerId, elapsedTime);
}


TriStatus triTimerRunning(const TriTimerId* timerId,
                          unsigned char* running)
{
  freettcn::PA::CPlatformAdaptor &pa = freettcn::PA::CPlatformAdaptor::Instance();
  return pa.TimerRunning(timerId, running);
}


TriStatus triPAReset()
{
  freettcn::PA::CPlatformAdaptor &pa = freettcn::PA::CPlatformAdaptor::Instance();
  return pa.Reset();
}


TriStatus triExternalFunction(const TriFunctionId* functionId,
                              TriParameterList* parameterList,
                              TriParameter* returnValue)
{
  freettcn::PA::CPlatformAdaptor &pa = freettcn::PA::CPlatformAdaptor::Instance();
  return pa.ExternalFunction(functionId, parameterList, returnValue);
}
