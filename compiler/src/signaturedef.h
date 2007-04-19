#ifndef SIGNATUREDEF_H
#define SIGNATUREDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Signature Definition Node.
   *
   * Class contains all information about TTCN-3 Signature Definition.
   */
  class CSignatureDef : public CModule::CDefinition {
  public:
    CSignatureDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CSignatureDef();
  };
  
  
}

#endif /* SIGNATUREDEF_H */
