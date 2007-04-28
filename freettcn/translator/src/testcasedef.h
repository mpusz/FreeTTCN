#ifndef TESTCASEDEF_H
#define TESTCASEDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Testcase Definition Node.
   *
   * Class contains all information about TTCN-3 Testcase Definition.
   */
  class CTestcaseDef : public CModule::CDefinition {
  public:
    CTestcaseDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CTestcaseDef();
  };
  
  
}

#endif /* TESTCASEDEF_H */
