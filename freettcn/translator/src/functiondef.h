#ifndef FUNCTIONDEF_H
#define FUNCTIONDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Function Definition Node.
   *
   * Class contains all information about TTCN-3 Function Definition.
   */
  class CFunctionDef : public CModule::CDefinition {
  public:
    CFunctionDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CFunctionDef();
  };
  
  
}

#endif /* FUNCTIONDEF_H */
