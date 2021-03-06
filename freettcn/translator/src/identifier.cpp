//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) compiler.

// freettcn is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// freettcn is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with freettcn; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   identifier.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#include "identifier.h"


/** 
 * @brief Class constructor
 * 
 * CIdentifier class constructor.
 * 
 * @param loc Location in a file
 * @param name Identifier name
 */
freettcn::translator::CIdentifier::CIdentifier(const CLocation &loc, const char *name):
  _loc(loc), _name(name)
{
}


/** 
 * @brief Returns identifier location
 * 
 * Method returns identifier location.
 * 
 * @return Identifier location
 */
const freettcn::translator::CLocation &freettcn::translator::CIdentifier::Loc() const
{
  return _loc;
}
