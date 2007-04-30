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
 * @file   entity.cpp
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:38:18 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/tools/entity.h"


freettcn::CEntity::CEntity():
  _ts(0), _logMask(0), _logging(false)
{
}

freettcn::CEntity::~CEntity()
{
}

freettcn::CTimeStamp &freettcn::CEntity::TimeStamp() const throw(freettcn::ENotFound)
{
  if (_ts)
    return *_ts;
  else
    throw freettcn::ENotFound();
}

freettcn::CLogMask &freettcn::CEntity::LogMask() const throw(freettcn::ENotFound)
{
  if (_logMask)
    return *_logMask;
  else
    throw freettcn::ENotFound();
}

void freettcn::CEntity::LogEnable(freettcn::CTimeStamp &ts, freettcn::CLogMask &logMask)
{
  _ts = &ts;
  _logMask = &logMask;
  _logging = true;
}

void freettcn::CEntity::LogDisable()
{
  _ts = 0;
  _logMask = 0;
  _logging = false;
}

bool freettcn::CEntity::Logging() const
{
  return _logging;
}
