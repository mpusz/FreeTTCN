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
 * @file   exception.cpp
 * @author Mateusz Pusz
 * @date   Tue May  8 11:19:39 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/tools/exception.h"
#ifndef _WIN32
#include <cxxabi.h>
#include <cstdlib>
#else
#include <typeinfo>
#endif
#include <cstdio>


/** 
 * @brief TTCN-3 base exception constructor.
 */
freettcn::Exception::Exception(const char *func, const char *file, int line, const std::string &message) throw():
  _func(func), _file(file), _line(line), _message(message)
{
}


/**
 * @brief TTCN-3 base exception destructor.
 */
freettcn::Exception::~Exception() throw()
{
}


/** 
 * @brief Method returns a string describing current TTCN-3 exception.
 *
 * @todo Maybe a stack trace of the place where an exception
 *       was constructed should be gathered and printed.
 * 
 * @return String describing the exception.
 */
const char* freettcn::Exception::what() const throw()
{
  std::string name;
#ifndef _WIN32
  int status = 0;
  char *namePtr;

  // demangle C++ mangler type name
  namePtr = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
  if (!namePtr && status) {
    // some error encountered during demangling
    fprintf(stderr, "Symbol demangling failed (%u)\n", status);
    name = typeid(*this).name();
  }
  else {
    // copy demagled name to buffer
    name = namePtr;
  }
#else
  name = typeid(*this).name();
#endif

  char buf[512];
  std::string fileShort;
  size_t pos = _file.find_last_of("/\\");
  if(pos != std::string::npos)
    fileShort = _file.substr(pos + 1);
  else
    fileShort = _file;
  sprintf(buf, "%.48s(%i): %.128s()", fileShort.c_str(), _line, _func.c_str());
  _buffer = _message + "\n" + "<" + name + " at " + buf + ">\n";

#ifndef _WIN32
  // free pointer allocated by demangler
  if(!namePtr && status)
    free(namePtr);  
#endif

  return _buffer.c_str();
}
