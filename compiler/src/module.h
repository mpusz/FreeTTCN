#ifndef MODULE_H
#define MODULE_H

#include "identifier.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Module Node.
   *
   * Class contains all information about TTCN-3 Module Definition. It
   * stores information about all TTCN-3 definitions and a control part (if exists).
   */
  class CModule : public CNamedNode {
  public:
    /**
     * @brief TTCN-3 Definition Node.
     *
     * Class is a base class for all TTCN-3 module definitions.
     */
    class CDefinition : public CNamedNode {
      CModule &module;
    public:
      CDefinition(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
      ~CDefinition();
      
      CModule &Module() { return module; }        /**< @brief Returns parent TTCN-3 module. */
    };
    
    /**
     * @brief TTCN-3 Control Part Node.
     *
     * Class contains all information about TTCN-3 Module Control Part.
     */
    class CControl : public CNode {
      CModule &module;
    public:
      CControl(CFile &f, const YYLTYPE &loc, CModule &mod);
      ~CControl();
      
      CModule &Module() { return module; }        /**< @brief Returns parent TTCN-3 module. */
      
      void DumpTTCN3(FILE *fdout) const;
      void DumpCPP(FILE *fdout) const;
    };
    
  private:
    typedef std::list<CDefinition *> Container;
    Container definitionList;
    CControl *control;
    
  public:
    friend class CDefinition;
    
    CModule(CFile &f, const YYLTYPE &loc, CIdentifier &id);
    ~CModule();
    
    void DumpTTCN3(FILE *fdout) const;
    void DumpCPP(FILE *fdout) const;
  };
}

#endif /* MODULE_H */
