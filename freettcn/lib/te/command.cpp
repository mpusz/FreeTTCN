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
 * @file   command.cpp
 * @author Mateusz Pusz
 * @date   Thu May 10 20:05:58 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/command.h"
#include "freettcn/te/testCase.h"
#include "freettcn/te/sourceData.h"


freettcn::TE::CCommand::CCommand(CTestComponentType::CInstance &comp, const CSourceData *srcData):
  _comp(comp), _srcData(srcData)
{
}


freettcn::TE::CCommand::~CCommand()
{
  if (_srcData)
    delete _srcData;
}




freettcn::TE::CCmdExecuteTimeout::CCmdExecuteTimeout(CTestComponentType::CInstance &comp,
                                                     freettcn::TE::CTestCase &testCase,
                                                     const TciParameterListType *parameterList,
                                                     TriTimerDuration duration, 
                                                     const CSourceData *srcData):
  CCommand(comp, srcData), _testCase(testCase), _parameterList(parameterList), _duration(duration)
{
}

bool freettcn::TE::CCmdExecuteTimeout::Run()
{
  // create MTC and start MTC
  _testCase.Start(const_cast<char *>(SrcData()->Source()), SrcData()->Line(), &Component(), _parameterList, _duration);
  
  // block Control component for the time of testcase execution
  Component().Status(CTestComponentType::CInstance::BLOCKED);
  
  return true;
}



freettcn::TE::CCmdExecuteWithoutTimeout::CCmdExecuteWithoutTimeout(CTestComponentType::CInstance &comp,
                                                                   freettcn::TE::CTestCase &testCase,
                                                                   const TciParameterListType *parameterList,
                                                                   const CSourceData *srcData):
  CCmdExecuteTimeout(comp, testCase, parameterList, 0, srcData)
{
}




freettcn::TE::CCmdStopEntityOp::CCmdStopEntityOp(CTestComponentType::CInstance &comp, const CSourceData *srcData):
  CCommand(comp, srcData)
{
}

bool freettcn::TE::CCmdStopEntityOp::Run()
{
  Component().Done(*SrcData());
  return true;
}
      


freettcn::TE::CCmdStopMTC::CCmdStopMTC(CTestComponentType::CInstance &comp, const CSourceData *srcData):
  CCommand(comp, srcData)
{
}

bool freettcn::TE::CCmdStopMTC::Run()
{
  Component().Done(*SrcData());
  return true;
}
      


