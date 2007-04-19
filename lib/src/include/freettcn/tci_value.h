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
 * @file   tci_value.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 09:00:07 2007
 * 
 * @brief  TTCN-3 Executable Value interface
 *
 */

#ifndef __TCI_VALUE_H__
#define __TCI_VALUE_H__

#include "freettcn/tci.h"


/**
 * @addtogroup Tci TCI
 * @{
 */

/**
 * @addtogroup TciInterface Interface
 * @{
 */

/**
 * @defgroup TciInterfaceTypesValues Abstract TTCN-3 data types and values
 * @{
 */

/**
 * @defgroup TciInterfaceTypes Types
 * @{
 */

/**
 * Returns the module identifier of the module in which type is defined.
 * Returns the distinct value null if type is a TTCN-3 base type, e.g. boolean,
 * integer, etc.).
 */
TciModuleIdType tciGetDefiningModule(TciType inst);


/**
 * Returns the name of the type as defined in the TTCN-3 module. @n
 * @n
 * String type reused from IDL (OMG recommendation)
 */
String tciGetName(TciType inst);

/**
 * Returns the type class of the respective type. A value of
 * TciTypeClassType can have one of the following constants:
 * ADDRESS, ANYTYPE, BITSTRING, BOOLEAN, CHARSTRING,
 * COMPONENT, ENUMERATED, FLOAT, HEXSTRING, INTEGER,
 * OBJID, OCTETSTRING, RECORD, RECORD_OF, SET,
 * SET_OF, UNION, UNIVERSAL_CHARSTRING, VERDICT.
 */
TciTypeClassType tciGetTypeClass(TciType inst);

/**
 * Returns a freshly created value of the given type. This initial value of the
 * created value is undefined.
 */
TciValue tciNewInstance(TciType inst);

/**
 * Returns the type encoding attribute as defined in the TTCN-3 module.
 */
String tciGetTypeEncoding(TciType inst);

/**
 * This operation returns the value encoding variant attribute as defined in
 * TTCN-3, if any. If no encoding variant attribute is defined the distinct value
 * null is returned.
 */
String tciGetTypeEncodingVariant(TciType inst);

/**
 * Returns the type extension attribute as defined in the TTCN-3 module.
 */
String* getTypeExtension(TciType inst);

  
/// @} TciInterfaceTypes


/**
 * @defgroup TciInterfaceValues Values
 * @{
 */

/**
 * @defgroup TciInterfaceValue Value
 * @{
 */

/**
 * Returns the type of the specified value.
 */
TciType tciGetType(TciValue inst);

/**
 * Returns @c true if the specified value is @c omit, @c false otherwise.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciNotPresent(TciValue inst);

/**
 * Returns the value encoding attribute as defined in TTCN-3, if any. If no
 * encoding attribute is defined the distinct value @c null is returned.
 */
String tciGetValueEncoding(TciValue inst);

/**
 * Returns the value encoding variant attribute as defined in TTCN-3, if any. If
 * no encoding variant attribute is defined the distinct value @c null is returned.
 */
String tciGetValueEncodingVariant(TciValue inst);

/// @} TciInterfaceValue


/**
 * @defgroup TciInterfaceIntegerValue IntegerValue
 * @{
 */

/**
 * Returns the (10-base) integer absolute value as an ASCII string.
 */
String tciGetIntAbs(TciValue inst);

/**
 * Returns the number of digits in an integer value.
 */
unsigned long int tciGetIntNumberOfDigits(TciValue inst);

/**
 * Returns true if the number is positive, false otherwise
 */
Boolean tciGetIntSign(TciValue inst);

/**
 * Returns the value of the digit at position 'position', where position 0 is the least significant digit.
 */
char tciGetIntDigit(TciValue inst, unsigned long int position);

/**
 * Sets the (10-base) absolute value of the integer via an ASCII string. The
 * first digit must not be 0 unless the value is 0.
 */
void tciSetIntAbs(TciValue inst, String value);

