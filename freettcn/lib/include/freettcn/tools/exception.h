//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) library.

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
 * @file   exception.h
 * @author Mateusz Pusz
 * @date   Tue May  8 11:19:20 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>
#include <string>

#define E_DATA __FUNCTION__, __FILE__, __LINE__

namespace freettcn {
  
  /**
   * @brief TTCN-3 base class for exceptions hierarchy.
   *
   * Class is a base for exceptions thrown by the TTCN-3 compiler.
   */
  class Exception : public std::exception
  {
    const std::string _func;
    const std::string _file;
    const int _line;
    const std::string _message;
    mutable std::string _buffer;
  
  public:
    Exception(const char *func, const char *file, int line, const std::string &message) throw();
    virtual ~Exception() throw();
    
    virtual const char *what() const throw();
  };
  
  /**
  * @brief Operation failed exception.
  *
  * Operation failed exception.
  */
  class EOperationFailed : public Exception {
  public:
    EOperationFailed(const char *func, const char *file, int line, const std::string &message):
        Exception(func, file, line, message) {}
  };

  /**
  * @brief Type or value casting failed
  *
  * Type or value casting failed exception.
  */
  class ECastFailed : public EOperationFailed {
  public:
    ECastFailed(const char *func, const char *file, int line, const std::string &message):
        EOperationFailed(func, file, line, message) {}
  };

  /**
  * @brief Object not found exception.
  *
  * Object not found exception.
  */
  class ENotFound : public EOperationFailed {
  public:
    ENotFound(const char *func, const char *file, int line, const std::string &message):
        EOperationFailed(func, file, line, message) {}
  };

  /**
  * @brief Element out of range exception.
  *
  * Element out of range exception.
  */
  class EOutOfRange : public ENotFound {
  public:
    EOutOfRange(const char *func, const char *file, int line, const std::string &message):
        ENotFound(func, file, line, message) {}
  };

  /**
  * @brief Object not initialized exception.
  *
  * Object not initialized exception.
  */
  class ENotInitialized : public ENotFound {
  public:
    ENotInitialized(const char *func, const char *file, int line, const std::string &message):
        ENotFound(func, file, line, message) {}
  };

  /**
  * @brief Operation not supported exception.
  *
  * Operation not supported exception.
  */
  class ENotSupported : public EOperationFailed {
  public:
    ENotSupported(const char *func, const char *file, int line, const std::string &message):
        EOperationFailed(func, file, line, message) {}
  };

  /**
  * @brief Feature not yet implemented exception.
  *
  * Feature not yet implemented exception.
  */
  class ENotImplemented : public ENotSupported {
  public:
    ENotImplemented(const char *func, const char *file, int line, const std::string &message):
        ENotSupported(func, file, line, message) {}
  };

}

#endif /* __EXCEPTION_H__ */
