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
 * @file   timeStampMgrSeconds.h
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:28:52 2007
 * 
 * @brief  TTCN-3 seconds timestamp manager class declaration.
 * 
 */

#ifndef __TIMESTAMPMGRSECONDS_H__
#define __TIMESTAMPMGRSECONDS_H__

#include "timeStampMgr.h"

namespace freettcn {

  class CTimeStampMgrSeconds : public CTimeStampMgr {
  protected:
    struct TTime {
      int sec;
      int usec;
    };

  private:
    const unsigned short _precision;
    TTime _absTimeOffset;
    
  protected:
    virtual void Set(TTime &ts) const;
    virtual int Convert(const TTime &value) const;
    virtual void Convert(int ts, TTime &value) const;

    void Sub(TTime &value, const TTime &delta) const;
    void Add(TTime &value, const TTime &delta) const;
    
  public:
    CTimeStampMgrSeconds(unsigned short precision = 4, TMode initMode = MODE_RELATIVE);
    virtual ~CTimeStampMgrSeconds();
    
    virtual void Reset();
    virtual int Get() const;
    virtual std::string String(int ts) const;
  };


} // namespace freettcn


#endif /* __TIMESTAMPMGRSECONDS_H__ */
