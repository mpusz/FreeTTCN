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
 * @file   timeStampMgrSeconds.cpp
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:31:19 2007
 * 
 * @brief  TTCN-3 seconds timestamp manager class definition.
 * 
 */

#include "freettcn/tools/timeStampMgrSeconds.h"
#include "freettcn/tools/exception.h"
#include <cmath>
#include <cstdio>
#include <sys/time.h>


freettcn::CTimeStampMgrSeconds::CTimeStampMgrSeconds(unsigned short precision /* 4 */, TMode initMode /* MODE_RELATIVE */):
  CTimeStampMgr(initMode), _precision(precision)
{
  Reset();
}


freettcn::CTimeStampMgrSeconds::~CTimeStampMgrSeconds()
{
}


void freettcn::CTimeStampMgrSeconds::Set(TTime &ts) const
{
  struct timeval tv;
  struct timezone tz;
  
  if(gettimeofday(&tv, &tz) == -1)
    throw EOperationFailed(E_DATA, "Couldn't get time of day!!!");
  
  ts.sec = tv.tv_sec;
  ts.usec = tv.tv_usec;
}


int freettcn::CTimeStampMgrSeconds::Convert(const TTime &value) const
{
  if (_precision) {
    TTime ts(value);
    
    Sub(ts, _absTimeOffset);
    
    int base = static_cast<int>(pow(10, _precision));
    return ts.sec * base + static_cast<int>(ts.usec * (base / 1000000.0));
  }
  else {
    return value.sec - _absTimeOffset.sec;
  }
}


void freettcn::CTimeStampMgrSeconds::Convert(int ts, TTime &value) const
{
  if (_precision) {
    int base = static_cast<int>(pow(10, _precision));
    value.sec = ts / base;
    value.usec = (ts - value.sec * base) * (1000000 / base);

    if (Mode() == MODE_ABSOLUTE)
      Add(value, _absTimeOffset);
  }
  else {
    value.sec = ts;
    value.usec = 0;
    
    if (Mode() == MODE_ABSOLUTE)
      value.sec += _absTimeOffset.sec;
  }
}


void freettcn::CTimeStampMgrSeconds::Sub(TTime &value, const TTime &delta) const
{
  // substract time offset from current time
  if (delta.usec > value.usec) {
    value.sec -= delta.sec + 1;
    value.usec += 1000000 - delta.usec;
  }
  else {
    value.sec -= delta.sec;
    value.usec -= delta.usec;
  }
}


void freettcn::CTimeStampMgrSeconds::Add(TTime &value, const TTime &delta) const
{
  // add time offset to current time
  value.sec += delta.sec;
  if ((value.usec += delta.usec) > 1000000) {
    value.sec++;
    value.usec -= 1000000;
  }
}


void freettcn::CTimeStampMgrSeconds::Reset()
{
  Set(_absTimeOffset);
  
  // adjust value to specified precision
  int base = static_cast<int>(pow(10, 6 - _precision));
  _absTimeOffset.usec -= _absTimeOffset.usec % base;
}


int freettcn::CTimeStampMgrSeconds::Get() const
{
  TTime value;
  Set(value);
  return Convert(value);
}


std::string freettcn::CTimeStampMgrSeconds::String(int ts) const
{
  TTime value;
  Convert(ts, value);
    
  char str[64];
  if (_precision)
    sprintf(str, "%0*u.%0*u", Mode() == MODE_ABSOLUTE ? 10 : 6, value.sec, _precision, static_cast<int>(value.usec / 1000000.0 * static_cast<int>(pow(10, _precision)) + 0.5));
  else
    sprintf(str, "%0*u", Mode() == MODE_ABSOLUTE ? 10 : 6, value.sec);
  
  return str;
}
