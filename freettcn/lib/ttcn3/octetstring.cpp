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
 * @file   octetstring.cpp
 * @author Mateusz Pusz
 * @date   Tue May 22 22:17:05 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/ttcn3/octetstring.h"
#include "freettcn/ttcn3/tciModuleId.h"
#include "freettcn/tools/exception.h"


void freettcn::ttcn3::CTypeOctetstring::CValue::setLength(Tsize p_length)
{
  _value.reset(new Tstring(*_value));
  _value->resize(p_length, '0');
}


void freettcn::ttcn3::CTypeOctetstring::CValue::setOctet(Tindex p_position, Tchar p_ochar)
{
  if(std::string("0123456789abcdefABCDEF").find_first_of(p_ochar) != std::string::npos) {
    _value.reset(new Tstring(*_value));
    _value->at(p_position) = p_ochar;
  }
  else
    throw EOperationFailed(E_DATA, "Invalid character '" + std::string(1, p_ochar) + "' provided as an element of octetstring type!!!");
}


void freettcn::ttcn3::CTypeOctetstring::CValue::setString(const Tstring &p_osValue) override
{
  if(p_osValue.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos) {
    _value.reset(new Tstring(p_osValue));
  }
  else
    throw EOperationFailed(E_DATA, "Invalid string '" + p_osValue + "' provided as a value of octetstring type!!!");
}




/// @todo verify if encoding can be set for built-in types
freettcn::ttcn3::CTypeOctetstring::CTypeOctetstring():
  CType(CTciModuleId::BuiltIn(), "octetstring", TCI_OCTETSTRING, "", "", CExtension())
{
}
