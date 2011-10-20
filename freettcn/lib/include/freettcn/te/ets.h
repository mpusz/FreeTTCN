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
 * @file   ets.h
 * @author Mateusz Pusz
 * @date   Sat Apr  7 22:10:55 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __ETS_H__
#define __ETS_H__

#include <freettcn/tools/nonCopyable.h>
#include <freettcn/etsi/tci.h>
#include <freettcn/te/builtInTypes.h>

namespace freettcn {

  class CType;
  
  namespace TE {

    class CModule;

    using namespace ORG_ETSI_TTCN3_TCI;
    
    class CExecutableTestSuite : CNonCopyable
    {
      const CBuiltInTypes _builtInTypes;
    public:
      CExecutableTestSuite() = default;
      ~CExecutableTestSuite() = default;
      
      CModule &Module(const TciModuleId &moduleId) const;
      CModule &Module(const Tstring &moduleName) const;
      
      const CBuiltInTypes &TypeTTCN3() const { return _builtInTypes; }
      std::shared_ptr<const freettcn::CType> Type(const Tstring &typeName) const;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __ETS_H__ */
