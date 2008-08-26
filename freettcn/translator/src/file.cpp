#include "file.h"
#include "module.h"

using namespace TTCN3;
  

/** 
 * @brief CFile class constructor.
 * 
 * @param fileName The name of a TTCN-3 source code file to compile.
 */
TTCN3::CFile::CFile(char const * const fileName):
  name(fileName), module(0)
{
}

/**
 * @brief CFile class destructor.
 */
TTCN3::CFile::~CFile()
{
  if (module)
    delete module;
}

/** 
 * @brief Get TTCN-3 module defined in TTCN-3 source file.
 * 
 * @exception ENotFound TTCN-3 Module not found in TTCN-3 file.
 * 
 * @return Reference to TTCN-3 Module node.
 */
CModule &TTCN3::CFile::Module() const
{
  if(!module)
    throw ENotFound();
  
  return *module;  
}
