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
 * @file   sourceData.cpp
 * @author Mateusz Pusz
 * @date   Thu Apr 26 08:47:29 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/sourceData.h"


freettcn::TE::CSourceData::CSourceData(const char *src, int line):
  _src(src), _line(line)
{
}


const char *freettcn::TE::CSourceData::Source() const
{
  return _src;
}


int freettcn::TE::CSourceData::Line() const
{
  return _line;
}
