//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) compiler.

// freettcn is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// freettcn is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with freettcn; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   dumper.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#include "dumper.h"
#include "freettcn/tools/exception.h"



freettcn::translator::CDumper *freettcn::translator::CDumper::_instance = 0;

freettcn::translator::CDumper &freettcn::translator::CDumper::Instance()
{
  if (_instance)
    return *_instance;
  
  throw ENotInitialized(E_DATA, "Translator Logger instance not inited!!!");
}


freettcn::translator::CDumper::CDumper(std::ostream &stream):
  _stream(stream), _indent(0)
{
  _instance = this;
}


freettcn::translator::CDumper::~CDumper()
{
  _instance = 0;
}


void freettcn::translator::CDumper::Header()
{
  PrintLine("#include <freettcn/te/module.h>");
  PrintLine("#include <freettcn/te/testComponent.h>");
  PrintLine("#include <freettcn/te/testCase.h>");
  PrintLine("#include <freettcn/te/behavior.h>");
  PrintLine("#include <freettcn/te/port.h>");
  PrintLine("#include <freettcn/te/record.h>");
  PrintLine("#include <freettcn/te/template.h>");
  PrintLine("#include <freettcn/te/timer.h>");
  PrintLine("#include <freettcn/te/basicTypes.h>");
  PrintLine("#include <freettcn/te/sourceData.h>");
  PrintLine("");
  PrintLine("");
  PrintLine("#define MY_CAST         dynamic_cast");
  PrintLine("");
  PrintLine("namespace freettcn {");
  IndentIncr();
}


void freettcn::translator::CDumper::Footer()
{
  IndentDecr();
  PrintLine("");
  PrintLine("} // namespace freettcn");
}
