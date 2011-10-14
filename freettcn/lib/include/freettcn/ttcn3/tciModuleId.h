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
 * @file   tciModuleId.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TCI_MODULE_ID_H__
#define __TCI_MODULE_ID_H__

#include <freettcn/etsi/tci.h>
#include <freettcn/tools/nonAssignable.h>
#include <memory>


namespace freettcn {

  namespace ttcn3 {
    
    using namespace ORG_ETSI_TTCN3_TCI;

    class CTciModuleId : CNonAssignable, public ORG_ETSI_TTCN3_TCI::TciModuleId {
      static CTciModuleId _builtIn;
      std::shared_ptr<const Tstring> _name;
    public:
      static const CTciModuleId &BuiltIn() { return _builtIn; }
      
      CTciModuleId(const Tstring &name): _name(new Tstring(name)) {}
      CTciModuleId(const CTciModuleId &) = default;
      CTciModuleId(CTciModuleId &&) = default;
      ~CTciModuleId() = default;
      TciModuleId *clone() const override                { return new CTciModuleId(*this); }
      
      const Tstring &getObjectName() const override      { return *_name; }
      void setObjectName(const Tstring &p_name) override { _name.reset(new Tstring(p_name)); }
      
      Tboolean operator==(const TciModuleId &mid) const override { return *_name == mid.getObjectName(); }
      Tboolean operator<(const TciModuleId &mid) const override  { return *_name < mid.getObjectName(); }
    };
        
  } // namespace ttcn3
  
} // namespace freettcn

#endif /* __TCI_MODULE_ID_H__ */
