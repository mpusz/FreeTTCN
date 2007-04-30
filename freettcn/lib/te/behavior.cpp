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
 * @file   behavior.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 13:39:26 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/behavior.h"
#include "freettcn/te/module.h"


freettcn::TE::CBehavior::CBehavior(CModule &module, const char *name):
  _module(module)
{
  _id.moduleName = const_cast<char *>(_module.Name());
  _id.objectName = const_cast<char *>(name);
  _id.aux = 0;
  
  // register in a module
  _module.BehaviorAdd(this);
}


freettcn::TE::CBehavior::~CBehavior()
{
}


const TciBehaviourIdType &freettcn::TE::CBehavior::Id() const
{
  return _id;
}
