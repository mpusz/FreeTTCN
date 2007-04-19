#ifndef EXTFUNCTIONDEF_H
#define EXTFUNCTIONDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 External Function Definition Node.
   *
   * Class contains all information about TTCN-3 External Function Definition.
   */
  class CExtFunctionDef : public CModule::CDefinition {
  public:
    CExtFunctionDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CExtFunctionDef();
  };
  
  
}

#endif /* EXTFUNCTIONDEF_H */
