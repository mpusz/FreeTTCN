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

namespace ORG_ETSI_TTCN3_TCI {

  /**
   * @addtogroup Tci TCI
   * @{
   */

  /**
   * @defgroup TciTypes Types
   * @{
   */

  class TciType {
  public:
    virtual ~TciType();
    virtual const TciModuleId &getDefiningModule() const = 0;
    virtual const Tstring &getName() const = 0;
    virtual const TciTypeClass &getTypeClass() const = 0;
    virtual const Tstring &getTypeEncoding() const = 0;
    virtual const Tstring &getTypeEncodingVariant() const = 0;
    virtual const std::vector<Tstring*> &getTypeExtension() const = 0;
    virtual TciValue *newInstance() = 0;
    virtual Tboolean operator==(const TciType &typ) const = 0;
    virtual TciType *clone() const = 0;
    virtual Tboolean operator<(const TciType &typ) const = 0;
  };

  
  class TciValue {
  public:
    virtual ~TciValue();
    virtual const TciType &getType() const = 0;
    virtual const Tstring &getValueEncoding() const = 0;
    virtual const Tstring &getValueEncodingVariant() const = 0;
    virtual Tboolean notPresent() const = 0;
    virtual Tboolean operator==(const TciValue &val) const = 0;
    virtual TciValue *clone() const = 0;
    virtual Tboolean operator<(const TciValue &val) const = 0;
  };


  class IntegerValue : public virtual TciValue {
  public:
    virtual ~IntegerValue();
    virtual Tinteger getInt() const = 0;
    virtual void setInt(Tinteger p_value) = 0;
    virtual Tboolean operator==(const IntegerValue &intVal) const = 0;
    virtual IntegerValue *clone() const = 0;
    virtual Tboolean operator<(const IntegerValue &intVal) const = 0;
  };
  
  
  class FloatValue : public virtual TciValue {
  public:
    virtual ~FloatValue();
    virtual Tfloat getFloat() const = 0;
    virtual void setFloat(Tfloat p_floatValue) = 0;
    virtual Tboolean operator==(const FloatValue &floatVal) const = 0;
    virtual FloatValue *clone() const = 0;
    virtual Tboolean operator<(const FloatValue &floatVal) const = 0;
  };
  
  
  class BooleanValue : public virtual TciValue {
  public:
    virtual ~BooleanValue();
    virtual Tboolean getBoolean() const = 0;
    virtual void setBoolean(Tboolean p_booleanValue) = 0;
    virtual Tboolean operator==(const BooleanValue &booleanVal) const = 0;
    virtual BooleanValue *clone() const = 0;
    virtual Tboolean operator<(const BooleanValue &booleanVal) const = 0;
  };
  
  
  class CharstringValue : public virtual TciValue {
  public:
    virtual ~CharstringValue();
    virtual char getChar(Tindex p_position) const = 0;
    virtual Tsize getLength() const = 0;
    virtual const Tstring &getString() const = 0;
    virtual void setChar(Tsize p_position, char p_char) = 0;
    virtual void setLength(Tsize p_length) = 0;
    virtual void setString(const Tstring &p_charValue) = 0;
    virtual Tboolean operator==(const CharstringValue &charStr) const = 0;
    virtual CharstringValue *clone() const = 0;
    virtual Tboolean operator<(const CharstringValue &charStr) const = 0;
  };


  class UniversalCharstringValue : public virtual TciValue {
  public:
    virtual ~UniversalCharstringValue();
    virtual wchar_t getChar(Tindex p_position) const = 0;
    virtual Tsize getLength() const = 0;
    virtual const TuniversalString &getString() const = 0;
    virtual void setChar(Tindex p_position, const wchar_t p_ucValue) = 0;
    virtual void setLength(Tsize p_length) = 0;
    virtual void setString(const TuniversalString &p_ucsValue) = 0;
    virtual Tboolean operator==(const UniversalCharstringValue &uniCharstr) const = 0;
    virtual UniversalCharstringValue *clone() const = 0;
    virtual Tboolean operator<(const UniversalCharstringValue &uniCharstr) const = 0;
  };
  

  class BitstringValue : public virtual TciValue {
  public:
    virtual ~BitstringValue();
    virtual Tbit getBit(Tindex p_position) const = 0;
    virtual Tsize getLength() const = 0;
    virtual const Tstring &getString() const = 0;
    virtual void setBit(Tindex p_position, Tbit p_bsValue) = 0;
    virtual void setLength(Tindex p_new_length) = 0;
    virtual void setString(const Tstring &p_bsValue) = 0;
    virtual Tboolean operator==(const BitstringValue &bitStr) const = 0;
    virtual BitstringValue *clone() const = 0;
    virtual Tboolean operator<(const BitstringValue &bitStr) const = 0;
  };
  

