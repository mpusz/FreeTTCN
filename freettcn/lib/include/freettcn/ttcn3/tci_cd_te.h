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
 * @file   tci_cd_te.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:51:37 2007
 * 
 * @brief  TTCN-3 Executable CD => TE operation interface (TCI-CD required)
 * 
 * This header specifies the operations the CD requires from the TE. All operations specified in this file are also
 * required at the TCI-TM and TCI-CH interfaces.
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 *
 */

#ifndef __TCI_CD_TE_H__
#define __TCI_CD_TE_H__

#include <freettcn/ttcn3/tci.h>


/**
 * @addtogroup Tci TCI
 * @{
 */

/**
 * @addtogroup TciInterface Interface
 * @{
 */

/**
 * @addtogroup TciInterfaceCD The TCI-CD interface
 * @{
 */

/**
 * @defgroup TciInterfaceCDRequired TCI-CD required
 * @{
 */


/** 
 * @brief Returns a type representing a TTCN-3 type.
 * 
 * Returns a type representing a TTCN-3 type. Predefined TTCN-3 types can be retrieved from the TE
 * by using the TTCN-3 keywords for the predefined types. In this case @p typeName denotes to the
 * basic TTCN-3 type like "charstring", "bitstring" etc.
 * Returns the distinct value @c null if the requested type can not be returned. Note that the @c anytype
 * and @c address can not be obtained with module set to @c null. Although they are predefined types
 * they might be distinct between modules. For example, @c address can either be the unmodified
 * predefined type, or a user-defined type in a module. Other predefined types can not be redefined.
 * 
 * @param typeName The TTCN-3 name of the type as defined in the TTCN-3 module. The following
 *                 are reserved type names and will return a predefined type:
 *                 - "integer"
 *                 - "float"
 *                 - "bitstring"
 *                 - "hexstring"
 *                 - "octetstring"
 *                 - "charstring"
 *                 - "universal charstring"
 *                 - "boolean"
 *                 - "verdicttype"
 *                 - "objid" @n
 *                 @p typeName has to be the fully qualified type name, i.e. @c module.typeName
 * 
 * @return A type representing the requested TTCN-3 type.
 */
TciType tciGetTypeForName(String typeName);


/** 
 * @brief Constructs and returns a basic TTCN-3 integer type.
 * 
 * Constructs and returns a basic TTCN-3 integer type.
 * 
 * @return An instance of Type representing a TTCN-3 integer type.
 */
TciType tciGetIntegerType();


/** 
 * @brief Constructs and returns a basic TTCN-3 float type.
 * 
 * Constructs and returns a basic TTCN-3 float type.
 * 
 * @return An instance of Type representing a TTCN-3 float type.
 */
TciType tciGetFloatType();


/** 
 * @brief Constructs and returns a basic TTCN-3 boolean type.
 * 
 * Constructs and returns a basic TTCN-3 boolean type.
 * 
 * @return An instance of Type representing a TTCN-3 boolean type.
 */
TciType tciGetBooleanType();


/** 
 * @brief Constructs and returns a basic TTCN-3 object id type.
 * 
 * Constructs and returns a basic TTCN-3 object id type.
 * 
 * @return An instance of Type representing a TTCN-3 object id type.
 */
TciType tciGetTciObjidType();


/**
 *  @todo No description in the TTCN-3 specification
 */
TciType tciGetCharType();


/**
 *  @todo No description in the TTCN-3 specification
 */
TciType tciGetUniversalCharType();


/** 
 * @brief Constructs and returns a basic TTCN-3 charstringtype.
 * 
 * Constructs and returns a basic TTCN-3 charstringtype.
 * 
 * @return An instance of Type representing a TTCN-3 charstring type.
 */
TciType tciGetTciCharstringType();


/** 
 * @brief Constructs and returns a basic TTCN-3 universal charstring type.
 * 
 * Constructs and returns a basic TTCN-3 universal charstring type.
 * 
 * @return An instance of Type representing a TTCN-3 universal charstring type.
 */
TciType tciGetUniversalCharstringType();


/** 
 * @brief Constructs and returns a basic TTCN-3 hexstring type.
 * 
 * Constructs and returns a basic TTCN-3 hexstring type.
 * 
 * @return An instance of Type representing a TTCN-3 hexstring type.
 */
TciType tciGetHexstringType();


/** 
 * @brief Constructs and returns a basic TTCN-3 bitstring type.
 * 
 * Constructs and returns a basic TTCN-3 bitstring type.
 * 
 * @return An instance of Type representing a TTCN-3 bitstring type.
 */
TciType tciGetBitstringType();


/** 
 * @brief Constructs and returns a basic TTCN-3 octetstring type.
 * 
 * Constructs and returns a basic TTCN-3 octetstring type.
 * 
 * @return An instance of Type representing a TTCN-3 octetstring type.
 */
TciType tciGetOctetstringType();


/** 
 * @brief Constructs and returns a basic TTCN-3 verdict type.
 * 
 * Constructs and returns a basic TTCN-3 verdict type.
 * 
 * @return An instance of Type representing a TTCN-3 verdict type.
 */
TciType tciGetVerdictType();


/** 
 * @brief The TE will be notified about an unrecoverable error situation.
 * 
 * The TE will be notified about an unrecoverable error situation within the CD and forward the
 * error indication to the test management.
 * 
 * @remarks Shall be called whenever an error situation has occurred.
 * 
 * @param message A string value, i.e. the error phrase describing the problem.
 */
void tciErrorReq(String message);


/// @} TciInterfaceCDRequired

/// @} TciInterfaceCD

/// @} TciInterface

/// @} Tci


#endif /* __TCI_CD_TE_H__ */
