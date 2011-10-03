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
 * @file   modulesContainer.h
 * @author Mateusz Pusz
 * @date   Thu Apr 26 16:49:51 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __MODULESCONTAINER_H__
#define __MODULESCONTAINER_H__

#include <freettcn/tools/nonCopyable.h>
#include <freettcn/tools/exception.h>
#include <vector>


namespace freettcn {

  namespace TE {
    
    class CModule;
    
    /**
     * Singleton design pattern
     */
    class CModulesContainer : CNonCopyable {
    public:
      typedef std::vector<CModule *> CModuleList;
      
    private:
      CModuleList _modList;
      
      CModulesContainer();
    public:
      static CModulesContainer &Instance();
      
      void Register(CModule &module);
      CModule &Get(const std::string &moduleId) const;
      const CModuleList &List() const;
    };

  } // namespace TE
  
} // namespace freettcn


#endif /* __MODULESCONTAINER_H__ */
