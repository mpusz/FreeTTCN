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

/**
 * @mainpage The FreeTTCN API documentation
 *
 * Abbreviations:
 *
 * @b MTC   - Main Test Component @n
 * @b PA    - Platform Adapter @n
 * @b SA    - SUT Adapter @n
 * @b SUT   - System Under Test @n
 * @b TC    - Test Control @n
 * @b TCI   - TTCN-3 Control Interface @n
 * @b TE    - TTCN-3 Executable @n
 * @b TM    - Test Management @n
 * @b TRI   - TTCN-3 Runtime Interface @n
 * @b TSI   - Test System Interface @n
 * @b TTCN  - Testing and Test Control Notation
 * 
 */


/**
 * @defgroup TTCN3InterfaceTypes TTCN-3 interface types
 * @{
 */

typedef struct BinaryString {
  unsigned char* data;
  long int bits;
  void* aux;
} BinaryString;


typedef struct QualifiedName {
  char* moduleName;
  char* objectName;
  void* aux;
} QualifiedName;


typedef unsigned char Boolean;

typedef char* String;

/**
 * @todo 'Double' type not in specification
 */
typedef double Double;

/// @} TTCN3InterfaceTypes


#endif /* __TYPES_H__ */
