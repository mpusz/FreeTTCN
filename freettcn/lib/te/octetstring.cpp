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

#include "freettcn/te/octetstring.h"
#include "freettcn/tools/exception.h"
#include <sstream>
#include <cstdlib>
#include <cstdio>


freettcn::TE::COctetstringType::COctetstringType():
  CType(0, "octetstring", TCI_OCTETSTRING_TYPE, nullptr, nullptr, nullptr)
{
}


freettcn::TE::COctetstringType::CInstance *freettcn::TE::COctetstringType::InstanceCreate() const
{
  return new freettcn::TE::COctetstringType::CInstance(*this);
}




freettcn::TE::COctetstringType::CInstance::CInstance(const CType &type) :
  freettcn::TE::CType::CInstance(type), _value("''O")
{
}


const char *freettcn::TE::COctetstringType::CInstance::Value() const
{
  if (Omit())
    throw EOperationFailed(E_DATA, "Cannot return a value when 'omit' is set!!!");
  return _value.c_str();
}


void freettcn::TE::COctetstringType::CInstance::Value(const char *value)
{
  const char *ptr = value;

  // check if the string starts with '
  if (*ptr != '\'')
    throw EOperationFailed(E_DATA, "Value should start with a ' sign!!!");
  ptr++;
  
  // find the end of the string
  const char *tempPtr = ptr;
  int len;
  for(len=0; *tempPtr && *tempPtr != '\''; len++, tempPtr++);

  // check if the string ends with 'O
  if (*tempPtr != '\'' || *(++tempPtr) != 'O' || *(++tempPtr))
    throw EOperationFailed(E_DATA, "Value should end with a 'O signs!!!");
  
  // check the length of the string
  if (len % 2)
    throw EOperationFailed(E_DATA, "Bad value length detected - octetstring should contain pairs of hex values!!!");
  
  // set new length and reset string
  Length(len / 2);
  
  // check if correct values in a string
  for(int i=0; i<len/2; i++, ptr+=2) {
    char tempStr[3] = { *ptr, *(ptr + 1), '\0' };
    char *end;
    int value = strtol(tempStr, &end, 16);
    if (end == tempStr || *end != '\0')
      throw EOperationFailed(E_DATA, "Octetstring should contain pairs of hex values!!!");
    
    // store new value
    sprintf(tempStr, "%02X", value);
    unsigned int index = i * 2 + 1;
    _value.replace(index, 2, tempStr);
  }
}


int freettcn::TE::COctetstringType::CInstance::Element(unsigned int position) const
{
  if (Omit())
    throw EOperationFailed(E_DATA, "Cannot set element when 'omit' is set!!!");
  
  if (position >= Length()) {
    std::stringstream stream;
    stream << "Element position: " << position << " too big (size: " << Length() << ")";
    throw EOutOfRange(E_DATA, stream.str());
  }
  
  unsigned int index = position * 2 + 1;
  std::string tempStr(_value.substr(index, 2));
  return strtol(tempStr.c_str(), 0, 16);
}


void freettcn::TE::COctetstringType::CInstance::Element(unsigned int position, int value)
{
  if (position >= Length()) {
    std::stringstream stream;
    stream << "Element position: " << position << " too big (size: " << Length() << ")";
    throw EOperationFailed(E_DATA, stream.str());
  }
  
  if (value < 0 || value > 0xFF)
    throw EOperationFailed(E_DATA, "Octetstring element must be between 0.255!!!");
  
  char tempStr[3];
  sprintf(tempStr, "%02X", value);
  
  unsigned int index = position * 2 + 1;
  _value.replace(index, 2, tempStr);
}


unsigned int freettcn::TE::COctetstringType::CInstance::Length() const
{
  return (_value.size() - 3) / 2;
}


void freettcn::TE::COctetstringType::CInstance::Length(unsigned int length)
{
  std::string temp(length * 2, '0');
  _value = "'" + temp + "'O";
}
