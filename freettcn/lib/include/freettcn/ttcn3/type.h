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
 * @file   type.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:51 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TYPE_H__
#define __TYPE_H__

#include <freettcn/etsi/tci.h>
#include <freettcn/tools/nonCopyable.h>
#include <memory>

namespace freettcn {

  namespace ttcn3 {
    
    using namespace ORG_ETSI_TTCN3_TCI;
    
    class CType : CNonCopyable, public ORG_ETSI_TTCN3_TCI::TciType  {
    public:
      class CValue : freettcn::CNonAssignable, public virtual ORG_ETSI_TTCN3_TCI::TciValue {
      private:
        const TciType &_type;
        std::unique_ptr<Tstring> _encoding;
        std::unique_ptr<Tstring> _encodingVariant;
        
      protected:
        CValue(const CValue &src);
        CValue(CValue &&) = default;
        
      public:
        CValue(const TciType &type,
               const Tstring &encoding,
               const Tstring &encodingVariant);
        ~CValue() = default;
        
        const TciType &getType() const override { return _type; }
        const Tstring &getValueEncoding() const override;
        const Tstring &getValueEncodingVariant() const override;
        Tboolean notPresent() const override    { return false; }
      };

      class CValueOmitted : public CValue {
      public:
        CValueOmitted(const TciType &type,
                      const Tstring &encoding,
                      const Tstring &encodingVariant);
        ~CValueOmitted() = default;
        TciValue *clone() const override;
        Tboolean notPresent() const override    { return true; }
        Tboolean operator==(const TciValue &val) const override;
        Tboolean operator<(const TciValue &val) const override;
      };
      
      typedef std::vector<Tstring*> CExtension;
      
    private:
      const TciModuleId  &_moduleId;
      const Tstring      _name;
      const TciTypeClass _class;
      const Tstring      _encoding;
      const Tstring      _encodingVariant;
      const CExtension   _extension;
      
    public:
      CType(const TciModuleId  &moduleId,
            const Tstring      &name,
            const TciTypeClass &typeClass,
            const Tstring      &encoding,
            const Tstring      &encodingVariant,
            const CExtension   &extension);
      ~CType() = default;
      
      const TciModuleId &getDefiningModule() const override  { return _moduleId; }
      const Tstring &getName() const override                { return _name; }
      const TciTypeClass &getTypeClass() const override      { return _class; }
      const Tstring &getTypeEncoding() const override        { return _encoding; }
      const Tstring &getTypeEncodingVariant() const override { return _encodingVariant; }
      const CExtension &getTypeExtension() const override    { return _extension; }
      Tboolean operator==(const TciType &typ) const override;
      Tboolean operator<(const TciType &typ) const override;
    };
    
    Tstring QualifiedName(const TciType &type);
    
  } // namespace ttcn3
  
} // namespace freettcn


#endif /* __TYPE_H__ */
