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

#include "location.h"
#include "freettcn/tools/tools.h"
#include <string>
#include <array>
#include <map>
#include <memory>


namespace freettcn {

  namespace translator {

    class CIdentifier;
    class CDumper;

    class CType {
    public:
      enum TKind {
        KIND_UNRESOLVED         = 0x0000,
        KIND_TYPE_PREDEFINED    = 0x0001 << 0,
        KIND_TYPE_RECORD        = 0x0001 << 1,
        KIND_TYPE_SET           = 0x0001 << 2,
        KIND_TYPE_UNION         = 0x0001 << 3,
        KIND_TYPE               = 0x000F,
        KIND_PORT               = 0x0001 << 4,
        KIND_COMPONENT          = 0x0001 << 5,
        KIND_ANY                = 0xFFFF
      };
      
    private:
      CType(const CType &);                       /**< @brief Disallowed */
      CType &operator=(const CType &);            /**< @brief Disallowed */
      
    public:
      static std::string KindToString(TKind kind);
      
      CType();
      virtual ~CType() = 0;
      virtual TKind Kind() const = 0;
      virtual const std::string &Name() const = 0;
      virtual void Dump(CDumper &dumper) const = 0;
      virtual bool Resolved() const = 0;
      virtual bool Resolve(TKind kind, const std::string &ownerInstanceStr) = 0;
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
      typedef std::array<std::shared_ptr<CTypePredefined>, 12> CTypeArray;
      static CTypeArray _array;

      const TType _type;
      std::string _name;
      
    public:
      static std::shared_ptr<CTypePredefined> Bitstring();
      static std::shared_ptr<CTypePredefined> Boolean();
      static std::shared_ptr<CTypePredefined> Charstring();
      static std::shared_ptr<CTypePredefined> UniversalCharstring();
      static std::shared_ptr<CTypePredefined> Integer();
      static std::shared_ptr<CTypePredefined> Octetstring();
      static std::shared_ptr<CTypePredefined> Hexstring();
      static std::shared_ptr<CTypePredefined> Verdict();
      static std::shared_ptr<CTypePredefined> Float();
      static std::shared_ptr<CTypePredefined> Address();
      static std::shared_ptr<CTypePredefined> Default();
      static std::shared_ptr<CTypePredefined> AnyType();
      
      CTypePredefined(TType type);

      virtual const std::string &Name() const;
      virtual TKind Kind() const;
      virtual void Dump(CDumper &dumper) const;
      virtual bool Resolved() const;
      virtual bool Resolve(TKind kind, const std::string &ownerInstanceStr);
      
      //      bool ValueVerify(const char *value);
      //      const CTypePredefined &Add(const CTypePredefined &type);
    };
    
    
    class CTypeReferenced : public CType {
      
      class CTypeUnresolved : public CType {
        const std::shared_ptr<const CIdentifier> _id;
      public:
        CTypeUnresolved(std::shared_ptr<const CIdentifier> id);
        virtual TKind Kind() const;
        virtual const std::string &Name() const;
        virtual void Dump(CDumper &dumper) const;
        virtual bool Resolved() const;
        virtual bool Resolve(TKind kind, const std::string &ownerInstanceStr);
        const CIdentifier &Id() const;
      };
      
      std::shared_ptr<CType> _type;
      bool _typeUnresolved;
      
    public:
      ~CTypeReferenced();
      CTypeReferenced(std::shared_ptr<CType> type);
      CTypeReferenced(std::shared_ptr<const CIdentifier> id);
      virtual TKind Kind() const;
      virtual const std::string &Name() const;
      virtual void Dump(CDumper &dumper) const;
      virtual bool Resolved() const;
      virtual bool Resolve(TKind kind, const std::string &ownerInstanceStr);
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
        std::shared_ptr<CType> _type;
        const std::shared_ptr<const CIdentifier> _id;
        const bool _optional;
      public:
        CField(std::shared_ptr<CType> type, std::shared_ptr<const CIdentifier> id, bool optional);
        CType &Type() const;
        const CIdentifier &Id() const;
        //        bool Optional() const;
      };
      
    private:
      typedef std::map<const std::string *, std::shared_ptr<const CField>, CPtrCmp> CFieldMap;
      CFieldMap _fieldMap;
      
    public:
      CTypeStructured(const std::string &name);
      ~CTypeStructured();
      virtual TKind Kind() const;
      virtual void Dump(CDumper &dumper) const;
      virtual void Register(std::shared_ptr<CField> field);
      virtual bool Resolved() const;
      virtual bool Resolve(TKind kind, const std::string &ownerInstanceStr);
    };
    
    
    class CTypeRecord : public CTypeStructured {
      typedef std::deque<std::shared_ptr<const CField>> CFieldList;
      CFieldList _fieldList;
    public:
      CTypeRecord(const std::string &name);
      virtual TKind Kind() const;
      virtual void Dump(CDumper &dumper) const;
      virtual void Register(std::shared_ptr<CField> field);
    };
    
    
    class CTypeUnion : public CTypeStructured {
    public:
      CTypeUnion(const std::string &name);
      virtual TKind Kind() const;
      virtual void Dump(CDumper &dumper) const;
    };
    
    
    class CTypePort : public CTypeLocal {
    public:
      enum TMode {
        MODE_MESSAGE,
        MODE_PROCEDURE,
        MODE_MIXED
      };
      
      enum TDirection {
        DIRECTION_IN,
        DIRECTION_OUT,
        DIRECTION_INOUT
      };
      
      class CItem {
      private:
        const CLocation _loc;                     /**< @brief Location in a file */
        CType *_type;                             /**< @brief Item type or 0 if 'all' */
        
      public:
        CItem(const CLocation &loc, CType &type);
        CItem(const CLocation &loc);
        const CLocation &Loc() const;
        bool All() const;
        CType &Type() const;
      };
      
    private:
      typedef std::map<const std::string, std::shared_ptr<const CItem>> CItemMap;
      typedef std::deque<std::shared_ptr<const CItem>> CItemList;
      const TMode _mode;
      CItemList _itemList;
      CItemMap _inItemMap;
      CItemMap _outItemMap;
      
    public:
      CTypePort(const std::string &name, TMode mode);
      ~CTypePort();
      virtual TKind Kind() const;
      virtual TMode Mode() const;
      virtual void Dump(CDumper &dumper) const;
      virtual void Register(std::shared_ptr<CItem> item, TDirection dir);
      virtual bool Resolved() const;
      virtual bool Resolve(TKind kind, const std::string &ownerInstanceStr);
    };
    
  } // namespace translator

} // namespace freettcn


#endif  // __TYPE_H__
