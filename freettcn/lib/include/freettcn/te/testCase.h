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
 * @file   testCase.h
 * @author Mateusz Pusz
 * @date   Wed Apr 25 10:49:25 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TESTCASE_H__
#define __TESTCASE_H__


extern "C" {
#include <freettcn/ttcn3/tci.h>
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/te/initObject.h>
#include <freettcn/te/port.h>


namespace freettcn {

  namespace TE {
    
    class CModule;
    class CBehavior;
    class CSourceData;
    class CTestComponentId;
    
    class CTestCase : public CInitObject {
      typedef std::list<CPortType::CInstance *> TPortList;
      
      CModule &_module;
      CSourceData const * const _srcData;
      const CTestComponentType &_mtcType;
      CBehavior * const _behavior;
      const CTestComponentType &_systemType;
      
      TciTestCaseIdType _id;
      
      // test case dynamic state
      TPortList _allPortStates;                   /**< a list of states of different ports */
      const CTestComponentId *_mtc;               /**< MTC reference */
//       TVerdict _verdict;                          /**< actual global test verdict of a test case,
//                                                      updated after every test component termination */
      void Cleanup();
      
    public:
      CTestCase(CModule &module, const char *name, const CSourceData *srcData,
                const CTestComponentType &mtcType, CBehavior *behavior,
                const CTestComponentType *systemType = 0);
      virtual ~CTestCase();
      
      TciParameterTypeListType Parameters() const;
      TriPortIdList SystemInterface() const;
      
      void Start(const char *src, int line,
                 const CTestComponentType::CInstance *creator,
                 const TciParameterListType *parameterList,
                 TriTimerDuration dur);
      void Execute(TciTestCaseIdType testCaseId, TriPortIdList tsiPortList);
      void Stop();
      
      void Register(CPortType::CInstance *port);
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TESTCASE_H__ */
