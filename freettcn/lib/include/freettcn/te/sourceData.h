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
 * @file   sourceData.h
 * @author Mateusz Pusz
 * @date   Thu Apr 26 08:46:45 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __SOURCEDATA_H__
#define __SOURCEDATA_H__


namespace freettcn {

  namespace TE {

    class CSourceData {
      char const * const _src;
      const int _line;
    public:
      CSourceData(const char *src, int line);
      const char *Source() const;
      int Line() const;
    };

  } // namespace TE
  
} // namespace freettcn


#endif /* __SOURCEDATA_H__ */