/**
 * Sets the number of digits in an integer value.
 */
void tciSetIntNumberOfDigits(TciValue inst, unsigned long int dig_num);

/**
 * Sets the sign to + (true) or - (false).
 */
void tciSetIntSign(TciValue inst, Boolean sign);

/**
 * Sets the value of the digit at position 'position', where position 0 is the least significant digit.
 */
void tciSetIntDigit(TciValue inst, unsigned long int position, char digit);

/// @} TciInterfaceIntegerValue


/**
 * @defgroup TciInterfaceFloatValue FloatValue
 * @{
 */

/**
 * Returns the float value of this TTCN-3 float.
 */
double tciGetFloatValue(TciValue inst);

/**
 * Sets this FloatValue to value.
 */
void tciSetFloatValue(TciValue inst, double value);

/// @} TciInterfaceFloatValue


/**
 * @defgroup TciInterfaceBooleanValue BooleanValue
 * @{
 */

/**
 * Returns the boolean value of the TTCN-3 boolean.
 */
Boolean tciGetBooleanValue(TciValue inst);

/**
 * Sets this boolean value to value.
 */
void tciSetBooleanValue(TciValue inst, Boolean value);

/// @} TciInterfaceBooleanValue


/**
 * @defgroup TciInterfaceObjidValue ObjidValue
 * @{
 */

/**
 * Returns the object id value of the TTCN-3 objid.
 */
TciObjidValue tciGetTciObjidValue(TciValue inst);

/**
 * Sets this ObjidValue to value.
 */
void tciSetObjidValue(TciValue inst, TciObjidValue value);

/// @} TciInterfaceObjidValue


/**
 * @defgroup TciInterfaceCharstringValue CharstringValue
 * @{
 */

/**
 * Returns the string value of the TTCN-3 charstring. The textual
 * representation of the empty TTCN-3 charstring is '', while its length
 * is zero.
 */
TciCharStringValue tciGetCStringValue(TciValue inst);

/**
 * Sets this CharstringValue to value.
 *
 * @todo TciCharString type redefined to TciCharStringValue
 */
void tciSetCStringValue(TciValue inst, TciCharStringValue value);

/**
 * Returns the char value of the TTCN-3 charstring at position. Position 0
 * denotes the first char of the TTCN-3 charstring. Valid values for
 * position are from 0 to length - 1.
 */
char tciGetCStringCharValue(TciValue inst, long int position);

/**
 * Set the character at position to value. Valid values for position are from 0
 * to length - 1.
 */
void tciSetCStringCharValue(TciValue inst, long int position, char value);

/**
 * Returns the length of this CharstringValue in chars, zero if the value of this
 * CharstringValue is omit.
 */
unsigned long int tciGetCStringLength(TciValue inst);

/**
 * setLength first resets this CharstringValue to its initial value and afterwards
 * sets the length of this CharstringValue in chars to len.
 */
void tciSetCStringLength(TciValue inst, unsigned long int len);

/// @} TciInterfaceCharstringValue


/**
 * @defgroup TciInterfaceUniversalCharstringValue UniversalCharstringValue
 * @{
 */

/**
 * Returns the textual representation of this
 * UniversalCharstringValue, as defined in TTCN-3.
 */
TciUCStringValue tciGetUCStringValue(TciValue inst);

/**
 * Sets the value of this UniversalCharstringValue according to the
 * textual representation as defined by value.
 */
void tciSetUCStringValue(TciValue inst, TciUCStringValue value);

/**
 * Returns the universal char value of the TTCN-3 universal
 * charstring at position. Position 0 denotes the first TUniversalChar
 * of the TTCN-3 universal charstring. Valid values for position
 * are from 0 to length - 1.
 */
void tciGetUCStringCharValue(TciValue inst, unsigned long int position, TciUCValue result);

/**
 * Sets the universal char at position to value. Valid values for position
 * are from 0 to length - 1.
 */
void tciSetUCStringCharValue(TciValue inst, unsigned long int position, TciUCValue value);

