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

namespace ORG_ETSI_TTCN3_TRI {

  /**
   * @addtogroup Tri TRI
   * @{
   */

  /**
   * @defgroup TriTypes Types
   * @{
   */

  class QualifiedName {
  public:
    ~QualifiedName();
    const Tstring &getModuleName() const;
    void setModuleName(const Tstring &mName);
    const Tstring &getObjectName () const;
    void setObjectName(const Tstring &oName);
    Tstring toString() const;
    Tboolean equals(const QualifiedName &qn) const;
    QualifiedName *cloneQualifiedName() const;
    Tboolean operator<(const QualifiedName &qn) const;
  };


  /**
   * @defgroup TriConnection Connection
   * @{
   */

  /**
   * A value of type TriComponentId includes an identifier, a name and the
   * component type. The distinct value of the latter is the component type name
   * as specified in the TTCN-3 ATS. This abstract type is mainly used to resolve
   * TRI communication operations on TSI ports that have mappings to many test
   * component ports.
   *
   * @note #compInst is for component instance
   */
  class TriComponentId {
  public:
    virtual ~TriComponentId();
    virtual const QualifiedName &getComponentTypeName() const = 0;
    virtual void setComponentTypeName(const QualifiedName &tName) = 0;
    virtual Tstring &getComponentName() const = 0;
    virtual void setComponentName(const Tstring &sName) = 0;
    virtual const Tinteger &getComponentId () const = 0;
    virtual void setComponentId(const Tinteger &id) = 0;
    virtual Tstring toString() const = 0;
    virtual Tboolean operator==(const TriComponentId &cmp) const = 0;
    virtual TriComponentId *cloneComponentId() const = 0;
    virtual Tboolean operator<(const TriComponentId &cmp) const = 0;
  };


  /**
   * A value of type TriComponentIdList is a list of TriComponentId. This
   * abstract type is used for multicast communication in TCI.
   *
   * @note No special values mark the end of #compIdList. The #length field shall
   *       be used to traverse this array properly.
   */
  class TriComponentIdList {
  public:
    virtual ~TriComponentIdList();
    virtual Tsize size() const = 0;
    virtual Tboolean isEmpty() const = 0;
    virtual const TriComponentId &get(Tsize index) const = 0;
    virtual void clear() = 0;
    virtual void add(const TriComponentId &comp) = 0;
    virtual Tboolean operator==(const TriComponentIdList &cmpl) const = 0;
    virtual TriComponentIdList *cloneComponentIdList() const = 0;
    virtual Tboolean operator<(const TriComponentIdList &cmpl) const = 0;
  };


  /**
   * A value of type TriPortId includes a value of type TriComponentId to
   * represent the component to which the port belongs, a port index (if present),
   * and the port name as specified in the TTCN-3 ATS. The TriPortId type is
   * mainly required to pass information about the TSI and connections to the TSI
   * from the TE to the SA.
   *
   * @note #compInst is for component instance
   * @note For a singular (non-array) declaration, the #portIndex value should
   *       be @c -1
   * @note The #aux is for future extensibility of TRI functionality
   */
  class TriPortId {
  public:
    virtual ~TriPortId(void);
    virtual const Tstring &getPortName() const = 0;
    void setPortName(const Tstring &pName) = 0;
    const TriComponentId &getComponent() const = 0;
    void setComponent(const TriComponentId &comp) = 0;
    Tsize getPortIndex() const = 0;
    void setPortIndex(Tsize index) = 0;
    const QualifiedName &getPortType() const = 0;
    void setPortType(const QualifiedName &pType) = 0;
    Tboolean isArray() const = 0;
    Tboolean operator==(const TriPortId &prt) const = 0;
    TriPortId *clonePortId() const = 0;
    Tboolean operator<(const TriPortId &prt) const = 0;
  };


  /**
   * A value of type TriPortIdList is a list of TriPortId. This abstract type is
   * used for initialization purposes after the invocation of a TTCN-3 test case.
   *
   * @note No special values mark the end of #portIdList. The #length field shall
   *       be used to traverse this array properly.
   */
  class TriPortIdList {
  public:
    virtual ~TriPortIdList();
    virtual Tsize size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual const TriPortId &get(Tsize index) const = 0;
    virtual void clear() = 0;
    virtual void add(const TriPortId &elem) = 0;
    virtual Tboolean operator==(const TriPortIdList &prtl) const = 0;
    virtual TriPortIdList *clonePortIdList() const = 0;
    virtual Tboolean operator<(const TriPortIdList &prtl) const = 0;
  };

