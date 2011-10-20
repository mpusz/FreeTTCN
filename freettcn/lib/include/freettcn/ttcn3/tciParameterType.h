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
 * @file   tciParameterType.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TCI_PARAMETER_TYPE_H__
#define __TCI_PARAMETER_TYPE_H__

#include <freettcn/etsi/tci.h>
#include <freettcn/tools/nonAssignable.h>
#include <memory>


namespace freettcn {

  using namespace ORG_ETSI_TTCN3_TCI;

  class CTciParameterType : CNonAssignable, public ORG_ETSI_TTCN3_TCI::TciParameterType {
    std::shared_ptr<const TciType> _type;
    TciParameterPassingMode _passingMode;
    CTciParameterType(const CTciParameterType &) = default;
  public:
    CTciParameterType(const TciType &type, TciParameterPassingMode passingMode): _type(type.clone()), _passingMode(passingMode) {}
    CTciParameterType(CTciParameterType &&) = default;
    ~CTciParameterType() = default;
    TciParameterType *clone() const override                                    { return new CTciParameterType(*this); }
      
    const TciType &getType() const override                                     { return *_type; }
    const TciParameterPassingMode &getParameterPassingMode() const override     { return _passingMode; }
      
    Tboolean operator==(const TciParameterType &parType) const override         { return _passingMode == parType.getParameterPassingMode() && *_type == parType.getType(); }
    Tboolean operator<(const TciParameterType &parType) const override          { return _passingMode < parType.getParameterPassingMode() && *_type < parType.getType(); }
  };

} // namespace freettcn


#endif /* __TCI_PARAMETER_TYPE_H__ */
