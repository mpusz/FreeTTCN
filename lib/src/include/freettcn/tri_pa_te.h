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
 * @file   tri_pa_te.h
 * @author Mateusz Pusz
 * @date   Mon Jan 29 15:47:07 2007
 * 
 * @brief  TTCN-3 Executable TRI platform interface operations PA=>TE
 * 
 */

#ifndef __TRI_PA_TE_H__
#define __TRI_PA_TE_H__

#include "freettcn/tri.h"


/**
 * @addtogroup Tri TRI
 * @{
 */

/**
 * @addtogroup TriIface Interface
 * @{
 */

/**
 * @addtogroup TriIfacePlatform Platform
 * @{
 */

/**
 * @addtogroup TriIfacePlatformTimer Timer operations
 * @{
 */

/**
 * @defgroup TriIfacePlatformTimer_PA_TE PA => TE
 * @{
 */

/** 
 * @brief Called by the PA after a timer has expired.
 * 
 * The timeout with the @p timerId can be added to the timeout list in the TE. The implementation of this
 * operation in the TE has to be done in such a manner that it addresses the different TTCN-3
 * semantics for timers defined in ES 201 873-4 [4] (see also clause 5.3.1). @n
 * @n
 * This operation is called by the PA after a timer, which has previously been started using the
 * triStartTimer() operation, has expired, i.e. it has reached its maximum duration value.
 * 
 * @param timerId identifier of the timer instance
 */
void triTimeout(const TriTimerId* timerId);

/// @} TriIfacePlatformTimer_PA_TE

/// @} TriIfacePlatformTimer

/// @} TriIfacePlatform

/// @} TriIface

/// @} Tri

#endif /* __TRI_PA_TE_H__ */
