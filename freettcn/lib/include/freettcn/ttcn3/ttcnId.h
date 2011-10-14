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
 * @file   ttcnId.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TTCN_ID_H__
#define __TTCN_ID_H__

#include <freettcn/etsi/tci.h>
#include <freettcn/etsi/tri.h>
#include <freettcn/tools/nonAssignable.h>


namespace freettcn {

  namespace ttcn3 {
    
#ifdef TTCN_ID_IFACE_FIXED_2

    class CQualifiedName : public ORG_ETSI_TTCN3_TRI::QualifiedName {
      std::shared_ptr<Tstring> _moduleName;
      std::shared_ptr<Tstring> _objectName;
    public:
      CQualifiedName(const Tstring &moduleName, const Tstring &objectName):
        _moduleName(new Tstring(moduleName)), _objectName(new Tstring(objectName)) {}
      CQualifiedName(const CQualifiedName &) = default;
      CQualifiedName(CQualifiedName &&) = default;
      ~CQualifiedName() = default;
      CQualifiedName *clone() const override             { return new CQualifiedName(*this); }
      
      const Tstring &getModuleName() const override      { return *_moduleName; }
      void setModuleName(const Tstring &mName) override  { _moduleName.reset(new Tstring(mName)); }
      const Tstring &getObjectName() const override      { return *_objectName; }
      void setObjectName(const Tstring &oName) override  { _objectName.reset(new Tstring(oName)); }
      Tstring toString() const override                  { return *_moduleName + "." + *_objectName; }
      
      Tboolean operator==(const ORG_ETSI_TTCN3_TRI::QualifiedName &qn) const override { return *_moduleName == qn.getModuleName() && *_objectName == qn.getObjectName(); }
      Tboolean operator<(const ORG_ETSI_TTCN3_TRI::QualifiedName &qn) const override  { return *_moduleName < qn.getModuleName() && *_objectName < qn.getObjectName(); }
    };
    
#endif
   
    // I really didn't have to go for variadic templates here but it was fun to do that that way ;-)
    // CTTCNIdImpl is a helper class that in fact implements most of the desired interface
    // CTTCNId is an end user class and it implements methods that has to be declared once on the last
    // level of inheritance hierarchy
    template<bool IS_BASE, typename ...REST>
    class CTTCNIdImpl;
    
    template<bool IS_BASE, typename ID, typename ...REST>
    class CTTCNIdImpl<IS_BASE, ID, REST...> : public CTTCNIdImpl<IS_BASE, REST...> {
    public:
#ifdef TTCN_ID_IFACE_FIXED_1
      CTTCNIdImpl(const Tstring &moduleName, const Tstring &objectName): CTTCNIdImpl<IS_BASE, REST...>(moduleName, objectName) {}
      Tboolean operator==(const ID &qn) const override   { return this->getModuleName() == qn.getModuleName() && this->getObjectName() == qn.getObjectName(); }
      Tboolean operator<(const ID &qn) const override    { return this->getModuleName() <  qn.getModuleName() && this->getObjectName() <  qn.getObjectName(); }
#elif TTCN_ID_IFACE_FIXED_2
      CTTCNIdImpl(const CQualifiedName &name): CTTCNIdImpl<IS_BASE, REST...>(name) {}
      Tboolean operator==(const ID &id) const override   { return this->getName() == id.getName(); }
      Tboolean operator<(const ID &id) const override    { return this->getName() < id.getName(); }
#endif
    };
    
#ifdef TTCN_ID_IFACE_FIXED_1
    
    template<bool IS_BASE, typename ID>
    class CTTCNIdImpl<IS_BASE, ID> : CNonAssignable, public ID {
      std::shared_ptr<Tstring> _moduleName;
      std::shared_ptr<Tstring> _objectName;
    public:
      CTTCNIdImpl(const Tstring &moduleName, const Tstring &objectName):
        _moduleName(new Tstring(moduleName)), _objectName(new Tstring(objectName)) {}
      
      const Tstring &getModuleName() const override      { return *_moduleName; }
      void setModuleName(const Tstring &mName) override  { _moduleName.reset(new Tstring(mName)); }
      const Tstring &getObjectName() const override      { return *_objectName; }
      void setObjectName(const Tstring &oName) override  { _objectName.reset(new Tstring(oName)); }
      Tstring toString() const override                  { return *_moduleName + "." + *_objectName; }
      
