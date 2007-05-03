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
#include "freettcn/te/value.h"
#include "freettcn/te/module.h"
#include "freettcn/te/testComponent.h"


freettcn::TE::CType::CType(const CModule   *module,
                           String          name,
                           TciTypeClassType typeClass,
                           String          encoding,
                           String          encodingVariant,
                           String          extension) :
  _module(module), _class(typeClass), _encoding(encoding), _encodingVariant(encodingVariant), _extension(extension)
{
  if (_module)
    _id.moduleName = const_cast<char *>(_module->Name());
  else
    _id.moduleName = "<freettcn>";
  _id.objectName = name;
  _id.aux = this;
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




freettcn::TE::CBooleanType::CBooleanType() :
  CType(0, "boolean", TCI_BOOLEAN_TYPE, "", "", "")
{
}

freettcn::TE::CValue *freettcn::TE::CBooleanType::InstanceCreate(bool omit /* false */) const
{
  return new freettcn::TE::CBooleanValue(*this, omit);
}




// freettcn::TE::CRecordType::CRecordType(const CModule    &module,
//                                        String           encoding,
//                                        String           encodingVariant,
//                                        String           extension) :
//   CType(&module, "record", TCI_RECORD_TYPE, encoding, encodingVariant, extension)
// {
// }

// freettcn::TE::CValue *freettcn::TE::CRecordType::InstanceCreate(bool omit /* false */) const
// {
//   return new freettcn::TE::CRecordValue(*this, omit);
// }




freettcn::TE::CTestComponentType::CTestComponentType(const freettcn::TE::CModule *module, String name) :
  freettcn::TE::CType(module, name, TCI_COMPONENT_TYPE, "", "", "")
{
}



freettcn::TE::CControlComponentType::CControlComponentType():
  freettcn::TE::CTestComponentType(0 , "_ControlComponentType_")
{
}

freettcn::TE::CValue *freettcn::TE::CControlComponentType::InstanceCreate(bool omit /* false */) const
{
  return new freettcn::TE::CTestComponent(*this);
}





/* *************************** B A S I C   T Y P E *************************** */

const freettcn::TE::CBooleanType freettcn::TE::CBasicType::_boolean;
const freettcn::TE::CControlComponentType freettcn::TE::CBasicType::_control;

const freettcn::TE::CBooleanType &freettcn::TE::CBasicType::Boolean()
{
  return _boolean;
}


const freettcn::TE::CControlComponentType &freettcn::TE::CBasicType::ControlComponent()
{
  return _control;
}
