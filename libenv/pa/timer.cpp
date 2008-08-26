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
 * @file   pa/timer.cpp
 * @author Mateusz Pusz
 * @date   Mon May  7 13:20:13 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/pa/timer.h"
#include "freettcn/pa/pa.h"
#include "freettcn/pa/paLogMask.h"
#include <freettcn/tools/timeStampMgr.h>
extern "C" {
#include <freettcn/ttcn3/tri_pa_te.h>
#include <freettcn/ttcn3/tci_tl.h>
}


freettcn::PA::CTimer::CTimer(const TriTimerId &timerId):
  _id(timerId)
{
}

freettcn::PA::CTimer::~CTimer()
{
}

void freettcn::PA::CTimer::Timeout() const
{
  freettcn::PA::CPlatformAdaptor &pa = freettcn::PA::CPlatformAdaptor::Instance();
  if (pa.Logging() && pa.LogMask().Get(freettcn::CLogMask::CMD_PA_T_TIMEOUT_DETECTED)) {
    TriComponentId comp = { { 0 } };
    tliTTimeoutDetected(0, pa.TimeStampMgr().Get(), 0, 0, comp, _id);
  }

  triTimeout(&_id);
}

const TriTimerId &freettcn::PA::CTimer::Id() const
{
  return _id;
}

