#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include "types.h"
#include "grammar.tab.h"
#include "file.h"

// Delete pointers in an STL sequence container.
template<class Seq> void purge(Seq &c)
{
  typename Seq::iterator it;
  for(it = c.begin(); it != c.end(); ++it) {
    delete *it;
    *it = 0;
  }
}

// Iterator version:
template<class InpIt> void purge(InpIt begin, InpIt end)
{
  while(begin != end) {
    delete *begin;
    *begin = 0;
    ++begin;
  }
}


char *TTCN3TypeToString(TTCN3Type_t type);
void yyerror(YYLTYPE const * const loc, TTCN3::CFile &file, char const * const msg, bool warning = false);
int yylex(YYSTYPE *val, YYLTYPE *loc, TTCN3::CFile &file);

#endif /* TOOLS_H */
