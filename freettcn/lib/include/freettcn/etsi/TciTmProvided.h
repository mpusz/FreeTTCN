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
 * @file   TciTmProvided.h
 * @author Mateusz Pusz
 * @date   Fri Feb  2 08:50:45 2007
 * 
 * @brief  TTCN-3 Executable TCI types
 *
 * @remarks This file implements interfaces specified in the ETSI standards:
 *  - ES 201 873-6: "Methods for Testing and Specification (MTS); The Testing and Test Control Notation version 3; Part 6: TTCN-3 Control Interface (TCI)"
 * 
 */

#ifndef __TCI_TM_PROVIDED_H__
#define __TCI_TM_PROVIDED_H__

#include <freettcn/etsi/tci.h>

namespace ORG_ETSI_TTCN3_TCI {
  
  class TciTmProvided {
  public:
    //Destructor
    virtual ~TciTmProvided();
    //Indicates to the TM that a test case with testCaseId has been started
    virtual void tciTestCaseStarted(const TciTestCaseId &testCaseId, const TciParameterList &parameterList,
                                    const Tfloat &timer) = 0;
    //Called to indicate that the test case has terminated execution
    virtual void tciTestCaseTerminated(const VerdictValue &verdict, const TciParameterList &parameterList) = 0;
    //Called to indicate that the control part of the selected module has just terminated execution
    virtual void tciControlTerminated() = 0;
    //The management provides to the TE a Value for the indicated parameterId
    virtual TciValue *tciGetModulePar(const TciModuleParameterId &parameterId) = 0;
    //Indicates the occurrence of an unrecoverable error situation
    virtual void tciError(const Tstring &message) = 0;
    //The TE indicates a message of a test component
    virtual void tciLog(const TriComponentId &testComponentId, const Tstring &message) = 0;
  };
  
} // namespace ORG_ETSI_TTCN3_TCI

#endif /* __TCI_TM_PROVIDED_H__ */
