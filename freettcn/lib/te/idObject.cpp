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
 * @file   idObject.cpp
 * @author Mateusz Pusz
 * @date   Tue May  8 07:53:59 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/idObject.h"
#include <cmath>
#include <iostream>



freettcn::TE::CIdObject::CIdManager freettcn::TE::CIdObject::_manager;


freettcn::TE::CIdObject::CIdObject()
{
  _manager.Allocate(*this, _id);
}

freettcn::TE::CIdObject::~CIdObject()
{
  _manager.Free(_id);
}

const BinaryString &freettcn::TE::CIdObject::InstanceId() const
{
  return _id;
}

freettcn::TE::CIdObject &freettcn::TE::CIdObject::Get(const BinaryString &id) throw(freettcn::ENotFound)
{
  return _manager.Object(id);
}






freettcn::TE::CIdObject::CIdManager::CIdManager()
{
}

unsigned int freettcn::TE::CIdObject::CIdManager::Id2Index(const BinaryString &id) const
{
  unsigned int idx = 0;
  
  for(unsigned short i=0; i<ceil(id.bits / 8) + 1; i++) {
    if (i)
      idx <<= 8;
    idx |= id.data[i];
  }
  
  return idx;
}

void freettcn::TE::CIdObject::CIdManager::Allocate(freettcn::TE::CIdObject &object, BinaryString &id)
{
  // prepare data
  TData data;
  data.valid = true;
  data.ptr = &object;
  
  // find first free index
  unsigned int idx;
  for(idx=0; idx<_idArray.size(); idx++)
    if (!_idArray[idx].valid)
      break;
  
  // store object under selected index
  if (idx == _idArray.size())
    _idArray.push_back(data);
  else
    _idArray[idx] = data;
  
  // allocate new id
  unsigned short idLen = idx / 0x100 + 1;
  unsigned char *instId = new unsigned char[idLen];
  for(unsigned short i=0; i<idLen; i++)
    instId[i] = (idx >> ((idLen - 1) * 8)) & 0xff;
  
  // assign data
  id.data = instId;
  id.bits = idLen * 8;
  id.aux = 0;
}

freettcn::TE::CIdObject &freettcn::TE::CIdObject::CIdManager::Object(const BinaryString &id) throw(freettcn::ENotFound)
{
  unsigned int idx = Id2Index(id);
  
  if (_idArray[idx].valid)
    return *_idArray[idx].ptr;
  
  std::cout << "ERROR: Id not found" << std::endl;
  throw freettcn::ENotFound();
}

void freettcn::TE::CIdObject::CIdManager::Free(const BinaryString &id) throw(freettcn::ENotFound)
{
  unsigned int idx = Id2Index(id);
  
  if (_idArray[idx].valid) {
    _idArray[idx].valid = false;
    _idArray[idx].ptr = 0;
    delete[] id.data;
  }
  else {
    std::cout << "ERROR: Id not found" << std::endl;
    throw freettcn::ENotFound();
  }
}
