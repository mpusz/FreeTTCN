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
 * @file   timeStampMgr.h
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:28:52 2007
 * 
 * @brief  Timestamp handler base class declaration.
 * 
 */

#ifndef __TIMESTAMPMGR_H__
#define __TIMESTAMPMGR_H__

#include <string>

namespace freettcn {

  /**
   * @brief Timestamp manager class
   * 
   * TTCN-3 standard defines base time unit as one second. Smaller time
   * periods should be represented as floating-point numbers. For some
   * scenarios it can be a bad solution. Sometimes user may want to interpret
   * elapsing time in different manner (hours, miliseconds, hardware clock
   * ticks, etc.). User may also want to collect absolute values or values
   * relative to test start. It is why CTimeStampMgr class was introduced.
   * 
   * CTimeStampMgr class is a base class for timestamp management hierarchy. It
   * provides base interface that allow operation in absolute and relative
   * mode. It also provides an interface for methods that gathers timestamps
   * from Operating System and converts them to a string.
   */
  class CTimeStampMgr {
  public:
    /**
     * @brief Timestamps handler class operational mode.
     */
    enum TMode {
      MODE_ABSOLUTE,
      MODE_RELATIVE
    };
    
  private:
    TMode _mode;                                  /**< @brief operational mode */
    
  public:
    CTimeStampMgr(TMode initMode = MODE_RELATIVE);
    virtual ~CTimeStampMgr();
    
    void Mode(TMode mode);
    TMode Mode() const;
    
    /**
     * @brief Resets relative value to current time
     *
     * Method resets relative value to current time by setting
     * new value of @p _absTimeOffset.
     */
    virtual void Reset() = 0;
    
    /** 
     * @brief Obtains timestamp from Operating System
     * 
     * Method obtains current timestamp from Operating System.
     * 
     * @return Current timestamp
     */
    virtual int Get() const = 0;
    
    /** 
     * @brief Converts timestamp to string
     * 
     * Method converts given timestamp to a string representation.
     *
     * @param ts timestamp value to convert
     * 
     * @return Timestamp string
     */
    virtual std::string String(int ts) const = 0;
  };

} // namespace freettcn



inline freettcn::CTimeStampMgr::CTimeStampMgr(TMode initMode /* MODE_RELATIVE */):
  _mode(initMode)
{
}


inline freettcn::CTimeStampMgr::~CTimeStampMgr()
{
}


inline void freettcn::CTimeStampMgr::Mode(TMode mode)
{
  _mode = mode;
}


inline freettcn::CTimeStampMgr::TMode freettcn::CTimeStampMgr::Mode() const
{
  return _mode;
}


#endif /* __TIMESTAMPMGR_H__ */
