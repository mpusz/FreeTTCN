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


extern "C" {
#include <freettcn/ttcn3/tri_te_sa.h>
}
#include "freettcn/sa/sa.h"



TriStatus triExecuteTestCase(const TriTestCaseId *testCaseId,
                             const TriPortIdList *tsiPortList)
{
  if (!testCaseId || !tsiPortList)
    return TRI_ERROR;
  
  freettcn::SA::CSUTAdaptor &sa = freettcn::SA::CSUTAdaptor::Instance();
  return sa.TestCaseExecute(*testCaseId, *tsiPortList);
}


TriStatus triMap(const TriPortId *compPortId,
                 const TriPortId *tsiPortId)
{
  if (!compPortId || !tsiPortId)
    return TRI_ERROR;
  
  freettcn::SA::CSUTAdaptor &sa = freettcn::SA::CSUTAdaptor::Instance();
  return sa.Map(*compPortId, *tsiPortId);
}


TriStatus triUnmap(const TriPortId *compPortId,
                   const TriPortId *tsiPortId)
{
  if (!compPortId || !tsiPortId)
    return TRI_ERROR;
  
  freettcn::SA::CSUTAdaptor &sa = freettcn::SA::CSUTAdaptor::Instance();
  return sa.Unmap(*compPortId, *tsiPortId);
}


TriStatus triSAReset()
{
  freettcn::SA::CSUTAdaptor &sa = freettcn::SA::CSUTAdaptor::Instance();
  return sa.Reset();
}
