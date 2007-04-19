#ifndef MODULEPARDEF_H
#define MODULEPARDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Module Parameter Definition Node.
   *
   * Class contains all information about TTCN-3 Module Parameter Definition.
   */
  class CModuleParDef : public CModule::CDefinition {
  public:
    CModuleParDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CModuleParDef();
  };
  
  
}

#endif /* MODULEPARDEF_H */
