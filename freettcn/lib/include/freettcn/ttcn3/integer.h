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
 * @file   integer.h
 * @author Mateusz Pusz
 * @date   Mon May 14 21:34:08 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <freettcn/ttcn3/tciType.h>

namespace freettcn {
  
  class CTypeInteger : public CType {
  public:
    class CValue : public ORG_ETSI_TTCN3_TCI::IntegerValue, public CType::CValue {
      Tinteger _value;
        
    protected:
      CValue(const CValue &) = default;
        
    public:
      explicit CValue(const std::shared_ptr<const TciType> &type, Tinteger value = 0): CType::CValue(type, "", ""), _value(value) {}
      CValue(CValue &&) = default;
      ~CValue() = default;
      IntegerValue *clone() const override   { return new CValue(*this); }
        
      Tinteger getInt() const override       { return _value; }
      void setInt(Tinteger p_value) override { _value = p_value; }
        
      Tboolean operator==(const TciValue &val) const override        { return val.operator==(*this); }
      Tboolean operator==(const IntegerValue &intVal) const override { return _value == intVal.getInt(); }
      Tboolean operator<(const TciValue &val) const override         { return !val.operator<(*this) && !val.operator==(*this); }
      Tboolean operator<(const IntegerValue &intVal) const override  { return _value < intVal.getInt(); }
    };
    
  private:
    static std::shared_ptr<CTypeInteger> _instance;
    
  protected:
    CTypeInteger(const CTypeInteger &) = default;
    
  public:
    CTypeInteger();
    CTypeInteger(CTypeInteger &&) = default;
    ~CTypeInteger() = default;
    TciType *clone() const override  { return new CTypeInteger(*this); }
    TciValue *newInstance() override { return new CValue(_instance); }
  };
    
} // namespace freettcn

#endif /* __INTEGER_H__ */
