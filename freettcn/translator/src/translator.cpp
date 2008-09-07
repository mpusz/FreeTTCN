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
 * @file   translator.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#include "translator.h"
#include "location.h"
#include "logger.h"
#include "freettcn/tools/exception.h"



freettcn::translator::CTranslator *freettcn::translator::CTranslator::_instance = 0;

freettcn::translator::CTranslator &freettcn::translator::CTranslator::Instance()
{
  if (_instance)
    return *_instance;
  
  throw ENotInitialized(E_DATA, "Translator instance not inited!!!");
}


freettcn::translator::CTranslator::CTranslator(const std::string &inputName, CLogger &logger):
  _logger(logger), _errorNum(0), _warningNum(0), _line(1)
{
  _instance = this;
  
  _files.push_back(CFile(inputName));
  _filesStack.push(&(*_files.rbegin()));
}


freettcn::translator::CTranslator::~CTranslator()
{
  _instance = 0;
}


void freettcn::translator::CTranslator::Warning(const CLocation &loc, const std::string &msg)
{
  std::cerr << loc.File().FullName() << ":" << loc.Line() << ":" << loc.Pos() << ": "
            << "error: " << msg << std::endl;
  _warningNum++;
}


void freettcn::translator::CTranslator::Error(const CLocation &loc, const std::string &msg)
{
  std::cerr << loc.File().FullName() << ":" << loc.Line() << ":" << loc.Pos() << ": "
            << "error: " << msg << std::endl;
  _errorNum++;
}


void freettcn::translator::CTranslator::Start() const
{
  _logger.Header();
}


const freettcn::translator::CFile &freettcn::translator::CTranslator::File() const
{
  if(_filesStack.empty())
    throw EOperationFailed(E_DATA, "File not initialized!!!");
  
  return *_filesStack.top();
}


void freettcn::translator::CTranslator::Line(unsigned line)
{
  _line = line;
}


unsigned freettcn::translator::CTranslator::Line() const
{
  return _line;
}


void freettcn::translator::CTranslator::ModuleBegin(const CIdentifier *id)
{
  if(File().ModuleName().compare(id->Name()))
    Error(id->Loc(), "Module ID '" + id->Name() + "' does not match TTCN-3 file name");
  _logger.PrintLine("");
  _logger.PrintLine("namespace " + id->Name() + " {");
  _logger.IndentIncr();
}


void freettcn::translator::CTranslator::ModuleEnd()
{
  _logger.IndentDecr();
  _logger.PrintLine("");
  _logger.PrintLine("} // namespace ");// + std::string(name));
  
  _filesStack.pop();
  if(_filesStack.empty())
    _logger.Footer();
}
