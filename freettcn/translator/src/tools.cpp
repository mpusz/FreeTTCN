#include <cstring>
#include "tools.h"


static long int errorNum = 0;

YYLTYPE *yylloc;
YYSTYPE *yylval;
extern char const *filename;
TTCN3::CFile *file;

extern int yylex(void);


char *
TTCN3TypeToString(TTCN3Type_t type)
{
  char *str[]={
    "NONE",
    "BITSTING",
    "BOOLEAN",
    "CHARSTRING",
    "UNIVERSAL_CHARSTRING",
    "INTEGER",
    "OCTETSTRING",
    "HEXSTRING",
    "VERDICT_TYPE",
    "FLOAT",
    "ADDRESS",
    "DEFAULT",
    "ANY_TYPE"
  };
  
  return str[type];
}

/** 
 * @brief Print compilation error.
 *
 * A function is responsible for printing errors and warnings found during
 * TTCN-3 source code compilation.
 *
 * @param loc Location of the error in the TTCN-3 source code.
 * @param file File in which error occured.
 * @param msg Message to display in warning message.
 * @param warning Flag that indicates that only compilation warning
 *                (not an error) should be printed.
 */
void
yyerror(YYLTYPE const * const loc, TTCN3::CFile &file, char const * const msg, bool warning /* false */)
{
  char text[1024];
  char const *msgPtr = msg;
  extern char *yytext;
  
  if (!strcmp(msg, "syntax error")) {
    sprintf(text, "Unexpected token '%s'", yytext);
    msgPtr = text;
  }
  
  fprintf(stderr, "%s:%u:%u:%u:%u: %s: %s\n",
          file.Name().c_str(), loc->first_line, loc->first_column, loc->last_line, loc->last_column,
          warning ? "warning" : "error", msgPtr);
  
  if (!warning)
    errorNum++;
}


int yylex(YYSTYPE *val, YYLTYPE *loc, TTCN3::CFile &file)
{
  yylloc = loc;
  yylval = val;
  ::file = &file;
  return yylex();
}
