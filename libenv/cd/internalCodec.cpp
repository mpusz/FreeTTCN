//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcnenv (Free TTCN Environment) library.

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
 * @file   internalCodec.cpp
 * @author Mateusz Pusz
 * @date   Wed May 30 10:15:56 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/cd/internalCodec.h"
extern "C" {
#include <freettcn/ttcn3/tci_value.h>
}


freettcn::CD::CInternalCodec::CInternalCodec():
  CCodec("<freettcn>")
{
}


bool freettcn::CD::CInternalCodec::CapabilityCheck(const Value &value, unsigned int &valueId) const
{
  // obtain type and module name of a value
  Type type = tciGetType(value);
  TciModuleIdType moduleId = tciGetDefiningModule(type);
  
  if (!moduleId.moduleName) {
    // that is TTCN-3 base type
    if (!tciGetTypeEncoding(type) && !tciGetTypeEncodingVariant(type)) {
      switch(tciGetTypeClass(type)) {
      case TCI_INTEGER_TYPE:
        valueId = ID_INTEGER;
        return true;
      default:
        ;
      }
    }
  }
  
  return false;
}


void freettcn::CD::CInternalCodec::Encode(unsigned int valueId, const Value &value, CBuffer &buffer) const
{
  switch(valueId) {
  case ID_INTEGER:
    /// @todo not a good idea to encode generic integer
    break;
  default:
    ;
  }
}