  class OctetstringValue : public virtual TciValue {
  public:
    virtual ~OctetstringValue();
    virtual Tsize getLength() const = 0;
    virtual const Tchar getOctet(Tindex p_position) const = 0;
    virtual const Tstring &getString() const = 0;
    virtual void setLength(Tsize p_length) = 0;
    virtual void setOctet(Tindex p_position, Tchar p_ochar) = 0;
    virtual void setString(const Tstring &p_osValue) = 0;
    virtual Tboolean operator==(const OctetstringValue &octStr) const = 0;
    virtual OctetstringValue *clone() const = 0;
    virtual Tboolean operator<(const OctetstringValue &octStr) const = 0;
  };
  
  
  class HexstringValue : public virtual TciValue {
  public:
    virtual ~HexstringValue();
    virtual Tchar getHex(Tindex p_position) const = 0;
    virtual Tsize getLength() const = 0;
    virtual const Tstring &getString() const = 0;
    virtual void setHex(Tindex p_position, Tchar p_hcValue) = 0;
    virtual void setLength(Tsize p_length) = 0;
    virtual void setString(const Tstring &p_hsValue) = 0;
    virtual Tboolean operator==(const HexstringValue &hexStr) const = 0;
    virtual HexstringValue *clone() const = 0;
    virtual Tboolean operator<(const HexstringValue &hexStr) const = 0;
  };
  

  class RecordValue : public virtual TciValue {
  public:
    virtual ~RecordValue();
    virtual const TciValue &getField(const Tstring &p_field_name) const = 0;
    virtual void setField(const Tstring &p_field_name,const TciValue &p_new_value) = 0;
    virtual const std::vector<Tstring *> &getFieldNames() const = 0;
    virtual void setFieldOmitted(const Tstring &fieldName) = 0;
    virtual Tboolean operator==(const RecordValue &rec) const = 0;
    virtual RecordValue *clone() const = 0;
    virtual Tboolean operator<(const RecordValue &rec) const = 0;
  };
  

  class RecordOfValue : public virtual TciValue {
  public:
    virtual ~RecordOfValue();
    virtual const TciValue &getField(Tindex p_position) = 0;
    virtual void setField(Tindex p_position, const TciValue &p_value) = 0;
    virtual void appendField(const TciValue &p_value) = 0;
    virtual const TciType &getElementType() const = 0;
    virtual Tsize getLength() const = 0;
    virtual void setLength(Tsize p_length) = 0;
    virtual Tindex getOffset() const = 0;
    virtual Tboolean operator==(const RecordOfValue &recOf) const = 0;
    virtual RecordOfValue *clone() const = 0;
    virtual Tboolean operator<(const RecordOfValue &recOf) const = 0;
  };
  

  class UnionValue : public virtual TciValue {
  public:
    virtual ~UnionValue();
    virtual void setVariant(const Tstring &p_variantName, const TciValue &p_value) = 0;
    virtual const TciValue &getVariant(const Tstring &p_variantName) const = 0;
    virtual const Tstring &getPresentVariantName() const = 0;
    virtual const std::set<Tstring *> &getVariantNames() const = 0;
    virtual Tboolean operator==(const UnionValue &unionVal) const = 0;
    virtual UnionValue *clone() const = 0;
    virtual Tboolean operator<(const UnionValue &unionVal) const = 0;
  };
  

  class EnumeratedValue : public virtual TciValue {
  public:
    virtual ~EnumeratedValue();
    virtual const Tstring &getEnum() const = 0;
    void setEnum(const Tstring &p_value) = 0;
    Tinteger getInt() const = 0;
    void setInt(Tinteger p_int);
    Tboolean operator==(const EnumeratedValue &enumVal) const = 0;
    EnumeratedValue *clone() const = 0;
    Tboolean operator<(const EnumeratedValue &enumVal) const = 0;
  };

  
  typedef enum {
    NONE       = 0,
    PASS       = 1,
    FAIL       = 2,
    INCONC     = 3,
    ERROR      = 4,
    USER_ERROR = 5
  } VerdictValueEnum;

