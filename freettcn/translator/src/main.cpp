//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) compiler.

// freettcn is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// freettcn is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with freettcn; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


#include <exception>
#include "file.h"
#include "module.h"

using namespace TTCN3;

static long int errorNum = 0;   /**< The number of errors found during compilation. */

extern void yyrestart(FILE *input_file); /**< Bison parser state reset. */
extern int yyparse(TTCN3::CFile &file); /**< Bison parse loop. */

unsigned long int TTCN3::CNode::refNum = 0;


/**
 * @brief Unexpected exception handler.
 *
 * Function is called when an unexpected exception is thrown.
 * Unexpected exception is an exception that is not defined in
 * function declaration exceptions throw list.
 */
static void ExceptionUnexpected()
{
  fprintf(stderr, "!Unexpected exception was thrown\n");
  abort();
}

/**
 * @brief Not caught exception handler. 
 *
 * Function is called when an exception is not caught (it is also
 * true when an exception is thrown inside handling of another
 * exception).
 */
static void ExceptionTerminate()
{
  fprintf(stderr, "!An exception was not caught\n");
  abort();
}


/**
 * @namespace TTCN3
 * @brief Common namespace for all TTCN-3 compiler tools.
 */


/**
 * @mainpage TTCN-3 Compiler Documentation
 * @author Mateusz Pusz
 * @version 0.01
 *
 * @section intro_sec Introduction
 * TTCN-3 (Testing and Test Control Notation version 3) is a flexible and
 * powerful programming language created for specifying and running test.
 * It is universal, platform independent and well defined in ETSI
 * standards. Standard not only describes the interface and behavior of
 * TTCN-3 language but also defines an interface of compiled TTCN-3 module
 * for C/C++ and Java environments.
 *
 * The problem is that currently there is no free compiler for TTCN-3 language.
 * The reason of this project is to try provide free compiler for it.
 * 
 * @section install_sec Installation
 * @subsection step1 Step 1: Opening the box
 * 
 * etc...
 */
int
main(int argc, char* argv[])
{
  extern FILE *yyin; //, *yyout;
//   extern int yydebug;
//   yydebug = 1;
  
  std::set_unexpected(ExceptionUnexpected);
  std::set_terminate(ExceptionTerminate);

  // skip over program name
  ++argv;
  --argc;
  
  FILE *fdout = stdout;
//   if ((fdout = fopen("out.txt", "w")) == 0) {
//     fprintf(stderr, "Error: File '%s' not found!!!\n", argv[0]);
//     exit(1);
//   }
  
  if (argc) {
    while (argc) {
      char const *fileName = argv[0];
      
      if ((yyin = fopen(fileName, "r")) != 0) {
        TTCN3::CFile file(fileName);
        yyrestart(yyin);
        if (yyparse(file))
          fprintf(stderr, "Fatal errors occured in '%s'!!!\n", fileName);

        try {
          file.Module().DumpTTCN3(fdout);
        }
        catch (ENotFound &ex) {
          fprintf(fdout, "Exception '%s' caught\n", ex.what());
        }
        catch (Exception &ex) {
          fprintf(stderr, "!TTCN3 exception '%s' caught\n", ex.what());
        }
        catch (std::exception &ex) {
          fprintf(stderr, "!C++ standard library exception '%s' caught\n", ex.what());
        }
        catch (...) {
          fprintf(stderr, "!Unknown exception caught\n");
        }
      }
      else {
        fprintf(stderr, "Error: File '%s' not found!!!\n", fileName);
        errorNum++;
      }
      
      // move to next file
      ++argv;
      --argc;
    }
  }
  else {
    char const * const fileName = "<stdin>";
    TTCN3::CFile *file = new TTCN3::CFile(fileName);
    
    yyin = stdin;
    if (yyparse(*file))
      fprintf(stderr, "Fatal errors occured in '%s'!!!\n", fileName);
  }
  
  if (TTCN3::CNode::refNum)
    fprintf(stderr, "%lu nodes are still allocated!!!\n", TTCN3::CNode::refNum);
  
  if (errorNum > 0)
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}
