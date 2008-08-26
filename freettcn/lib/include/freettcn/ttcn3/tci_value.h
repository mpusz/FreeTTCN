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
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 *
 */

#ifndef __TCI_VALUE_H__
#define __TCI_VALUE_H__

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
TciModuleIdType tciGetDefiningModule(Type inst);


/**
 * Returns the name of the type as defined in the TTCN-3 module.
 * 
 * @note String type reused from IDL (OMG recommendation)
 */
String tciGetName(Type inst);

/**
 * Returns the type class of the respective type. A value of
 * TciTypeClassType can have one of the following constants:
 * ADDRESS, ANYTYPE, BITSTRING, BOOLEAN, CHARSTRING,
 * COMPONENT, ENUMERATED, FLOAT, HEXSTRING, INTEGER,
 * OBJID, OCTETSTRING, RECORD, RECORD_OF, SET,
 * SET_OF, UNION, UNIVERSAL_CHARSTRING, VERDICT.
 */
TciTypeClassType tciGetTypeClass(Type inst);

/**
 * Returns a freshly created value of the given type. This initial value of the
 * created value is undefined.
 */
Value tciNewInstance(Type inst);

/**
 * Returns the type encoding attribute as defined in the TTCN-3 module.
 */
String tciGetTypeEncoding(Type inst);

/**
 * This operation returns the value encoding variant attribute as defined in
 * TTCN-3, if any. If no encoding variant attribute is defined the distinct value
 * null is returned.
 */
String tciGetTypeEncodingVariant(Type inst);

/**
 * Returns the type extension attribute as defined in the TTCN-3 module.
 *
 * @todo getTypeExtension() renamed to tciGetTypeExtension()
 */
// String *getTypeExtension(Type inst);
String *tciGetTypeExtension(Type inst);

  
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
Type tciGetType(Value inst);

/**
 * Returns @c true if the specified value is @c omit, @c false otherwise.
 *
 * Boolean type reused from IDL (OMG recommendation)
 */
Boolean tciNotPresent(Value inst);

/**
 * Returns the value encoding attribute as defined in TTCN-3, if any. If no
 * encoding attribute is defined the distinct value @c null is returned.
 */
String tciGetValueEncoding(Value inst);

/**
 * Returns the value encoding variant attribute as defined in TTCN-3, if any. If
 * no encoding variant attribute is defined the distinct value @c null is returned.
 */
String tciGetValueEncodingVariant(Value inst);

/// @} TciInterfaceValue


/**
 * @defgroup TciInterfaceIntegerValue IntegerValue
 * @{
 */

/**
 * Returns the (10-base) integer absolute value as an ASCII string.
 */
String tciGetIntAbs(Value inst);

/**
 * Returns the number of digits in an integer value.
 */
unsigned long int tciGetIntNumberOfDigits(Value inst);

/**
 * Returns true if the number is positive, false otherwise
 */
Boolean tciGetIntSign(Value inst);

/**
 * Returns the value of the digit at position 'position', where position 0 is the least significant digit.
 */
char tciGetIntDigit(Value inst, unsigned long int position);

/**
 * Sets the (10-base) absolute value of the integer via an ASCII string. The
 * first digit must not be 0 unless the value is 0.
 */
void tciSetIntAbs(Value inst, String value);

/**
 * Sets the number of digits in an integer value.
 */
void tciSetIntNumberOfDigits(Value inst, unsigned long int dig_num);

/**
 * Sets the sign to + (true) or - (false).
 */
void tciSetIntSign(Value inst, Boolean sign);

/**
 * Sets the value of the digit at position 'position', where position 0 is the least significant digit.
 */
void tciSetIntDigit(Value inst, unsigned long int position, char digit);

/// @} TciInterfaceIntegerValue


/**
 * @defgroup TciInterfaceFloatValue FloatValue
 * @{
 */

/**
 * Returns the float value of this TTCN-3 float.
 */
double tciGetFloatValue(Value inst);