  class VerdictValue : public virtual TciValue {
  public:
    virtual ~VerdictValue();
    virtual const VerdictValueEnum &getVerdict() const = 0;
    virtual void setVerdict(const VerdictValueEnum & p_enum) = 0;
    virtual Tboolean operator==(const VerdictValue &verdictVal) const = 0;
    virtual VerdictValue *clone() const = 0;
    virtual Tboolean operator<(const VerdictValue &verdictVal) const = 0;
  };

  
  class AddressValue {
  public:
    virtual ~AddressValue();
    virtual const TciValue &getAddress() const = 0;
    virtual void setAddress(const TciValue &T) = 0;
    virtual Tboolean operator==(const AddressValue &addr) const = 0;
    virtual AddressValue *cloneAddressValue() const = 0;
    virtual Tboolean operator<(const AddressValue &addr) const = 0;
  };


  class TciValueTemplate {
  public:
    virtual ~TciValueTemplate();
    virtual Tboolean isOmit() const = 0;
    virtual Tboolean isAny() const = 0;
    virtual Tboolean isAnyOrOmit() const = 0;
    virtual const Tstring &getTemplateDef() const = 0;
    virtual Tboolean operator==(const TciValueTemplate &vtempl) const = 0;
    virtual TciValueTemplate *clone() const = 0;
    virtual Tboolean operator<(const TciValueTemplate &vtempl) const = 0;
  };
  

  class TciNonValueTemplate {
  public:
    virtual ~TciNonValueTemplate();
    virtual Tboolean isAny() const = 0;
    virtual Tboolean isAll() const = 0;
    virtual const Tstring &getTemplateDef() const = 0;
    virtual Tboolean operator==(const TciNonValueTemplate &nvtempl) const = 0;
    virtual TciNonValueTemplate *clone() const = 0;
    virtual Tboolean operator<(const TciNonValueTemplate &nvtempl) const = 0;
  };


  /**
   * A value of TciModuleParameterIdType is the qualified name of a TTCN-3 module parameter
   * as specified in the TTCN-3 ATS. This abstract type is used for module
   * parameter handling.
   */
  class TciModuleParameterId : ORG_ETSI_TTCN3_TRI::QualifiedName {
  public:
    virtual ~TciModuleParameterId();
    virtual Tboolean operator==(const TciModuleParameterId &mparId) const = 0;
    virtual TciModuleParameterId *clone() const = 0;
    virtual Tboolean operator<(const TciModuleParameterId &mparId) const = 0;
  };


  /**
   * A value of TciValueList is a list of values.
   */
  class TciValueList {
  public:
    virtual ~TciValueList();
    virtual Tsize size() const = 0;
    virtual Tboolean empty() const = 0;
    virtual const TciValue *get(Tindex index) const = 0;
    virtual void clear() = 0;
    virtual void add(const TciValue &comp) = 0;
    virtual Tboolean operator==(const TciValueList &valList) const = 0;
    virtual TciValueList *clone() const = 0;
    virtual Tboolean operator<(const TciValueList &valList) const = 0;
  };
  

  typedef enum {
    TCI_OK    = 0,
    TCI_ERROR = -1
  } TciStatus;


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
  class TciModuleId {
  public:
    virtual ~TciModuleId();
    virtual const Tstring &getObjectName() const = 0;
    virtual void setObjectName(const Tstring &p_name) = 0;
    virtual Tboolean operator==(const TciModuleId &mid) const = 0;
    virtual TciModuleId *clone() const = 0;
    virtual Tboolean operator<(const TciModuleId &mid) const = 0;
  };
  
  /**
   * A value of type TciModuleIdListType is a list of TciModuleIdType. This
   * abstract type is used when retrieving the list of modules which are imported by a
   * TTCN-3 module.
   *
   * @todo There is no definition in the TTCN-3 standard specification
   */
  class TciModuleIdList {
  public:
    virtual ~TciModuleIdList();
    virtual Tsize size() const = 0;
    virtual Tboolean empty() const = 0;
    virtual const TciModuleId *get(Tsize p_index) const = 0;
    virtual void clear() = 0;
    virtual void push_back(const TciModuleId &comp) = 0;
    virtual Tboolean operator==(const TciModuleIdList &midList) const = 0;
    virtual TciModuleIdList *clone() const = 0;
    virtual Tboolean operator<(const TciModuleIdList &midList) const = 0;
  };
  
  /**
   * A value of type TciModuleParameterType is a structure of
   * TciModuleParameterIdType and Value. This abstract type is used to
   * represent the parameter name and the default value of a module parameter.
   */
  class TciModuleParameter {
  public:
    virtual ~TciModuleParameter();
    virtual const TciValue &getDefaultValue() const = 0;
    virtual const Tstring &getModuleParameterName() const = 0;
    virtual const TciModuleParameterId &getTciModuleParameterId() const = 0;
    virtual Tboolean operator==(const TciModuleParameter &mpar) const = 0;
    virtual TciModuleParameter *clone() const = 0;
    virtual Tboolean operator<(const TciModuleParameter &mpar) const = 0;
  };
  
