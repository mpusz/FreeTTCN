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
 * @file   tri.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 08:55:41 2007
 * 
 * @brief  TTCN-3 Executable TRI types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-5: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 5: TTCN-3 Runtime Interface (TRI)"
 * 
 */

#ifndef __TRI_H__
#define __TRI_H__

#include <freettcn/ttcn3/types.h>


/**
 * @addtogroup Tri TRI
 * @{
 */

/**
 * @defgroup TriTypes Types
 * @{
 */


/**
 * @defgroup TriConnection Connection
 * @{
 */

/**
 * A value of type TriComponentId includes an identifier, a name and the component
 * type. The distinct value of the latter is the component type name as specified in the
 * TTCN-3 ATS. This abstract type is mainly used to resolve TRI communication
 * operations on TSI ports that have mappings to many test component ports.
 */
typedef struct TriComponentId {
  BinaryString compInst;
  String compName;
  QualifiedName compType;
} TriComponentId;


/**
 * A value of type TriComponentIdList is a list of TriComponentId. This
 * abstract type is used for multicast communication in TCI.
 *
 * @sa TriComponentId
 */
typedef struct TriComponentIdList {
  TriComponentId** compIdList;
  long int length;
} TriComponentIdList;


/**
 * A value of type TriPortId includes a value of type TriComponentId to
 * represent the component to which the port belongs, a port index (if present), and the
 * port name as specified in the TTCN-3 ATS. The TriPortId type is mainly required
 * to pass information about the TSI and connections to the TSI from the TE to the SA.
 */
typedef struct TriPortId {
  TriComponentId compInst;
  char* portName;
  long int portIndex;
  QualifiedName portType;
  void* aux;
} TriPortId;                


/**
 * A value of type TriPortIdList is a list of TriPortId. This abstract type is
 * used for initialization purposes after the invocation of a TTCN-3 test case.
 *
 * @sa TriPortId
 */
typedef struct TriPortIdList {
  TriPortId** portIdList;
  long int length;
} TriPortIdList;

/// @} TriConnection




/**
 * @defgroup TriCommunication Communication
 * @{
 */

/**
 * A value of type TriMessage is encoded test data that either is to be sent to
 * the SUT or has been received from the SUT.
 */
typedef BinaryString TriMessage;


/**
 * A value of type TriAddress indicates a source or destination address within
 * the SUT. This abstract type can be used in TRI communication operations and is
 * an open type, which is opaque to the TE.
 */
typedef BinaryString TriAddress;


/**
 * A value of type TriAddressList is a list of #TriAddress. This abstract
 * type is used for multicast communication in TRI.
 *
 * @sa TriAddress
 */
typedef struct TriAddressList {
  TriAddress** addrList;
  long int length;
} TriAddressList;


/**
 * A value of type TriSignatureId is the name of a procedure signature as
 * specified in the TTCN-3 ATS. This abstract type is used in procedure based TRI
 * communication operations.
 */
typedef QualifiedName TriSignatureId;


/**
 * A value of type TriParameterPassingMode is either @a in, @a inout, or @a out. This
 * abstract type is used in procedure based TRI communication operations and for
 * external function calls.
 */
typedef enum TriParameterPassingMode {
  TRI_IN = 0,
  TRI_INOUT = 1,
  TRI_OUT = 2
} TriParameterPassingMode;


/**
 * A value of type TriParameter includes an encoded parameter and a value of
 * #TriParameterPassingMode to represent the passing mode specified for the
 * parameter in the TTCN-3 ATS.
 */
typedef struct TriParameter {
  BinaryString par;
  TriParameterPassingMode mode;
} TriParameter;


/**
 * A value of type TriParameterList is a list of TriParameter. This
 * abstract type is used in procedure based TRI communication operations and for
 * external function calls.
 *
 * @sa TriParameter
 */
typedef struct TriParameterList {
  TriParameter** parList;
  long int length;
} TriParameterList;


/**
 * A value of type TriException is an encoded type and value of an exception
 * that either is to be sent to the SUT or has been received from the SUT. This
 * abstract type is used in procedure based TRI communication operations.
 */
typedef BinaryString TriException;

/// @} TriCommunication




/**
 * @defgroup TriTimer Timer
 * @{
 */

/**
 * A value of type TriTimerId specifies an identifier for a timer. This abstract
 * type is required for all TRI timer operations.
 */
typedef BinaryString TriTimerId;


/**
 * A value of type TriTimerDuration specifies the duration for a timer in
 * seconds.
 */
typedef Double TriTimerDuration;

/// @} TriTimer




/**
 * @defgroup TriMiscellaneous Miscellaneous
 * @{
 */

/**
 * A value of type TriTestCaseId is the name of a test case as specified in the
 * TTCN-3 ATS.
 */
typedef QualifiedName TriTestCaseId;


/**
 * A value of type TriFunctionId is the name of an external function as
 * specified in the TTCN-3 ATS.
 */
typedef QualifiedName TriFunctionId;


/**
 * A value of type TriStatus is either @c TRI_OK or @c TRI_Error indicating the
 * success or failure of a TRI operation.
 */
typedef long int TriStatus;

#define TRI_ERROR -1
#define TRI_OK 0

/// @} TriMiscellaneous

/// @} TriTypes

/// @} Tri

#endif /* __TRI_H__ */