  /// @} TriConnection




  /**
   * @defgroup TriCommunication Communication
   * @{
   */

  /**
   * A value of type TriMessage is encoded test data that either is to be sent to
   * the SUT or has been received from the SUT.
   */
  class TriMessage {
  public:
    virtual ~TriMessage();
    virtual const Tbyte *getData() const = 0;
    virtual void setData(const Tbyte *str, Tsize bitLen) = 0;
    virtual Tsize getBitsDataLen() const = 0;
    virtual Tstring toString() const = 0;
    virtual Tboolean operator==(const TriMessage &msg) const = 0;
    virtual TriMessage *cloneMessage() const = 0;
    virtual Tboolean operator<(const TriMessage &msg) const = 0;
  };
  
  
  /**
   * A value of type TriAddress indicates a source or destination address within
   * the SUT. This abstract type can be used in TRI communication operations and is
   * an open type, which is opaque to the TE.
   */
  class TriAddress {
  public:
    virtual ~TriAddress();
    virtual const Tbyte *getEncodedData()const = 0;
    virtual void setEncodedData(const Tbyte *str, Tsize bitLen) = 0;
    virtual Tsize getBitsDataLen()const = 0;
    virtual Tboolean operator==(const TriAddress &add) const = 0;
    virtual TriAddress *cloneAddress() const = 0;
    virtual Tboolean operator<(const TriAddress &add) const = 0;
  };


  /**
   * A value of type TriAddressList is a list of #TriAddress. This abstract
   * type is used for multicast communication in TRI.
   *
   * @note No special values mark the end of #addrList. The #length field shall be
   *       used to traverse this array properly.
   */
  class TriAddressList {
  public:
    virtual ~TriAddressList();
    virtual Tsize size() const = 0;
    virtual Tboolean isEmpty() const = 0;
    virtual const TriAddress &get(Tsize index) const = 0;
    virtual void clear() = 0;
    virtual void add(const TriAddress &elem) = 0;
    virtual Tboolean operator==(const TriAddressList &addl) const = 0;
    virtual TriAddressList *cloneAddressList() const = 0;
    virtual Tboolean operator<(const TriAddressList &addl) const = 0;
  };


  /**
   * A value of type TriSignatureId is the name of a procedure signature as
   * specified in the TTCN-3 ATS. This abstract type is used in procedure based TRI
   * communication operations.
   */
  class TriSignatureId : QualifiedName {
  public:
    virtual ~TriSignatureId();
    virtual Tboolean operator==(const TriSignatureId &sid) const = 0;
    virtual TriSignatureId *cloneSignatureId () const = 0;
    virtual Tboolean operator<(const TriSignatureId &sid) const = 0;
  };
  
  
  /**
   * A value of type TriParameterPassingMode is either @a in, @a inout, or @a out.
   * This abstract type is used in procedure based TRI communication operations
   * and for external function calls.
   *
   * @note The values of instances of this type shall reflect the parameter
   *       passing mode defined in the corresponding TTCN-3 procedure signatures.
   */
  typedef enum {
    IN = 0,
    OUT = 1,
    INOUT = 2
  } TriParameterPassingMode;


  /**
   * A value of type TriParameter includes an encoded parameter and a value of
   * #TriParameterPassingMode to represent the passing mode specified for the
   * parameter in the TTCN-3 ATS.
   */
  class TriParameter {
  public:
    virtual ~TriParameter();
    virtual const Tstring &getParameterName() const = 0;
    virtual void setParameterName(const Tstring &name) = 0;
    virtual const TriParameterPassingMode &getParameterPassingMode() const = 0;
    virtual void setParameterPassingMode(const TriParameterPassingMode &mode) = 0;
    virtual const Tbyte *getEncodedParameter() const = 0;
    virtual void setEncodedParameter(const Tbyte *str, Tsize bitLen) = 0;
    virtual Tsize getBitsDataLen() const = 0;
    virtual Tboolean operator==(const TriParameter &par) const = 0;
    virtual TriParameter *cloneParameter() const = 0;
    virtual Tboolean operator<(const TriParameter &par) const = 0;
  };


