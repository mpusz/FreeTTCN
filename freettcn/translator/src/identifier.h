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
 * @file   identifier.h
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#ifndef __IDENTIFIER_H__
#define __IDENTIFIER_H__

#include "freettcn/tools/nonCopyable.h"
#include "location.h"
#include <string>
#include <memory>


namespace freettcn {
  
  namespace translator {
    
    /**
     * @brief TTCN-3 Identifier.
     *
     * Class contains all information about TTCN-3 Identifier
     * (it stores names of variables, structs, functions, etc.).
     */
    class CIdentifier : CNonCopyable {
      const CLocation _loc;                       /**< @brief Location in a file */
      const std::string _name;                    /**< @brief Identifier name */
      
    public:
      CIdentifier(const CLocation &loc, const char *name);
      
      const CLocation &Loc() const;
      const std::string &Name() const;
    };
    
  } // namespace translator

} // namespace freettcn


/** 
 * @brief Returns identifier name
 * 
 * Method returns identifier name
 * 
 * @return Identifier name
 */
inline const std::string &freettcn::translator::CIdentifier::Name() const
{
  return _name;
}

#endif /* __IDENTIFIER_H__ */
