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

#include "ttcn3Parser.h"
#include "module.h"
#include "file.h"
#include "freettcn/tools/tools.h"
#include <string>
#include <deque>
#include <list>
#include <map>
#include <set>


namespace freettcn {

  namespace translator {

    class CLogger;
    class CDumper;
    class CIdentifier;
    class CTypeStructured;
    class CType;
    
    class CTranslator {
    private:
      typedef std::deque<CFile> CFileList;
      typedef std::stack<const CFile *> CFileStack;

      typedef std::map<const std::string *, const CModule::CDefinition *, CPtrCmp> CScope;
      typedef std::list<CScope> CScopeStack;
      typedef std::set<std::string> CUnresolvedSymbols;
      
      static CTranslator *_instance;              /**< @brief Translator instance */
      
      CLogger &_logger;                           /**< @brief Logger instance */
      unsigned _errorNum;                         /**< @brief The number of errors */
      unsigned _warningNum;                       /**< @brief The number of warning */
      
      CFileList _files;                           /**< @brief All parsed files */
      CFileStack _filesStack;                     /**< @brief Current files on the stack */
      unsigned _line;                             /**< @brief Line in a file */
      
      CScopeStack _scopes;                        /**< @brief TTCN-3 scopes stack */
      CUnresolvedSymbols _unresolvedSymbols;      /**< @brief Unresolved symbols set */

      std::auto_ptr<CModule> _module;             /**< @brief TTCN-3 module */
      CTypeStructured *_structType;               /**< @brief Current structured type */
      CModule::CDefinitionMethod *_method;        /**< @brief Current TTCN-3 method (testcase, template, etc.) */
      
      CTranslator(const CTranslator &);           /**< @brief Disallowed */
      CTranslator &operator=(const CTranslator &); /**< @brief Disallowed */
      
    public:
      static CTranslator &Instance();
      
      CTranslator(const std::string &inputName, CLogger &logger);
      ~CTranslator();
      
      CLogger &Logger() const;
      
      void Warning(const CLocation &loc, const std::string &msg);
      void Error(const CLocation &loc, const std::string &msg);
      unsigned WarningNum() const;
      unsigned ErrorNum() const;

      void Dump(CDumper &dumper) const;
      
      const CFile &File() const;
      void Line(unsigned line);

      void ScopePush();
      bool ScopeSymbol(const CModule::CDefinition &def);
      const CModule::CDefinition *ScopeSymbol(const CIdentifier &id);
      void ScopePop();
      
      void Module(const CIdentifier *id, const std::string &language);
      void ModulePar(const CIdentifier *id, const CType *type, const CExpression *expr);
      void ConstValue(const CIdentifier *id, const CType *type, const CExpression *expr);
      void Struct(const CIdentifier *id, bool set);
      void StructField(const CIdentifier *id, const CType *type, bool optional);
      void Testcase(const CIdentifier *id);
      void Template(const CIdentifier *id);
      void FormalParameter(const CIdentifier *id, const CType *type, const std::string &dirStr);
    };
    
  } // namespace translator

} // namespace freettcn


#endif  // __TRANSLATOR_H__
