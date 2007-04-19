#ifndef FILE_H
#define FILE_H

#include "exception.h"
#include <string>


namespace TTCN3 {
  
  class CModule;
  
  /**
   * @brief TTCN-3 Module File Information.
   *
   * Class contains all information about the file in which TTCN-3 module is
   * located.
   */
  class CFile {
    const std::string name;
    CModule *module;
    
  public:
    CFile(char const * const fileName);
    ~CFile();
    
    const std::string &Name() const { return name; } /**< @brief Returns TTCN-3 module file name. */
    
    void Module(CModule &mod) { module = &mod; }  /**< @brief Sets TTCN-3 module defined in a file. */
    CModule &Module() const throw(ENotFound);
  };
  
  
}

#endif /* FILE_H */
