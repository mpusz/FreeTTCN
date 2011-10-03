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
 * @file   translator.h
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#ifndef __TRANSLATOR_H__
#define __TRANSLATOR_H__

#include "freettcn/tools/nonCopyable.h"
#include "ttcn3Parser.h"
#include "module.h"
#include "file.h"
#include "freettcn/tools/tools.h"
#include <string>
#include <list>
#include <map>
#include <set>


namespace freettcn {

  namespace translator {

    class CLogger;
    class CDumper;
    class CIdentifier;
    class CType;
    class CTypeReferenced;
    class CTypeStructured;
    
    class CTranslator : CNonCopyable {
    private:
      typedef std::stack<std::shared_ptr<const CFile>> CFileStack;
      
      typedef std::map<const std::string *, const CModule::CDefinition *, CPtrCmp> CScope;
      typedef std::list<CScope> CScopeStack;
      typedef std::set<std::string> CUnresolvedSymbolsSet;
      typedef std::map<std::string, std::shared_ptr<CTypeReferenced>> CTypeReferencedMap;
      
      static CTranslator *_instance;              /**< @brief Translator instance */
      
      CLogger &_logger;                           /**< @brief Logger instance */
      unsigned _errorNum;                         /**< @brief The number of errors */
      unsigned _warningNum;                       /**< @brief The number of warning */
      
      CFileStack _filesStack;                     /**< @brief Current files on the stack */
      unsigned _line;                             /**< @brief Line in a file */
      
      CScopeStack _scopes;                        /**< @brief TTCN-3 scopes stack */
      CUnresolvedSymbolsSet _unresolvedSymbols;   /**< @brief Unresolved symbols set */
      CTypeReferencedMap _referencedTypes;        /**< @brief Referenced types map that speeds up resolving process */
      
      std::shared_ptr<CModule> _module;           /**< @brief TTCN-3 module */
      std::shared_ptr<CTypeStructured> _structType; /**< @brief Current structured type */
      std::shared_ptr<CTypePort> _portType;       /**< @brief Current port type */
      std::shared_ptr<CModule::CDefinitionMethod> _method;        /**< @brief Current TTCN-3 method (testcase, template, etc.) */
      
    public:
      static CTranslator &Instance();
      
      CTranslator(const std::string &inputName, CLogger &logger);
      ~CTranslator();
      
      CLogger &Logger() const;
      
      void Error(const CLocation &loc, const std::string &msg);
      void Warning(const CLocation &loc, const std::string &msg);
      void Note(const CLocation &loc, const std::string &msg);
      unsigned ErrorNum() const;
      unsigned WarningNum() const;

      void Dump(CDumper &dumper) const;
      
      const CFile &File() const;
      void Line(unsigned line);

      void ScopePush();
      bool ScopeSymbol(const CModule::CDefinition &def);
      const CModule::CDefinition *ScopeSymbol(const CIdentifier &id);
      void ScopePop();
      
      std::shared_ptr<CType> Type(const std::string &name) const;
      std::shared_ptr<CTypeReferenced> TypeReferenced(std::shared_ptr<const CIdentifier> id);
      
      void Module(std::shared_ptr<const CIdentifier> id, const std::string &language);
      void ModulePar(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, std::shared_ptr<const CExpression> expr);
      void ConstValue(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, std::shared_ptr<const CExpression> expr);
      void Struct(std::shared_ptr<const CIdentifier> id, bool set);
      void StructField(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, bool optional);
      void Union(std::shared_ptr<const CIdentifier> id);
      void UnionField(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type);
      void Port(std::shared_ptr<const CIdentifier> id, CTypePort::TMode mode);
      void PortItem(const CLocation &loc, std::shared_ptr<CType> type, const std::string &dirStr);
      void Testcase(std::shared_ptr<const CIdentifier> id);
      void Template(std::shared_ptr<const CIdentifier> id);
      void FormalParameter(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, const std::string &dirStr);
    };
    
  } // namespace translator

} // namespace freettcn


#endif  // __TRANSLATOR_H__
