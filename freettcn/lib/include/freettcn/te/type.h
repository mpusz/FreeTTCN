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
 * @file   type.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:51 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TYPE_H__
#define __TYPE_H__

extern "C" {
#include <freettcn/ttcn3/tci.h>
}

namespace freettcn {

  namespace TE {

    class CValue;
    class CModule;
    
    class CType {
      const CModule *_module;
      QualifiedName _id;
      TciTypeClassType _class;
      String _encoding;
      String _encodingVariant;
      String _extension;
      
    public:
      CType(const CModule    *module,
            String           name,
            TciTypeClassType typeClass,
            String          encoding,
            String          encodingVariant,
            String          extension);
      virtual ~CType();
      
      const CModule *DefiningModule() const;
      String Name() const;
      const QualifiedName &Id() const;
      TciTypeClassType Class() const;
      
      String Encoding() const;
      String EncodingVariant() const;
      String Extension() const;
      
      virtual CValue *InstanceCreate(bool omit = false) const = 0;
    };
    
    
    class CBooleanType : public CType {
    public:
      CBooleanType();
      virtual CValue *InstanceCreate(bool omit = false) const;
    };
    
    
//     class CRecordType : public CType {
//     public:
//       CRecordType(const CModule    &module,
//                   String           encoding,
//                   String           encodingVariant,
//                   String           extension);
//       virtual CValue *InstanceCreate(bool omit = false) const;
//     };




    class CTestComponentType : public CType {
    public:
      CTestComponentType(const CModule *module, String name);
    };
    
    class CControlComponentType : public CTestComponentType {
    public:
      CControlComponentType();
      virtual CValue *InstanceCreate(bool omit = false) const;
    };
    
    
    
    
    
    
    class CBasicType {
      static const CBooleanType _boolean;
      static const CControlComponentType _control;
    public:
      static const CBooleanType &Boolean();
      static const CControlComponentType &ControlComponent();
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TYPE_H__ */
