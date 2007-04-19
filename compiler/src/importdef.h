#ifndef IMPORTDEF_H
#define IMPORTDEF_H

#include "module.h"
#include "list.h"


namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Template Specification Element Node.
   *
   * Class contains all information about TTCN-3 Template Specification List Element.
   */
  class CImportSpecElement : public CNode {
  public:
    CImportSpecElement(CFile &f, const YYLTYPE &loc);
    ~CImportSpecElement();
    
    void DumpTTCN3(FILE *fdout) const;
    void DumpCPP(FILE *fdout) const;
  };
  
  /**
   * @brief TTCN-3 Template Specification Node.
   *
   * Class contains all information about TTCN-3 Template Specification List.
   */
  class CImportSpec : public CNode {
  protected:
    CSemicolonList *list;
  public:
    CImportSpec(CFile &f, const YYLTYPE &loc, CSemicolonList *l);
    ~CImportSpec();
    
    void DumpTTCN3(FILE *fdout) const;
    void DumpCPP(FILE *fdout) const;
  };
  
  /**
   * @brief TTCN-3 Template Specification With Exceptions Node.
   *
   * Class contains all information about TTCN-3 Template Specification List With Exceptions.
   */
  class CImportSpecAllWithExcepts : public CImportSpec {
  public:
    CImportSpecAllWithExcepts(CFile &f, const YYLTYPE &loc, CSemicolonList *list);
    ~CImportSpecAllWithExcepts();
    
    void DumpTTCN3(FILE *fdout) const;
    void DumpCPP(FILE *fdout) const;
  };
  
  /**
   * @brief TTCN-3 Import Definition Node.
   *
   * Class contains all information about TTCN-3 Import Definition.
   */
  class CImportDef : public CModule::CDefinition {
    const bool recursive;
    CImportSpec *spec;
    
  public:
    CImportDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod, const bool rec);
    ~CImportDef();
    
    void Spec(CImportSpec &importSpec) { spec = &importSpec; } /**< @brief Sets Import Specification List. */
    
    void DumpTTCN3(FILE *fdout) const;
    void DumpCPP(FILE *fdout) const;
  };

}

#endif /* IMPORTDEF_H */
