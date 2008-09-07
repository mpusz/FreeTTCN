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
 * @file   file.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */

#include "file.h"


/** 
 * @brief Class constructor.
 *
 * CFile class constructor.
 * 
 * @param fileName The name of a TTCN-3 source code file to compile.
 */
freettcn::translator::CFile::CFile(const std::string &fileName):
  _fullName(fileName)
{
  size_t pos1 = _fullName.find_last_of("/\\");
  size_t pos2 = _fullName.find_last_of('.');
  if(pos1 != std::string::npos)
    _path = _fullName.substr(0, pos1 + 1);
  _moduleName = _fullName.substr(pos1 + 1, pos2 - pos1 - 1);
  _extension = _fullName.substr(pos2);
}


/** 
 * @brief Returns file directory part
 * 
 * Method returns file directory part.
 * 
 * @return File directory part
 */
const std::string &freettcn::translator::CFile::Path() const
{
  return _path;
}


/** 
 * @brief Returns expected module name
 * 
 * Method returns expected module name.
 * 
 * @return Expected module name
 */
const std::string &freettcn::translator::CFile::ModuleName() const
{
  return _moduleName;
}


/** 
 * @brief Returns file extension
 * 
 * Method returns file extension.
 * 
 * @return File extension
 */
const std::string &freettcn::translator::CFile::Extension() const
{
  return _extension;
}