  /**
   * A value of type TriParameterList is a list of TriParameter. This
   * abstract type is used in procedure based TRI communication operations and for
   * external function calls.
   *
   * @note No special values mark the end of #parList. The #length field shall be
   *       used to traverse this array properly.
   */
  class TriParameterList {
  public:
    virtual ~TriParameterList();
    virtual Tsize size() const = 0;
    virtual Tboolean isEmpty() const = 0;
    virtual const TriParameter &get(Tsize index) const = 0;
    virtual void clear() = 0;
    virtual void add(const TriParameter &parameter) = 0;
    virtual Tboolean operator==(const TriParameterList &pml) const = 0;
    virtual TriParameterList *cloneParameterList() const = 0;
    virtual Tboolean operator<(const TriParameterList &pml) const = 0;
  };
  

  /**
   * A value of type TriException is an encoded type and value of an exception
   * that either is to be sent to the SUT or has been received from the SUT. This
   * abstract type is used in procedure based TRI communication operations.
   */
  class TriException {
  public:
    virtual ~TriException();
    virtual const Tbyte *getData() const = 0;
    virtual void setData(const Tbyte *str, Tsize bitLen) = 0;
    virtual Tsize getBitsDataLen() const = 0;
    virtual Tstring toString() const = 0;
    virtual Tboolean operator==(const TriException &exc) const = 0;
    virtual TriException *cloneException() const = 0;
    virtual Tboolean operator<(const TriException &exc) const = 0;
  };

  /// @} TriCommunication




  /**
   * @defgroup TriTimer Timer
   * @{
   */

  /**
   * A value of type TriTimerId specifies an identifier for a timer. This abstract
   * type is required for all TRI timer operations.
   *
   * @note Pending ETSI statement on timer and snapshot semantics may influence
   *       future representation!
   */
  class TriTimerId {
  public:
    virtual ~TriTimerId();
    virtual const Tstring &getTimerName() const = 0;
    virtual void setTimerName (const Tstring &tName) = 0;
    virtual const Tinteger getTId() const = 0;
    virtual Tboolean operator==(const TriTimerId &tmid) const = 0;
    virtual TriTimerId *cloneTimerId() const = 0;
    virtual Tboolean operator<(const TriTimerId &tmid) const = 0;
  };
  
  
  /**
   * A value of type TriTimerDuration specifies the duration for a timer in
   * seconds.
   */
  class TriTimerDuration {
  public:
    virtual ~TriTimerDuration();
    virtual Tfloat getDuration() const = 0;
    virtual void setDuration(Tfloat duration) = 0;
    virtual Tboolean operator==(const TriTimerDuration &timd) const = 0;
    virtual TriTimerDuration *cloneTimerDuration() const = 0;
    virtual Tboolean operator<(const TriTimerDuration &timd) const = 0;
  };
  
  /// @} TriTimer




  /**
   * @defgroup TriMiscellaneous Miscellaneous
   * @{
   */

  /**
   * A value of type TriTestCaseId is the name of a test case as specified in the
   * TTCN-3 ATS.
   */
  class TriTestCaseId : QualifiedName {
  public:
    virtual ~TriTestCaseId();
    virtual Tboolean operator==(const TriTestCaseId &tcid) const = 0;
    virtual TriTestCaseId *cloneTestCaseId() const = 0;
    virtual Tboolean operator<(const TriTestCaseId &tcid) const = 0;
  };
  
  
  /**
   * A value of type TriFunctionId is the name of an external function as
   * specified in the TTCN-3 ATS.
   */
  class TriFunctionId : QualifiedName {
  public:
    virtual ~TriFunctionId();
    virtual Tboolean operator==(const TriFunctionId &fid) const = 0;
    virtual TriFunctionId *cloneFunctionId() const = 0;
    virtual Tboolean operator<(const TriFunctionId &fid) const = 0;
  };


  /**
   * A value of type TriStatus is either @c TRI_OK or @c TRI_ERROR indicating the
   * success or failure of a TRI operation.
   *
   * @note All negative values are reserverd for future extension of TRI
   *       functionality
   */
  typedef enum {
    TRI_OK    = 0,
    TRI_ERROR = -1
  } TriStatus;
  
  /// @} TriMiscellaneous

  /// @} TriTypes

  /// @} Tri

} // namespace ORG_ETSI_TTCN3_TRI

#endif /* __TRI_H__ */
