#ifndef ALTSTEPDEF_H
#define ALTSTEPDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Altstep Definition Node.
   *
   * Class contains all information about TTCN-3 Altstep Definition block.
   */
  class CAltstepDef : public CModule::CDefinition {
  public:
    CAltstepDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CAltstepDef();
  };
  
  
}

#endif /* ALTSTEPDEF_H */
