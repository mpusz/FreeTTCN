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


/**
 * @file   glibPlatformAdaptor.h
 * @author Mateusz Pusz
 * @date   Mon May  7 14:27:15 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __GLIBPLATFORMADAPTOR_H__
#define __GLIBPLATFORMADAPTOR_H__

#include <freettcn/pa/pa.h>
#include <freettcn/pa/timer.h>


class CTimer : public freettcn::PA::CTimer {
public:
  CTimer(const TriTimerId &timerId);

  virtual void Start(TriTimerDuration duration) throw(freettcn::EOperationFailed);
  virtual void Stop() throw(freettcn::EOperationFailed);
  virtual TriTimerDuration Read() const throw(freettcn::EOperationFailed);
  virtual bool Running() const throw(freettcn::EOperationFailed);
};


class CPlatformAdaptor : public freettcn::PA::CPlatformAdaptor {
  virtual CTimer *TimerCreate(const TriTimerId &timerId) const;
};


#endif /* __GLIBPLATFORMADAPTOR_H__ */
