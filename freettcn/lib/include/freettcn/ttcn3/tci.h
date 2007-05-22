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
 * @file   tci.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:50:45 2007
 * 
 * @brief  TTCN-3 Executable TCI types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 * 
 */

#ifndef __TCI_H__
#define __TCI_H__

#include <freettcn/ttcn3/types.h>


/**
 * @addtogroup Tci TCI
 * @{
 */

/**
 * @defgroup TciTypes Types
 * @{
 */


/**
 * @defgroup TciTypesUndocumented Undocumented
 * @{
 */

/********************* -V-  M O J E  -V- *******************/

/**
 * @todo TciType type not defined in specification
 */
typedef void *TciType;

/**
 * @todo TciValue type not defined in specification
 */
typedef void *TciValue;

/**
 * @todo TciVerdictValue type not defined in specification
 */
typedef TciValue TciVerdictValue;

/**
 * @todo TciValueTemplate type not defined in specification
 */
typedef TciValue TciValueTemplate;

/**
 * @todo TciNonValueTemplate type not defined in specification
 */
typedef TciValue TciNonValueTemplate;

/**
 * A value of type TciModuleIdListType is a list of TciModuleIdType. This
 * abstract type is used when retrieving the list of modules which are imported by a
 * TTCN-3 module.
 *
 * @todo There is no definition in the TTCN-3 standard specification
 */

/**
 * A value of TciModuleParameterIdType is the qualified name of a TTCN-3 module parameter
 * as specified in the TTCN-3 ATS. This abstract type is used for module
 * parameter handling.
 *
 * @todo There is no definition in the TTCN-3 standard specification
 */
typedef String TciModuleParameterIdType;
// typedef QualifiedName TciModuleParameterIdType;

/**
 * A value of type TciParameterTypeType is a structure of Type and
 * TciParameterPassingModeType. This abstract type is used to represent the
 * type and the parameter passing mode of a test case parameter.
 *
 * @todo There is no definition in the TTCN-3 standard specification
 */

/// @} TciTypesUndocumented

/********************* -^-  M O J E  -^- *******************/


/**
 * @defgroup TciData General abstract data
 * @{
 */

/**
 * @defgroup TciDataManagement Management
 * @{
 */

/**
 * A value of TciModuleIdType is the name of a TTCN-3 module as specified in
 * the TTCN-3 ATS. This abstract type is used for module handling.
 */
typedef QualifiedName TciModuleIdType;

/**
 * A value of type TciModuleParameterType is a structure of
 * TciModuleParameterIdType and Value. This abstract type is used to
 * represent the parameter name and the default value of a module parameter.
 */
typedef struct TciModuleParameterType {
//   String parName;                              /**< my change */
  TciModuleParameterIdType parName;
  TciValue defaultValue;
} TciModuleParameterType;

/**
 * A value of type TciModuleParameterListType is a list of
 * TciModuleParameterType. This abstract type is used when retrieving the
 * module parameters of a TTCN-3 module.
 */
typedef struct TciModuleParameterListType {
  long int               length;
  TciModuleParameterType *modParList;
} TciModuleParameterListType;

/**
 * A value of type TciParameterPassingModeType is either IN, INOUT, or
 * OUT. This abstract type is used when starting a test case or when the termination of a
 * test case is indicated.
 */
typedef enum {
  TCI_IN_PAR    = 0,
  TCI_INOUT_PAR = 1,
  TCI_OUT_PAR   = 2
} TciParameterPassingModeType;

/**
 * A value of type TciParameterType includes a TTCN-3 Value and a value of
 * TciParameterPassingModeType to represent the parameter passing mode
 * specified for the parameter in the TTCN-3 ATS.
 */
typedef struct TciParameterType {
  String   parName;
  TciParameterPassingModeType parPassMode;
  TciValue                    parValue;
} TciParameterType;

/**
 * A value of type TciParameterListType is a list of TciParameterType.
 * This abstract type is used when starting a test case or when the termination of a test
 * case is indicated.
 *
 * @a length 0 shall be interpreted as "empty list".
 */
typedef struct TciParameterListType {                                         
  long int          length;
  TciParameterType *parList;
} TciParameterListType;

/**
 * A value of type TciParameterTypeListType is a list of
 * TciParameterTypeType. This abstract type is used to represent the list of
 * parameters of a test case.
 *
 * length 0 shall be interpreted as "empty list".
 */
typedef struct TciParameterTypeListType {                                         
  long int length;
  TciType *parList;
} TciParameterTypeListType;

/**
 * A value of TciTestCaseIdType is the qualified name of a TTCN-3 testcase as
 * specified in the TTCN-3 ATS. This abstract type is used for testcase handling.
 */
typedef QualifiedName TciTestCaseIdType;

/**
 * length 0 shall be interpreted as "empty list".
 */
typedef struct TciTestCaseIdListType {                                         
  long int          length;
  TciTestCaseIdType *idList;
} TciTestCaseIdListType;


/**
 * A value of type TciTypeClassType is a literal of the set of type classes in
 * TTCN-3 such as boolean, float, record, etc. This abstract type is used for value
 * handling.
 */
