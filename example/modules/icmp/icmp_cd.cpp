//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) usage example.

// This example is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This example is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this example; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   icmp_cd.cpp
 * @author Mateusz Pusz
 * @date   Wed May 30 10:39:36 2007
 * 
 * @brief  
 * 
 * 
 */

#include "icmp_cd.h"
extern "C" {
#include <freettcn/ttcn3/tci_value.h>
}
#include <cstring>


freettcn::icmp::CCodec::CCodec():
  CD::CCodec("icmp")
{
}


bool freettcn::icmp::CCodec::CapabilityCheck(TciValue value, unsigned int &valueId) const
{
  // obtain type and module name of a value
  TciType type = tciGetType(value);
  TciModuleIdType moduleId = tciGetDefiningModule(type);
  
  if (!strcmp(moduleId.moduleName, "icmp")) {
    // that is icmp module type
    if (!strcmp(tciGetName(type), "ICMPMsg")) {
      valueId = ID_ICMPMSG;
      return true;
    }
  }
  
  return false;
}


void freettcn::icmp::CCodec::Encode(unsigned int valueId, TciValue value, BinaryString &buffer) const
{
  switch(valueId) {
  case ID_ICMPMSG:
    
    break;

  default:
    ;
  }
}
