#include "importdef.h"

using namespace TTCN3;


/** 
 * @brief CImportSpecElement class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 */
TTCN3::CImportSpecElement::CImportSpecElement(CFile &f, const YYLTYPE &loc):
  CNode(f, loc)
{
}

/**
 * @brief CImportSpecElement class destructor.
 */
TTCN3::CImportSpecElement::~CImportSpecElement()
{
}


/** 
 * @brief Dump class contents into TTCN-3 source code.
 *
 * Method is used to dump TTCN-3 source code to a file based on information
 * tree described by classes in memory.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CImportSpecElement::DumpTTCN3(FILE *fdout) const
{
}


/** 
 * @brief Dump class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CImportSpecElement::DumpCPP(FILE *fdout) const
{
}



/** 
 * @brief CImportSpec class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param l Coma-separated list defined in import specifier.
 */
TTCN3::CImportSpec::CImportSpec(CFile &f, const YYLTYPE &loc, CSemicolonList *l):
  CNode(f, loc), list(l)
{
}

/**
 * @brief CImportSpec class destructor.
 */
TTCN3::CImportSpec::~CImportSpec()
{
  if (list)
    delete list;
}


/** 
 * @brief Dump class contents into TTCN-3 source code.
 *
 * Method is used to dump TTCN-3 source code to a file based on information
 * tree described by classes in memory.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CImportSpec::DumpTTCN3(FILE *fdout) const
{
  if (list)
    list->DumpTTCN3(fdout);
}


/** 
 * @brief Dump class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CImportSpec::DumpCPP(FILE *fdout) const
{
}



/** 
 * @brief CImportSpecAllWithExcepts class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param l Coma-separated list defined in import specifier.
 */
TTCN3::CImportSpecAllWithExcepts::CImportSpecAllWithExcepts(CFile &f, const YYLTYPE &loc, CSemicolonList *l):
  CImportSpec(f, loc, l)
{
}

/**
 * @brief CImportSpecAllWithExcepts class destructor.
 */
TTCN3::CImportSpecAllWithExcepts::~CImportSpecAllWithExcepts()
{
}


/** 
 * @brief Dump class contents into TTCN-3 source code.
 *
 * Method is used to dump TTCN-3 source code to a file based on information
 * tree described by classes in memory.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CImportSpecAllWithExcepts::DumpTTCN3(FILE *fdout) const
{
  fprintf(fdout, " all");
  if (list) {
    fprintf(fdout, " except ");
    list->DumpTTCN3(fdout);
  }
}


/** 
 * @brief Dump class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CImportSpecAllWithExcepts::DumpCPP(FILE *fdout) const
{
}



/** 
 * @brief CImportDef class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param id TTCN-3 node identifier.
 * @param mod TTCN-3 module in witch altstep is defined.
 * @param rec Recursive import flag.
 */
TTCN3::CImportDef::CImportDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod, const bool rec):
  CDefinition(f, loc, id, mod), recursive(rec), spec(0)
{
}


/**
 * @brief CImportDef class destructor.
 */
TTCN3::CImportDef::~CImportDef()
{
  if (spec)
    delete spec;
}


/** 
 * @brief Dump class contents into TTCN-3 source code.
 *
 * Method is used to dump TTCN-3 source code to a file based on information
 * tree described by classes in memory.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CImportDef::DumpTTCN3(FILE *fdout) const
{
  fprintf(fdout, "import from %s%s", Name().c_str(),
          recursive ? "T_RECURSIVE" : "");
  
  if (spec)
    spec->DumpTTCN3(fdout);
  
  fprintf(fdout, ";\n");
}



/** 
 * @brief Dump class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CImportDef::DumpCPP(FILE *fdout) const
{
}
