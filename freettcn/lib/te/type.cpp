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
 * @file   type.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:08:14 2007
 * 
 * @brief  
 * 
 * 
 */


#include "freettcn/te/type.h"
#include "freettcn/te/module.h"


freettcn::TE::CType::CType(const CModule   *module,
                           const char      *name,
                           TciTypeClassType typeClass,
                           const char      *encoding,
                           const char      *encodingVariant,
                           const char      *extension) :
  _module(module), _class(typeClass), _encoding(encoding), _encodingVariant(encodingVariant), _extension(extension)
{
  if (_module)
    _id.moduleName = const_cast<char *>(_module->Name());
  else
    _id.moduleName = "{freettcn}";
  _id.objectName = const_cast<char *>(name);
  _id.aux = this;
}

freettcn::TE::CType::~CType()
{
}

const freettcn::TE::CModule *freettcn::TE::CType::DefiningModule() const
{
  return _module;
}

const char *freettcn::TE::CType::Name() const
{
  return _id.objectName;
}

const QualifiedName &freettcn::TE::CType::Id() const
{
  return _id;
}

TciTypeClassType freettcn::TE::CType::Class() const
{
  return _class;
}

const char *freettcn::TE::CType::Encoding() const
{
  return _encoding;
}

const char *freettcn::TE::CType::EncodingVariant() const
{
  return _encodingVariant;
}

const char *freettcn::TE::CType::Extension() const
{
  return _extension;
}




freettcn::TE::CType::CInstance::CInstance(const CType &type, bool omit) :
  _type(type), _omit(omit)
{
}

freettcn::TE::CType::CInstance::~CInstance()
{
}

const freettcn::TE::CType &freettcn::TE::CType::CInstance::Type() const
{
  return _type;
}

bool freettcn::TE::CType::CInstance::Omit() const
{
  return _omit;
}

const char *freettcn::TE::CType::CInstance::Encoding() const
{
  return Type().Encoding();
}

const char *freettcn::TE::CType::CInstance::EncodingVariant() const
{
  return Type().EncodingVariant();
}

const char *freettcn::TE::CType::CInstance::Extension() const
{
  return Type().Extension();
}




// void freettcn::TE::CIntegerValue::AbsValue(String value) throw(freettcn::EOperationFailed)
// {
//   if (*value == '\0')
//     throw freettcn::EOperationFailed();
  
//   char *endPtr;
//   //  std::errno = 0;    /* To distinguish success/failure after call */
//   unsigned long val = strtoul(value, &endPtr, 10);
//   if (*endPtr != '\0' || value == endPtr) // ||
// //       (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)))
//     throw freettcn::EOperationFailed();
  
//   _absValue = val;
// }


// void freettcn::TE::CIntegerValue::DigitsNum(unsigned long int dig_num)
// {
// }


// void freettcn::TE::CIntegerValue::Sign(bool sign)
// {
//   _sign = sign;
// }

