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
 * @file   boolean.cpp
 * @author Mateusz Pusz
 * @date   Fri May  4 09:24:05 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/boolean.h"
#include "freettcn/tools/exception.h"


freettcn::TE::CBooleanType::CBooleanType() :
  CType(0, "boolean", TCI_BOOLEAN_TYPE, "", "", "")
{
}

freettcn::TE::CBooleanType::CInstance *freettcn::TE::CBooleanType::InstanceCreate() const
{
  return new freettcn::TE::CBooleanType::CInstance(*this);
}


freettcn::TE::CBooleanType::CInstance::CInstance(const CType &type) :
  freettcn::TE::CType::CInstance(type)
{
}

freettcn::TE::CBooleanType::CInstance::CInstance(const CType &type, bool value) :
  freettcn::TE::CType::CInstance(type), _value(value)
{
}

bool freettcn::TE::CBooleanType::CInstance::Value() const
{
  if (Omit())
    throw EOperationFailed(E_DATA, "Cannot get value for an instance with Omit set!!!");
  return _value;
}

void freettcn::TE::CBooleanType::CInstance::Value(bool value)
{
  _value = value;
}
