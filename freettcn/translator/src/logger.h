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

#include <string>
#include <stack>


namespace freettcn {
  
  namespace translator {
    
    class CLocation;
    class CFile;
    
    class CLogger {
      struct TGroup {
        const CFile *file;
        std::string msg;
      };
      typedef std::stack<TGroup> CGroupStack;
      
      CGroupStack _groupStack;                    /**< @brief Stack of errors groups */
      bool _groupUsed;                            /**< @brief Specifies if a group was printed already */
      
      CLogger(const CLogger &);                   /**< @brief Disallowed */
      CLogger &operator=(const CLogger &);        /**< @brief Disallowed */
      
      void GroupPrint();
      
    public:
      CLogger();
      virtual ~CLogger();
      
      virtual void Warning(const CLocation &loc, const std::string &msg);
      virtual void Error(const CLocation &loc, const std::string &msg);
      
      void GroupPush(const CFile &file, const std::string &msg);
      void GroupPop();
    };
    
  } // namespace translator
  
} // namespace freettcn

#endif  // __LOGGER_H__
