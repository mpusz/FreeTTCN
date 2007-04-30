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
 * @file   timeStamp.h
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:28:52 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__

#include <string>

namespace freettcn {

  class CTimeStamp {
  public:
    enum TMode {
      MODE_ABSOLUTE,
      MODE_RELATIVE
    };
    
    struct TTime {
      int sec;
      int usec;
    };
  private:
    const unsigned short _precision;
    TMode _mode;
    TTime _absTimeOffset;
    
  protected:
    virtual void Set(TTime &ts) const;
    void Sub(TTime &value, const TTime &delta) const;
    void Add(TTime &value, const TTime &delta) const;
    virtual int Convert(TTime &value) const;
    virtual void Convert(int ts, TTime &ts) const;
    
  public:
    CTimeStamp(unsigned short precision = 4, TMode initMode = MODE_RELATIVE);
    virtual ~CTimeStamp();
    
    void Mode(TMode mode);
    TMode Mode() const;
    void Reset();
    
    int Get() const;
    virtual std::string String(int ts) const;
  };

} // namespace freettcn


#endif /* __TIMESTAMP_H__ */
