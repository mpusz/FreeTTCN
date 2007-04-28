#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Type Definition Node.
   *
   * Class contains all information about TTCN-3 Type Definition.
   */
  class CTypeDef : public CModule::CDefinition {
  public:
    CTypeDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CTypeDef();
  };
  
  
}

#endif /* TYPEDEF_H */
