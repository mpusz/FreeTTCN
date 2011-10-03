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
 * @file   idObject.h
 * @author Mateusz Pusz
 * @date   Tue May  8 07:52:06 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __IDOBJECT_H__
#define __IDOBJECT_H__

extern "C" {
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/tools/nonCopyable.h>
#include <freettcn/tools/exception.h>
#include <vector>


namespace freettcn {
  
  namespace TE {
    
    class CIdObject : CNonCopyable {
      /**
       * Singleton design pattern
       */
      class CIdManager : freettcn::CNonCopyable {
        struct TData {
          bool valid;
          CIdObject *ptr;
        };
        typedef std::vector<TData> CIdArray;
        
        CIdArray _idArray;
        
        unsigned int Id2Index(const BinaryString &id) const;
        
      public:
        CIdManager();
        ~CIdManager();
        void Allocate(CIdObject &object, BinaryString &id);
        CIdObject &Object(const BinaryString &id);
        void Free(const BinaryString &id);
      };
      
      static CIdManager _manager;
      
      BinaryString _id;
      
    protected:
      const BinaryString &InstanceId() const;
      
    public:
      static CIdObject &Get(const BinaryString &id);
      
      CIdObject();
      virtual ~CIdObject() = 0;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __IDOBJECT_H__ */
