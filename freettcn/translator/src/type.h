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
      virtual void Dump(CDumper &dumper) const = 0;
      virtual bool Resolved() const = 0;
      virtual bool Resolve() = 0;
      virtual bool Match(const CType &type) const;
    };
    
    
    class CTypePredefined : public CType {
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
      static CTypePredefined _bitstring;
      static CTypePredefined _boolean;
      static CTypePredefined _charstring;
      static CTypePredefined _universalCharstring;
      static CTypePredefined _integer;
      static CTypePredefined _octetstring;
      static CTypePredefined _hexstring;
      static CTypePredefined _verdict;
      static CTypePredefined _float;
      static CTypePredefined _address;
      static CTypePredefined _default;
      static CTypePredefined _anyType;
      
      const TType _type;
      std::string _name;
      
    public:
      static CTypePredefined &Bitstring();
      static CTypePredefined &Boolean();
      static CTypePredefined &Charstring();
      static CTypePredefined &UniversalCharstring();
      static CTypePredefined &Integer();
      static CTypePredefined &Octetstring();
      static CTypePredefined &Hexstring();
      static CTypePredefined &Verdict();
      static CTypePredefined &Float();
      static CTypePredefined &Address();
      static CTypePredefined &Default();
      static CTypePredefined &AnyType();
      
      CTypePredefined(TType type);

      virtual const std::string &Name() const;
      virtual void Dump(CDumper &dumper) const;
      virtual bool Resolved() const;
      virtual bool Resolve();
      
      //      bool ValueVerify(const char *value);
      //      const CTypePredefined &Add(const CTypePredefined &type);
    };
    
    
    class CTypeReferenced : public CType {
      
      class CTypeUnresolved : public CType {
        const std::auto_ptr<const CIdentifier> _id;
      public:
        CTypeUnresolved(const CIdentifier *id);
        virtual const std::string &Name() const;
        virtual void Dump(CDumper &dumper) const;
        virtual bool Resolved() const;
        virtual bool Resolve();
      };
      
      CType *_type;
      bool _typeUnresolved;
      
    public:
      CTypeReferenced(CType &type);
      CTypeReferenced(const CIdentifier *id);
      ~CTypeReferenced();
      virtual const std::string &Name() const;
      virtual void Dump(CDumper &dumper) const;
      virtual bool Resolved() const;
      virtual bool Resolve();
    };
    
    
    class CTypeLocal : public CType {
      const std::string _name;
    public:
      CTypeLocal(const std::string &name);
      virtual const std::string &Name() const;
    };
    
    
    class CTypeStructured : public CTypeLocal {
    public:
      class CField {
        CType &_type;
        const std::auto_ptr<const CIdentifier> _id;
        const bool _optional;
      public:
        CField(CType &type, const CIdentifier *id, bool optional);
        CType &Type() const;
        const CIdentifier &Id() const;
        bool Optional() const;
      };
      
    private:
      typedef std::map<const std::string *, CField *, CPtrCmp> CFieldMap;
      CFieldMap _fieldMap;
      
    public:
      CTypeStructured(const std::string &name);
      ~CTypeStructured();
      virtual void Dump(CDumper &dumper) const;
      virtual void Register(CField *field);
      virtual bool Resolved() const;
      virtual bool Resolve();
    };
    
    
    class CTypeRecord : public CTypeStructured {
      typedef std::deque<const CField *> CFieldList;
      CFieldList _fieldList;
    public:
      CTypeRecord(const std::string &name);
      virtual void Dump(CDumper &dumper) const;
      virtual void Register(CField *field);
    };
    
  } // namespace translator

} // namespace freettcn


#endif  // __TYPE_H__