/**
 * Returns the length of this universal charstring value in universal chars, zero
 * if the value of this universal charstring value is omit.
 */
unsigned long int tciGetUCStringLength(TciValue inst);

/**
 * setLength first resets this UniversalCharstringValue to its initial value and
 * afterwards sets the length of this UniversalCharstringValue in
 * universal chars to @p len.
 */
void tciSetUCStringLength(TciValue inst, unsigned long int len);

/// @} TciInterfaceUniversalCharstringValue


/**
 * @defgroup TciInterfaceBitstringValue BitstringValue
 * @{
 */

/**
 * Returns the textual representation of this BitstringValue, as defined
 * in TTCN-3. E.g. the textual representation of 0101 is "0101"B. The
 * textual representation of the empty TTCN-3 bitstring is ""B, while its
 * length is zero.
 */
String tciGetBStringValue(TciValue inst);

/**
 * Sets the value of this BitstringValue according to the textual
 * representation as defined by value. E.g. the value of this
 * BitstringValue is 0101 if the textual representation in value is
 * "0101"B.
 */
void tciSetBStringValue(TciValue inst, String value);

/**
 * Returns the value (0 | 1) at position of this TTCN-3 bitstring as a
 * character. Position 0 denotes the first bit of the TTCN-3 bitstring. Valid
 * values for position are from 0 to length - 1.
 */
int tciGetBStringBitValue(TciValue inst, long int position);

/**
 * Sets the bit at position to the value (0 | 1). Position 0 denotes the first
 * bit in this BitstringValue. Valid values for position are from 0 to
 * length - 1.
 */
void tciSetBStringBitValue(TciValue inst, unsigned long int position, int value);

/**
 * Returns the length of this BitstringValue in bits, zero if the value of
 * this BitstringValue is @c omit.
 */
unsigned long int tciGetBStringLength(TciValue inst);

/**
 * setLength first resets this BitstringValue to its initial value and afterwards
 * sets the length of this BitstringValue in bits to @p len.
 */
void tciSetBStringLength(TciValue inst, long int len);

/// @} TciInterfaceBitstringValue


/**
 * @defgroup TciInterfaceOctetstringValue OctetstringValue
 * @{
 */

/**
 * Returns the textual representation of this OctetstringValue, as
 * defined in TTCN-3. E.g. the textual representation of 0xCAFFEE is
 * "CAFFEE"O. The textual representation of the empty TTCN-3
 * octetstring is ""O, while its length is zero.
 */
String tciGetOStringValue(TciValue inst);

/**
 * Sets the value of this OctetstringValue according to the textual
 * representation as defined by value. E.g. The value of this
 * OctetstringValue is 0xCAFFEE if the textual representation in
 * value is "CAFFEE"O.
 */
void tciSetOStringValue(TciValue inst, String value);

/**
 * Returns the value (0..255) at position of this TTCN-3 octetstring.
 * Position 0 denotes the first octet of the TTCN-3 octetstring. Valid values
 * for position are from 0 to length - 1.
 */
int tciGetOStringOctetValue(TciValue inst, unsigned long int position);

/**
 * Sets the octet at position to value (0..255). Position 0 denotes the
 * first octet in the octetstring. Valid values for position are from 0 to
 * length - 1.
 */
void tciSetOStringOctetValue(TciValue inst, unsigned long int position, int value);

/**
 * Returns the length of this OctetstringValue in octets, zero if the
 * value of this OctetstringValue is omit.
 */
unsigned long int tciGetOStringLength(TciValue inst);

/**
 * setLength first resets this OctetstringValue to its initial value and
 * afterwards sets the length of this OctetstringValue in octets to
 * len.
 */
void tciSetOStringLength(TciValue inst, unsigned long int len);

/// @} TciInterfaceOctetstringValue


/**
 * @defgroup TciInterfaceHexstringValue HexstringValue
 * @{
 */

