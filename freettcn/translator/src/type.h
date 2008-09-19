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
 * @file   type.h
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#ifndef __TYPE_H__
#define __TYPE_H__

#include "freettcn/tools/tools.h"
#include <string>
#include <map>
#include <memory>


namespace freettcn {

  namespace translator {

    class CIdentifier;
    class CDumper;

    class CType {
      CType(const CType &);                       /**< @brief Disallowed */
      CType &operator=(const CType &);            /**< @brief Disallowed */
    public:
      CType();
      virtual ~CType() = 0;
      virtual const std::string &Name() const = 0;
      virtual bool Match(const CType &type) const;
    };
    
    
    class CTypeInternal : public CType {
    public:
      enum TType {
        TYPE_BITSTING,
        TYPE_BOOLEAN,
        TYPE_CHARSTRING,
        TYPE_UNIVERSAL_CHARSTRING,
        TYPE_INTEGER,
        TYPE_OCTETSTRING,
        TYPE_HEXSTRING,
        TYPE_VERDICT,
        TYPE_FLOAT,
        TYPE_ADDRESS,
        TYPE_DEFAULT,
        TYPE_ANY_TYPE
      };
      
    private:
      static CTypeInternal _bitstring;
      static CTypeInternal _boolean;
      static CTypeInternal _charstring;
      static CTypeInternal _universalCharstring;
      static CTypeInternal _integer;
      static CTypeInternal _octetstring;
      static CTypeInternal _hexstring;
      static CTypeInternal _verdict;
      static CTypeInternal _float;
      static CTypeInternal _address;
      static CTypeInternal _default;
      static CTypeInternal _anyType;
      
      const TType _type;
      std::string _name;
      
    public:
      static const CTypeInternal &Bitstring();
      static const CTypeInternal &Boolean();
      static const CTypeInternal &Charstring();
      static const CTypeInternal &UniversalCharstring();
      static const CTypeInternal &Integer();
      static const CTypeInternal &Octetstring();
      static const CTypeInternal &Hexstring();
      static const CTypeInternal &Verdict();
      static const CTypeInternal &Float();
      static const CTypeInternal &Address();
      static const CTypeInternal &Default();
      static const CTypeInternal &AnyType();
      
      CTypeInternal(TType type);

      virtual const std::string &Name() const;
      
      //      bool ValueVerify(const char *value);
      //      const CTypeInternal &Add(const CTypeInternal &type);
    };
    
    
    class CTypeReferenced : public CType {
      const std::string &_name;
    public:
      CTypeReferenced(const std::string &name);
      virtual const std::string &Name() const;
      virtual void Dump(CDumper &dumper) = 0;
    };
    
    
    class CTypeStructured : public CTypeReferenced {
    public:
      class CField {
        const CType &_type;
        const std::auto_ptr<const CIdentifier> _id;
        const bool _optional;
      public:
        CField(const CType &type, const CIdentifier *id, bool optional);
        const CType &Type() const;
        const CIdentifier &Id() const;
        bool Optional() const;
      };
      
    private:
      typedef std::map<const std::string *, const CField *, CPtrCmp> CFieldMap;
      CFieldMap _fieldMap;
      
    public:
      CTypeStructured(const std::string &name);
      ~CTypeStructured();
      virtual void Dump(CDumper &dumper);
      virtual void Register(const CField *field);
    };
    
  } // namespace translator

} // namespace freettcn


#endif  // __TYPE_H__
