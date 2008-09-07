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
 * @file   location.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#include "location.h"


/** 
 * @brief Class constuctor
 * 
 * CLocation class constuctor.
 * 
 * @param file TTCN-3 file
 * @param line Line number
 * @param pos Position in a line
 */
freettcn::translator::CLocation::CLocation(const CFile &file, unsigned line, unsigned pos):
  _file(file), _line(line), _pos(pos)
{
}


/** 
 * @brief Returns TTCN-3 file
 * 
 * Method returns TTCN-3 file.
 * 
 * @return TTCN-3 file
 */
const freettcn::translator::CFile &freettcn::translator::CLocation::File() const
{
  return _file;
}


/** 
 * @brief Returns line number
 * 
 * Method returns line number.
 * 
 * @return Line number
 */
unsigned freettcn::translator::CLocation::Line() const
{
  return _line;
}


/** 
 * @brief Returns position in a line
 * 
 * Method returns position in a line.
 * 
 * @return Position in a line
 */
unsigned freettcn::translator::CLocation::Pos() const
{
  return _pos;
}
