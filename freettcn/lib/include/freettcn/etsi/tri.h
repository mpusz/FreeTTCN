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

#include <freettcn/etsi/types.h>

namespace ORG_ETSI_TTCN3_TRI {

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
    /// @todo const missing in spec
#ifdef ISSUE_0005947
    virtual const Tstring &getComponentName() const = 0;
#else
    virtual Tstring &getComponentName() const = 0;
#endif
    virtual void setComponentName(const Tstring &sName) = 0;
    virtual const Tinteger &getComponentId() const = 0;
    virtual void setComponentId(const Tinteger &id) = 0;
    /// @todo why is that here?
    virtual Tstring toString() const = 0;
    virtual Tboolean operator==(const TriComponentId &cmp) const = 0;
#ifdef ISSUE_0005949
    virtual TriComponentId *clone() const = 0;
#else
    virtual TriComponentId *cloneComponentId() const = 0;
#endif
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
#ifdef ISSUE_0005949
    virtual Tboolean empty() const = 0;
#else
    virtual Tboolean isEmpty() const = 0;
#endif
#ifdef ISSUE_0005949
    virtual const TriComponentId *get(Tsize index) const = 0;
#else
    virtual const TriComponentId &get(Tsize index) const = 0;
#endif
    virtual void clear() = 0;
#ifdef ISSUE_0005949
    virtual void push_back(const TriComponentId &comp) = 0;
#else
    virtual void add(const TriComponentId &comp) = 0;
#endif
    virtual Tboolean operator==(const TriComponentIdList &cmpl) const = 0;
#ifdef ISSUE_0005949
    virtual TriComponentIdList *clone() const = 0;
#else
    virtual TriComponentIdList *cloneComponentIdList() const = 0;
#endif
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
    virtual void setPortName(const Tstring &pName) = 0;
    virtual const TriComponentId &getComponent() const = 0;
    virtual void setComponent(const TriComponentId &comp) = 0;
    virtual Tsize getPortIndex() const = 0;
    virtual void setPortIndex(Tsize index) = 0;
    virtual const QualifiedName &getPortType() const = 0;
    virtual void setPortType(const QualifiedName &pType) = 0;
    virtual Tboolean isArray() const = 0;
    virtual Tboolean operator==(const TriPortId &prt) const = 0;
#ifdef ISSUE_0005949
    virtual TriPortId *clone() const = 0;
#else
    virtual TriPortId *clonePortId() const = 0;
#endif
    virtual Tboolean operator<(const TriPortId &prt) const = 0;
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
#ifdef ISSUE_0005949
    virtual bool empty() const = 0;
#else
    virtual bool isEmpty() const = 0;
#endif
#ifdef ISSUE_0005949
    virtual const TriPortId *get(Tsize index) const = 0;
#else
    virtual const TriPortId &get(Tsize index) const = 0;
#endif
    virtual void clear() = 0;
#ifdef ISSUE_0005949
    virtual void push_back(const TriPortId &elem) = 0;
#else
    virtual void add(const TriPortId &elem) = 0;
#endif
    virtual Tboolean operator==(const TriPortIdList &prtl) const = 0;
#ifdef ISSUE_0005949
    virtual TriPortIdList *clone() const = 0;
#else
    virtual TriPortIdList *clonePortIdList() const = 0;
#endif
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
    /// @todo why is that here?
    virtual Tstring toString() const = 0;
    virtual Tboolean operator==(const TriMessage &msg) const = 0;
#ifdef ISSUE_0005949
    virtual TriMessage *clone() const = 0;
#else
    virtual TriMessage *cloneMessage() const = 0;
#endif
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
#ifdef ISSUE_0005949
    virtual TriAddress *clone() const = 0;
#else
    virtual TriAddress *cloneAddress() const = 0;
#endif
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
#ifdef ISSUE_0005949
    virtual Tboolean empty() const = 0;
#else
    virtual Tboolean isEmpty() const = 0;
#endif
#ifdef ISSUE_0005949
    virtual const TriAddress *get(Tsize index) const = 0;
#else
    virtual const TriAddress &get(Tsize index) const = 0;
#endif
    virtual void clear() = 0;
#ifdef ISSUE_0005949
    virtual void push_back(const TriAddress &elem) = 0;
#else
    virtual void add(const TriAddress &elem) = 0;
#endif
    virtual Tboolean operator==(const TriAddressList &addl) const = 0;
#ifdef ISSUE_0005949
    virtual TriAddressList *clone() const = 0;
#else
    virtual TriAddressList *cloneAddressList() const = 0;
#endif
    virtual Tboolean operator<(const TriAddressList &addl) const = 0;
  };


  /**
   * A value of type TriSignatureId is the name of a procedure signature as
   * specified in the TTCN-3 ATS. This abstract type is used in procedure based TRI
   * communication operations.
   */
