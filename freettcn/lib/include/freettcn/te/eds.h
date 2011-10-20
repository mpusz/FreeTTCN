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
 * @file   eds.h
 * @author Mateusz Pusz
 * @date   Sat Apr  7 22:10:55 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __EDS_H__
#define __EDS_H__

#include <freettcn/tools/nonCopyable.h>

namespace freettcn {
  
  namespace TE {
    
    class CEncodingDecodingSystem : CNonCopyable
    {
    public:
      CEncodingDecodingSystem() = default;
      ~CEncodingDecodingSystem() = default;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __EDS_H__ */
