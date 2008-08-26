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
#include "freettcn/pa/paLogMask.h"
#include <freettcn/tools/timeStampMgr.h>
#include <freettcn/tools/exception.h>
extern "C" {
#include <freettcn/ttcn3/tci_tl.h>
}


freettcn::PA::CPlatformAdaptor *freettcn::PA::CPlatformAdaptor::_instance = 0;

freettcn::PA::CPlatformAdaptor &freettcn::PA::CPlatformAdaptor::Instance()
{
  if (_instance)
    return *_instance;
  
  throw ENotInitialized(E_DATA, "PA instance not inited!!!");
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
  for(CTimerList::const_iterator it=_timerList.begin(); it!=_timerList.end(); ++it)
    if ((*it)->Running())
      (*it)->Stop();
  
  // clear timers list
  Purge(_timerList);
  
  return TRI_OK;
}



freettcn::PA::CTimer &freettcn::PA::CPlatformAdaptor::TimerGet(const TriTimerId &timerId) const
{
  for(CTimerList::const_iterator it=_timerList.begin(); it!=_timerList.end(); ++it)
    if (&timerId == &(*it)->Id())
      return *(*it);
  
  throw ENotFound(E_DATA, "Timer not found!!!");
}


TriStatus freettcn::PA::CPlatformAdaptor::TimerStart(const TriTimerId *timerId, TriTimerDuration timerDuration)
{
  if (!timerId)
    return TRI_ERROR;
  
  freettcn::PA::CTimer *timer = 0;
  
  // check if timer running already
  for(CTimerList::const_iterator it=_timerList.begin(); it!=_timerList.end(); ++it) {
    if (timerId == &(*it)->Id()) {
      timer = *it;
      break;
    }
  }
  
  if (!timer) {
    // create new timer
    timer = TimerCreate(*timerId);
    _timerList.push_back(timer);
  }
  
  timer->Start(timerDuration);
  
  if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_PA_T_START)) {
    TriComponentId comp = { { 0 } };
    tliTStart(0, TimeStampMgr().Get(), 0, 0, comp, *timerId, timerDuration);
  }
  
  return TRI_OK;
}


TriStatus freettcn::PA::CPlatformAdaptor::TimerStop(const TriTimerId *timerId)
{
  if (!timerId)
    return TRI_ERROR;
  
  try {
    freettcn::PA::CTimer &timer = TimerGet(*timerId);
    timer.Stop();
    
    if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_PA_T_STOP)) {
      TriComponentId comp = { { 0 } };
      tliTStop(0, TimeStampMgr().Get(), 0, 0, comp, *timerId, timer.Read());
    }

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
    
    if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_PA_T_READ)) {
      TriComponentId comp = { { 0 } };
      tliTStart(0, TimeStampMgr().Get(), 0, 0, comp, *timerId, *elapsedTime);
    }
    
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

    if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_PA_T_RUNNING)) {
      TriComponentId comp = { { 0 } };
      tliTRunning(0, TimeStampMgr().Get(), 0, 0, comp, *timerId, *running ? runningT : expiredT);
    }
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
