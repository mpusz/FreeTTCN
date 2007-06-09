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

#include "freettcn/te/record.h"
#include "freettcn/tools/tools.h"
#include <cstring>
#include <iostream>


freettcn::TE::CRecordType::CRecordType(const CModule    &module,
                                       const char       *name,
                                       String           encoding,
                                       String           encodingVariant,
                                       String           extension) :
  CType(&module, name, TCI_RECORD_TYPE, encoding, encodingVariant, extension), _fieldNames(0)
{
}


freettcn::TE::CRecordType::~CRecordType()
{
  Purge(_fieldDataArray);
  if (_fieldNames) {
    for (unsigned int i=0; _fieldNames[i]; i++)
      delete[] _fieldNames[i];
    delete[] _fieldNames;
  }
}


void freettcn::TE::CRecordType::Register(const CType &type, const char *name, bool optional /* false */)
{
  _fieldDataArray.push_back(new CFieldData(type, name, optional));
}


void freettcn::TE::CRecordType::Init()
{
  _fieldNames = new char *[_fieldDataArray.size() + 1];
  
  for(unsigned int i=0; i<_fieldDataArray.size(); i++) {
    unsigned int size = strlen(_fieldDataArray[i]->Name()) + 1;
    _fieldNames[i] = new char[size];
    strcpy(_fieldNames[i], _fieldDataArray[i]->Name());
  }
  
  // must be NULL terminated array of names
  _fieldNames[_fieldDataArray.size()] = 0;
}


unsigned int freettcn::TE::CRecordType::FieldIdx(const char *fieldName) const throw(ENotFound)
{
  for(unsigned int i=0; i<_fieldDataArray.size(); i++)
    if (!strcmp(_fieldDataArray[i]->Name(), fieldName))
      return i;
  std::cout << "ERROR: Record Field not found" << std::endl;
  throw freettcn::ENotFound();
}


freettcn::TE::CRecordType::CInstance *freettcn::TE::CRecordType::InstanceCreate() const
{
  CInstance *record = new CInstance(*this);
  
  for(unsigned int i=0; i<_fieldDataArray.size(); i++)
    record->Register(_fieldDataArray[i]->Type().InstanceCreate());
  
  return record;
}




freettcn::TE::CRecordType::CFieldData::CFieldData(const CType &type, const char *name, bool optional):
  _type(type), _name(name), _optional(optional)
{
}

const freettcn::TE::CType &freettcn::TE::CRecordType::CFieldData::Type() const
{
  return _type;
}

const char *freettcn::TE::CRecordType::CFieldData::Name() const
{
  return _name;
}

bool freettcn::TE::CRecordType::CFieldData::Optional() const
{
  return _optional;
}




freettcn::TE::CRecordType::CInstance::CInstance(const CType &type) :
  freettcn::TE::CType::CInstance(type)
{
}


freettcn::TE::CRecordType::CInstance::~CInstance()
{
  Purge(_fieldArray);
}


void freettcn::TE::CRecordType::CInstance::Register(CType::CInstance *field)
{
  _fieldArray.push_back(field);
}


// unsigned int freettcn::TE::CRecordType::CInstance::FieldNum() const
// {
// }


freettcn::TE::CType::CInstance &freettcn::TE::CRecordType::CInstance::Field(const char *fieldName) const throw(ENotFound, EOmitSet)
{
  if (Omit())
    throw EOmitSet();
  
  return *_fieldArray[static_cast<const CRecordType &>(Type()).FieldIdx(fieldName)];
}


freettcn::TE::CType::CInstance &freettcn::TE::CRecordType::CInstance::Field(unsigned int fieldIdx) const throw(ENotFound, EOmitSet)
{
  if (Omit())
    throw EOmitSet();
  
  if (fieldIdx < _fieldArray.size())
    return *_fieldArray[fieldIdx];
  
  std::cout << "ERROR: Record field index: " << fieldIdx << " too big (size: " << _fieldArray.size() << ")" << std::endl;
  throw ENotFound();
}


char const * const * freettcn::TE::CRecordType::CInstance::FieldNames() const
{
  return static_cast<const CRecordType &>(Type())._fieldNames;
}
