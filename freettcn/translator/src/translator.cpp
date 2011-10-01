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
#include "expression.h"
#include "identifier.h"
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
  _filesStack.pop();
}


freettcn::translator::CLogger &freettcn::translator::CTranslator::Logger() const
{
  return _logger;
}


void freettcn::translator::CTranslator::Error(const CLocation &loc, const std::string &msg)
{
  _logger.Error(loc, msg);
  _errorNum++;
}


void freettcn::translator::CTranslator::Warning(const CLocation &loc, const std::string &msg)
{
  _logger.Warning(loc, msg);
  _warningNum++;
}


void freettcn::translator::CTranslator::Note(const CLocation &loc, const std::string &msg)
{
  _logger.Note(loc, msg);
}


unsigned freettcn::translator::CTranslator::ErrorNum() const
{
  return _errorNum;
}


unsigned freettcn::translator::CTranslator::WarningNum() const
{
  return _warningNum;
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


void freettcn::translator::CTranslator::ScopePush()
{
  CScope scope;
  _scopes.push_front(scope);
}


bool freettcn::translator::CTranslator::ScopeSymbol(const CModule::CDefinition &def)
{
  /// @todo Check if ID does not name predefined function
  
  // check if ID already defined
  const CModule::CDefinition *localDef = 0;
  for(CScopeStack::const_iterator stackIt=_scopes.begin(); stackIt!=_scopes.end(); ++stackIt) {
    CScope::const_iterator scopeIt = stackIt->find(&def.Id().Name());
    if(scopeIt != stackIt->end())
      localDef = scopeIt->second;
  }
  if(localDef) {
    Error(def.Id().Loc(), "conflicting declaration '" + def.Type()->Name() + " " + def.Id().Name() + "'");
    Error(localDef->Id().Loc(), "'" + def.Id().Name() + "' has a previous declaration as '" + localDef->Type()->Name() + " " +  localDef->Id().Name() + "'");
    return false;
  }
  else {
    // add new symbol
    _scopes.front()[&def.Id().Name()] = &def;
    return true;
  }
}


const freettcn::translator::CModule::CDefinition *freettcn::translator::CTranslator::ScopeSymbol(const CIdentifier &id)
{
  const CModule::CDefinition *def = 0;
  
  for(CScopeStack::const_iterator stackIt=_scopes.begin(); stackIt!=_scopes.end(); ++stackIt) {
    CScope::const_iterator scopeIt = stackIt->find(&id.Name());
    if(scopeIt != stackIt->end())
      def = scopeIt->second;
  }
  if(!def) {
    // symbol not defined
    CUnresolvedSymbolsSet::const_iterator it = _unresolvedSymbols.find(id.Name());
    if(it == _unresolvedSymbols.end()) {
      // print the error only once for that symbol
      Error(id.Loc(), "'" + id.Name() + "' was not declared in this scope");
      
      // add identifier to unresolved symbols set
      _unresolvedSymbols.insert(id.Name());
    }
    
    return 0;
  }
  
  return def;
}


void freettcn::translator::CTranslator::ScopePop()
{
  if(_scopes.empty())
    throw EOperationFailed(E_DATA, "End of scopes stack!!!");
  _scopes.pop_front();
}


std::shared_ptr<freettcn::translator::CType> freettcn::translator::CTranslator::Type(const std::string &name) const
{
  for(CScopeStack::const_iterator stackIt=_scopes.begin(); stackIt!=_scopes.end(); ++stackIt) {
    CScope::const_iterator scopeIt = stackIt->find(&name);
    if(scopeIt != stackIt->end())
      return scopeIt->second->Type();
  }
  
  return 0;
}


std::shared_ptr<freettcn::translator::CTypeReferenced> freettcn::translator::CTranslator::TypeReferenced(std::shared_ptr<const CIdentifier> id)
{
  // check if referenced type is created already
  CTypeReferencedMap::iterator it = _referencedTypes.find(id->Name());
  if(it != _referencedTypes.end()) {
    /// @todo check if type can be resolved now
    return it->second;
  }
  
  // look for type definition
  std::shared_ptr<CType> type = Type(id->Name());
  if(type) {
    // create new referenced type and insert to the map
    std::shared_ptr<CTypeReferenced> refType(new CTypeReferenced(type));
    _referencedTypes[id->Name()] = refType;
    return refType;
  }
  
  // create new unresolved referenced type and insert to the map
  std::shared_ptr<CTypeReferenced> refType(new CTypeReferenced(id));
  _referencedTypes[id->Name()] = refType;
  return refType;
}


void freettcn::translator::CTranslator::Module(std::shared_ptr<const CIdentifier> id, const std::string &language)
{
  // check module ID 
  if(File().ModuleName().compare(id->Name()))
    Error(id->Loc(), "module ID '" + id->Name() + "' does not match TTCN-3 file name");
  
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
      Error(id->Loc(), "unknown module language " + language + " detected (only \"TTCN-3:2005\" is supported)");
    
    if(lang != CModule::LANGUAGE_TTCN_3_2005)
      Error(id->Loc(), "unsupported module language " + language + " detected (only \"TTCN-3:2005\" is supported)");
  }
  
  // create new module
  _module = std::shared_ptr<CModule>(new CModule(id, lang));
}