  /**
   * A value of type TciModuleParameterListType is a list of
   * TciModuleParameterType. This abstract type is used when retrieving the
   * module parameters of a TTCN-3 module.
   */
  class TciModuleParameterList {
  public:
    virtual ~TciModuleParameterList();
    virtual Tsize size () const = 0;
    virtual Tboolean empty () const = 0;
    virtual const TciModuleParameter *get(Tindex p_index) const = 0;
    virtual void clear() = 0;
    virtual void push_back(const TciModuleParameter &comp) = 0;
    virtual Tboolean operator==(const TciModuleParameterList &mparList) const = 0;
    virtual TciModuleParameterList *clone () const = 0;
    virtual Tboolean operator<(const TciModuleParameterList &mparList) const = 0;
  };
  
  /**
   * A value of type TciParameterPassingModeType is either IN, INOUT, or
   * OUT. This abstract type is used when starting a test case or when the termination of a
   * test case is indicated.
   */
  typedef enum {
    IN = 0,
    OUT = 1,
    INOUT = 2
  } TciParameterPassingMode;
  
  /**
   * A value of type TciParameterType includes a TTCN-3 Value and a value of
   * TciParameterPassingModeType to represent the parameter passing mode
   * specified for the parameter in the TTCN-3 ATS.
   */
  class TciParameter {
  public:
    virtual ~TciParameter();
    virtual const TciValue &getValue() const = 0;
    virtual void setValue(TciValue &value) = 0;
    virtual const TciParameterPassingMode &getParameterPassingMode() const = 0;
    virtual void setParameterPassingMode(const TciParameterPassingMode &mode) = 0;
    virtual const Tstring &getParameterName() const = 0;
    virtual void setParameterName(const Tstring &name) = 0;
    virtual Tboolean operator==(const TciParameter &param) const = 0;
    virtual TciParameter *clone() const = 0;
    virtual Tboolean operator<(const TciParameter &param) const = 0;
  };
  
  /**
   * A value of type TciParameterListType is a list of TciParameterType.
   * This abstract type is used when starting a test case or when the termination of a test
   * case is indicated.
   *
   * @a length 0 shall be interpreted as "empty list".
   */
  class TciParameterList {
  public:
    virtual ~TciParameterList();
    virtual Tsize size() const = 0;
    virtual Tboolean empty() const = 0;
    virtual const TciParameter *get(Tindex p_index) const = 0;
    virtual void clear() = 0;
    virtual void push_back(const TciParameter &comp) = 0;
    virtual Tboolean operator==(const TciParameterList &param) const = 0;
    virtual TciParameterList *clone() const = 0;
    virtual Tboolean operator<(const TciParameterList &param) const = 0;
  };

  /**
   * A value of type TciParameterTypeType is a structure of Type and
   * TciParameterPassingModeType. This abstract type is used to represent the
   * type and the parameter passing mode of a test case parameter.
   */
  class TciParameterType {
  public:
    virtual ~TciParameterType ();
    virtual const TciType &getType() const = 0;
    virtual const TciParameterPassingMode &getParameterPassingMode() const = 0;
    virtual Tboolean operator==(const TciParameterType &parType) const = 0;
    virtual TciParameterType *clone() const = 0;
    virtual Tboolean operator<(const TciParameterType &parType) const = 0;
  };
  
  /**
   * A value of type TciParameterTypeListType is a list of
   * TciParameterTypeType. This abstract type is used to represent the list of
   * parameters of a test case.
   *
   * length 0 shall be interpreted as "empty list".
   */
  class TciParameterTypeList {
  public:
    virtual ~TciParameterTypeList();
    virtual Tsize size() const = 0;
    virtual Tboolean empty() const = 0;
    virtual const TciParameterType *get(Tindex p_position) const = 0;
    virtual void clear() = 0;
    virtual void push_back(const TciParameterType &comp) = 0;
    virtual Tboolean operator==(const TciParameterTypeList &ptypeList) const = 0;
    virtual TciParameterTypeList *clone() const = 0;
    virtual Tboolean operator<(const TciParameterTypeList &ptypeList) const = 0;
  };
  
  /**
   * A value of TciTestCaseIdType is the qualified name of a TTCN-3 testcase as
   * specified in the TTCN-3 ATS. This abstract type is used for testcase handling.
   */
  class TciTestCaseId : TciBehaviourId {
  public:
    virtual ~TciTestCaseId();
    virtual Tboolean operator==(const TciTestCaseId &tcid) const = 0;
    virtual TciTestCaseId *clone() const = 0;
    virtual Tboolean operator<(const TciTestCaseId &tcid) const = 0;
  };