/**
 * Sets this FloatValue to value.
 */
void tciSetFloatValue(Value inst, double value);

/// @} TciInterfaceFloatValue


/**
 * @defgroup TciInterfaceBooleanValue BooleanValue
 * @{
 */

/**
 * Returns the boolean value of the TTCN-3 boolean.
 */
Boolean tciGetBooleanValue(Value inst);

/**
 * Sets this boolean value to value.
 */
void tciSetBooleanValue(Value inst, Boolean value);

/// @} TciInterfaceBooleanValue


/**
 * @defgroup TciInterfaceObjidValue ObjidValue
 * @{
 */

/**
 * Returns the object id value of the TTCN-3 objid.
 */
TciObjidValue tciGetTciObjidValue(Value inst);

/**
 * Sets this ObjidValue to value.
 */
void tciSetObjidValue(Value inst, TciObjidValue value);

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
TciCharStringValue tciGetCStringValue(Value inst);

/**
 * Sets this CharstringValue to value.
 *
 * @todo TciCharString type redefined to TciCharStringValue
 */
void tciSetCStringValue(Value inst, TciCharStringValue value);

/**
 * Returns the char value of the TTCN-3 charstring at position. Position 0
 * denotes the first char of the TTCN-3 charstring. Valid values for
 * position are from 0 to length - 1.
 */
char tciGetCStringCharValue(Value inst, long int position);

/**
 * Set the character at position to value. Valid values for position are from 0
 * to length - 1.
 */
void tciSetCStringCharValue(Value inst, long int position, char value);

/**
 * Returns the length of this CharstringValue in chars, zero if the value of this
 * CharstringValue is omit.
 */
unsigned long int tciGetCStringLength(Value inst);

/**
 * setLength first resets this CharstringValue to its initial value and afterwards
 * sets the length of this CharstringValue in chars to len.
 */
void tciSetCStringLength(Value inst, unsigned long int len);

/// @} TciInterfaceCharstringValue


/**
 * @defgroup TciInterfaceUniversalCharstringValue UniversalCharstringValue
 * @{
 */

/**
 * Returns the textual representation of this
 * UniversalCharstringValue, as defined in TTCN-3.
 */
TciUCStringValue tciGetUCStringValue(Value inst);

/**
 * Sets the value of this UniversalCharstringValue according to the
 * textual representation as defined by value.
 */
void tciSetUCStringValue(Value inst, TciUCStringValue value);

/**
 * Returns the universal char value of the TTCN-3 universal
 * charstring at position. Position 0 denotes the first TUniversalChar
 * of the TTCN-3 universal charstring. Valid values for position
 * are from 0 to length - 1.
 */
void tciGetUCStringCharValue(Value inst, unsigned long int position, TciUCValue result);

/**
 * Sets the universal char at position to value. Valid values for position
 * are from 0 to length - 1.
 */
void tciSetUCStringCharValue(Value inst, unsigned long int position, TciUCValue value);

/**
 * Returns the length of this universal charstring value in universal chars, zero
 * if the value of this universal charstring value is omit.
 */
unsigned long int tciGetUCStringLength(Value inst);

/**
 * setLength first resets this UniversalCharstringValue to its initial value and
 * afterwards sets the length of this UniversalCharstringValue in
 * universal chars to @p len.
 */
void tciSetUCStringLength(Value inst, unsigned long int len);

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
String tciGetBStringValue(Value inst);

/**
 * Sets the value of this BitstringValue according to the textual
 * representation as defined by value. E.g. the value of this
 * BitstringValue is 0101 if the textual representation in value is
 * "0101"B.
 */
void tciSetBStringValue(Value inst, String value);

/**
 * Returns the value (0 | 1) at position of this TTCN-3 bitstring as a
 * character. Position 0 denotes the first bit of the TTCN-3 bitstring. Valid
 * values for position are from 0 to length - 1.
 */
int tciGetBStringBitValue(Value inst, long int position);

