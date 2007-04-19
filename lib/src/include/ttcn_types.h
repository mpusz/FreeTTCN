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


#include "module.h"

namespace freettcn {

  class CValue;
  
  class CType {
    const CModule *_module;
    char *_name;
    TciTypeClassType _class;
    String _encoding;
    String _encodingVariant;
    String _extension;
    
  protected:
    CType(const CModule    *module,
          String           name,
          TciTypeClassType typeClass,
          String           encoding,
          String           encodingVariant,
          String           extension);
    virtual ~CType();
    
  public:
    const CModule *DefiningModule() const;
    String Name() const;
    TciTypeClassType Class() const;
    
    String Encoding() const;
    String EncodingVariant() const;
    String Extension() const;
    
    virtual CValue *InstanceCreate(bool omit = false) const = 0;
  };
  
  class CBooleanType : public CType {
  public:
    CBooleanType(String           encoding,
                 String           encodingVariant,
                 String           extension);
    virtual CValue *InstanceCreate(bool omit = false) const;
  };

  class CRecordType : public CType {
  public:
    CRecordType(const CModule    *module,
                String           encoding,
                String           encodingVariant,
                String           extension);
    virtual CValue *InstanceCreate(bool omit = false) const;
  };
}