  /**
   * A value of type TciTypeClassType is a literal of the set of type classes in
   * TTCN-3 such as boolean, float, record, etc. This abstract type is used for value
   * handling.
   */
  typedef enum {
    TCI_ADDRESS = 0,
    TCI_ANYTYPE = 1,
    TCI_BITSTRING = 2,
    TCI_BOOLEAN = 3,
    TCI_CHARSTRING = 5,
    TCI_COMPONENT = 6,
    TCI_ENUMERATED = 7,
    TCI_FLOAT = 8,
    TCI_HEXSTRING = 9,
    TCI_INTEGER = 10,
    TCI_OCTETSTRING = 12,
    TCI_RECORD = 13,
    TCI_RECORD_OF = 14,
    TCI_ARRAY = 15,
    TCI_SET = 16,
    TCI_SET_OF = 17,
    TCI_UNION = 18,
    TCI_UNIVERSAL_CHARSTRING = 20,
    TCI_VERDICT = 21
  } TciTypeClass;


  /**
   * A value of type TciTestComponentKindType is a literal of the set of kinds of
   * TTCN-3 test components, i.e. MTC, PTC, PTC_ALIVE, and CONTROL. This
   * abstract type is used for component handling.
   */
  typedef enum {
    SYSTEM_COMP = 0,
    PTC_COMP = 1,
    PTC_ALIVE_COMP = 2,
    MTC_COMP = 3,
    CTRL_COMP = 4
  } TciTestComponentKind;


  /// @} TciDataManagement


  /**
   * @defgroup TciDataCommunication Communication
   * @{
   */


  /**
   * A value of type TciBehaviourIdType identifies a TTCN-3 behaviour
   * functions.
   */
  class TciBehaviourId : ORG_ETSI_TTCN3_TRI::QualifiedName {
  public:
    virtual ~TciBehaviourId();
    virtual Tboolean operator==(const TciBehaviourId &bid) const = 0;
    virtual TciBehaviourId *clone() const = 0;
    virtual Tboolean operator<(const TciBehaviourId &bid) const = 0;
  };

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
   * A value of TciValueDifference is a structure containing a value, a
   * template, and a description for the reason of this difference.
   */
  class TciValueDifference {
  public:
    virtual ~TciValueDifference();
    virtual const TciValue &getValue() const = 0;
    virtual void setValue(TciValue &val) = 0;
    virtual const TciValueTemplate &getTciValueTemplate() const = 0;
    virtual void setTciValueTemplate(TciValueTemplate &valT) = 0;
    virtual const Tstring &getDescription() const = 0;
    virtual void setDescription(const Tstring &descr) = 0;
    virtual Tboolean operator==(const TciValueDifference &vdiff) const = 0;
    virtual TciValueDifference *clone() const = 0;
    virtual Tboolean operator<(const TciValueDifference &vdiff) const = 0;
  };


  /**
   * A value of TciValueDifferenceList is a sequence of value
   * differences.
   * 
   * length 0 shall be interpreted as "empty list".
   */
  class TciValueDifferenceList {
  public:
    virtual ~TciValueDifferenceList();
    virtual Tsize size() const = 0;
    virtual Tboolean empty() const = 0;
    virtual const TciValueDifference *get(Tinteger p_position) const = 0;
    virtual void clear() = 0;
    virtual void add(const TciValueDifference &comp) = 0;
    virtual Tboolean operator==(const TciValueDifferenceList &vdList) const = 0;
    virtual TciValueDifferenceList *clone() const = 0;
    virtual Tboolean operator<(const TciValueDifferenceList &vdList) const = 0;
  };


  /**
   * A value of ComponentStatusType is either "inactiveC", "runningC",
   * "stoppedC", or "killedC".
   */
  typedef enum {
    INACTIVE_C = 0,
    RUNNING_C  = 1,
    STOPPED_C  = 2,
    KILLED_C   = 3,
    NULL_C     = 4
  } ComponentStatus;

  /**
   * A value of TimerStatusType is either "runningT", "inactiveT", or
   * "expiredT".
   */
  typedef enum {
    RUNNING_T  = 0,
    INACTIVE_T = 1,
    EXPIRED_T  = 2,
    NULL_T     = 3
  } TimerStatus;


  /// @} TciDataLoggingValue

  /// @} TciDataLogging

  /// @} TciData

  /// @} TciTypes

  /// @} Tci

} // namespace ORG_ETSI_TTCN3_TCI

#endif /* __TCI_H__ */