#ifdef ISSUE_0005946_A
  class TriSignatureId : public QualifiedName {
#elif ISSUE_0005946_B
  class TriSignatureId {
#else
  class TriSignatureId : QualifiedName {
#endif
  public:
    virtual ~TriSignatureId();
    virtual Tboolean operator==(const TriSignatureId &sid) const = 0;
#ifdef ISSUE_0005946_A
    // nothing here
#elif defined(ISSUE_0005946_B) || defined(ISSUE_0005949)
    virtual TriSignatureId *clone() const = 0;
#ifdef ISSUE_0005946_B
    virtual const QualifiedName &getName() const = 0;
#endif
#else
    virtual TriSignatureId *cloneSignatureId() const = 0;
#endif
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
#ifdef ISSUE_0005949
    virtual TriParameter *clone() const = 0;
#else
    virtual TriParameter *cloneParameter() const = 0;
#endif
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
#ifdef ISSUE_0005949
    virtual Tboolean empty() const = 0;
#else
    virtual Tboolean isEmpty() const = 0;
#endif
#ifdef ISSUE_0005949
    virtual const TriParameter *get(Tsize index) const = 0;
#else
    virtual const TriParameter &get(Tsize index) const = 0;
#endif
    virtual void clear() = 0;
#ifdef ISSUE_0005949
    virtual void push_back(const TriParameter &parameter) = 0;
#else
    virtual void add(const TriParameter &parameter) = 0;
#endif
    virtual Tboolean operator==(const TriParameterList &pml) const = 0;
#ifdef ISSUE_0005949
    virtual TriParameterList *clone() const = 0;
#else
    virtual TriParameterList *cloneParameterList() const = 0;
#endif
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
    /// @todo why is that here?
    virtual Tstring toString() const = 0;
    virtual Tboolean operator==(const TriException &exc) const = 0;
#ifdef ISSUE_0005949
    virtual TriException *clone() const = 0;
#else
    virtual TriException *cloneException() const = 0;
#endif
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
    virtual void setTimerName(const Tstring &tName) = 0;
    /// @todo what is that???
    virtual const Tinteger getTId() const = 0;
    virtual Tboolean operator==(const TriTimerId &tmid) const = 0;
#ifdef ISSUE_0005949
    virtual TriTimerId *clone() const = 0;
#else
    virtual TriTimerId *cloneTimerId() const = 0;
#endif
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
#ifdef ISSUE_0005949
    virtual TriTimerDuration *clone() const = 0;
#else
    virtual TriTimerDuration *cloneTimerDuration() const = 0;
#endif
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
#ifdef ISSUE_0005946_A
  class TriTestCaseId : public QualifiedName {
#elif ISSUE_0005946_B
  class TriTestCaseId {
#else
  class TriTestCaseId : QualifiedName {
#endif
  public:
    virtual ~TriTestCaseId();
    virtual Tboolean operator==(const TriTestCaseId &tcid) const = 0;
#ifdef ISSUE_0005946_A
    // nothing here
#elif defined(ISSUE_0005946_B) || defined(ISSUE_0005949)
    virtual TriTestCaseId *clone() const = 0;
#ifdef ISSUE_0005946_B
    virtual const QualifiedName &getName() const = 0;
#endif
#else
    virtual TriTestCaseId *cloneTestCaseId() const = 0;
#endif
    virtual Tboolean operator<(const TriTestCaseId &tcid) const = 0;
  };
  
  
  /**
   * A value of type TriFunctionId is the name of an external function as
   * specified in the TTCN-3 ATS.
   */
#ifdef ISSUE_0005946_A
  class TriFunctionId : public QualifiedName {
#elif ISSUE_0005946_B
  class TriFunctionId {
#else
  class TriFunctionId : QualifiedName {
#endif
  public:
    virtual ~TriFunctionId();
    virtual Tboolean operator==(const TriFunctionId &fid) const = 0;
#ifdef ISSUE_0005946_A
    // nothing here
#elif defined(ISSUE_0005946_B) || defined(ISSUE_0005949)
    virtual TriFunctionId *clone() const = 0;
#ifdef ISSUE_0005946_B
    virtual const QualifiedName &getName() const = 0;
#endif
#else
    virtual TriFunctionId *cloneFunctionId() const = 0;
#endif
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