void freettcn::translator::CTranslator::ModulePar(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, std::shared_ptr<const CExpression> expr)
{
  if(!type)
    throw EOperationFailed(E_DATA, "Module Parameter type not specified!!!");
  
  if(!(type->Kind() & CType::KIND_TYPE)) {
    Error(id->Loc(), "module parameter '" + id->Name() + "' type cannot be of '" + CType::KindToString(type->Kind()) + "' type");
    return;
  }
  
  // check if constant expression
  if(expr && !expr->Constant())
    Error(id->Loc(), "module parameter '" + id->Name() + "' should resolve to a constant value");
  
  // check if types match
  if(expr && !type->Match(*expr->Type()))
    Error(id->Loc(), "expression of module parameter '" + id->Name() + "' does not match parameter type '" + type->Name() + "'");
  
  std::shared_ptr<CModule::CDefinitionParameter> def(new CModule::CDefinitionParameter(id, type, expr));
  if(ScopeSymbol(*def))
    // register new module parameter
    _module->Register(def);
}


void freettcn::translator::CTranslator::ConstValue(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, std::shared_ptr<const CExpression> expr)
{
  if(!type)
    throw EOperationFailed(E_DATA, "Const value type not specified!!!");
  
  if(!(type->Kind() & CType::KIND_TYPE)) {
    Error(id->Loc(), "const value '" + id->Name() + "' type cannot be of '" + CType::KindToString(type->Kind()) + "' type");
    return;
  }
  
  // check if constant expression
  if(expr && !expr->Constant())
    Error(id->Loc(), "const value '" + id->Name() + "' should resolve to a constant value");
  
  // check if types match
  if(expr && !type->Match(*expr->Type()))
    Error(id->Loc(), "expression of const value '" + id->Name() + "' does not match const type '" + type->Name() + "'");
  
  std::shared_ptr<CModule::CDefinitionConstValue> def(new CModule::CDefinitionConstValue(id, type, expr));
  if(ScopeSymbol(*def))
    // register new const value
    _module->Register(def);
}


void freettcn::translator::CTranslator::Struct(std::shared_ptr<const CIdentifier> id, bool set)
{
  _structType.reset();
  
  std::shared_ptr<CTypeStructured> structType;
  if(set)
    structType.reset(new CTypeStructured(id->Name()));
  else
    structType.reset(new CTypeRecord(id->Name()));
  
  std::shared_ptr<CModule::CDefinitionTypeLocal> def(new CModule::CDefinitionTypeLocal(id, structType));
  if(ScopeSymbol(*def)) {
    // register new structured type
    _structType = structType;
    _module->Register(def);
  }
}


void freettcn::translator::CTranslator::StructField(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, bool optional)
{
  if(!_structType)
    throw EOperationFailed(E_DATA, "Current structured type not set!!!");
  
  if(!type)
    throw EOperationFailed(E_DATA, "Structured type '" + _structType->Name() + "' field '" +  id->Name() + "' type not specified!!!");
  
  if(!(type->Kind() & CType::KIND_TYPE) && type->Kind() != CType::KIND_UNRESOLVED) {
    Error(id->Loc(), "structured type '" + _structType->Name() + "' field cannot be of '" + CType::KindToString(type->Kind()) + "' type");
    return;
  }

  _structType->Register(std::shared_ptr<CTypeStructured::CField>(new CTypeStructured::CField(type, id, optional)));
}


void freettcn::translator::CTranslator::Union(std::shared_ptr<const CIdentifier> id)
{
  _structType.reset();
  
  std::shared_ptr<CTypeStructured> structType(new CTypeUnion(id->Name()));
  std::shared_ptr<CModule::CDefinitionTypeLocal> def(new CModule::CDefinitionTypeLocal(id, structType));
  if(ScopeSymbol(*def)) {
    // register new structured type
    _structType = structType;
    _module->Register(def);
  }
}


