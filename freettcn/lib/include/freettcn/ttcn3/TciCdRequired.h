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
 * @file   TciCdRequired.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:50:45 2007
 * 
 * @brief  TTCN-3 Executable TCI types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 * 
 */

#ifndef __TCI_CD_REQUIRED_H__
#define __TCI_CD_REQUIRED_H__

#include <freettcn/ttcn3/tci.h>

namespace ORG_ETSI_TTCN3_TCI {
  
  class TciCdRequired {
  public:
    //Destructor
    virtual ~TciCdRequired();
    //Returns a type representing a ttcn type
    virtual const TciType *getTypeForName(const Tstring typeName) const = 0;
    //Constructs and returns a basic TTCN-3 integer type
    virtual const TciType &getInteger() const = 0;
    //Constructs and returns a basic TTCN-3 float type
    virtual const TciType &getFloat() const = 0;
    //Constructs and returns a basic TTCN-3 boolean type
    virtual const TciType &getBoolean() const = 0;
    //Constructs and returns a basic TTCN-3 charstring type
    virtual const TciType &getCharstring() const = 0;
    //Constructs and returns a basic TTCN-3 universal charstring type
    virtual const TciType &getUniversalCharstring() const = 0;
    //Constructs and returns a basic TTCN-3 hexstring type
    virtual const TciType &getHexstring() const = 0;
    //Constructs and returns a basic TTCN-3 bitstring type
    virtual const TciType &getBitstring() const = 0;
    //Constructs and returns a basic TTCN-3 octetstring type
    virtual const TciType &getOctetstring() const = 0;
    //Constructs and returns a basic TTCN-3 verdict type
    virtual const TciType &getVerdict() const = 0;
    //The TE will be notified about an unrecoverable error situation within the CD
    virtual void tciErrorReq(const Tstring message) = 0;
  };
  
} // namespace ORG_ETSI_TTCN3_TCI

#endif /* __TCI_CD_REQUIRED_H__ */
