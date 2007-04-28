#include <cxxabi.h>
#include <cstdio>
#include <cstdlib>
#include "exception.h"


/** 
 * @brief TTCN-3 base exception constructor.
 */
TTCN3::Exception::Exception() throw():
  std::exception()
{
}


/**
 * @brief TTCN-3 base exception destructor.
 */
TTCN3::Exception::~Exception() throw()
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
const char* TTCN3::Exception::what() const throw()
{
  int status = 0;
  char *namePtr;
  
  // demangle C++ mangler type name
  namePtr = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
  if (!namePtr && status) {
    // some error encountered during demangling
    fprintf(stderr, "Symbol demangling failed (%u)\n", status);
    sprintf(msg, "%s", typeid(*this).name());
  }
  else {
    // copy demagled name to buffer
    sprintf(msg, "%s", namePtr);
    
    // free pointer allocated by demangler
    free(namePtr);
  }
  
  return msg;
}
