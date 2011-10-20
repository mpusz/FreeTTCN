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
 * @file   tciType.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:08:14 2007
 * 
 * @brief  
 * 
 * 
 */


#include "freettcn/ttcn3/tciType.h"
#include <algorithm>


freettcn::CType::CValue::CValue(const std::shared_ptr<const TciType> &type,
                                const Tstring &encoding,
                                const Tstring &encodingVariant):
  _type(type)
{
  if(encoding.empty() || encoding == type->getTypeEncoding())
    _encoding.reset(new Tstring(encoding));
  if(encodingVariant.empty() || encodingVariant == type->getTypeEncodingVariant())
    _encoding.reset(new Tstring(encodingVariant));
}


const Tstring &freettcn::CType::CValue::getValueEncoding() const
{
  if(_encoding)
    return *_encoding;
  else
    return _type->getTypeEncoding();
}


const Tstring &freettcn::CType::CValue::getValueEncodingVariant() const
{
  if(_encodingVariant)
    return *_encodingVariant;
  else
    return _type->getTypeEncodingVariant();
}




freettcn::CType::CValueOmitted::CValueOmitted(const std::shared_ptr<const TciType> &type,
                                              const Tstring &encoding /* = "" */,
                                              const Tstring &encodingVariant /* = "" */):
  CValue(type, encoding, encodingVariant)
{
}


ORG_ETSI_TTCN3_TCI::TciValue *freettcn::CType::CValueOmitted::clone() const
{
  return new CValueOmitted(*this);
}


Tboolean freettcn::CType::CValueOmitted::operator==(const TciValue &val) const
{
  return notPresent() == val.notPresent() &&
    getValueEncoding() == val.getValueEncoding() &&
    getValueEncodingVariant() == val.getValueEncodingVariant() &&
    getType() == val.getType();
}


Tboolean freettcn::CType::CValueOmitted::operator<(const TciValue &val) const override
{
  return notPresent() < val.notPresent() &&
    getValueEncoding() < val.getValueEncoding() &&
    getValueEncodingVariant() < val.getValueEncodingVariant() && 
    getType() < val.getType();
}



freettcn::CType::CType(const std::shared_ptr<const TciModuleId> &moduleId,
                       const Tstring      &name,
                       const TciTypeClass &typeClass,
                       const Tstring      &encoding,
                       const Tstring      &encodingVariant,
                       const CExtension   &extension):
  _moduleId(moduleId), _name(new Tstring(name)), _class(typeClass), _encoding(new Tstring(encoding)), _encodingVariant(new Tstring(encodingVariant)), _extension(new CExtension)
{
  std::for_each(extension.begin(), extension.end(),
                [this](Tstring *str) { _extension->push_back(new Tstring(*str)); });
}


Tboolean freettcn::CType::operator==(const TciType &typ) const
{
  return _class == typ.getTypeClass() &&
    *_name == typ.getName() &&
    *_encoding == typ.getTypeEncoding() &&
    *_encodingVariant == typ.getTypeEncodingVariant() &&
    *_extension == typ.getTypeExtension() &&
    *_moduleId == typ.getDefiningModule();
}


Tboolean freettcn::CType::operator<(const TciType &typ) const
{
  return _class < typ.getTypeClass() &&
    *_name < typ.getName() &&
    *_encoding < typ.getTypeEncoding() &&
    *_encodingVariant < typ.getTypeEncodingVariant() &&
    *_extension < typ.getTypeExtension() &&
    *_moduleId < typ.getDefiningModule();
}



Tstring freettcn::QualifiedName(const ORG_ETSI_TTCN3_TCI::TciType &type)
{
  return type.getDefiningModule().getObjectName() + "." + type.getName();
}
