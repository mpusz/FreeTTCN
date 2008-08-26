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

#include <freettcn/te/type.h>
#include <vector>


namespace freettcn {

  namespace TE {
    
    class CRecordType : public CType {
    public:
      class CInstance : public CType::CInstance {
        typedef std::vector<CType::CInstance *> CFieldArray;
        CFieldArray _fieldArray;
        
      public:
        CInstance(const CType &type);
        ~CInstance();
        
        void Register(CType::CInstance *field);
        
//         unsigned int FieldNum() const;
        CType::CInstance &Field(const char *fieldName) const;
        CType::CInstance &Field(unsigned int fieldIdx) const;
        char const * const * FieldNames() const;
      };
      
    private:
      class CFieldData {
        const CType &_type;
        const char *_name;
        const bool _optional;
      public:
        CFieldData(const CType &type, const char *name, bool optional);
        const CType &Type() const;
        const char *Name() const;
        bool Optional() const;
      };
      typedef std::vector<CFieldData *> CFieldDataArray;
      CFieldDataArray _fieldDataArray;
      char **_fieldNames;
      
      unsigned int FieldIdx(const char *fieldName) const;
      
    protected:
      void Register(const CType &type, const char *name, bool optional = false);
      void Init();
      
    public:
      friend class CInstance;
      
      CRecordType(const CModule    &module,
                  const char       *name,
                  String           encoding,
                  String           encodingVariant,
                  String           extension);
      ~CRecordType();
      virtual CInstance *InstanceCreate() const;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __RECORD_H__ */
