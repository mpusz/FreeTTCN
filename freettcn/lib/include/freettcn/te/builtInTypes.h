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
 * @file   builtInTypes.h
 * @author Mateusz Pusz
 * @date   Fri May  4 09:19:29 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __BUILTINTYPES_H__
#define __BUILTINTYPES_H__

#include <freettcn/tools/nonCopyable.h>
#include <memory>

namespace freettcn {
  
  class CTypeInteger;
  class CTypeFloat;
  class CTypeBoolean;
  class CTypeCharstring;
  class CTypeUniversalCharstring;
  class CTypeHexstring;
  class CTypeBitstring;
  class CTypeOctetstring;
  class CTypeVerdict;
  
  namespace TE {
    
    class CBuiltInTypes : CNonCopyable {
      std::shared_ptr<const CTypeInteger> _integer;
      std::shared_ptr<const CTypeBoolean> _boolean;
      std::shared_ptr<const CTypeOctetstring> _octetstring;
      std::shared_ptr<const CTypeVerdict> _verdict;
    public:
      CBuiltInTypes();
      ~CBuiltInTypes() = default;
      const std::shared_ptr<const CTypeInteger> &Integer() const         { return _integer; }
      const std::shared_ptr<const CTypeBoolean> &Boolean() const         { return _boolean; }
      const std::shared_ptr<const CTypeOctetstring> &Octetstring() const { return _octetstring; }
      const std::shared_ptr<const CTypeVerdict> &Verdict() const         { return _verdict; }
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __BUILTINTYPES_H__ */
