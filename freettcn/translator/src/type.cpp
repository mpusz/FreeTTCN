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


std::string freettcn::translator::CType::KindToString(TKind kind)
{
  switch(kind) {
  case KIND_TYPE_PREDEFINED:
    return "predefined";
  case KIND_TYPE_RECORD:
    return "record";
  case KIND_TYPE_SET:
    return "set";
  case KIND_TYPE_UNION:
    return "union";
  case KIND_PORT:
    return "port";
  case KIND_COMPONENT:
    return "component";
  default:
    {
      std::stringstream stream;
      stream << "Unknown kind '" << kind << "'!!!";
      throw EOutOfRange(E_DATA, stream.str());
    }
  }
  
}


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



freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_bitstring(freettcn::translator::CTypePredefined::TYPE_BITSTING);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_boolean(freettcn::translator::CTypePredefined::TYPE_BOOLEAN);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_charstring(freettcn::translator::CTypePredefined::TYPE_CHARSTRING);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_universalCharstring(freettcn::translator::CTypePredefined::TYPE_UNIVERSAL_CHARSTRING);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_integer(freettcn::translator::CTypePredefined::TYPE_INTEGER);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_octetstring(freettcn::translator::CTypePredefined::TYPE_OCTETSTRING);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_hexstring(freettcn::translator::CTypePredefined::TYPE_HEXSTRING);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_verdict(freettcn::translator::CTypePredefined::TYPE_VERDICT);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_float(freettcn::translator::CTypePredefined::TYPE_FLOAT);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_address(freettcn::translator::CTypePredefined::TYPE_ADDRESS);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_default(freettcn::translator::CTypePredefined::TYPE_DEFAULT);
freettcn::translator::CTypePredefined freettcn::translator::CTypePredefined::_anyType(freettcn::translator::CTypePredefined::TYPE_ANY_TYPE);


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Bitstring()
{
  return _bitstring;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Boolean()
{
  return _boolean;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Charstring()
{
  return _charstring;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::UniversalCharstring()
{
  return _universalCharstring;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Integer()
{
  return _integer;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Octetstring()
{
  return _octetstring;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Hexstring()
{
  return _hexstring;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Verdict()
{
  return _verdict;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Float()
{
  return _float;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Address()
{
  return _address;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::Default()
{
  return _default;
}


freettcn::translator::CTypePredefined &freettcn::translator::CTypePredefined::AnyType()
{
  return _anyType;
}




freettcn::translator::CTypePredefined::CTypePredefined(TType type):
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


const std::string &freettcn::translator::CTypePredefined::Name() const
{
  return _name;
}


freettcn::translator::CType::TKind freettcn::translator::CTypePredefined::Kind() const
{
  return KIND_TYPE_PREDEFINED;
}


void freettcn::translator::CTypePredefined::Dump(CDumper &dumper) const
{
}


bool freettcn::translator::CTypePredefined::Resolved() const
{
  return true;
}


bool freettcn::translator::CTypePredefined::Resolve(TKind kind, const std::string &ownerInstanceStr)
{
  throw EOperationFailed(E_DATA, "Resolving should not be done on CTypePredefined!!!");
}






freettcn::translator::CTypeReferenced::CTypeUnresolved::CTypeUnresolved(const CIdentifier *id):
  _id(id)
{
}


freettcn::translator::CType::TKind freettcn::translator::CTypeReferenced::CTypeUnresolved::Kind() const
{
  return KIND_UNRESOLVED;
}


const std::string &freettcn::translator::CTypeReferenced::CTypeUnresolved::Name() const
{
  return _id->Name();
}


void freettcn::translator::CTypeReferenced::CTypeUnresolved::Dump(CDumper &dumper) const
{
}


bool freettcn::translator::CTypeReferenced::CTypeUnresolved::Resolved() const
{
  throw EOperationFailed(E_DATA, "That type is always unresolved!!!");
}


bool freettcn::translator::CTypeReferenced::CTypeUnresolved::Resolve(TKind kind, const std::string &ownerInstanceStr)
{
  throw EOperationFailed(E_DATA, "Cannot resolve CTypeUnresolved!!!");
}


const freettcn::translator::CIdentifier &freettcn::translator::CTypeReferenced::CTypeUnresolved::Id() const
{
  return *_id;
}





freettcn::translator::CTypeReferenced::CTypeReferenced(CType &type):
  _type(&type), _typeUnresolved(false)
{
}


freettcn::translator::CTypeReferenced::CTypeReferenced(const CIdentifier *id):
  _type(new CTypeUnresolved(id)), _typeUnresolved(true)
{
}


freettcn::translator::CTypeReferenced::~CTypeReferenced()
{
  if(_typeUnresolved)
    delete _type;
}


freettcn::translator::CType::TKind freettcn::translator::CTypeReferenced::Kind() const
{
  return _type->Kind();
}


const std::string &freettcn::translator::CTypeReferenced::Name() const
{
  return _type->Name();
}


void freettcn::translator::CTypeReferenced::Dump(CDumper &dumper) const
{
  return _type->Dump(dumper);
}


bool freettcn::translator::CTypeReferenced::Resolved() const
{
  return !_typeUnresolved && _type->Resolved();
}


bool freettcn::translator::CTypeReferenced::Resolve(TKind kind, const std::string &ownerInstanceStr)
{
  if(_typeUnresolved) {
    // try to resolve
    CTranslator &translator = CTranslator::Instance();
    CType *type = translator.Type(_type->Name());
    if(type) {
      // check kind
      if(!(type->Kind() & kind)) {
        CTypeUnresolved &unrType = dynamic_cast<CTypeUnresolved &>(*_type);
        CTranslator &translator = CTranslator::Instance();
        translator.Error(unrType.Id().Loc(), ownerInstanceStr + " cannot be of '" + KindToString(type->Kind()) + "' type");
        return false;
      }
      
      // assign resolved type
      delete _type;
      _type = type;
      _typeUnresolved = false;
      
      // check new type
      return _type->Resolved() || _type->Resolve(kind, ownerInstanceStr);
    }
    return false;
  }
  else {
    return _type->Resolve(kind, ownerInstanceStr);
  }
}



freettcn::translator::CTypeLocal::CTypeLocal(const std::string &name):
  _name(name)
{
}


const std::string &freettcn::translator::CTypeLocal::Name() const
{
  return _name;
}




freettcn::translator::CTypeStructured::CField::CField(CType &type, const CIdentifier *id, bool optional):
  _type(type), _id(id), _optional(optional)
{
}


freettcn::translator::CType &freettcn::translator::CTypeStructured::CField::Type() const
{
  return _type;
}


const freettcn::translator::CIdentifier &freettcn::translator::CTypeStructured::CField::Id() const
{
  return *_id;
}


// bool freettcn::translator::CTypeStructured::CField::Optional() const
// {
//   return _optional;
// }



freettcn::translator::CTypeStructured::CTypeStructured(const std::string &name):
  CTypeLocal(name)
{
}


freettcn::translator::CTypeStructured::~CTypeStructured()
{
  PurgeMap(_fieldMap);
}


freettcn::translator::CType::TKind freettcn::translator::CTypeStructured::Kind() const
{
  return KIND_TYPE_SET;
}


void freettcn::translator::CTypeStructured::Dump(CDumper &dumper) const
{
}


void freettcn::translator::CTypeStructured::Register(CField *field)
{
  if(!field)
    throw ENotInitialized(E_DATA, "Structured type field not provided!!!");
  
  std::auto_ptr<CField> fieldPtr(field);
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


bool freettcn::translator::CTypeStructured::Resolved() const
{
  for(CFieldMap::const_iterator it=_fieldMap.begin(); it!=_fieldMap.end(); ++it)
    if(!it->second->Type().Resolved())
      return false;
  
  return true;
}


bool freettcn::translator::CTypeStructured::Resolve(TKind kind, const std::string &ownerInstanceStr)
{
  CTranslator &translator = CTranslator::Instance();
  bool status = true;
  
  for(CFieldMap::iterator it=_fieldMap.begin(); it!=_fieldMap.end(); ++it) {
    if(!it->second->Type().Resolved()) {
      if(!it->second->Type().Resolve(KIND_TYPE, "field '" + it->second->Id().Name() + "'")) {
        translator.Error(it->second->Id().Loc(), "field '" + it->second->Id().Name() + "' of unresolved type '" + it->second->Type().Name() + "' specified");
        status = false;
      }
    }
  }
  
  return status;
}




freettcn::translator::CTypeRecord::CTypeRecord(const std::string &name):
  CTypeStructured(name)
{
}


freettcn::translator::CType::TKind freettcn::translator::CTypeRecord::Kind() const
{
  return KIND_TYPE_RECORD;
}


void freettcn::translator::CTypeRecord::Dump(CDumper &dumper) const
{
}


void freettcn::translator::CTypeRecord::Register(CField *field)
{
  CTypeStructured::Register(field);
  _fieldList.push_back(field);
}




freettcn::translator::CTypeUnion::CTypeUnion(const std::string &name):
  CTypeStructured(name)
{
}


freettcn::translator::CType::TKind freettcn::translator::CTypeUnion::Kind() const
{
  return KIND_TYPE_UNION;
}


void freettcn::translator::CTypeUnion::Dump(CDumper &dumper) const
{
}



freettcn::translator::CTypePort::CItem::CItem(const CLocation &loc, CType &type):
  _loc(loc), _type(&type)
{
}


freettcn::translator::CTypePort::CItem::CItem(const CLocation &loc):
  _loc(loc), _type(0)
{
}


const freettcn::translator::CLocation &freettcn::translator::CTypePort::CItem::Loc() const
{
  return _loc;
}


bool freettcn::translator::CTypePort::CItem::All() const
{
  return !_type;
}


freettcn::translator::CType &freettcn::translator::CTypePort::CItem::Type() const
{
  if(_type)
    return *_type;
  
  throw EOperationFailed(E_DATA, "'all' port item does not have type!!!");
}


freettcn::translator::CTypePort::CTypePort(const std::string &name, TMode mode):
  CTypeLocal(name), _mode(mode)
{
}


freettcn::translator::CTypePort::~CTypePort()
{
  Purge(_itemList);
}


freettcn::translator::CType::TKind freettcn::translator::CTypePort::Kind() const
{
  return KIND_PORT;
}


freettcn::translator::CTypePort::TMode freettcn::translator::CTypePort::Mode() const
{
  return _mode;
}


void freettcn::translator::CTypePort::Dump(CDumper &dumper) const
{
}


void freettcn::translator::CTypePort::Register(CItem *item, TDirection dir)
{
  if(!item)
    throw ENotInitialized(E_DATA, "Port item not provided!!!");
  
  std::auto_ptr<CItem> itemPtr(item);
  std::string name = item->All() ? "all" : item->Type().Name();
  
  CTranslator &translator = CTranslator::Instance();
  
  // check if item already defined
  bool status = true;;
  CItemMap::const_iterator inIt = (dir == DIRECTION_IN || dir == DIRECTION_INOUT) ? _inItemMap.find(name) : _inItemMap.end();
  CItemMap::const_iterator outIt = (dir == DIRECTION_OUT || dir == DIRECTION_INOUT) ? _outItemMap.find(name) : _outItemMap.end();
  if(inIt != _inItemMap.end() && (dir == DIRECTION_IN || outIt != _outItemMap.end())) {
    translator.Warning(item->Loc(), "duplicated 'in' port item declaration '" + name + "' specified");
    translator.Warning(inIt->second->Loc(), "'" + name + "' has a previous declaration here");
    status = false;
  }
  if(outIt != _outItemMap.end() && (dir == DIRECTION_OUT || inIt != _inItemMap.end())) {
    translator.Warning(item->Loc(), "duplicated 'out' port item declaration '" + name + "' specified");
    translator.Warning(outIt->second->Loc(), "'" + name + "' has a previous declaration here");
    status = false;
  }
  if(!status)
    return;
  
  CItemMap::const_iterator inAllIt = _inItemMap.find("all");
  CItemMap::const_iterator outAllIt = _outItemMap.find("all");
  unsigned inNum = _inItemMap.size();
  unsigned outNum = _outItemMap.size();
  if(inAllIt != _inItemMap.end())
    inNum--;
  if(outAllIt != _outItemMap.end())
    outNum--;
  
  // check if 'all'
  if(item->All()) {
    // check 'in' direction
    if((dir == DIRECTION_IN && inNum) ||
       (dir == DIRECTION_INOUT && inNum && outNum)) {
      for(CItemMap::const_iterator it=_inItemMap.begin(); it!=_inItemMap.end(); ++it)
        translator.Warning(it->second->Loc(), "'" + it->second->Type().Name() + "' 'in' port item declared while 'all' is present");
      translator.Warning(item->Loc(), "'all' 'in' port item declared here");
    }
    
    // check 'out' direction
    if((dir == DIRECTION_OUT && outNum) ||
       (dir == DIRECTION_INOUT && inNum && outNum)) {
      for(CItemMap::const_iterator it=_outItemMap.begin(); it!=_outItemMap.end(); ++it)
        translator.Warning(it->second->Loc(), "'" + it->second->Type().Name() + "' 'out' port item declared while 'all' is present");
      translator.Warning(item->Loc(), "'all' 'out' port item declared here");
    }
  }
  else {
    // check if all declared for that direction
    if(dir == DIRECTION_IN && inAllIt != _inItemMap.end()) {
      translator.Warning(item->Loc(), "'" + item->Type().Name() + "' 'in' port item declared while 'all' is present");
      translator.Warning(inAllIt->second->Loc(), "'all' 'in' port item declared here");
    }
    if(dir == DIRECTION_OUT && outAllIt != _outItemMap.end()) {
      translator.Warning(item->Loc(), "'" + item->Type().Name() + "' 'out' port item declared while 'all' is present");
      translator.Warning(outAllIt->second->Loc(), "'all' 'out' port item declared here");
    }
    if(dir == DIRECTION_INOUT && inAllIt != _inItemMap.end() && outAllIt != _outItemMap.end()) {
      translator.Warning(item->Loc(), "'" + item->Type().Name() + "' 'inout' port item declared while 'all' is present");
      if(*inAllIt == *outAllIt) {
        translator.Warning(inAllIt->second->Loc(), "'all' 'inout' port item declared here");
      }
      else {
        translator.Warning(inAllIt->second->Loc(), "'all' 'in' port item declared here");
        translator.Warning(outAllIt->second->Loc(), "'all' 'out' port item declared here");
      }
    }
  }

  // add new item
  if(dir == DIRECTION_IN || (dir == DIRECTION_INOUT && inIt == _inItemMap.end()))
    _inItemMap[name] = itemPtr.get();
  if(dir == DIRECTION_OUT || (dir == DIRECTION_INOUT && outIt == _outItemMap.end()))
    _outItemMap[name] = itemPtr.get();
  _itemList.push_back(itemPtr.release());
}


bool freettcn::translator::CTypePort::Resolved() const
{
  for(CItemList::const_iterator it=_itemList.begin(); it!=_itemList.end(); ++it)
    if(!(*it)->All() && !(*it)->Type().Resolved())
      return false;
  
  return true;
}


bool freettcn::translator::CTypePort::Resolve(TKind kind, const std::string &ownerInstanceStr)
{
  CTranslator &translator = CTranslator::Instance();
  bool status = true;
  
  for(CItemList::const_iterator it=_itemList.begin(); it!=_itemList.end(); ++it) {
    if(!(*it)->All() && !(*it)->Type().Resolved()) {
      if(!(*it)->Type().Resolve(KIND_TYPE, "port item '" + (*it)->Type().Name() + "'")) {
        translator.Error((*it)->Loc(), "port item '" + (*it)->Type().Name() + "' of unresolved type");
        status = false;
      }
    }
  }
  
  return status;
}
