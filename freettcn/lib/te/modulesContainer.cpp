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
 * @file   modulesContainer.cpp
 * @author Mateusz Pusz
 * @date   Thu Apr 26 16:48:52 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/modulesContainer.h"
#include "freettcn/te/module.h"
#include <iostream>


freettcn::TE::CModulesContainer::CModulesContainer()
{
}

freettcn::TE::CModulesContainer &freettcn::TE::CModulesContainer::Instance()
{
  static freettcn::TE::CModulesContainer container;
  
  return container;
}

void freettcn::TE::CModulesContainer::Register(CModule &module)
{
  _modList.push_back(&module);
}

freettcn::TE::CModule &freettcn::TE::CModulesContainer::Get(const std::string &moduleId) const throw(ENotFound)
{
  for(CModuleList::const_iterator it=_modList.begin(); it != _modList.end(); ++it)
    if ((*it)->Id().moduleName == moduleId)
      return *(*it);
  std::cout << "ERROR: Module not found" << std::endl;
  throw freettcn::ENotFound();
}

const freettcn::TE::CModulesContainer::CModuleList &freettcn::TE::CModulesContainer::List() const
{
  return _modList;
}
