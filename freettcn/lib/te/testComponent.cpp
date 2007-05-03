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
 * @file   testComponent.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 13:38:56 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/testComponent.h"
#include "freettcn/te/module.h"
#include "freettcn/te/type.h"


freettcn::TE::CTestComponent::CTestComponent(const CType &type):
  freettcn::TE::CValue(type, false), _inited(false), _module(0)
{
}


freettcn::TE::CTestComponent::~CTestComponent()
{
}


void freettcn::TE::CTestComponent::Init(freettcn::TE::CModule &module, TciTestComponentKindType kind, String name)
{
  _module = &module;
  _kind = kind;
  
  _id.compInst.data = 0;                          /**< @todo Create unique identifier */
  _id.compInst.bits = 0;
  _id.compInst.aux = this;
  _id.compName = name;
  _id.compType = Type().Id();
  
  // register in a module
  _module->TestComponentAdd(*this);
  
  _inited = true;
}


const TriComponentId &freettcn::TE::CTestComponent::Id() const throw(freettcn::TE::CTestComponent::ENotInited)
{
  return _id;
}


void freettcn::TE::CTestComponent::Start(const freettcn::TE::CBehavior &behavior, TciParameterListType parameterList) throw(freettcn::TE::CTestComponent::ENotInited)
{
  // schedule executing test component
  //   Timer().Start();
}


// void freettcn::TE::CTestComponent::Map(const freettcn::TE::CPort &fromPort, const freettcn::TE::CPort &toPort) throw(freettcn::TE::CTestComponent::ENotInited)
// {
// }


// void freettcn::TE::CTestComponent::Verdict(VerdictType_t value)
// {
// }


