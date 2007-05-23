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
 * @file   octetstring.h
 * @author Mateusz Pusz
 * @date   Tue May 22 22:16:17 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __OCTETSTRING_H__
#define __OCTETSTRING_H__

#include <freettcn/te/type.h>
#include <string>


namespace freettcn {

  namespace TE {
    
    class COctetstringType : public CType {
    public:
      class CInstance : public CType::CInstance {
        std::string _value;
      public:
        CInstance(const CType &type);
        
        const char *Value() const throw(EOmitSet);
        void Value(const char *value) throw(EOperationFailed);
        
        int Element(unsigned int position) const throw(EOperationFailed, EOmitSet);
        void Element(unsigned int position, int value) throw(EOperationFailed);
        
        unsigned int Length() const;
        void Length(unsigned int length);
      };
      
    public:
      friend class CInstance;
      
      COctetstringType();
      virtual CInstance *InstanceCreate() const;
    };
    
  } // namespace TE
  
} // namespace freettcn

#endif /* __OCTETSTRING_H__ */
