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
 * @file   tl.cpp
 * @author Mateusz Pusz
 * @date   Fri Apr 20 08:11:42 2007
 * 
 * @brief  
 * 
 * 
 */


#include "freettcn/tools/tciValueDumper.h"
extern "C" {
#include "freettcn/ttcn3/tci_value.h"
}


const char *freettcn::CTciValueDumper::Boolean2String(TciValue value)
{
  const char *str[] = { "FALSE",
                        "TRUE" };
  
  return str[tciGetBooleanValue(value)];
}


const char *freettcn::CTciValueDumper::Verdict2String(TciVerdictValue value)
{
  const char *str[] = { "NONE",
                        "PASS",
                        "INCONC",
                        "FAIL",
                        "ERROR" };
  
  return str[tciGetVerdictValue(value)];
}
