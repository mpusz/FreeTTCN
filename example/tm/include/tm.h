//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) usage example.

// This example is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This example is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this example; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   tm.h
 * @author Mateusz Pusz
 * @date   Fri Apr  6 17:52:52 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TM_H__
#define __TM_H__


extern "C" {
#include "freettcn/tci.h"
#include "freettcn/tri.h"
}
#include "tools.h"
#include <string>
#include <vector>


namespace freettcn {
  
  namespace TM {
    
    class CLogMask : public freettcn::CLogMask {
    public:
      CLogMask(bool enabled = true);
      ~CLogMask();
    };
    
    
    
    class CTestManagement : public freettcn::CEntity {
      
      class CTestCase {
        TciTestCaseIdType _id;
      public:
        CTestCase(const TciTestCaseIdType &id);
        ~CTestCase();
        std::string Name() const;
        TciTestCaseIdType Id() const;
        void Print() const;
        
        void Start(const TciParameterListType &parameterlist);
        void Started(const TciParameterListType &parameterList, double timer);
        void Terminated(TciVerdictValue verdict, const TciParameterListType &parameterlist);
        void Stop();
      };
      
      class CModuleParameter {
        TciModuleParameterIdType _parName;
        TciValue _defaultValue;
        TciValue _value;
      public:
        CModuleParameter(const TciModuleParameterType &par);
        ~CModuleParameter();
        std::string Name() const;
        TciValue Value() throw(EOperationFailed);
        void Print() const;
      };
      
      typedef std::vector<CTestCase *> TCList;
      typedef std::vector<CModuleParameter *> ModuleParList;
      
      static CTestManagement *_instance;
      
      bool _moduleRunning;                        /**< specifies if a test case or control part is running */
      TriComponentId _ctrlCompId;                 /**< component Id of running Control part */
      CTestCase *_tc;                             /**< currently started test case */
      ModuleParList _modParList;
      TCList _tcList;
      
      CTestManagement& operator=(CTestManagement&);  // Disallowed
      CTestManagement(const CTestManagement&);       // Disallowed
      
      void Clear();
      CTestCase &TestCaseGet(const std::string &testCaseId) const throw(ENotFound);
      void ModuleParamsSet();
      
    public:
      static CTestManagement &Instance() throw(ENotFound);
      
      CTestManagement();
      virtual ~CTestManagement();
      
      void Init(const std::string &moduleId) throw(EOperationFailed);
      
      virtual void Log(const TriComponentId &testComponentId, String message);
      virtual void Error(String message);
      void Abort();
      
      virtual TciValue ModuleParameterGet(const TciModuleParameterIdType &parameterId) const;
      
      void TestCaseInit(const std::string &testCaseId) throw(ENotFound);
      void TestCaseStart(const std::string &testCaseId, const TciParameterListType &parameterlist) throw(ENotFound);
      void TestCaseStarted(const TciTestCaseIdType &testCaseId, const TciParameterListType &parameterList, double timer);
      void TestCaseTerminated(TciVerdictValue verdict, const TciParameterListType &parameterlist);
      void TestCaseStop() throw(EOperationFailed);

      void ControlInit();
      void ControlStart();
      void ControlStop() throw(EOperationFailed);
      void ControlTerminated();
    };
    
  } // namespace TM
  
} // namespace freettcn



#endif /* __TM_H__ */
