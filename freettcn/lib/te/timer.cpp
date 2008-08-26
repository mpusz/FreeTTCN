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
 * @file   te/timer.cpp
 * @author Mateusz Pusz
 * @date   Tue May  8 11:10:58 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/timer.h"
#include "freettcn/te/behavior.h"
extern "C" {
#include <freettcn/ttcn3/tri_te_pa.h>
}


freettcn::TE::CTimer::CTimer(CTestComponentType::CInstanceLocal &comp, bool implicit):
  _component(comp), _implicit(implicit),
  _status(IDLE), _defaultDurationValid(false)
{
  _component.TimerAdd(*this, _implicit);
}

freettcn::TE::CTimer::CTimer(CTestComponentType::CInstanceLocal &comp, bool implicit, TriTimerDuration defaultDuration):
  _component(comp), _implicit(implicit),
  _status(IDLE), _defaultDurationValid(true), _defaultDuration(defaultDuration)
{
  if (_defaultDuration < 0)
    throw EOperationFailed(E_DATA, "Timer default duration < 0!!!");
  
  _component.TimerAdd(*this, _implicit);
}

freettcn::TE::CTimer::~CTimer()
{
  _component.TimerRemove(*this, _implicit);
  if (Running())
    Stop();
}

const TriTimerId &freettcn::TE::CTimer::Id() const
{
  return InstanceId();
}

void freettcn::TE::CTimer::Start()
{
  if (!_defaultDurationValid)
    throw EOperationFailed(E_DATA, "Default duration not set!!!");
  
  _activeDuration = _defaultDuration;
  if (triStartTimer(&InstanceId(), _activeDuration) == TRI_ERROR)
    throw EOperationFailed(E_DATA, "triStartTimer() failed!!!");
  
  _status = RUNNING;
}

void freettcn::TE::CTimer::Start(TriTimerDuration duration)
{
  if (duration < 0)
    throw EOperationFailed(E_DATA, "Timer duration < 0!!!");
  
  _activeDuration = duration;
  if (triStartTimer(&InstanceId(), _activeDuration) == TRI_ERROR)
    throw EOperationFailed(E_DATA, "triStartTimer() failed!!!");
  
  _status = RUNNING;
}

void freettcn::TE::CTimer::Stop()
{
  if (triStopTimer(&InstanceId()) == TRI_ERROR)
    throw EOperationFailed(E_DATA, "triStopTimer() failed!!!");
}

TriTimerDuration freettcn::TE::CTimer::Read() const
{
  if (_status == RUNNING) {
    TriTimerDuration dur;
    if (triReadTimer(&InstanceId(), &dur) == TRI_ERROR)
      throw EOperationFailed(E_DATA, "triReadTimer() failed !!!");
    return dur;
  }
  else
    return 0;
}

bool freettcn::TE::CTimer::Running() const
{
//   unsigned char running;
//   if (triTimerRunning(&InstanceId(), &running) == TRI_ERROR)
//     throw EOperationFailed();
//   return running;
  return _status == RUNNING;
}

void freettcn::TE::CTimer::HandlerAdd(unsigned int behavoiorOffset)
{
  _offsetList.push_back(behavoiorOffset);
}

void freettcn::TE::CTimer::HandlerRemove(unsigned int behavoiorOffset)
{
  for(COffsetList::iterator it=_offsetList.begin(); it!=_offsetList.end(); ++it) {
    if (*it == behavoiorOffset) {
      _offsetList.erase(it);
      break;
    }
  }
}

void freettcn::TE::CTimer::Timeout()
{
  _status = TIMEOUT;
  
  // timer can be deleted during execution
  COffsetList list(_offsetList);
  _offsetList.clear();
  
  for(COffsetList::iterator it=list.begin(); it!=list.end(); ++it)
    _component.Run(*it);
}
