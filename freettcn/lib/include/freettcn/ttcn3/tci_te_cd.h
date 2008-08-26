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
 * @file   tci_te_cd.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:53:59 2007
 * 
 * @brief  TTCN-3 Executable TE => CD operation interface (TCI-CD provided)
 * 
 * This header specifies the operations the CD shall provide to the TE.
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 *
 */

#ifndef __TCI_TE_CD_H__
#define __TCI_TE_CD_H__

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
 * @defgroup TciInterfaceCDProvided TCI-CD provided
 * @{
 */


/** 
 * @brief Decodes message according to the encoding rules and returns a TTCN-3 value.
 * 
 * This operations decodes @p message according to the encoding rules and returns a TTCN-3 value.
 * The @p decodingHypothesis shall be used to determine whether the encoded value can be
 * decoded. If an encoding rule is not self-sufficient, i.e. if the encoded message does not inherently
 * contain its type @p decodingHypothesis shall be used. If the encoded value can be decoded
 * without the decoding hypothesis, the distinct @c null value shall be returned if the type determined
 * from the encoded message is not compatible with the decoding hypothesis.
 * 
 * @remarks This operation shall be called whenever the TE has to decode an encoded value. The TE might
 * decode immediately after reception of a encoded value, or might for performance considerations
 * postpone the decoding until the actual access of the encoded value.
 *
 * @note BinaryString type reused from TRI
 * 
 * @param message The encoded message to be decoded.
 * @param decHypothesis The hypothesis the decoding can be based on.
 * 
 * @return Returns the decoded value, if the value is of a compatible type as the @p decodingHypothesis, else
 *         the distinct value @c null.
 */
Value tciDecode(BinaryString message,
                Type         decHypothesis);


/** 
 * @brief Returns an encoded TriMessage according to the encoding rules.
 * 
 * Returns an encoded TriMessage according to the encoding rules.
 * 
 * @remarks This operation shall be called whenever the TE has to encode a Value.
 *
 * @note BinaryString type reused from TRI
 * 
 * @param value The value to be encoded.
 * 
 * @return Returns an encoded TriMessage for the specified encoding rule.
 */
BinaryString tciEncode(Value value);


/// @} TciInterfaceCDProvided

/// @} TciInterfaceCD

/// @} TciInterface

/// @} Tci


#endif /* __TCI_TE_CD_H__ */
