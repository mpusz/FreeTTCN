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


#include "freettcn/pa/pa.h"

extern "C" {
  //#include "freettcn/tri_pa_te.h"
  //#include "freettcn/tci_tl.h"
}


freettcn::PA::CLogMask::CLogMask(bool enabled /* true */):
  freettcn::CLogMask(freettcn::LOG_PA_NUM, enabled)
{
}

freettcn::PA::CLogMask::~CLogMask()
{
}



freettcn::PA::CPlatformAdaptor *freettcn::PA::CPlatformAdaptor::_instance = 0;

freettcn::PA::CPlatformAdaptor &freettcn::PA::CPlatformAdaptor::Instance() throw(ENotFound)
{
  if (_instance)
    return *_instance;
  
  throw ENotFound();
}

freettcn::PA::CPlatformAdaptor::CPlatformAdaptor()
{
  _instance = this;
}

freettcn::PA::CPlatformAdaptor::~CPlatformAdaptor()
{
  //  Clear();
  _instance = 0;
}


TriStatus freettcn::PA::CPlatformAdaptor::Reset()
{
  return TRI_OK;
}