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
 * @file   logMask.h
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:35:01 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __LOGMASK_H__
#define __LOGMASK_H__

#include <vector>

namespace freettcn {

  class CLogMask {
    unsigned short _num;
    std::vector<bool> _array;
  public:
    explicit CLogMask(unsigned short num, bool enabled = true);
    virtual ~CLogMask() = 0;
    
    void Set(bool enabled);
    void Set(unsigned short idx, bool enabled);
    bool Get(unsigned short idx);
  };

} // namespace freettcn


#endif /* __LOGMASK_H__ */
