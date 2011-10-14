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
 * @file   verdict.h
 * @author Mateusz Pusz
 * @date   Sun May 13 19:34:48 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __VERDICT_H__
#define __VERDICT_H__

#include <freettcn/ttcn3/tciType.h>

namespace freettcn {
  
  namespace ttcn3 {
    
    class CTypeVerdict : public CType {
    public:
      class CValue : public ORG_ETSI_TTCN3_TCI::VerdictValue, public CType::CValue {
        VerdictValueEnum _value;

      protected:
        CValue(const CValue &) = default;
        CValue(CValue &&) = default;
        
      public:
        explicit CValue(const TciType &type, VerdictValueEnum value = NONE): CType::CValue(type, "", ""), _value(value) {}
        ~CValue() = default;
        VerdictValue *clone() const override                           { return new CValue(*this); }
        
        const VerdictValueEnum &getVerdict() const override            { return _value; }
        void setVerdict(const VerdictValueEnum &p_enum) override       { _value = p_enum; }
        
        Tboolean operator==(const TciValue &val) const override        { return val.operator==(*this); }
        Tboolean operator==(const VerdictValue &verdictVal) const override { return _value == verdictVal.getVerdict(); }
        Tboolean operator<(const TciValue &val) const override         { return !val.operator<(*this) && !val.operator==(*this); }
        Tboolean operator<(const VerdictValue &verdictVal) const override  { return _value < verdictVal.getVerdict(); }
      };
      
      CTypeVerdict();
      ~CTypeVerdict() = default;
      TciType *clone() const override  { return new CTypeVerdict; }
      TciValue *newInstance() override { return new CValue(*this); }
    };
    
  } // namespace ttcn3
  
} // namespace freettcn

#endif /* __VERDICT_H__ */
