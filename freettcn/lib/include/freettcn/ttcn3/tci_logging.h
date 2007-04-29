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
 * Returns true if the template is an omit template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciIsOmit(TciValueTemplate inst);

/**
 * Returns true if the template is an any template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciIsAny(TciValueTemplate inst);

/**
 * Returns true if the template is an any or omit template.
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
 * Returns true if the template is an any template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 *
 * @todo Redeclaration
 */
Boolean tciIsAny(TciNonValueTemplate inst);

/**
 * Returns true if the template is an all template.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciIsAll(TciNonValueTemplate inst);

/**
 * Returns the definition of that template.
 *
 * String type reused from IDL (OMG recommendation)
 *
 * @todo Redeclaration
 */
String tciGetTemplateDef(TciNonValueTemplate inst);

/// @} TciInterfaceNonValueTemplate

/// @} TciInterfaceLogging

/// @} TciInterface

/// @} Tci


#endif /* __TCI_LOGGING_H__ */
