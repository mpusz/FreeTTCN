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
 * @file   tciModuleParameter.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TCI_MODULE_PARAMETER_H__
#define __TCI_MODULE_PARAMETER_H__

#include <freettcn/etsi/tci.h>
#include <freettcn/tools/nonAssignable.h>
#include <memory>


namespace freettcn {

  using namespace ORG_ETSI_TTCN3_TCI;

  class CTciModuleParameter : CNonAssignable, public ORG_ETSI_TTCN3_TCI::TciModuleParameter {
    std::shared_ptr<const TciModuleParameterId> _id;
    std::shared_ptr<const TciValue> _defaultValue;
    CTciModuleParameter(const CTciModuleParameter &) = default;
      
  public:
    CTciModuleParameter(std::shared_ptr<const TciModuleParameterId> id,
                        std::shared_ptr<const TciValue> defaultValue):
      _id(id), _defaultValue(defaultValue) {}
    CTciModuleParameter(CTciModuleParameter &&) = default;
    ~CTciModuleParameter() = default;
    TciModuleParameter *clone() const override                           { return new CTciModuleParameter(*this); }
      
    const TciValue &getDefaultValue() const override                     { return *_defaultValue; }
    const Tstring &getModuleParameterName() const override               { return _id->getObjectName(); }
    const TciModuleParameterId &getTciModuleParameterId() const override { return *_id; }
      
    Tboolean operator==(const TciModuleParameter &mpar) const override   { return *_id == mpar.getTciModuleParameterId(); }
    Tboolean operator<(const TciModuleParameter &mpar) const override    { return *_id < mpar.getTciModuleParameterId(); }
  };

} // namespace freettcn


#endif /* __TCI_MODULE_PARAMETER_H__ */