typedef enum {
  TCI_ADDRESS_TYPE,
  TCI_ANYTYPE_TYPE,
  TCI_BITSTRING_TYPE,
  TCI_BOOLEAN_TYPE,
  TCI_CHAR_TYPE,
  TCI_CHARSTRING_TYPE,
  TCI_COMPONENT_TYPE,
  TCI_ENUMERATED_TYPE,
  TCI_FLOAT_TYPE,
  TCI_HEXSTRING_TYPE,
  TCI_INTEGER_TYPE,
  TCI_OBJID_TYPE,
  TCI_OCTETSTRING_TYPE,
  TCI_RECORD_TYPE,
  TCI_RECORD_OF_TYPE,
  TCI_SET_TYPE,
  TCI_SET_OF_TYPE,
  TCI_UNION_TYPE,
  TCI_UNIVERSAL_CHAR_TYPE,
  TCI_UNIVERSAL_CHARSTRING_TYPE,
  TCI_VERDICT_TYPE
} TciTypeClassType;

/**
 * A value of type TciTestComponentKindType is a literal of the set of kinds of
 * TTCN-3 test components, i.e. MTC, PTC, PTC_ALIVE, and CONTROL. This
 * abstract type is used for component handling.
 */
typedef enum {
  TCI_CTRL_COMP,
  TCI_MTC_COMP,
  TCI_PTC_COMP,
  TCI_SYS_COMP,
  TCI_ALIVE_COMP
} TciTestComponentKindType;


/// @} TciDataManagement


/**
 * @defgroup TciDataCommunication Communication
 * @{
 */


/**
 * A value of type TciBehaviourIdType identifies a TTCN-3 behaviour
 * functions.
 */
typedef QualifiedName TciBehaviourIdType;

/// @} TciDataCommunication


/**
 * @defgroup TciDataLogging Abstract logging types
 * @{
 */

/**
 * @defgroup TciDataLoggingValue The Value List and Mismatch Types
 * @{
 */

/**
 * A value of TciValueList is a list of values.
 *
 * @todo There is no definition in the TTCN-3 standard specification
 */


/**
 * A value of TciValueDifference is a structure containing a value, a
 * template, and a description for the reason of this difference.
 */
typedef struct TciValueDifference {
  TciValue val;
  TciValueTemplate tmpl;
  String desc;
} TciValueDifference;

/**
 * A value of TciValueDifferenceList is a sequence of value
 * differences.
 * 
 * length 0 shall be interpreted as "empty list".
 */
typedef struct TciValueDifferenceList {                                     
  long int           length;
  TciValueDifference diffList[];
} TciValueDifferenceList;


/**
 * A value of ComponentStatusType is either "inactiveC", "runningC",
 *"stoppedC", or "killedC".
 */
/// @todo 3.2.1
typedef enum {
  TCI_inactiveC,
  TCI_runningC,
  TCI_stoppedC,
  TCI_killedC
} ComponentStatus;

/**
 * A value of TimerStatusType is either "runningT", "inactiveT", or
 * "expiredT".
 */
/// @todo 3.2.1
typedef enum {
  TCI_runningT,
  TCI_inactiveT,
  TCI_expiredT
} TimerStatus;


/**
 * A value of PortStatusType is either " startedP", "haltedP", or "
 * stoppedP".
 */
/// @todo 3.2.1 - not used???
typedef enum {
  TCI_startedP,
  TCI_haltedP,
  TCI_stoppedP
} PortStatus;


/// @} TciDataLoggingValue

/// @} TciDataLogging

/// @} TciData


/**
 * @defgroup TciMiscellaneous Miscellaneous
 * @{
 */


/**
 * @defgroup TciMiscellaneousVerdict Verdict representation
 * @{
 */

/**
 * Since the TciVerdictValue interface is defined in terms of integers, consensus
 * must be established on which value defines which verdict.
 */
const int TCI_VERDICT_NONE     = 0;
const int TCI_VERDICT_PASS     = 1;
const int TCI_VERDICT_INCONC   = 2;
const int TCI_VERDICT_FAIL     = 3;
const int TCI_VERDICT_ERROR    = 4;

/// @} TciMiscellaneousVerdict


/**
 * @defgroup TciMiscellaneousObjid Objid representation
 * @{
 */

/**
 * Since the Objid value is returned "as is" via the Objid value interface,
 * a representation must be defined.
 */
typedef struct TciObjidElemValue {
  char*    elem_as_ascii;
  long int elem_as_number;
  void*    aux;
} TciObjidElemValue;

typedef struct TciObjidValue {                                             
  long int      length;
  //  TciObjidElem *elements;                     /**< @todo My change of TciObjidElem->TciObjidElemValue */
  TciObjidElemValue *elements;
} TciObjidValue;


// CharstringValue representation
typedef struct TciCharStringValue {
  unsigned long int length;
  char*              string;
} TciCharStringValue;

// Universal Character[string] representation
typedef unsigned char TciUCValue[4];
typedef struct TciUCStringValue {
  unsigned long int length;
//   TciUCType         *string;                   /**< @todo My change of TciUCType->TciUCValue */
  TciUCValue        *string;
} TciUCStringValue;


/// @} TciMiscellaneousObjid

/// @} TciMiscellaneous

/// @} TciTypes

/// @} Tci

#endif /* __TCI_H__ */
