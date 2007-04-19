#ifndef TEMPLATEDEF_H
#define TEMPLATEDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Template Definition Node.
   *
   * Class contains all information about TTCN-3 Template Definition.
   */
  class CTemplateDef : public CModule::CDefinition {
  public:
    CTemplateDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CTemplateDef();
  };
  
  
}

#endif /* TEMPLATEDEF_H */
