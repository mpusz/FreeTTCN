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
 * @file   record.h
 * @author Mateusz Pusz
 * @date   Tue May 22 07:52:06 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __RECORD_H__
#define __RECORD_H__

#include <freettcn/ttcn3/tciType.h>
#include <freettcn/tools/tools.h>
#include <map>

namespace freettcn {

  class CTypeRecord : public CType {
  public:
    typedef std::vector<Tstring *> CFieldNames;
      
    class CValue : public ORG_ETSI_TTCN3_TCI::RecordValue, public CType::CValue {
      typedef std::map<const Tstring *, std::shared_ptr<TciValue>, CPtrCmp> CFieldMap;
        
      const CFieldNames &_fieldNames;
      CFieldMap _fieldMap;

    protected:
      CValue(const CValue &src);
        
    public:
      explicit CValue(const std::shared_ptr<const CTypeRecord> &type);
      CValue(CValue &&) = default;
      ~CValue() = default;
      RecordValue *clone() const override                        { return new CValue(*this); }
        
      const TciValue &getField(const Tstring &p_field_name) const override;
      void setField(const Tstring &p_field_name, const TciValue &p_new_value) override;
      const CFieldNames &getFieldNames() const override          { return _fieldNames; }
      void setFieldOmitted(const Tstring &fieldName) override;
        
      Tboolean operator==(const TciValue &val) const override    { return val.operator==(*this); }
      Tboolean operator==(const RecordValue &rec) const override;
      Tboolean operator<(const TciValue &val) const override     { return !val.operator<(*this) && !val.operator==(*this); }
      Tboolean operator<(const RecordValue &rec) const override;
    };
      
  private:
    class CFieldData {
      CType *_type;
      Tstring _name;
      bool _optional;
    public:
      CFieldData(CType &type, const Tstring &name, bool optional):
        _type(&type), _name(name), _optional(optional) {}
      CFieldData(const CFieldData &) = default;
      CFieldData(CFieldData &&) = default;
      ~CFieldData() = default;
      CFieldData &operator=(const CFieldData &) = default;
        
      CType &Type() const         { return *_type; }
      const Tstring &Name() const { return _name; }
      Tstring &Name()             { return _name; }
      bool Optional() const       { return _optional; }
    };
      
    typedef std::vector<CFieldData> CFieldDataArray;
    CFieldDataArray _fieldDataArray;
    CFieldNames _fieldNames;
      
  protected:
    CTypeRecord(const CTypeRecord &) = default;
    void Add(CType &fieldType, const Tstring &fieldName, bool optional = false);
      
  public:
    CTypeRecord(const std::shared_ptr<const TciModuleId> &moduleId,
                const Tstring      &name,
                const Tstring      &encoding,
                const Tstring      &encodingVariant,
                const CExtension   &extension,
                size_t             fieldNum);
    CTypeRecord(CTypeRecord &&) = default;
    ~CTypeRecord() = default;
    TciType *clone() const override  { return new CTypeRecord(*this); }
    TciValue *newInstance() override { return new CValue(std::shared_ptr<const CTypeRecord>(new CTypeRecord(*this))); }
  };
    
} // namespace freettcn


#endif /* __RECORD_H__ */
