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
 * @file   ttcn_values.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:08:28 2007
 * 
 * @brief  
 * 
 * 
 */


#include "ttcn_values.h"
#include <cstdlib>


freettcn::TE::CValue::CValue(const CType &type, bool omit) :
  _type(type), _omit(omit)
{
}

freettcn::TE::CValue::~CValue()
{
}

const freettcn::TE::CType &freettcn::TE::CValue::Type() const
{
  return _type;
}

bool freettcn::TE::CValue::Omit() const
{
  return _omit;
}

const String freettcn::TE::CValue::Encoding() const
{
  return Type().Encoding();
}

const String freettcn::TE::CValue::EncodingVariant() const
{
  return Type().EncodingVariant();
}

const String freettcn::TE::CValue::Extension() const
{
  return Type().Extension();
}



freettcn::TE::CBooleanValue::CBooleanValue(const CType &type, bool omit) :
  CValue(type, omit)
{
}



freettcn::TE::CRecordValue::CRecordValue(const CType &type, bool omit) :
  CValue(type, omit)
{
}






void freettcn::TE::CIntegerValue::AbsValue(String value) throw(freettcn::EOperationFailed)
{
  if (*value == '\0')
    throw freettcn::EOperationFailed();
  
  char *endPtr;
  //  std::errno = 0;    /* To distinguish success/failure after call */
  unsigned long val = strtoul(value, &endPtr, 10);
  if (*endPtr != '\0' || value == endPtr) // ||
//       (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)))
    throw freettcn::EOperationFailed();
  
  _absValue = val;
}


void freettcn::TE::CIntegerValue::DigitsNum(unsigned long int dig_num)
{
}


void freettcn::TE::CIntegerValue::Sign(bool sign)
{
  _sign = sign;
}




TciValue freettcn::TE::CRecordValue::Field(String fieldName) const
{
  return 0;
}
