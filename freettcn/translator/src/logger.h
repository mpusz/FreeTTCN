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
 * @file   logger.h
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <iomanip>

namespace freettcn {

  namespace translator {

    class CLogger {
      static const unsigned INDENT_SIZE = 2;
      static CLogger *_instance;

      std::ostream &_stream;
      unsigned _indent;
    
      CLogger(const CLogger &);                   /**< @brief Disallowed */
      CLogger &operator=(const CLogger &);        /**< @brief Disallowed */

    public:
      static CLogger &Instance();
    
      CLogger(std::ostream &stream);
      virtual ~CLogger();
    
      void IndentIncr();
      void IndentDecr();
      
      virtual void PrintLine(const std::string &line) const;
      //      virtual void Print(const std::string &str);

      virtual void Header();
      virtual void Footer();
    };

  } // namespace translator

} // namespace freettcn


inline void freettcn::translator::CLogger::PrintLine(const std::string &line) const
{
  if(_indent)
    _stream << std::setw(_indent) << " ";
  _stream << line << std::endl;
}


inline void freettcn::translator::CLogger::IndentIncr()
{
  _indent += INDENT_SIZE;
}


inline void freettcn::translator::CLogger::IndentDecr()
{
  _indent -= INDENT_SIZE;
}
 

#endif  // __LOGGER_H__
