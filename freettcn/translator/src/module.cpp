#include "module.h"

using namespace TTCN3;



/** 
 * @brief CModule class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param id TTCN-3 node identifier.
 */
TTCN3::CModule::CModule(CFile &f, const YYLTYPE &loc, CIdentifier &id):
  CNamedNode(f, loc, id), control(0)
{
}


/**
 * @brief CModule class destructor.
 */
TTCN3::CModule::~CModule()
{
  // delete all the definitions in a list
  std::for_each(definitionList.begin(), definitionList.end(), ptr_fun(operator delete));
//   for(Iterator it = definitionList.begin(); it != definitionList.end(); ++it)
//     delete *it;
  definitionList.clear();
  
  // delete control part if present
  if (control)
    delete control;
}


/** 
 * @brief Dump class contents into TTCN-3 source code.
 *
 * Method is used to dump TTCN-3 source code to a file based on information
 * tree described by classes in memory.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CModule::DumpTTCN3(FILE *fdout) const
{
  fprintf(fdout, "\nmodule %s {\n", Name().c_str());
  
  for(Container::const_iterator it = definitionList.begin(); it != definitionList.end(); ++it)
    (*it)->DumpTTCN3(fdout);
  
  if (control)
    control->DumpTTCN3(fdout);
  
  fprintf(fdout, "}\n\n");
}


/** 
 * @brief Dump class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CModule::DumpCPP(FILE *fdout) const
{
}



/** 
 * @brief CDefinition class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param id TTCN-3 node identifier.
 * @param mod TTCN-3 module in witch altstep is defined.
 */
TTCN3::CModule::CDefinition::CDefinition(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod):
  CNamedNode(f, loc, id), module(mod)
{
  mod.definitionList.push_back(this);
}

/**
 * @brief CDefinition class destructor.
 */
TTCN3::CModule::CDefinition::~CDefinition()
{
}




/** 
 * @brief CControl class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param mod TTCN-3 module in witch altstep is defined.
 */
TTCN3::CModule::CControl::CControl(CFile &f, const YYLTYPE &loc, CModule &mod):
  CNode(f, loc), module(mod)
{
}


/**
 * @brief CControl class destructor.
 */
TTCN3::CModule::CControl::~CControl()
{
}


/** 
 * @brief Dump dupa class contents into TTCN-3 source code.
 *
 * Method is used to dump TTCN-3 source code to a file based on information
 * tree described by classes in memory.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CModule::CControl::DumpTTCN3(FILE *fdout) const
{
  fprintf(fdout, "Control Part\n");
}


/** 
 * @brief Dump dupa class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CModule::CControl::DumpCPP(FILE *fdout) const
{
}
