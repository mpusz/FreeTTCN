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
#include "file.h"
#include <deque>
#include <stack>


namespace freettcn {

  namespace translator {

    class CLogger;
    class CIdentifier;
    
    class CTranslator {
      typedef std::deque<CFile> CFileList;
      typedef std::stack<const CFile *> CFileStack;

      static CTranslator *_instance;              /**< @brief Translator instance */
      
      CLogger &_logger;                           /**< @brief Logger instance */
      unsigned _errorNum;                         /**< @brief The number of errors */
      unsigned _warningNum;                       /**< @brief The number of warning */
      
      CFileList _files;                           /**< @brief All parsed files */
      CFileStack _filesStack;                     /**< @brief Current files on the stack */
      unsigned _line;                             /**< @brief Line in a file */
      
      CTranslator(const CTranslator &);           /**< @brief Disallowed */
      CTranslator &operator=(const CTranslator &); /**< @brief Disallowed */
      
    public:
      static CTranslator &Instance();
      
      CTranslator(const std::string &inputName, CLogger &logger);
      virtual ~CTranslator();
      
      virtual void Warning(const CLocation &loc, const std::string &msg);
      virtual void Error(const CLocation &loc, const std::string &msg);
      
      void Start() const;
      const CFile &File() const;
      
      void Line(unsigned line);
      unsigned Line() const;
      
      void ModuleBegin(const CIdentifier *id);
      void ModuleEnd();
    };
    
  } // namespace translator

} // namespace freettcn


#endif  // __TRANSLATOR_H__
