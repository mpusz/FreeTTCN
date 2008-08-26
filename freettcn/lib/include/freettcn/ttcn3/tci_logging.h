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
 * @file   tci_logging.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:59:18 2007
 * 
 * @brief  TTCN-3 Executable logging interface
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 * 
 */

#ifndef __TCI_LOGGING_H__
#define __TCI_LOGGING_H__

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
 * @defgroup TciInterfaceLogging Abstract logging types
 * @{
 */

/**
 * @defgroup TciInterfaceValueTemplate TciValueTemplate
 * @{
 */

/**
 * Returns @c true if the template is an @c omit template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciIsOmit(TciValueTemplate inst);

/**
 * Returns @c true if the template is an @c any template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciIsAny(TciValueTemplate inst);

/**
 * Returns @c true if the template is an @c any or @c omit template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciIsAnyOrOmit(TciValueTemplate inst);

/**
 * Returns the definition of that template.
 *
 * String type reused from IDL (OMG recommendation)
 */
String tciGetTemplateDef(TciValueTemplate inst);

/// @} TciInterfaceValueTemplate


/**
 * @defgroup TciInterfaceNonValueTemplate TciNonValueTemplate
 * @{
 */

/**
 * Returns @c true if the template is an @c any template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciIsAnyNonValue(TciNonValueTemplate inst);

/**
 * Returns @c true if the template is an @c all template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciIsAllNonValue(TciNonValueTemplate inst);

/**
 * Returns the definition of that template.
 *
 * String type reused from IDL (OMG recommendation)
 */
String tciGetTemplateDefNonValue(TciNonValueTemplate inst);

/// @} TciInterfaceNonValueTemplate


/**
 * @defgroup TciInterfaceValueListAndMismatchTypes Tci Value List and Mismatch Types
 * @{
 */

/**
 * Returns @c true if the template is an any template.
 *
 * @todo Should be renamed to tciSize()
 */
int size(TciValueList inst);

/**
 * Returns @c true if the template is an all template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 *
 * @todo Renamed to tciIsEmpty()
 */
//Boolean isEmpty(TciValueList inst);
Boolean tciIsEmpty(TciValueList inst);

/**
 * Returns the definition of that template.
 *
 * @todo Renamed to tciGet()
 * @todo Value renamed to tciValue
 */
//Value get(TciValueList inst, int index);
TciValue tciGet(TciValueList inst, int index);

/// @} TciInterfaceValueListAndMismatchTypes


/**
 * @defgroup TciInterfaceValueDifference TciValueDifference
 * @{
 */

/**
 * Returns @c true if the template is an any template.
 *
 * @todo Renamed to tciGetValue()
 * @todo Value renamed to tciValue
 */
//Value getValue(TciValueDifference inst);
TciValue tciGetValue(TciValueDifference inst);

/**
 * Returns @c true if the template is an all template.
 *
 * @todo Renamed to tciGetValueTemplate()
 */
//TciValueTemplate getTciValueTemplate(TciValueDifference inst);
TciValueTemplate tciGetValueTemplate(TciValueDifference inst);

/**
 * Returns the definition of that template.
 *
 * String type reused from IDL (OMG recommendation)
 *
 * @todo Renamed to tciGetDescription()
 */
//String getDescription(TciValueDifference inst);
String tciGetDescription(TciValueDifference inst);


/**
 * @defgroup TciInterfaceValueDifferenceList TciValueDifferenceList
 * @{
 */

/**
 * Returns @c true if the template is an any template.
 *
 * @todo Renamed to tciSize()
 */
//int size(TciValueDifferenceList inst);
int tciSize(TciValueDifferenceList inst);

/**
 * Returns @c true if the template is an all template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 *
 * @todo Renamed to tciIsEmpty()
 */
//Boolean isEmpty(TciValueDifferenceList inst);
Boolean tciIsEmpty(TciValueDifferenceList inst);

/**
 * Returns the definition of that template.
 *
 * @todo Renamed to tciGet()
 */
//TciValueDifference get(TciValueDifferenceList inst, int index);
TciValueDifference tciGet(TciValueDifferenceList inst, int index);

/// @} TciInterfaceValueListAndMismatchTypes

/// @} TciInterfaceValueDifference

/// @} TciInterfaceLogging

/// @} TciInterface

/// @} Tci


#endif /* __TCI_LOGGING_H__ */
