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
 * @file   typesContainer.cpp
 * @author Mateusz Pusz
 * @date   Thu Apr 26 17:32:57 2007
 * 
 * @brief  
 * 
 * 
 */

#include "typesContainer.h"


freettcn::TE::CControlComponent::CControlComponent(const CType &type):
  freettcn::TE::CTestComponent(type)
{
}


freettcn::TE::CControlComponentType::CControlComponentType():
  freettcn::TE::CTestComponentType(0 , "_ControlComponentType_")
{
}

freettcn::TE::CValue *freettcn::TE::CControlComponentType::InstanceCreate(bool omit /* false */) const
{
  return new freettcn::TE::CControlComponent(*this);
}




const freettcn::TE::CBooleanType freettcn::TE::CTypesContainer::_boolean;
const freettcn::TE::CControlComponentType freettcn::TE::CTypesContainer::_control;

const freettcn::TE::CBooleanType &freettcn::TE::CTypesContainer::Boolean()
{
  return _boolean;
}


const freettcn::TE::CControlComponentType &freettcn::TE::CTypesContainer::ControlComponent()
{
  return _control;
}
