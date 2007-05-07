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
 * @file   pa.cpp
 * @author Mateusz Pusz
 * @date   Mon May  7 13:18:49 2007
 * 
 * @brief  
 * 
 * 
 */


#include "freettcn/pa/pa.h"
#include "freettcn/pa/timer.h"
#include <freettcn/tools/tools.h>
#include <iostream>


freettcn::PA::CPlatformAdaptor *freettcn::PA::CPlatformAdaptor::_instance = 0;

freettcn::PA::CPlatformAdaptor &freettcn::PA::CPlatformAdaptor::Instance() throw(ENotFound)
{
  if (_instance)
    return *_instance;
  
  throw ENotFound();
}

freettcn::PA::CPlatformAdaptor::CPlatformAdaptor()
{
  _instance = this;
}

freettcn::PA::CPlatformAdaptor::~CPlatformAdaptor()
{
  Reset();
  
  _instance = 0;
}


TriStatus freettcn::PA::CPlatformAdaptor::Reset()
{
  // stop all timers
  for(TTimerList::const_iterator it=_timerList.begin(); it!=_timerList.end(); ++it)
    if ((*it)->Running())
      (*it)->Stop();
  
  // clear timers list
  Purge(_timerList);
  
  return TRI_OK;
}



freettcn::PA::CTimer &freettcn::PA::CPlatformAdaptor::TimerGet(const TriTimerId &timerId) const throw(freettcn::ENotFound)
{
  for(TTimerList::const_iterator it=_timerList.begin(); it!=_timerList.end(); ++it)
    if (&timerId == &(*it)->Id())
      return *(*it);
  
  std::cout << "ERROR: Timer not found!!!" << std::endl;
  throw freettcn::ENotFound();
}


TriStatus freettcn::PA::CPlatformAdaptor::TimerStart(const TriTimerId *timerId, TriTimerDuration timerDuration)
{
  if (!timerId)
    return TRI_ERROR;
  
  freettcn::PA::CTimer *timer;
  
  // check if timer running already
  for(TTimerList::const_iterator it=_timerList.begin(); it!=_timerList.end(); ++it) {
    if (timerId == &(*it)->Id()) {
      timer = *it;
      break;
    }
  }
  
  if (!timer)
    // create new timer
    timer = TimerCreate(*timerId);
  
  timer->Start(timerDuration);
  
  return TRI_OK;
}


TriStatus freettcn::PA::CPlatformAdaptor::TimerStop(const TriTimerId *timerId)
{
  if (!timerId)
    return TRI_ERROR;
  
  try {
    freettcn::PA::CTimer &timer = TimerGet(*timerId);
    timer.Stop();
    
    return TRI_OK;
  }
  catch(freettcn::Exception) {
    return TRI_ERROR;
  }
}


TriStatus freettcn::PA::CPlatformAdaptor::TimerRead(const TriTimerId* timerId, TriTimerDuration* elapsedTime)
{
  if (!timerId)
    return TRI_ERROR;
  
  if (!elapsedTime)
    return TRI_ERROR;
  
  try {
    freettcn::PA::CTimer &timer = TimerGet(*timerId);
    *elapsedTime = timer.Read();
    
    return TRI_OK;
  }
  catch(freettcn::Exception) {
    return TRI_ERROR;
  }
}


TriStatus freettcn::PA::CPlatformAdaptor::TimerRunning(const TriTimerId* timerId, unsigned char* running)
{
  if (!timerId)
    return TRI_ERROR;
  
  if (!running)
    return TRI_ERROR;
  
  try {
    freettcn::PA::CTimer &timer = TimerGet(*timerId);
    *running = timer.Running();
  }
  catch(freettcn::Exception) {
    return TRI_ERROR;
  }
  
  return TRI_OK;
}


TriStatus freettcn::PA::CPlatformAdaptor::ExternalFunction(const TriFunctionId* functionId,
                                                           TriParameterList* parameterList,
                                                           TriParameter* returnValue)
{
  return TRI_OK;
}
