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
 * @file   file.h
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#ifndef __FILE_H__
#define __FILE_H__

#include "freettcn/tools/nonCopyable.h"
#include <string>

namespace freettcn {
  
  namespace translator {

    /**
     * @brief TTCN-3 File Information.
     *
     * Class contains all information about the file in which TTCN-3 module is
     * located.
     */
    class CFile : CNonCopyable {
      const std::string _fullName;                /**< @brief File name with path included */
      std::string _path;                          /**< @brief File path */
      std::string _moduleName;                    /**< @brief Module name (file name without expression) */
      std::string _extension;                     /**< @brief Extension */
    
    public:
      explicit CFile(const std::string &fileName);
      
      const std::string &FullName() const;
      const std::string &Path() const;
      const std::string &ModuleName() const;
      const std::string &Extension() const;
    };
  
  } // namespace translator

} // namespace freettcn


/** 
 * @brief Returns TTCN-3 file full name
 * 
 * Method returns TTCN-3 file full name.
 * 
 * @return TTCN-3 file full name
 */
inline const std::string &freettcn::translator::CFile::FullName() const
{
  return _fullName;
}

#endif // __FILE_H__
