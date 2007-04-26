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


extern "C" {
#include "freettcn/tri_te_sa.h"
}
#include "sa.h"



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
