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
 * @brief  TTCN-3 entities base class definition
 * 
 */

#include "freettcn/tools/entity.h"
#include "freettcn/tools/exception.h"


/** 
 * @brief CEntity class constructor
 */
freettcn::CEntity::CEntity():
  _logging(false)
{
}


/** 
 * @brief CEntity class destructor
 */
freettcn::CEntity::~CEntity()
{
}


/** 
 * @brief Returns class that handles timestamp
 *
 * Methods returns class that handles timestamp.
 * 
 * @exception freettcn::ENotFound Timestamps handler class not set.
 * 
 * @return Class that handles timestamps
 */
freettcn::CTimeStampMgr &freettcn::CEntity::TimeStampMgr() const
{
  if (_ts)
    return *_ts;
  else
    throw ENotFound(E_DATA, "Timestamps handler class not set!!!");
}


/** 
 * @brief Returns class that defines logging mask
 *
 * Method returns class that defines logging mask.
 *
 * @exception freettcn::ENotFound Logging mask not set
 * 
 * @return Class that defines logging mask
 */
freettcn::CLogMask &freettcn::CEntity::LogMask() const
{
  if (_logMask)
    return *_logMask;
  else
    throw ENotFound(E_DATA, "Logging mask not set!!!");
}


/** 
 * @brief Specifies if logging is enabled
 * 
 * Method specifies if logging is enabled for current entity.
 * 
 * @return Logging flag
 */
bool freettcn::CEntity::Logging() const
{
  return _logging;
}


/** 
 * @brief Starts logging on current entity
 * 
 * Method enables logging on current entity end sets classes that handles
 * timestamping and defines which events should be logged.
 * 
 * @param ts Timestamps manager class
 * @param logMask Logging mask definition
 */
void freettcn::CEntity::LogEnable(std::shared_ptr<CTimeStampMgr> ts, std::shared_ptr<CLogMask> logMask)
{
  _ts = ts;
  _logMask = logMask;
  _logging = true;
}


/** 
 * @brief Stops logging on current entity
 * 
 * Method disables logging on current entity.
 */
void freettcn::CEntity::LogDisable()
{
  _ts.reset();
  _logMask.reset();
  _logging = false;
}