/**
 * Returns the textual representation of this HexstringValue, as defined
 * in TTCN-3. E.g. the textual representation of 0xAFFEE is "AFFEE"H.
 * The textual representation of the empty TTCN-3 hexstring is ""H,
 * while its length is zero.
 */
String tciGetHStringValue(TciValue inst);

/**
 * Sets the value of this HexstringValue according to the textual
 * representation as defined by value. E.g. The value of this
 * HexstringValue is 0xAFFEE if the textual representation in value
 * is "AFFEE"H.
 */
void tciSetHStringValue(TciValue inst, String value);

/**
 * Returns the value (0..15) at position of this TTCN-3 hexstring.
 * Position 0 denotes the first hex digits of the TTCN-3 hexstring. Valid
 * values for position are from 0 to length - 1.
 */
int tciGetHStringHexValue(TciValue inst, unsigned long int position);

/**
 * Sets the hex digit at position to value (0..15). Position 0 denotes the first
 * octet in the hexstring. Valid values for position are from 0 to
 * length - 1.
 */
void tciSetHStringHexValue(TciValue inst, unsigned long int position, int value);

/**
 * Returns the length of this HexstringValue in octets, zero if the value of
 * this HexstringValue is omit.
 */
long int tciGetHStringLength(TciValue inst);

/**
 * setLength first resets this HexstringValue to its initial value and
 * afterwards sets the length of this HexstringValue in hex digits to
 * len.
 */
void tciSetHStringLength(TciValue inst, unsigned long int len);

/// @} TciInterfaceHexstringValue


/**
 * @defgroup TciInterfaceRecordValue RecordValue
 * @{
 */

/**
 * Returns the value of the field named @p fieldName. The return value is the
 * common abstract base type @c Value, as a record field can have any type
 * defined in TTCN-3. If the field can not be obtained from the record the
 * distinct value @c null is returned.
 */
TciValue tciGetRecFieldValue(TciValue inst, String fieldName);

/**
 * Sets the field named @p fieldName of the record to value. No assumption
 * shall be made on how a field is stored in a record. An internal
 * implementation might choose to store a reference to this value or to copy
 * the value. It is safe to assume that the value is copied. Therefore it should
 * be relied on that subsequent modifications of @p value will not be
 * considered in the record.
 */
void tciSetRecFieldValue(TciValue inst, String fieldName, TciValue value);

/**
 * Returns a sequence of string of field names, the empty sequence, if the
 * record has no fields.
 *
 * Returns a NULL-terminated array of the field names.
 */
char** tciGetRecFieldNames(TciValue inst);


/**
 * Mark the referenced field of the record as being omitted.
 *
 * @todo setFieldOmitted() redefined as tciSetFieldOmitted()
 */
void tciSetFieldOmitted(TciValue inst, String fieldName);
// void setFieldOmitted(String fieldName)

/// @} TciInterfaceRecordValue



/**
 * @defgroup TciInterfaceRecordOfValue RecordOfValue
 * @{
 */

/**
 * Returns the value of the record of at @p position if position is
 * between zero and length -1, the distinct value @c null otherwise. The
 * return value is the common abstract base type @c Value, as a record of
 * can have fields of any type defined in TTCN-3.
 */
TciValue tciGetRecOfFieldValue(TciValue inst, unsigned long int position);

/**
 * Sets the field at @p position to @p value. If position is greater than
 * (length -1) the record of is extended to have the length (position
 * + 1). The record of elements between the original position at
 * length and position - 1 is set to @c omit. No assumption shall be
 * made on how a field is stored in a record of. An internal
 * implementation might choose to store a reference to this value or to copy
 * the value. It is safe to assume that the value is copied. Therefore, it should
 * be relied on that subsequent modifications of @p value will not be
 * considered in the record of.
 */
void tciSetRecOfFieldValue(TciValue inst, unsigned long int position, TciValue value);

/**
 * Appends the value at the end of the record of, i.e. at position length.
 * No assumption shall be made on how a field is stored in a record of.
 * An internal implementation might choose to store a reference to this value
 * or to copy the value. It is safe to assume that the value is copied. Therefore,
 * it should be relied on that subsequent modifications of @p value will not be
 * considered in the record of.
 */
