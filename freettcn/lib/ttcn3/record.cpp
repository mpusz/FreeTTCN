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
 * @file   record.cpp
 * @author Mateusz Pusz
 * @date   Tue May 22 09:02:12 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/ttcn3/record.h"
#include "freettcn/tools/exception.h"
#include <algorithm>



freettcn::CTypeRecord::CValue::CValue(const std::shared_ptr<const CTypeRecord> &type):
  CType::CValue(type, "", ""), _fieldNames(type->_fieldNames)
{
  std::for_each(type->_fieldDataArray.begin(), type->_fieldDataArray.end(),
                [this](const CFieldData &d)
                { _fieldMap[&d.Name()] = std::shared_ptr<TciValue>(d.Type().newInstance()); } );
}


freettcn::CTypeRecord::CValue::CValue(const CValue &src):
  CType::CValue(src), _fieldNames(src._fieldNames), _fieldMap(src._fieldMap)
{
}


const ORG_ETSI_TTCN3_TCI::TciValue &freettcn::CTypeRecord::CValue::getField(const Tstring &p_field_name) const
{
  auto it = _fieldMap.find(&p_field_name);
  if(it == _fieldMap.end())
    throw ENotFound(E_DATA, "Field name '" + p_field_name + "' is not a member of record '" + QualifiedName(getType()) + "'!!!");
  return *it->second;
}


void freettcn::CTypeRecord::CValue::setField(const Tstring &p_field_name, const TciValue &p_new_value)
{
  auto it = _fieldMap.find(&p_field_name);
  if(it == _fieldMap.end())
    throw EOperationFailed(E_DATA, "Field name '" + p_field_name + "' is not a member of record '" + QualifiedName(getType()) + "'!!!");
  
  // check if type matches
  if(p_new_value.getType() == it->second->getType())
    it->second.reset(p_new_value.clone());
  else
    throw ENotFound(E_DATA, "Value of type '" + QualifiedName(p_new_value.getType()) + "' provided for record '" + QualifiedName(getType()) + "' field '" + p_field_name + "' of type '" + QualifiedName(it->second->getType()) + "'!!!");
}


void freettcn::CTypeRecord::CValue::setFieldOmitted(const Tstring &fieldName)
{
  auto it = _fieldMap.find(&fieldName);
  if(it == _fieldMap.end())
    throw ENotFound(E_DATA, "Field name '" + fieldName + "' is not a member of record '" + QualifiedName(getType()) + "'!!!");
  TciValue &val = *it->second;
  it->second.reset(new CValueOmitted(std::shared_ptr<TciType>(val.getType().clone()), val.getValueEncoding(), val.getValueEncodingVariant()));
}


Tboolean freettcn::CTypeRecord::CValue::operator==(const RecordValue &rec) const
{
  return getType() == rec.getType() &&
    _fieldNames == rec.getFieldNames() &&
    std::all_of(_fieldMap.begin(), _fieldMap.end(),
                [&rec](decltype(*_fieldMap.begin()) p)
                { return *p.second == rec.getField(*p.first); } );
}


Tboolean freettcn::CTypeRecord::CValue::operator<(const RecordValue &rec) const
{
  return getType() < rec.getType() &&
    _fieldNames < rec.getFieldNames() &&
    _fieldNames.size() < rec.getFieldNames().size() &&
    std::all_of(_fieldMap.begin(), _fieldMap.end(),
                [&rec](decltype(*_fieldMap.begin()) p)
                { return *p.second < rec.getField(*p.first); } );
}



freettcn::CTypeRecord::CTypeRecord(const std::shared_ptr<const TciModuleId> &moduleId,
                                   const Tstring      &name,
                                   const Tstring      &encoding,
                                   const Tstring      &encodingVariant,
                                   const CExtension   &extension,
                                   size_t             fieldNum):
  CType(moduleId, name, TCI_RECORD, encoding, encodingVariant, extension)
{
  _fieldDataArray.reserve(fieldNum);
  _fieldNames.reserve(fieldNum);
}


void freettcn::CTypeRecord::Add(CType &fieldType, const Tstring &fieldName, bool optional /* = false */)
{
  _fieldDataArray.push_back(CFieldData(fieldType, fieldName, optional));
  _fieldNames.push_back(&_fieldDataArray.back().Name());
}
