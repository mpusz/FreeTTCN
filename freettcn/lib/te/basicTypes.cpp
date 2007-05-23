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
 * @file   basicTypes.cpp
 * @author Mateusz Pusz
 * @date   Fri May  4 09:29:40 2007
 * 
 * @brief  
 * 
 * 
 */


#include "freettcn/te/basicTypes.h"


const freettcn::TE::CIntegerType freettcn::TE::CBasicTypes::_integer;
const freettcn::TE::CBooleanType freettcn::TE::CBasicTypes::_boolean;
const freettcn::TE::COctetstringType freettcn::TE::CBasicTypes::_octetstring;
const freettcn::TE::CVerdictType freettcn::TE::CBasicTypes::_verdict;
const freettcn::TE::CControlComponentType freettcn::TE::CBasicTypes::_control;



const freettcn::TE::CIntegerType &freettcn::TE::CBasicTypes::Integer()
{
  return _integer;
}

const freettcn::TE::CBooleanType &freettcn::TE::CBasicTypes::Boolean()
{
  return _boolean;
}

const freettcn::TE::COctetstringType &freettcn::TE::CBasicTypes::Octetstring()
{
  return _octetstring;
}

const freettcn::TE::CVerdictType &freettcn::TE::CBasicTypes::Verdict()
{
  return _verdict;
}


const freettcn::TE::CControlComponentType &freettcn::TE::CBasicTypes::ControlComponent()
{
  return _control;
}