/**
 * Sets the bit at position to the value (0 | 1). Position 0 denotes the first
 * bit in this BitstringValue. Valid values for position are from 0 to
 * length - 1.
 */
void tciSetBStringBitValue(Value inst, unsigned long int position, int value);

/**
 * Returns the length of this BitstringValue in bits, zero if the value of
 * this BitstringValue is @c omit.
 */
unsigned long int tciGetBStringLength(Value inst);

/**
 * setLength first resets this BitstringValue to its initial value and afterwards
 * sets the length of this BitstringValue in bits to @p len.
 */
void tciSetBStringLength(Value inst, long int len);

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
String tciGetOStringValue(Value inst);

/**
 * Sets the value of this OctetstringValue according to the textual
 * representation as defined by value. E.g. The value of this
 * OctetstringValue is 0xCAFFEE if the textual representation in
 * value is "CAFFEE"O.
 */
void tciSetOStringValue(Value inst, String value);

/**
 * Returns the value (0..255) at position of this TTCN-3 octetstring.
 * Position 0 denotes the first octet of the TTCN-3 octetstring. Valid values
 * for position are from 0 to length - 1.
 */
int tciGetOStringOctetValue(Value inst, unsigned long int position);

/**
 * Sets the octet at position to value (0..255). Position 0 denotes the
 * first octet in the octetstring. Valid values for position are from 0 to
 * length - 1.
 */
void tciSetOStringOctetValue(Value inst, unsigned long int position, int value);

/**
 * Returns the length of this OctetstringValue in octets, zero if the
 * value of this OctetstringValue is omit.
 */
unsigned long int tciGetOStringLength(Value inst);

/**
 * setLength first resets this OctetstringValue to its initial value and
 * afterwards sets the length of this OctetstringValue in octets to
 * len.
 */
void tciSetOStringLength(Value inst, unsigned long int len);

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
String tciGetHStringValue(Value inst);

/**
 * Sets the value of this HexstringValue according to the textual
 * representation as defined by value. E.g. The value of this
 * HexstringValue is 0xAFFEE if the textual representation in value
 * is "AFFEE"H.
 */
void tciSetHStringValue(Value inst, String value);

/**
 * Returns the value (0..15) at position of this TTCN-3 hexstring.
 * Position 0 denotes the first hex digits of the TTCN-3 hexstring. Valid
 * values for position are from 0 to length - 1.
 */
int tciGetHStringHexValue(Value inst, unsigned long int position);

/**
 * Sets the hex digit at position to value (0..15). Position 0 denotes the first
 * octet in the hexstring. Valid values for position are from 0 to
 * length - 1.
 */
void tciSetHStringHexValue(Value inst, unsigned long int position, int value);

/**
 * Returns the length of this HexstringValue in octets, zero if the value of
 * this HexstringValue is omit.
 */
long int tciGetHStringLength(Value inst);

/**
 * setLength first resets this HexstringValue to its initial value and
 * afterwards sets the length of this HexstringValue in hex digits to
 * len.
 */
void tciSetHStringLength(Value inst, unsigned long int len);

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
Value tciGetRecFieldValue(Value inst, String fieldName);

/**
 * Sets the field named @p fieldName of the record to value. No assumption
 * shall be made on how a field is stored in a record. An internal
 * implementation might choose to store a reference to this value or to copy
 * the value. It is safe to assume that the value is copied. Therefore it should
 * be relied on that subsequent modifications of @p value will not be
 * considered in the record.
 */
void tciSetRecFieldValue(Value inst, String fieldName, Value value);

/**
 * Returns a sequence of string of field names, the empty sequence, if the
 * record has no fields.
 *
 * Returns a NULL-terminated array of the field names.
 */
char **tciGetRecFieldNames(Value inst);


/**
 * Mark the referenced field of the record as being omitted.
 *
 * @todo setFieldOmitted() redefined as tciSetFieldOmitted()
 */
