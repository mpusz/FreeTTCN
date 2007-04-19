#ifndef EXTCONSTDEF_H
#define EXTCONSTDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 External Const Definition Node.
   *
   * Class contains all information about TTCN-3 External Const Definition.
   */
  class CExtConstDef : public CModule::CDefinition {
  public:
    CExtConstDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CExtConstDef();
  };
  
  
}

#endif /* EXTCONSTDEF_H */
