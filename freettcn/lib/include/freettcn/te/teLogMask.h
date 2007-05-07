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
 * @file   teLogMask.h
 * @author Mateusz Pusz
 * @date   Mon May  7 13:58:29 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TELOGMASK_H__
#define __TELOGMASK_H__

#include <freettcn/tools/logMask.h>


namespace freettcn {

  namespace TE {
    
    class CLogMask : public freettcn::CLogMask {
    public:
      CLogMask(bool enabled = true);
      ~CLogMask();
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TELOGMASK_H__ */
