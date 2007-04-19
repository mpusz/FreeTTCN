#ifndef TYPES_H
#define TYPES_H

enum TTCN3Type_e {
  TTCN3_NONE,
  TTCN3_BITSTING,
  TTCN3_BOOLEAN,
  TTCN3_CHARSTRING,
  TTCN3_UNIVERSAL_CHARSTRING,
  TTCN3_INTEGER,
  TTCN3_OCTETSTRING,
  TTCN3_HEXSTRING,
  TTCN3_VERDICT_TYPE,
  TTCN3_FLOAT,
  TTCN3_ADDRESS,
  TTCN3_DEFAULT,
  TTCN3_ANY_TYPE
};
typedef enum TTCN3Type_e TTCN3Type_t;

namespace TTCN3 {
  class CIdentifier;
  class CCommaList;
  class CSemicolonList;
  class CImportDef;
  class CImportSpec;
  class CImportSpecElement;
}

#endif /* TYPES_H */
