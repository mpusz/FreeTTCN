//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcnenv (Free TTCN Environment) library.

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
 * @file   internalCodec.h
 * @author Mateusz Pusz
 * @date   Wed May 30 10:06:03 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __INTERNALCODEC_H__
#define __INTERNALCODEC_H__

#include <freettcn/cd/codec.h>


namespace freettcn {
  
  namespace CD {
    
    class CInternalCodec : public CCodec {
      enum {
        ID_INTEGER
      };
    public:
      CInternalCodec();
      bool CapabilityCheck(TciValue value, unsigned int &valueId) const;
      void Encode(unsigned int valueId, TciValue value, BinaryString &buffer) const;
    };
    
  } // namespace CD

} // namespace freettcn


#endif /* __INTERNALCODEC_H__ */
