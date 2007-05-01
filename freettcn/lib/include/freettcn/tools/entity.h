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
 * @file   entity.h
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:38:47 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __ENTITY_H__
#define __ENTITY_H__


#include <freettcn/tools/exception.h>

namespace freettcn {
  
  class CTimeStamp;
  class CLogMask;
  
  class CEntity {
  public:
    enum Type {
      TYPE_TE,
      TYPE_TM,
      TYPE_CH,
      TYPE_CD,
      TYPE_SA,
      TYPE_PA,
      TYPE_TL
    };
    
  private:
    CTimeStamp *_ts;
    CLogMask *_logMask;
    bool _logging;
  public:
    CEntity();
    virtual ~CEntity() = 0;
    
    CTimeStamp &TimeStamp() const throw(ENotFound);
    CLogMask &LogMask() const throw(ENotFound);
    
    void LogEnable(CTimeStamp &ts, CLogMask &logMask);
    void LogDisable();
    bool Logging() const;
  };
  
} // namespace freettcn


#endif /* __ENTITY_H__ */