void freettcn::translator::CTranslator::UnionField(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type)
{
  if(!_structType)
    throw EOperationFailed(E_DATA, "Current structured type not set!!!");
  
  if(!type)
    throw EOperationFailed(E_DATA, "Union '" + _structType->Name() + "' field '" +  id->Name() + "' type not specified!!!");
  
  if(!(type->Kind() & CType::KIND_TYPE) && type->Kind() != CType::KIND_UNRESOLVED) {
    Error(id->Loc(), "union '" + _structType->Name() + "' field cannot be of '" + CType::KindToString(type->Kind()) + "' type");
    return;
  }

  _structType->Register(std::shared_ptr<CTypeStructured::CField>(new CTypeStructured::CField(type, id, true)));
}


void freettcn::translator::CTranslator::Port(std::shared_ptr<const CIdentifier> id, CTypePort::TMode mode)
{
  _portType.reset();
  
  std::shared_ptr<CTypePort> portType(new CTypePort(id->Name(), mode));
  std::shared_ptr<CModule::CDefinitionTypeLocal> def(new CModule::CDefinitionTypeLocal(id, portType));
  if(ScopeSymbol(*def)) {
    // register new port type
    _portType = portType;
    _module->Register(def);
  }
}


void freettcn::translator::CTranslator::PortItem(const CLocation &loc, std::shared_ptr<CType> type, const std::string &dirStr)
{
  if(!_portType)
    throw EOperationFailed(E_DATA, "Port type not set!!!");
  
  CTypePort::TDirection dir = CTypePort::DIRECTION_INOUT;
  if(dirStr == "in")
    dir = CTypePort::DIRECTION_IN;
  else if(dirStr == "out")
    dir = CTypePort::DIRECTION_OUT;
  
  std::shared_ptr<CTypePort::CItem> item;
  if(type){
    if(!(type->Kind() & CType::KIND_TYPE) && type->Kind() != CType::KIND_UNRESOLVED) {
      Error(loc, "port '" + _portType->Name() + "' item cannot be of '" + CType::KindToString(type->Kind()) + "' type");
      return;
    }
    item.reset(new CTypePort::CItem(loc, *type));
  }
  else
    item.reset(new CTypePort::CItem(loc));
  
  _portType->Register(item, dir);
}


void freettcn::translator::CTranslator::Testcase(std::shared_ptr<const CIdentifier> id)
{
  _method.reset();
  
  std::shared_ptr<CModule::CDefinitionTestcase> def(new CModule::CDefinitionTestcase(id, CTypePredefined::Verdict()));
  if(ScopeSymbol(*def)) {
    // register new testcase
    _method = def;
    _module->Register(def);
  }
}


void freettcn::translator::CTranslator::Template(std::shared_ptr<const CIdentifier> id)
{
  _method.reset();
  
  /// @todo template type
  std::shared_ptr<CModule::CDefinitionTemplate> def(new CModule::CDefinitionTemplate(id, CTypePredefined::Verdict()));
  if(ScopeSymbol(*def)) {
    // register new template
    _method = def;
    _module->Register(def);
  }
}


void freettcn::translator::CTranslator::FormalParameter(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, const std::string &dirStr)
{
  if(!type)
    throw EOperationFailed(E_DATA, "Formal Parameter type not specified!!!");
  
  if(!_method)
    throw EOperationFailed(E_DATA, "Current method not set!!!");

  if(!type->Resolved()) {
    if(!type->Resolve(CType::KIND_TYPE, "formal parameter '" + id->Name() + "'")) {
      Error(id->Loc(), "formal parameter '" + id->Name() + "' of unresolved type '" + type->Name() + "' specified");
      return;
    }
  }

  if(!(type->Kind() & CType::KIND_TYPE)) {
    Error(id->Loc(), "formal parameter '" + id->Name() + "' cannot be of '" + CType::KindToString(type->Kind()) + "' type");
    return;
  }
  
  CModule::CDefinitionFormalParameter::TDirection dir = CModule::CDefinitionFormalParameter::DIRECTION_INOUT;
  if(dirStr == "in")
    dir = CModule::CDefinitionFormalParameter::DIRECTION_IN;
  else if(dirStr == "out")
    dir = CModule::CDefinitionFormalParameter::DIRECTION_OUT;
  
  std::shared_ptr<CModule::CDefinitionFormalParameter> def(new CModule::CDefinitionFormalParameter(id, type, dir));
  if(ScopeSymbol(*def)) {
    // register new module parameter in a method
    _method->Register(def);
  }
}
