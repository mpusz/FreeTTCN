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
 * @file   integer.h
 * @author Mateusz Pusz
 * @date   Mon May 14 21:34:08 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <freettcn/te/type.h>
#include <freettcn/tools/exception.h>

namespace freettcn {
  
  namespace TE {
    
    class CIntegerType : public CType {
    public:
      class CInstance : public CType::CInstance {
        long _value;
      public:
        CInstance(const CType &type);
        CInstance(const CType &type, long value);
        
        virtual CInstance *Duplicate() const;
        
        void AbsValue(const char *value) throw(EOperationFailed);
//         void DigitsNum(unsigned long dig_num);
//         void Sign(bool sign);
        long Value() const throw(EOmitSet);
        void Value(long value);
      };
      
    public:
      CIntegerType();
      virtual CInstance *InstanceCreate() const;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __INTEGER_H__ */
