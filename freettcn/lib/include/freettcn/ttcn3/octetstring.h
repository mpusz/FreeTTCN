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
 * @file   octetstring.h
 * @author Mateusz Pusz
 * @date   Tue May 22 22:16:17 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __OCTETSTRING_H__
#define __OCTETSTRING_H__

#include <freettcn/ttcn3/tciType.h>

namespace freettcn {

  class CTypeOctetstring : public CType {
  public:
    class CValue : public ORG_ETSI_TTCN3_TCI::OctetstringValue, public CType::CValue {
      std::shared_ptr<Tstring> _value;

    protected:
      CValue(const CValue &) = default;
        
    public:
      explicit CValue(const std::shared_ptr<const TciType> &type, Tstring value = ""): CType::CValue(type, "", ""), _value(new Tstring(value)) {}
      CValue(CValue &&) = default;
      ~CValue() = default;
      OctetstringValue *clone() const override                  { return new CValue(*this); }
        
      Tsize getLength() const override                          { return _value->size(); }
#ifdef ISSUE_0005945
      const Tinteger getOctet(Tindex p_position) const override { return _value->at(p_position); }
#else
      const Tchar getOctet(Tindex p_position) const override    { return _value->at(p_position); }
#endif
      const Tstring &getString() const override                 { return *_value; }
      void setLength(Tsize p_length) override;
#ifdef ISSUE_0005945
      void setOctet(Tindex p_position, Tinteger p_ochar) override;
#else
      void setOctet(Tindex p_position, Tchar p_ochar) override;
#endif
      void setString(const Tstring &p_osValue) override;
        
      Tboolean operator==(const TciValue &val) const override            { return val.operator==(*this); }
      Tboolean operator==(const OctetstringValue &octStr) const override { return *_value == octStr.getString(); }
      Tboolean operator<(const TciValue &val) const override             { return !val.operator<(*this) && !val.operator==(*this); }
      Tboolean operator<(const OctetstringValue &octStr) const override  { return *_value < octStr.getString(); }
    };
      
  private:
    static std::shared_ptr<CTypeOctetstring> _instance;
    
  protected:
    CTypeOctetstring(const CTypeOctetstring &) = default;
    
  public:
    CTypeOctetstring();
    CTypeOctetstring(CTypeOctetstring &&) = default;
    ~CTypeOctetstring() = default;
    TciType *clone() const override  { return new CTypeOctetstring; }
    TciValue *newInstance() override { return new CValue(_instance); }
  };
    
} // namespace freettcn

#endif /* __OCTETSTRING_H__ */
