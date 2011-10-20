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

#include "freettcn/ttcn3/integer.h"
#include "freettcn/ttcn3/tciModuleId.h"


/// @todo verify if encoding can be set for built-in types
freettcn::CTypeInteger::CTypeInteger():
  CType(CTciModuleId::BuiltIn(), "integer", TCI_INTEGER, "", "", CExtension())
{
  if(!_instance)
    _instance.reset(new CTypeInteger(*this));
}
