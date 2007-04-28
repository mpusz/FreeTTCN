#ifndef LIST_H
#define LIST_H

#include "module.h"

namespace TTCN3 {

  /**
   * @brief TTCN-3 List Definition Node.
   *
   * Class is a base class for all list types defined in TTCN-3.
   */
  class CList : public CNode {
  protected:
    typedef std::list<CNode *> Container;
    Container list;
  public:
    CList(CFile &f, const YYLTYPE &loc);
    ~CList();
    
    void Add(CNode &elem);
  };
  
  /**
   * @brief TTCN-3 Comma-separated List Definition Node.
   *
   * Class contains all information about TTCN-3 Comma-separated List Definition.
   */
  class CCommaList : public CList {
  public:
    CCommaList(CFile &f, const YYLTYPE &loc);
    ~CCommaList();
    
    void DumpTTCN3(FILE *fdout) const;
    void DumpCPP(FILE *fdout) const;
  };
  
  /**
   * @brief TTCN-3 Semicolon-separated List Definition Node.
   *
   * Class contains all information about TTCN-3 Semicolon-separated Definition.
   */
  class CSemicolonList : public CList {
  public:
    CSemicolonList(CFile &f, const YYLTYPE &loc);
    ~CSemicolonList();
    
    void DumpTTCN3(FILE *fdout) const;
    void DumpCPP(FILE *fdout) const;
  };

}

#endif /* LIST_H */
