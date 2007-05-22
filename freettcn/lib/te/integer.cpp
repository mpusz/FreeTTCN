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
 * @file   integer.cpp
 * @author Mateusz Pusz
 * @date   Mon May 14 21:37:54 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/integer.h"
#include <cstdlib>
#include <cstdio>

freettcn::TE::CIntegerType::CIntegerType() :
  CType(0, "integer", TCI_INTEGER_TYPE, "", "", "")
{
}

freettcn::TE::CIntegerType::CInstance *freettcn::TE::CIntegerType::InstanceCreate() const
{
  return new freettcn::TE::CIntegerType::CInstance(*this);
}


freettcn::TE::CIntegerType::CInstance::CInstance(const CType &type) :
  freettcn::TE::CType::CInstance(type)
{
}

freettcn::TE::CIntegerType::CInstance::CInstance(const CType &type, long value) :
  freettcn::TE::CType::CInstance(type), _value(value)
{
}

void freettcn::TE::CIntegerType::CInstance::AbsValue(const char *value) throw(EOperationFailed)
{
  if (*value == '\0')
    throw freettcn::EOperationFailed();
  
  char *endPtr;
  //  std::errno = 0;    /* To distinguish success/failure after call */
  unsigned long val = strtoul(value, &endPtr, 10);
  if (*endPtr != '\0' || value == endPtr) // ||
//       (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)))
    throw freettcn::EOperationFailed();
  
  Value(val);
}


// void freettcn::TE::CIntegerType::CInstance::DigitsNum(unsigned long int dig_num)
// {
// }


// void freettcn::TE::CIntegerType::CInstance::Sign(bool sign)
// {
//   _sign = sign;
// }


long freettcn::TE::CIntegerType::CInstance::Value() const throw(EOmitSet)
{
  if (Omit())
    throw EOmitSet();
  return _value;
}


void freettcn::TE::CIntegerType::CInstance::Value(long value)
{
  _value = value;
}
