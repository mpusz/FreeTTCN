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
 * @file   triComponentId.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TRI_COMPONENT_ID_H__
#define __TRI_COMPONENT_ID_H__

#include <freettcn/etsi/tri.h>
#include <freettcn/tools/nonAssignable.h>
#include <memory>


namespace freettcn {

  using namespace ORG_ETSI_TTCN3_TRI;

  class CTriComponentId : CNonAssignable, public ORG_ETSI_TTCN3_TRI::TriComponentId {
    std::shared_ptr<const QualifiedName> _typeName;
    std::shared_ptr<const Tstring> _name;
    Tinteger _id;
  public:
    CTriComponentId(const std::shared_ptr<const QualifiedName> &typeName, const Tstring &name, Tinteger id):
      _typeName(typeName), _name(new Tstring(name)), _id(id) {}
    CTriComponentId(const CTriComponentId &) = default;
    CTriComponentId(CTriComponentId &&) = default;
    ~CTriComponentId() = default;
#ifdef ISSUE_0005949
    TriComponentId *clone() const override             { return new CTriComponentId(*this); }
#else
    TriComponentId *cloneComponentId() override const  { return new CTriComponentId(*this); }
#endif
      
    const QualifiedName &getComponentTypeName() const override     { return *_typeName; }
    void setComponentTypeName(const QualifiedName &tName) override { _typeName.reset(tName.clone()); }
    const Tstring &getComponentName() const override               { return *_name; }
    void setComponentName(const Tstring &sName) override           { _name.reset(new Tstring(sName)); }
    const Tinteger &getComponentId() const override                { return _id; }
    void setComponentId(const Tinteger &id) override               { _id = id; }
    Tstring toString() const override                              { return *_name + "(" + _typeName->toString() + ")"; }
      
    Tboolean operator==(const TriComponentId &cmp) const override  { return _id == cmp.getComponentId(); }
    Tboolean operator<(const TriComponentId &cmp) const override   { return _id < cmp.getComponentId(); }
  };
        
} // namespace freettcn

#endif /* __TRI_COMPONENT_ID_H__ */
