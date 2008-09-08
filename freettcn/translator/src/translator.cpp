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
#include "module.h"
#include "logger.h"
#include "dumper.h"
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
  _logger.Warning(loc, msg);
  _warningNum++;
}


void freettcn::translator::CTranslator::Error(const CLocation &loc, const std::string &msg)
{
  _logger.Error(loc, msg);
  _errorNum++;
}


unsigned freettcn::translator::CTranslator::WarningNum() const
{
  return _warningNum;
}


unsigned freettcn::translator::CTranslator::ErrorNum() const
{
  return _errorNum;
}


void freettcn::translator::CTranslator::Dump(CDumper &dumper) const
{
  dumper.Header();
  _module->Dump(dumper);
  dumper.Footer();
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


// unsigned freettcn::translator::CTranslator::Line() const
// {
//   return _line;
// }


void freettcn::translator::CTranslator::ModuleBegin(const CIdentifier *id, const std::string &language)
{
  std::auto_ptr<const CIdentifier> idPtr(id);
  
  _logger.GroupPush(id->Loc().File(), "In module ‘" + id->Name() + "’:");
  
  // check module ID 
  if(File().ModuleName().compare(id->Name()))
    Error(id->Loc(), "Module ID '" + id->Name() + "' does not match TTCN-3 file name");
  
  // check language
  CModule::TLanguage lang = CModule::LANGUAGE_TTCN_3_2005;
  if(!language.empty()) {
    if(language == "\"TTCN-3:2005\"")
      lang = CModule::LANGUAGE_TTCN_3_2005;
    else if(language == "\"TTCN-3:2003\"")
      lang = CModule::LANGUAGE_TTCN_3_2003;
    else if(language == "\"TTCN-3:2001\"")
      lang = CModule::LANGUAGE_TTCN_3_2001;
    else
      Error(id->Loc(), "Unknown module language " + language + " detected (only \"TTCN-3:2005\" is supported)");
    
    if(lang != CModule::LANGUAGE_TTCN_3_2005)
      Error(id->Loc(), "Unsupported module language " + language + " detected (only \"TTCN-3:2005\" is supported)");
  }
  
  // create new module
  _module = std::auto_ptr<CModule>(new CModule(idPtr.release(), lang));
}


void freettcn::translator::CTranslator::ModuleEnd()
{
  _filesStack.pop();
  _logger.GroupPop();
}
