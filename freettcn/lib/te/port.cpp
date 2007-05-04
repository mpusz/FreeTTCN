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
 * @file   port.cpp
 * @author Mateusz Pusz
 * @date   Wed May  2 17:46:49 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/port.h"
#include "freettcn/te/module.h"


freettcn::TE::CPortType::CPortType(const freettcn::TE::CModule &module, const char *name)
{
  _id.moduleName = const_cast<char *>(module.Name());
  _id.objectName = const_cast<char *>(name);
  _id.aux = 0;
}

const QualifiedName &freettcn::TE::CPortType::Id() const
{
  return _id;
}





freettcn::TE::CPortType::CInstance::CInstance(const freettcn::TE::CPortType &type,
                                              const freettcn::TE::CTestComponentType::CInstance &component,
                                              const char *name, int portIdx /* -1 */)
{
  _id.compInst = component.Id();
  _id.portName = const_cast<char *>(name);
  _id.portIndex = portIdx;
  _id.portType = type.Id();
  _id.aux = this;
}


const TriPortId &freettcn::TE::CPortType::CInstance::Id() const
{
  return _id;
}
