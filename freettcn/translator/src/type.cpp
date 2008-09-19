//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) compiler.

// freettcn is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// freettcn is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with freettcn; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   type.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#include "type.h"
#include "identifier.h"
#include "translator.h"
#include "freettcn/tools/exception.h"
#include <sstream>


freettcn::translator::CType::CType()
{
}


freettcn::translator::CType::~CType()
{
}


bool freettcn::translator::CType::Match(const CType &type) const
{
  /// @todo Implement matching
  return &type == this;
}



freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_bitstring(freettcn::translator::CTypeInternal::TYPE_BITSTING);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_boolean(freettcn::translator::CTypeInternal::TYPE_BOOLEAN);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_charstring(freettcn::translator::CTypeInternal::TYPE_CHARSTRING);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_universalCharstring(freettcn::translator::CTypeInternal::TYPE_UNIVERSAL_CHARSTRING);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_integer(freettcn::translator::CTypeInternal::TYPE_INTEGER);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_octetstring(freettcn::translator::CTypeInternal::TYPE_OCTETSTRING);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_hexstring(freettcn::translator::CTypeInternal::TYPE_HEXSTRING);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_verdict(freettcn::translator::CTypeInternal::TYPE_VERDICT);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_float(freettcn::translator::CTypeInternal::TYPE_FLOAT);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_address(freettcn::translator::CTypeInternal::TYPE_ADDRESS);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_default(freettcn::translator::CTypeInternal::TYPE_DEFAULT);
freettcn::translator::CTypeInternal freettcn::translator::CTypeInternal::_anyType(freettcn::translator::CTypeInternal::TYPE_ANY_TYPE);


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Bitstring()
{
  return _bitstring;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Boolean()
{
  return _boolean;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Charstring()
{
  return _charstring;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::UniversalCharstring()
{
  return _universalCharstring;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Integer()
{
  return _integer;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Octetstring()
{
  return _octetstring;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Hexstring()
{
  return _hexstring;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Verdict()
{
  return _verdict;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Float()
{
  return _float;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Address()
{
  return _address;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::Default()
{
  return _default;
}


const freettcn::translator::CTypeInternal &freettcn::translator::CTypeInternal::AnyType()
{
  return _anyType;
}




freettcn::translator::CTypeInternal::CTypeInternal(TType type):
  _type(type)
{
  switch(_type) {
  case TYPE_BITSTING:
    _name = "bitstring";
    break;
  case TYPE_BOOLEAN:
    _name = "boolean";
    break;
  case TYPE_CHARSTRING:
    _name = "charstring";
    break;
  case TYPE_UNIVERSAL_CHARSTRING:
    _name = "universal charstring";
    break;
  case TYPE_INTEGER:
    _name = "integer";
    break;
  case TYPE_OCTETSTRING:
    _name = "octetstring";
    break;
  case TYPE_HEXSTRING:
    _name = "hexstring";
    break;
  case TYPE_VERDICT:
    _name = "verdicttype";
    break;
  case TYPE_FLOAT:
    _name = "float";
    break;
  case TYPE_ADDRESS:
    _name = "address";
    break;
  case TYPE_DEFAULT:
    _name = "default";
    break;
  case TYPE_ANY_TYPE:
    _name = "anytype";
    break;
  default:
    {
      std::stringstream stream;
      stream << "Unknown internal type: " << _type << "!!!";
      throw EOperationFailed(E_DATA, stream.str());
    }
  }
}


const std::string &freettcn::translator::CTypeInternal::Name() const
{
  return _name;
}




freettcn::translator::CTypeReferenced::CTypeReferenced(const std::string &name):
  _name(name)
{
}


const std::string &freettcn::translator::CTypeReferenced::Name() const
{
  return _name;
}



freettcn::translator::CTypeStructured::CField::CField(const CType &type, const CIdentifier *id, bool optional):
  _type(type), _id(id), _optional(optional)
{
}


const freettcn::translator::CType &freettcn::translator::CTypeStructured::CField::Type() const
{
  return _type;
}


const freettcn::translator::CIdentifier &freettcn::translator::CTypeStructured::CField::Id() const
{
  return *_id;
}


bool freettcn::translator::CTypeStructured::CField::Optional() const
{
  return _optional;
}


freettcn::translator::CTypeStructured::CTypeStructured(const std::string &name):
  CTypeReferenced(name)
{
}


freettcn::translator::CTypeStructured::~CTypeStructured()
{
  PurgeMap(_fieldMap);
}


void freettcn::translator::CTypeStructured::Dump(CDumper &dumper)
{
}


void freettcn::translator::CTypeStructured::Register(const CField *field)
{
  if(!field)
    throw ENotInitialized(E_DATA, "Structured type field not provided!!!");
  
  std::auto_ptr<const CField> fieldPtr(field);
  CTranslator &translator = CTranslator::Instance();
  
  // check if recursion not defined
  if(field->Type().Name() == Name()) {
    translator.Error(field->Id().Loc(), "structured types recursion detected - field '" + field->Id().Name() + "' cannot have the same type '" + Name() + "' as its parent");
    return;
  }
  
  /// @todo Check recursion for nested types
  
  // check if field ID already defined
  CFieldMap::const_iterator it=_fieldMap.find(&field->Id().Name());
  if(it != _fieldMap.end()) {
    translator.Error(field->Id().Loc(), "conflicting field declaration '" + field->Type().Name() + " " + field->Id().Name() + "'");
    translator.Error(it->second->Id().Loc(), "'" + field->Id().Name() + "' has a previous declaration as '" + it->second->Type().Name() + " " +  it->second->Id().Name() + "'");
    return;
  }
  
  // add new field
  _fieldMap[&field->Id().Name()] = fieldPtr.release();
}
