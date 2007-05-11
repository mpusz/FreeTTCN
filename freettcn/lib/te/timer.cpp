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
 * @file   timer.cpp
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
#include <iostream>


freettcn::TE::CTimer::CTimer(CTestComponentType::CInstance &comp, bool implicit, CCommand *cmd):
  _component(comp), _implicit(implicit), _command(cmd),
  _status(IDLE), _defaultDurationValid(false)
{
  _component.TimerAdd(*this, _implicit);
}

freettcn::TE::CTimer::CTimer(CTestComponentType::CInstance &comp, bool implicit, CCommand *cmd, TriTimerDuration defaultDuration) throw(EOperationFailed):
  _component(comp), _implicit(implicit), _command(cmd),
  _status(IDLE), _defaultDurationValid(true), _defaultDuration(defaultDuration)
{
  if (!cmd) {
    std::cout << "ERROR: Timer command not set!!!" << std::endl;
    throw freettcn::EOperationFailed();
  }
  
  if (_defaultDuration < 0) {
    std::cout << "ERROR: Timer default duration < 0!!!" << std::endl;
    throw freettcn::EOperationFailed();
  }
  
  _component.TimerAdd(*this, _implicit);
}

freettcn::TE::CTimer::~CTimer()
{
  if (_command)
    delete _command;
  _component.TimerRemove(*this, _implicit);
}

const TriTimerId &freettcn::TE::CTimer::Id() const
{
  return InstanceId();
}

void freettcn::TE::CTimer::Start() throw(freettcn::EOperationFailed)
{
  if (!_defaultDurationValid) {
    std::cout << "ERROR: Default duration not set!!!" << std::endl;
    throw freettcn::EOperationFailed();
  }
  
  _activeDuration = _defaultDuration;
  if (triStartTimer(&InstanceId(), _activeDuration) == TRI_ERROR)
    throw freettcn::EOperationFailed();
  
  _status = RUNNING;
}

void freettcn::TE::CTimer::Start(TriTimerDuration duration) throw(freettcn::EOperationFailed)
{
  if (duration < 0) {
    std::cout << "ERROR: Timer duration < 0!!!" << std::endl;
    throw freettcn::EOperationFailed();
  }
  
  _activeDuration = duration;
  if (triStartTimer(&InstanceId(), _activeDuration) == TRI_ERROR)
    throw freettcn::EOperationFailed();
  
  _status = RUNNING;
}

void freettcn::TE::CTimer::Stop() throw(freettcn::EOperationFailed)
{
  if (triStopTimer(&InstanceId()) == TRI_ERROR)
    throw freettcn::EOperationFailed();
}

TriTimerDuration freettcn::TE::CTimer::Read() const throw(freettcn::EOperationFailed)
{
  if (_status == RUNNING) {
    TriTimerDuration dur;
    if (triReadTimer(&InstanceId(), &dur) == TRI_ERROR)
      throw freettcn::EOperationFailed();
    return dur;
  }
  else
    return 0;
}

bool freettcn::TE::CTimer::Running() const throw(freettcn::EOperationFailed)
{
//   unsigned char running;
//   if (triTimerRunning(&InstanceId(), &running) == TRI_ERROR)
//     throw freettcn::EOperationFailed();
//   return running;
  return _status == RUNNING;
}

void freettcn::TE::CTimer::Timeout()
{
  _status = TIMEOUT;
  
  _command->Run(_component);
}






freettcn::TE::CTimer::CCommand::~CCommand()
{
}

freettcn::TE::CTimer::CCmdComponentRun::CCmdComponentRun(const CBehavior &behavior):
  _behavior(behavior)
{
}

void freettcn::TE::CTimer::CCmdComponentRun::Run(CTestComponentType::CInstance &comp)
{
  _behavior.Enqueue(comp);
  comp.Run();
}
