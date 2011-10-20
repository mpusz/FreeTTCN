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
 * @file   boolean.h
 * @author Mateusz Pusz
 * @date   Fri May  4 09:10:30 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __BOOLEAN_H__
#define __BOOLEAN_H__

#include <freettcn/ttcn3/tciType.h>

namespace freettcn {

  class CTypeBoolean : public CType {
  public:
    class CValue : public ORG_ETSI_TTCN3_TCI::BooleanValue, public CType::CValue {
      Tboolean _value;

    protected:
      CValue(const CValue &) = default;

    public:
      explicit CValue(const std::shared_ptr<const TciType> &type, Tboolean value = false): CType::CValue(type, "", ""), _value(value) {}
      CValue(CValue &&) = default;
      ~CValue() = default;
      BooleanValue *clone() const override              { return new CValue(*this); }
        
      Tboolean getBoolean() const override              { return _value; }
      void setBoolean(Tboolean p_booleanValue) override { _value = p_booleanValue; }
        
      Tboolean operator==(const TciValue &val) const override            { return val.operator==(*this); }
      Tboolean operator==(const BooleanValue &booleanVal) const override { return _value == booleanVal.getBoolean(); }
      Tboolean operator<(const TciValue &val) const override             { return !val.operator<(*this) && !val.operator==(*this); }
      Tboolean operator<(const BooleanValue &booleanVal) const override  { return _value < booleanVal.getBoolean(); }
    };
    
  private:
    static std::shared_ptr<CTypeBoolean> _instance;
    
  protected:
    CTypeBoolean(const CTypeBoolean &) = default;
    
  public:
    CTypeBoolean();
    CTypeBoolean(CTypeBoolean &&) = default;
    ~CTypeBoolean() = default;
    TciType *clone() const override  { return new CTypeBoolean(*this); }
    TciValue *newInstance() override { return new CValue(_instance); }
  };
    
} // namespace freettcn

#endif /* __BOOLEAN_H__ */