      Tboolean operator==(const ID &qn) const override   { return *_moduleName == qn.getModuleName() && *_objectName == qn.getObjectName(); }
      Tboolean operator<(const ID &qn) const override    { return *_moduleName < qn.getModuleName()  && *_objectName < qn.getObjectName(); }
    };
    
#elif TTCN_ID_IFACE_FIXED_2
    
    template<bool IS_BASE, typename ID>
    class CTTCNIdImpl<IS_BASE, ID> : CNonAssignable, public ID {
      std::shared_ptr<CQualifiedName> _name;
    public:
      CTTCNIdImpl(const CQualifiedName &name): _name(name.clone()) {}
      const ORG_ETSI_TTCN3_TRI::QualifiedName &getName() const override { return *_name; }
      Tboolean operator==(const ID &id) const override                  { return *_name == id.getName(); }
      Tboolean operator<(const ID &id) const override                   { return *_name < id.getName(); }
    };

#endif
    
    template<typename ...REST>
    class CTTCNId;
    
    template<typename ID, typename ...REST>
    class CTTCNId<ID, REST...> : public CTTCNIdImpl<true, ID, REST...> {
    public:
#ifdef TTCN_ID_IFACE_FIXED_1
      CTTCNId(const Tstring &moduleName, const Tstring &objectName): CTTCNIdImpl<true, ID, REST...>(moduleName, objectName) {}
#elif TTCN_ID_IFACE_FIXED_2
      CTTCNId(const CQualifiedName &name): CTTCNIdImpl<true, ID, REST...>(name) {}
#endif
      CTTCNId *clone() const override { return new CTTCNId(*this); }
    };
    
    template<typename ID>
    class CTTCNId<ID> : public CTTCNIdImpl<true, ID> {
    public:
#ifdef TTCN_ID_IFACE_FIXED_1
      CTTCNId(const Tstring &moduleName, const Tstring &objectName): CTTCNIdImpl<true, ID>(moduleName, objectName) {}
#elif TTCN_ID_IFACE_FIXED_2
      CTTCNId(const CQualifiedName &name): CTTCNIdImpl<true, ID>(name) {}
#endif
      CTTCNId *clone() const override { return new CTTCNId(*this); }
    };
    

#ifdef TTCN_ID_IFACE_FIXED_1

    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::QualifiedName, ORG_ETSI_TTCN3_TCI::TciModuleParameterId> CTciModuleParameterId;
    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::QualifiedName, ORG_ETSI_TTCN3_TCI::TciBehaviourId> CTciBehaviourId;
    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::QualifiedName, ORG_ETSI_TTCN3_TCI::TciBehaviourId, ORG_ETSI_TTCN3_TCI::TciTestCaseId> CTciTestCaseId;

    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::QualifiedName, ORG_ETSI_TTCN3_TRI::TriSignatureId> CTriSignatureId;
    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::QualifiedName, ORG_ETSI_TTCN3_TRI::TriTestCaseId> CTriTestCaseId;
    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::QualifiedName, ORG_ETSI_TTCN3_TRI::TriFunctionId> CTriFunctionId;

#elif TTCN_ID_IFACE_FIXED_2

    typedef CTTCNId<ORG_ETSI_TTCN3_TCI::TciModuleParameterId> CTciModuleParameterId;
    typedef CTTCNId<ORG_ETSI_TTCN3_TCI::TciBehaviourId> CTciBehaviourId;
    typedef CTTCNId<ORG_ETSI_TTCN3_TCI::TciBehaviourId, ORG_ETSI_TTCN3_TCI::TciTestCaseId> CTciTestCaseId;

    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::TriSignatureId> CTriSignatureId;
    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::TriTestCaseId> CTriTestCaseId;
    typedef CTTCNId<ORG_ETSI_TTCN3_TRI::TriFunctionId> CTriFunctionId;

#endif
    
  } // namespace ttcn3
  
} // namespace freettcn


#endif /* __TTCN_ID_H__ */
