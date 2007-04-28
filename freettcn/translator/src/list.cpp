#include "list.h"

using namespace TTCN3;


/** 
 * @brief CList class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 */
TTCN3::CList::CList(CFile &f, const YYLTYPE &loc):
  CNode(f, loc)
{
}

/**
 * @brief CList class destructor.
 */
TTCN3::CList::~CList()
{
  // delete all the definitions in a list
  std::for_each(list.begin(), list.end(), ptr_fun(operator delete));
//   for(Iterator it = list.begin(); it != list.end(); ++it)
//     delete *it;
  list.clear();
}

/** 
 * @brief Add a new element to the list.
 * 
 * @param elem TTCN-3 node to add to a list.
 */
void TTCN3::CList::Add(CNode &elem)
{
  list.push_back(&elem);
}



/** 
 * @brief CCommaList class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 */
TTCN3::CCommaList::CCommaList(CFile &f, const YYLTYPE &loc):
  CList(f, loc)
{
}

/**
 * @brief CCommaList class destructor.
 */
TTCN3::CCommaList::~CCommaList()
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
void TTCN3::CCommaList::DumpTTCN3(FILE *fdout) const
{
  fprintf(fdout, "{");
  
  for(Container::const_iterator it = list.begin(); it != list.end(); ++it) {
    if (it != list.begin())
      fprintf(fdout, ", ");
    (*it)->DumpTTCN3(fdout);
  }
  
  fprintf(fdout, "}");
}


/** 
 * @brief Dump class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CCommaList::DumpCPP(FILE *fdout) const
{
}



/** 
 * @brief CSemicolonList class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 */
TTCN3::CSemicolonList::CSemicolonList(CFile &f, const YYLTYPE &loc):
  CList(f, loc)
{
}

/**
 * @brief CSemicolonList class destructor.
 */
TTCN3::CSemicolonList::~CSemicolonList()
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
void TTCN3::CSemicolonList::DumpTTCN3(FILE *fdout) const
{
  fprintf(fdout, "{");
  
  for(Container::const_iterator it = list.begin(); it != list.end(); ++it) {
    (*it)->DumpTTCN3(fdout);
    fprintf(fdout, "; ");
  }
  
  fprintf(fdout, "}");
}

/** 
 * @brief Dump class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CSemicolonList::DumpCPP(FILE *fdout) const
{
}
