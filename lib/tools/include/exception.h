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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

namespace freettcn {
  
  /**
   * @brief TTCN-3 base class for exceptions hierarchy.
   *
   * Class is a base for exceptions thrown by the TTCN-3 compiler.
   */
  class Exception : public std::exception
  {
    mutable char msg[255];
  
  public:
    Exception() throw();
    ~Exception() throw();
  
    const char *what() const throw();
  };
  
  /**
   * @brief TTCN-3 Operation failed because data was not found.
   *
   * Exception is thrown by class method when data that should be
   * returned was not found.
   */
  class ENotFound : public Exception {};

  class EOperationFailed : public Exception {};
  class ECastFailed      : public EOperationFailed {};

}

#endif /* EXCEPTION_H */
