/**
 * @file   tools.cpp
 * @author Mateusz Pusz
 * @date   Fri Apr 20 11:25:58 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/tools/tools.h"
#include <iostream>
#include <cmath>
#include <sys/time.h>


freettcn::CTimeStamp::CTimeStamp(unsigned short precision /* 4 */, TMode initMode /* MODE_RELATIVE */):
  _precision(precision), _mode(initMode)
{
  Reset();
}


freettcn::CTimeStamp::~CTimeStamp()
{
}


void freettcn::CTimeStamp::Set(TTime &ts) const
{
  struct timeval tv;
  struct timezone tz;
  
  if (gettimeofday(&tv, &tz) == -1)
    std::cout << "ERROR!!! Couldn't get time of day" << std::endl;
  
  ts.sec = tv.tv_sec;
  ts.usec = tv.tv_usec;
}


void freettcn::CTimeStamp::Sub(TTime &value, const TTime &delta) const
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


void freettcn::CTimeStamp::Add(TTime &value, const TTime &delta) const
{
  // add time offset to current time
  value.sec += delta.sec;
  if ((value.usec += delta.usec) > 1000000) {
    value.sec++;
    value.usec -= 1000000;
  }
}


int freettcn::CTimeStamp::Convert(TTime &value) const
{
  if (_precision) {
    Sub(value, _absTimeOffset);

    int base = static_cast<int>(pow(10, _precision));
    return value.sec * base + value.usec * base / 1000000;
  }
  else {
    return value.sec - _absTimeOffset.sec;
  }
}


void freettcn::CTimeStamp::Convert(int ts, TTime &value) const
{
  if (_precision) {
    int base = static_cast<int>(pow(10, _precision));
    value.sec = ts / base;
    value.usec = (ts - value.sec * base) * 1000000 / base;
    
    if (_mode == MODE_ABSOLUTE)
      Add(value, _absTimeOffset);
  }
  else {
    value.sec = ts;
    value.usec = 0;
    
    if (_mode == MODE_ABSOLUTE)
      value.sec += _absTimeOffset.sec;
  }
}


void freettcn::CTimeStamp::Mode(TMode mode)
{
  _mode = mode;
}


void freettcn::CTimeStamp::Reset()
{
  Set(_absTimeOffset);
  
  // adjust value to specified precision
  int base = static_cast<int>(pow(10, 6 - _precision));
  _absTimeOffset.usec -= _absTimeOffset.usec % base;
}


int freettcn::CTimeStamp::Get() const
{
  TTime value;
  Set(value);
  return Convert(value);
}


std::string freettcn::CTimeStamp::String(int ts) const
{
  TTime value;
  Convert(ts, value);
    
  char str[64];
  if (_precision)
    sprintf(str, "%0*u.%0*u", _mode == MODE_ABSOLUTE ? 10 : 6, value.sec, _precision, static_cast<int>(value.usec / 1000000.0 * static_cast<int>(pow(10, _precision)) + 0.5));
  else
    sprintf(str, "%0*u", _mode == MODE_ABSOLUTE ? 10 : 6, value.sec);
  
  return str;
}




freettcn::CLogMask::CLogMask(unsigned short num, bool enabled /* true */):
  _num(num), _array(num, enabled)
{
}

freettcn::CLogMask::~CLogMask()
{
}

void freettcn::CLogMask::Set(bool enabled)
{
  for(unsigned short i=0; i<_array.size(); i++)
    _array[i] = enabled;
}

void freettcn::CLogMask::Set(unsigned short idx, bool enabled)
{
  _array[idx] = enabled;
}

bool freettcn::CLogMask::Get(unsigned short idx)
{
  return _array[idx];
}



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
