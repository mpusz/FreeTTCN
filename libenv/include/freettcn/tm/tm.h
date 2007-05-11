//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcnenv (Free TTCN Environment) library.

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
#include <freettcn/ttcn3/tci.h>
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/tools/logMask.h>
#include <freettcn/tools/entity.h>
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
      
    protected:
      class CTestCase {
        TciTestCaseIdType _id;
      public:
        CTestCase(const TciTestCaseIdType &id);
        ~CTestCase();
        std::string Name() const;
        TciTestCaseIdType Id() const;
        
        TciParameterTypeListType Parameters() const;
        TriPortIdList Interface() const;
        
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
      };
      
      typedef std::vector<CTestCase *> TTCList;
      typedef std::vector<CModuleParameter *> TModuleParList;
      
    private:
      static CTestManagement *_instance;
      
      bool _moduleRunning;                        /**< specifies if a test case or control part is running */
      TriComponentId _ctrlCompId;                 /**< component Id of running Control part */
      CTestCase *_tc;                             /**< currently started test case */
      TModuleParList _modParList;
      TTCList _tcList;
      
      CTestManagement& operator=(CTestManagement&);  // Disallowed
      CTestManagement(const CTestManagement&);       // Disallowed
      
      void Clear();
      
    protected:
      const TTCList &TCList() const;
      CTestCase &TestCaseGet(const std::string &testCaseId) const throw(ENotFound);
      const TModuleParList &ModuleParameterList() const;
      
    public:
      static CTestManagement &Instance() throw(ENotFound);
      
      CTestManagement();
      virtual ~CTestManagement();
      
      void Init(const std::string &moduleId) throw(EOperationFailed);
      
      virtual void Log(const TriComponentId &testComponentId, String message);
      virtual void Error(String message);
      void Abort();
      
      virtual TciValue ModuleParameterGet(const TciModuleParameterIdType &parameterId) const;
      
      virtual void TestCaseStart(const std::string &testCaseId, const TciParameterListType &parameterlist) throw(ENotFound);
      virtual void TestCaseStarted(const TciTestCaseIdType &testCaseId, const TciParameterListType &parameterList, double timer);
      virtual void TestCaseTerminated(TciVerdictValue verdict, const TciParameterListType &parameterlist);
      virtual void TestCaseStop() throw(EOperationFailed);
      
      virtual void ControlStart();
      virtual void ControlStop() throw(EOperationFailed);
      virtual void ControlTerminated();
    };
    
  } // namespace TM
  
} // namespace freettcn



#endif /* __TM_H__ */