void tciAppendRecOfFieldValue(TciValue inst, TciValue value);

/**
 * Returns the Type of the elements of this record of.
 */
TciType tciGetRecOfElementType(TciValue inst);

/**
 * Returns the actual length of the record of value, zero if the record
 * of value is @c omit.
 */
unsigned long int tciGetRecOfLength(TciValue inst);

/**
 * Sets the length of the record of to len. If len is greater than the
 * original length, newly created elements have the value omit. If len is
 * less or equal than the original length this operation is ignored.
 */
void tciSetRecOfLength(TciValue inst, unsigned long int len);

/// @} TciInterfaceRecordOfValue



/**
 * @defgroup TciInterfaceUnionValue UnionValue
 * @{
 */

/**
 * Returns the value of the TTCN-3 union @p variantName, if
 * @p variantName equals the result of tciGetUnionPresentVariantName(), the
 * distinct value @c null otherwise. @p variantName denotes the name of the
 * union variant as defined in TTCN-3.
 */
TciValue tciGetUnionVariant(TciValue inst, String variantName);

/**
 * Sets @p variantName of the union to value. If @p variantName is not
 * defined for this union this operation is ignored. If another variant was
 * selected the new variant is selected instead.
 */
void tciSetUnionVariant(TciValue inst, String variantName, TciValue value);

/**
 * Returns a String representing the currently selected variant name in the
 * given TTCN-3 union. The distinct value @c null is returned if no variant is
 * selected.
 */
String tciGetUnionPresentVariantName(TciValue inst);

/**
 * Returns a sequence of string of variant names, the distinct value null, if
 * the union has no fields. If the UnionValue represents the TTCN-3
 * anytype, i.e. the type class of the type obtained by getType() is
 * ANYTYPE, all predefined and user-defined TTCN-3 types is returned.
 *
 * Returns a NULL-terminated array of the field names.
 */
char** tciGetUnionVariantNames(TciValue inst);

/// @} TciInterfaceUnionValue



/**
 * @defgroup TciInterfaceEnumeratedValue EnumeratedValue
 * @{
 */

/**
 * Returns the string identifier of this EnumeratedValue. This identifier
 * equals the identifier in the TTCN-3 specification.
 */
String tciGetEnumValue(TciValue inst);

/**
 * Sets the enum to @p enumValue. If @p enumValue is not an allowed value for
 * this enumeration the operation is ignored.
 */
void tciSetEnumValue(TciValue inst, String enumValue);

/// @} TciInterfaceEnumeratedValue



/**
 * @defgroup TciInterfaceVerdictValue VerdictValue
 * @{
 */

/**
 * Returns the integer value for this VerdictValue. The integer is one of
 * the following constants: @c ERROR, @c FAIL, @c INCONC, @c NONE, @c PASS.
 */
int tciGetVerdictValue(TciValue inst);

/**
 * Sets this VerdictValue to @p verdict. Note that a VerdictValue
 * can be set to any of the above mentioned verdicts at any time. The
 * VerdictValue does not perform any verdict calculations as defined in
 * TTCN-3. For example, it is legal to set the VerdictValue first to
 * @c ERROR and then to @c PASS.
 */
void tciSetVerdictValue(TciValue inst, int verdict);

/// @} TciInterfaceVerdictValue




/**
 * @defgroup TciInterfaceAddressValue AddressValue
 * @{
 */

/**
 * Returns the address value, which will no longer be of type class ADDRESS
 * but rather of the actual type used for address.
 */
TciValue tciGetAddressValue(TciValue inst);

/**
 * Sets this address value to @p value.
 */
void tciSetAddressValue(TciValue inst, TciValue value);

/// @} TciInterfaceAddressValue

/// @} TciInterfaceValues

/// @} TciInterfaceTypesValues

/// @} TciInterface

/// @} Tci


#endif /* __TCI_VALUE_H__ */
