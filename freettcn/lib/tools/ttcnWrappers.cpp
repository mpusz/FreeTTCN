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
 * @file   ttcnWrappers.cpp
 * @author Mateusz Pusz
 * @date   Fri May 11 08:46:34 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/tools/ttcnWrappers.h"
#include <cstring>


freettcn::CTriComponentId::CTriComponentId(const TriComponentId &id)
{
  _id = id;
  
  // reallocate memory
  _id.compInst.data = new unsigned char[_id.compInst.bits / 8];
  memmove(_id.compInst.data, id.compInst.data, _id.compInst.bits / 8);
  
  unsigned int size = strlen(id.compName) + 1;
  _id.compName = new char[size];
  strcpy(_id.compName, id.compName);
  
  size = strlen(id.compType.moduleName) + 1;
  _id.compType.moduleName = new char[size];
  strcpy(_id.compType.moduleName, id.compType.moduleName);
  
  size = strlen(id.compType.objectName) + 1;
  _id.compType.objectName = new char[size];
  strcpy(_id.compType.objectName, id.compType.objectName);
}

freettcn::CTriComponentId::~CTriComponentId()
{
  delete[] _id.compInst.data;
  delete[] _id.compName;
  delete[] _id.compType.moduleName;
  delete[] _id.compType.objectName;
}

const TriComponentId &freettcn::CTriComponentId::Id() const
{
  return _id;
}
