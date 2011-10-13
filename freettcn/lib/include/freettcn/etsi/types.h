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
 * @file   types.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 08:54:53 2007
 * 
 * @brief  TTCN-3 Executable basic types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-5: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 5: TTCN-3 Runtime Interface (TRI)"
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 *
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>

/**
 * @defgroup TTCN3InterfaceTypes TTCN-3 interface types
 * @{
 */
typedef bool Tboolean;
typedef long int Tinteger;
typedef unsigned long int Tsize;
typedef unsigned long int Tindex;
typedef double Tfloat;
typedef std::string Tstring;
typedef std::wstring TuniversalString;
typedef unsigned char Tbit;

typedef unsigned char Tbyte;

typedef unsigned char Tchar; /// @todo Type not defined in spec 

/// @} TTCN3InterfaceTypes


namespace ORG_ETSI_TTCN3_TRI {

  class QualifiedName {
  public:
    ~QualifiedName();
    const Tstring &getModuleName() const;
    void setModuleName(const Tstring &mName);
    const Tstring &getObjectName() const;
    void setObjectName(const Tstring &oName);
    Tstring toString() const;
    Tboolean equals(const QualifiedName &qn) const;
    QualifiedName *cloneQualifiedName() const;
    Tboolean operator<(const QualifiedName &qn) const;
  };

} // namespace ORG_ETSI_TTCN3_TRI


#endif /* __TYPES_H__ */
