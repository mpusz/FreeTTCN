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
 * @file   tci_cd_te.cpp
 * @author Mateusz Pusz
 * @date   Sun May 13 22:04:31 2007
 * 
 * @brief  
 * 
 * 
 */


extern "C" {
#include "freettcn/ttcn3/tci_cd_te.h"
}
#include "freettcn/te/basicTypes.h"
#include "freettcn/te/modulesContainer.h"
#include "freettcn/te/module.h"
#include <iostream>
#include <cstring>



TciType tciGetTypeForName(String typeName)
{
  // check if qualified name
  const char *dot = strchr(typeName, '.');
  if (!dot) {
    // no module name given
    if (!strcmp(typeName, "integer"))
      return const_cast<void *>(static_cast<const void *>(&freettcn::TE::CBasicTypes::Integer()));
//     if (!strcmp(typeName, "float"))
//       return ;
//     if (!strcmp(typeName, "bitstring"))
//       return ;
//     if (!strcmp(typeName, "hexstring"))
//       return ;
    if (!strcmp(typeName, "octetstring"))
      return const_cast<void *>(static_cast<const void *>(&freettcn::TE::CBasicTypes::Octetstring()));
//     if (!strcmp(typeName, "charstring"))
//       return ;
//     if (!strcmp(typeName, "universal charstring"))
//       return ;
    if (!strcmp(typeName, "boolean"))
      return const_cast<void *>(static_cast<const void *>(&freettcn::TE::CBasicTypes::Boolean()));
    if (!strcmp(typeName, "verdicttype"))
      return const_cast<void *>(static_cast<const void *>(&freettcn::TE::CBasicTypes::Verdict()));
//     if (!strcmp(typeName, "objid"))
//       return ;
    
    std::cout << "ERROR: Predefined type with name: " << typeName << " not found!!!" << std::endl;
  }
  else {
    // prepare module name
    char *moduleId = new char[dot - typeName + 1];
    strncpy(moduleId, typeName, dot - typeName);
    moduleId[dot - typeName] = 0;
    
    // obtain module
    try {
      freettcn::TE::CModulesContainer &modContainer = freettcn::TE::CModulesContainer::Instance();
      freettcn::TE::CModule &module = modContainer.Get(moduleId);
      
      const char *name = dot + 1;
      
      // obtain module parameters
      const freettcn::TE::CType &type = module.Type(name);
      
      delete moduleId;
      
      return const_cast<void *>(static_cast<const void *>(&type));
    }
    catch(freettcn::ENotFound) {
      delete moduleId;
    }
  }
  
  return 0;
}


TciType tciGetIntegerType()
{
  return const_cast<void *>(static_cast<const void *>(&freettcn::TE::CBasicTypes::Integer()));
}


// TciType tciGetFloatType()
// {
// }


TciType tciGetBooleanType()
{
  return const_cast<void *>(static_cast<const void *>(&freettcn::TE::CBasicTypes::Boolean()));
}


// TciType tciGetTciObjidType()
// {
// }


// TciType tciGetCharType()
// {
// }


// TciType tciGetUniversalCharType()
// {
// }


// TciType tciGetTciCharstringType()
// {
// }


// TciType tciGetUniversalCharstringType()
// {
// }


// TciType tciGetHexstringType()
// {
// }


// TciType tciGetBitstringType()
// {
// }


TciType tciGetOctetstringType()
{
  return const_cast<void *>(static_cast<const void *>(&freettcn::TE::CBasicTypes::Octetstring()));
}


TciType tciGetVerdictType()
{
  return const_cast<void *>(static_cast<const void *>(&freettcn::TE::CBasicTypes::Verdict()));
}


// void tciErrorReq(String message)
// {
// }
