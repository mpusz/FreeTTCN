//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) usage example.

// This example is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This example is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this example; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   icmp_cd.h
 * @author Mateusz Pusz
 * @date   Wed May 30 14:09:12 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __ICMP_CD_H__
#define __ICMP_CD_H__

#include <freettcn/cd/codec.h>


namespace freettcn {
  
  namespace icmp {
    
    class CCodec : public CD::CCodec {
      enum {
        ID_ICMPMSG
      };
    public:
      CCodec();
      bool CapabilityCheck(const Value &value, unsigned int &valueId) const;
      void Encode(unsigned int valueId, const Value &value, CD::CBuffer &buffer) const;
    };
    
  } // namespace icmp

} // namespace freettcn


#endif /* __ICMP_CD_H__ */
