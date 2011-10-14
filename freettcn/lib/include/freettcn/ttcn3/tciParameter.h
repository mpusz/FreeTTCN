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
 * @file   tciParameter.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TCI_PARAMETER_H__
#define __TCI_PARAMETER_H__

#include <freettcn/etsi/tci.h>
#include <freettcn/tools/nonAssignable.h>
#include <memory>


namespace freettcn {

  namespace ttcn3 {
    
    using namespace ORG_ETSI_TTCN3_TCI;

    class CTciParameter : CNonAssignable, public ORG_ETSI_TTCN3_TCI::TciParameter {
      std::shared_ptr<const Tstring> _name;
      TciParameterPassingMode _passingMode;
      std::shared_ptr<const TciValue> _value;
      
    public:
      CTciParameter(const Tstring &name, TciParameterPassingMode passingMode, const TciValue &value):
        _name(new Tstring(name)), _passingMode(passingMode), _value(value.clone()) {}
      CTciParameter(const CTciParameter &) = default;
      CTciParameter(CTciParameter &&) = default;
      ~CTciParameter() = default;
      TciParameter *clone() const override                                        { return new CTciParameter(*this); }
      
      const TciValue &getValue() const override                                   { return *_value; }
      void setValue(TciValue &value) override                                     { _value.reset(value.clone()); }
      const TciParameterPassingMode &getParameterPassingMode() const override     { return _passingMode; }
      void setParameterPassingMode(const TciParameterPassingMode &mode) override  { _passingMode = mode; }
      const Tstring &getParameterName() const override                            { return *_name; }
      void setParameterName(const Tstring &name) override                         { _name.reset(new Tstring(name)); }
      
      Tboolean operator==(const TciParameter &param) const override               { return *_name == param.getParameterName(); }
      Tboolean operator<(const TciParameter &param) const override                { return *_name < param.getParameterName(); }
    };

  } // namespace ttcn3
  
} // namespace freettcn


#endif /* __TCI_PARAMETER_H__ */
