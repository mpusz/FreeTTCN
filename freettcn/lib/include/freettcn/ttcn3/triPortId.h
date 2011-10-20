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
 * @file   triPortId.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TRI_PORT_ID_H__
#define __TRI_PORT_ID_H__

#include <freettcn/etsi/tri.h>
#include <freettcn/tools/nonAssignable.h>
#include <memory>


namespace freettcn {

  using namespace ORG_ETSI_TTCN3_TRI;

  class CTriPortId : CNonAssignable, public ORG_ETSI_TTCN3_TRI::TriPortId {
    std::shared_ptr<const QualifiedName> _type;
    std::shared_ptr<const Tstring> _name;
    std::shared_ptr<const TriComponentId> _component;
    Tinteger _index;

    CTriPortId(const CTriPortId &) = default;
  public:
    CTriPortId(const std::shared_ptr<const QualifiedName> &type, const Tstring &name,
               const std::shared_ptr<const TriComponentId> &component, Tindex index):
      _type(type), _name(new Tstring(name)), _component(component), _index(index) {}
    CTriPortId(CTriPortId &&) = default;
    ~CTriPortId() = default;
#ifdef ISSUE_0005949
    TriPortId *clone() const override        { return new CTriPortId(*this); }
#else
    TriPortId *clonePortId() override const  { return new CTriPortId(*this); }
#endif
      
    const Tstring &getPortName() const override            { return *_name; }
    void setPortName(const Tstring &pName) override        { _name.reset(new Tstring(pName)); }
    const TriComponentId &getComponent() const override    { return *_component; }
    void setComponent(const TriComponentId &comp) override { _component.reset(comp.cloneComponentId()); }
    Tsize getPortIndex() const override                    { return _index; }
    void setPortIndex(Tsize index) override                { _index = index; }
    const QualifiedName &getPortType() const override      { return *_type; }
    void setPortType(const QualifiedName &pType) override  { _type.reset(pType.clone()); }
    Tboolean isArray() const override                      { return _index != -1; }
      
    Tboolean operator==(const TriPortId &prt) const override  { return *_name == prt.getPortName() && *_component == prt.getComponent(); }
    Tboolean operator<(const TriPortId &prt) const override   { return *_name < prt.getPortName() && *_component < prt.getComponent(); }
  };
        
} // namespace freettcn

#endif /* __TRI_PORT_ID_H__ */
