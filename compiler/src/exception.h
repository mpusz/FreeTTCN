#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

namespace TTCN3 {
  
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

}

#endif /* EXCEPTION_H */