void tciSetFieldOmitted(Value inst, String fieldName);
// void setFieldOmitted(Value inst, String fieldName)

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
Value tciGetRecOfFieldValue(Value inst, unsigned long int position);

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
void tciSetRecOfFieldValue(Value inst, unsigned long int position, Value value);

/**
 * Appends the value at the end of the record of, i.e. at position length.
 * No assumption shall be made on how a field is stored in a record of.
 * An internal implementation might choose to store a reference to this value
 * or to copy the value. It is safe to assume that the value is copied. Therefore,
 * it should be relied on that subsequent modifications of @p value will not be
 * considered in the record of.
 */
void tciAppendRecOfFieldValue(Value inst, Value value);

/**
 * Returns the Type of the elements of this record of.
 */
Type tciGetRecOfElementType(Value inst);

/**
 * Returns the actual length of the record of value, zero if the record
 * of value is @c omit.
 */
unsigned long int tciGetRecOfLength(Value inst);

/**
 * Sets the length of the record of to len. If len is greater than the
 * original length, newly created elements have the value omit. If len is
 * less or equal than the original length this operation is ignored.
 */
void tciSetRecOfLength(Value inst, unsigned long int len);

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
Value tciGetUnionVariant(Value inst, String variantName);

/**
 * Sets @p variantName of the union to value. If @p variantName is not
 * defined for this union this operation is ignored. If another variant was
 * selected the new variant is selected instead.
 */
void tciSetUnionVariant(Value inst, String variantName, Value value);

/**
 * Returns a String representing the currently selected variant name in the
 * given TTCN-3 union. The distinct value @c null is returned if no variant is
 * selected.
 */
String tciGetUnionPresentVariantName(Value inst);

/**
 * Returns a sequence of string of variant names, the distinct value null, if
 * the union has no fields. If the UnionValue represents the TTCN-3
 * anytype, i.e. the type class of the type obtained by getType() is
 * ANYTYPE, all predefined and user-defined TTCN-3 types is returned.
 *
 * Returns a NULL-terminated array of the field names.
 */
char **tciGetUnionVariantNames(Value inst);

/// @} TciInterfaceUnionValue



/**
 * @defgroup TciInterfaceEnumeratedValue EnumeratedValue
 * @{
 */

/**
 * Returns the string identifier of this EnumeratedValue. This identifier
 * equals the identifier in the TTCN-3 specification.
 */
String tciGetEnumValue(Value inst);

/**
 * Sets the enum to @p enumValue. If @p enumValue is not an allowed value for
 * this enumeration the operation is ignored.
 */
void tciSetEnumValue(Value inst, String enumValue);

/// @} TciInterfaceEnumeratedValue



/**
 * @defgroup TciInterfaceVerdictValue VerdictValue
 * @{
 */

/**
 * Returns the integer value for this VerdictValue. The integer is one of
 * the following constants: @c ERROR, @c FAIL, @c INCONC, @c NONE, @c PASS.
 */
int tciGetVerdictValue(Value inst);

/**
 * Sets this VerdictValue to @p verdict. Note that a VerdictValue
 * can be set to any of the above mentioned verdicts at any time. The
 * VerdictValue does not perform any verdict calculations as defined in
 * TTCN-3. For example, it is legal to set the VerdictValue first to
 * @c ERROR and then to @c PASS.
 */
void tciSetVerdictValue(Value inst, int verdict);

/// @} TciInterfaceVerdictValue




/**
 * @defgroup TciInterfaceAddressValue AddressValue
 * @{
 */

/**
 * Returns the address value, which will no longer be of type class ADDRESS
 * but rather of the actual type used for address.
 */
Value tciGetAddressValue(Value inst);

/**
 * Sets this address value to @p value.
 */
void tciSetAddressValue(Value inst, Value value);

/// @} TciInterfaceAddressValue

/// @} TciInterfaceValues

/// @} TciInterfaceTypesValues

/// @} TciInterface

/// @} Tci


#endif /* __TCI_VALUE_H__ */
