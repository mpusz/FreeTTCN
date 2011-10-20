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
 * @file   ets.cpp
 * @author Mateusz Pusz
 * @date   Thu Apr 26 16:48:52 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/ets.h"
#include "freettcn/ttcn3/tciType.h"
#include "freettcn/ttcn3/tciModuleId.h"
#include "freettcn/te/modulesContainer.h"
#include "freettcn/te/module.h"
#include "freettcn/ttcn3/integer.h"
#include "freettcn/ttcn3/boolean.h"
#include "freettcn/ttcn3/octetstring.h"
#include "freettcn/ttcn3/verdict.h"
#include "freettcn/tools/exception.h"


freettcn::TE::CModule &freettcn::TE::CExecutableTestSuite::Module(const TciModuleId &moduleId) const
{
  return CModulesContainer::Instance().Get(moduleId);
}


freettcn::TE::CModule &freettcn::TE::CExecutableTestSuite::Module(const Tstring &moduleName) const
{
  CTciModuleId id(moduleName);
  return Module(id);
}


std::shared_ptr<const freettcn::CType> freettcn::TE::CExecutableTestSuite::Type(const Tstring &typeName) const
{
  if(typeName == "anytype" || typeName == "address")
    // special meaning of "anytype" "address"
    /// @todo enqueue new message
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
    
  if(typeName == "integer")
    return _builtInTypes.Integer();
  else if(typeName == "float")
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  else if(typeName == "bitstring")
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  else if(typeName == "hexstring")
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  else if(typeName == "octetstring")
    return _builtInTypes.Octetstring();
  else if(typeName == "charstring")
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  else if(typeName == "universal charstring")
    throw ENotImplemented(E_DATA, "Call is not supported yet!!!");
  else if(typeName == "boolean")
    return _builtInTypes.Boolean();
  else if(typeName == "verdicttype")
    return _builtInTypes.Verdict();
  else {
    // read qualified name
    Tstring::size_type pos = typeName.find_first_of(".");
    if(pos == Tstring::npos)
      throw EOperationFailed(E_DATA, "'" + typeName + "' is not a fully qualified type name");
    Tstring::size_type pos2 = typeName.find_last_of(".");
    if(pos != pos2)
      throw EOperationFailed(E_DATA, "'" + typeName + "' is not a fully qualified type name");
      
    Tstring module(typeName, 0, pos);
    Tstring type(typeName, pos + 1);
    return Module(module).Type(type);
  }
}
