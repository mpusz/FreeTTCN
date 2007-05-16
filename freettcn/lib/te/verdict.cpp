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
 * @file   verdict.cpp
 * @author Mateusz Pusz
 * @date   Sun May 13 19:37:56 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/verdict.h"


freettcn::TE::CVerdictType::CVerdictType():
  CType(0, "verdicttype", TCI_VERDICT_TYPE, "", "", "")
{
}

freettcn::TE::CVerdictType::CInstance *freettcn::TE::CVerdictType::InstanceCreate() const
{
  return new freettcn::TE::CVerdictType::CInstance(*this);
}


freettcn::TE::CVerdictType::CInstance::CInstance(const CType &type):
  freettcn::TE::CType::CInstance(type)
{
}

freettcn::TE::CVerdictType::CInstance::CInstance(const CType &type, TVerdict value):
  freettcn::TE::CType::CInstance(type), _value(value)
{
  Omit(false);
}

freettcn::TE::TVerdict freettcn::TE::CVerdictType::CInstance::Value() const throw(EOmitSet)
{
  if (Omit())
    throw EOmitSet();
  return _value;
}

void freettcn::TE::CVerdictType::CInstance::Value(TVerdict value)
{
  _value = value;
  Omit(false);
}
