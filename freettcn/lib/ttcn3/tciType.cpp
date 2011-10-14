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
//#include "freettcn/te/module.h"


freettcn::ttcn3::CType::CValue::CValue(const TciType &type,
                                    const Tstring &encoding,
                                    const Tstring &encodingVariant):
  _type(type)
{
  if(encoding.empty() || encoding == type.getTypeEncoding())
    _encoding.reset(new Tstring(encoding));
  if(encodingVariant.empty() || encodingVariant == type.getTypeEncodingVariant())
    _encoding.reset(new Tstring(encodingVariant));
}


freettcn::ttcn3::CType::CValue::CValue(const CValue &src):
  _type(src._type)
{
  if(src._encoding)
    _encoding.reset(new Tstring(*src._encoding));
  if(src._encodingVariant)
    _encodingVariant.reset(new Tstring(*src._encodingVariant));
}


// freettcn::ttcn3::CType::CInstance &freettcn::ttcn3::CType::CInstance::operator=(const CInstance &value)
// {
//   if (&_type == &value._type) {
//     _omit = value._omit;
    
//     return *this;
//   }
  
//   throw EOperationFailed(E_DATA, "Cannot assign values of different types!!!");
// }

// const freettcn::ttcn3::CType &freettcn::ttcn3::CType::CInstance::Type() const
// {
//   return _type;
// }

const Tstring &freettcn::ttcn3::CType::CValue::getValueEncoding() const
{
  if(_encoding)
    return *_encoding;
  else
    return _type.getTypeEncoding();
}


const Tstring &freettcn::ttcn3::CType::CValue::getValueEncodingVariant() const
{
  if(_encodingVariant)
    return *_encodingVariant;
  else
    return _type.getTypeEncodingVariant();
}




freettcn::ttcn3::CType::CValueOmitted::CValueOmitted(const TciType &type,
                                                  const Tstring &encoding,
                                                  const Tstring &encodingVariant):
  CValue(type, encoding, encodingVariant)
{
}


ORG_ETSI_TTCN3_TCI::TciValue *freettcn::ttcn3::CType::CValueOmitted::clone() const
{
  return new CValueOmitted(getType(), getValueEncoding(), getValueEncodingVariant());
}


Tboolean freettcn::ttcn3::CType::CValueOmitted::operator==(const TciValue &val) const
{
  return notPresent() == val.notPresent() &&
    getValueEncoding() == val.getValueEncoding() &&
    getValueEncodingVariant() == val.getValueEncodingVariant() &&
    getType() == val.getType();
}


Tboolean freettcn::ttcn3::CType::CValueOmitted::operator<(const TciValue &val) const override
{
  return notPresent() < val.notPresent() &&
    getValueEncoding() < val.getValueEncoding() &&
    getValueEncodingVariant() < val.getValueEncodingVariant() && 
    getType() < val.getType();
}



freettcn::ttcn3::CType::CType(const TciModuleId  &moduleId,
                           const Tstring      &name,
                           const TciTypeClass &typeClass,
                           const Tstring      &encoding,
                           const Tstring      &encodingVariant,
                           const CExtension   &extension):
  _moduleId(moduleId), _name(name), _class(typeClass), _encoding(encoding), _encodingVariant(encodingVariant), _extension(extension)
{
}


Tboolean freettcn::ttcn3::CType::operator==(const TciType &typ) const
{
  return _class == typ.getTypeClass() &&
    _name == typ.getName() &&
    _encoding == typ.getTypeEncoding() &&
    _encodingVariant == typ.getTypeEncodingVariant() &&
    _extension == typ.getTypeExtension() &&
    _moduleId == typ.getDefiningModule();
}


Tboolean freettcn::ttcn3::CType::operator<(const TciType &typ) const
{
  return _class < typ.getTypeClass() &&
    _name < typ.getName() &&
    _encoding < typ.getTypeEncoding() &&
    _encodingVariant < typ.getTypeEncodingVariant() &&
    _extension < typ.getTypeExtension() &&
    _moduleId < typ.getDefiningModule();
}



Tstring freettcn::ttcn3::QualifiedName(const ORG_ETSI_TTCN3_TCI::TciType &type)
{
  return type.getDefiningModule().getObjectName() + "." + type.getName();
}
