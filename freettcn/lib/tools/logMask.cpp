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
 * @file   logMask.cpp
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:36:31 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/tools/logMask.h"



freettcn::CLogMask::CLogMask(unsigned short num, bool enabled /* true */):
  _num(num), _array(num, enabled)
{
}

freettcn::CLogMask::~CLogMask()
{
}

void freettcn::CLogMask::Set(bool enabled)
{
  for(unsigned short i=0; i<_array.size(); i++)
    _array[i] = enabled;
}

void freettcn::CLogMask::Set(unsigned short idx, bool enabled)
{
  _array[idx] = enabled;
}

bool freettcn::CLogMask::Get(unsigned short idx)
{
  return _array[idx];
}
