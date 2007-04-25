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
 * @file   ttcn_types.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:08:14 2007
 * 
 * @brief  
 * 
 * 
 */


#include "ttcn_types.h"
#include "ttcn_values.h"


freettcn::TE::CType::CType(const CModule   *module,
                           String          name,
                           TciTypeClassType typeClass,
                           String          encoding,
                           String          encodingVariant,
                           String          extension) :
  _module(module), _name(name), _class(typeClass), _encoding(encoding), _encodingVariant(encodingVariant), _extension(extension)
{
}

freettcn::TE::CType::~CType()
{
}

const freettcn::TE::CModule *freettcn::TE::CType::DefiningModule() const
{
  return _module;
}

String freettcn::TE::CType::Name() const
{
  return _name;
}

TciTypeClassType freettcn::TE::CType::Class() const
{
  return _class;
}

String freettcn::TE::CType::Encoding() const
{
  return _encoding;
}

String freettcn::TE::CType::EncodingVariant() const
{
  return _encodingVariant;
}

String freettcn::TE::CType::Extension() const
{
  return _extension;
}




freettcn::TE::CBooleanType::CBooleanType(String           encoding,
                                         String           encodingVariant,
                                         String           extension) :
  CType(0, "boolean", TCI_BOOLEAN_TYPE, encoding, encodingVariant, extension)
{
}

freettcn::TE::CValue *freettcn::TE::CBooleanType::InstanceCreate(bool omit /* false */) const
{
  return new freettcn::TE::CBooleanValue(*this, omit);
}




freettcn::TE::CRecordType::CRecordType(const CModule    *module,
                                       String           encoding,
                                       String           encodingVariant,
                                       String           extension) :
  CType(module, "record", TCI_RECORD_TYPE, encoding, encodingVariant, extension)
{
}

freettcn::TE::CValue *freettcn::TE::CRecordType::InstanceCreate(bool omit /* false */) const
{
  return new freettcn::TE::CRecordValue(*this, omit);
}
