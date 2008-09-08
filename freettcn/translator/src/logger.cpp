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
 * @file   logger.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#include "logger.h"
#include "location.h"
#include "file.h"
#include "freettcn/tools/exception.h"
#include <iostream>


freettcn::translator::CLogger::CLogger():
  _groupUsed(false)
{
}


freettcn::translator::CLogger::~CLogger()
{
}


void freettcn::translator::CLogger::Warning(const CLocation &loc, const std::string &msg)
{
  GroupPrint();
  std::cerr << loc.File().FullName() << ":" << loc.Line() << ":" << loc.Pos() << ": "
            << "error: " << msg << std::endl;
}


void freettcn::translator::CLogger::Error(const CLocation &loc, const std::string &msg)
{
  GroupPrint();
  std::cerr << loc.File().FullName() << ":" << loc.Line() << ":" << loc.Pos() << ": "
            << "error: " << msg << std::endl;
}


void freettcn::translator::CLogger::GroupPrint()
{
  if(_groupStack.size() && !_groupUsed) {
    const TGroup &group = _groupStack.top();
    std::cerr << group.file->FullName() << ": " << group.msg << std::endl;
    _groupUsed = true;
  }
}


void freettcn::translator::CLogger::GroupPush(const CFile &file, const std::string &msg)
{
  TGroup group = { &file, msg };
  _groupStack.push(group);
  _groupUsed = false;
}


void freettcn::translator::CLogger::GroupPop()
{
  if(!_groupStack.size())
    throw EOperationFailed(E_DATA, "Logger group empty already!!!");
  
  _groupStack.pop();
  _groupUsed = false;
}
