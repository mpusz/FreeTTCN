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
 * @file   location.h
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#ifndef __LOCATION_H__
#define __LOCATION_H__


namespace freettcn {
  
  namespace translator {

    class CFile;
    
    /**
     * @brief TTCN-3 File Location
     *
     * Class contains all information about token location in a
     * TTCN file.
     */
    class CLocation {
      const CFile &_file;                         /**< @brief TTCN-3 file name */
      const unsigned _line;                       /**< @brief Line number */
      const unsigned _pos;                        /**< @brief Position in a line */
      
    public:
      CLocation(const CFile &file, unsigned line, unsigned pos);
      CLocation(const CLocation &) = default;
      CLocation &operator=(const CLocation &) = default;
      const CFile &File() const;
      unsigned Line() const;
      unsigned Pos() const;
    };
    
  } // namespace translator
  
} // namespace freettcn

#endif /* __LOCATION_H__ */
