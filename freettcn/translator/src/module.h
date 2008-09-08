//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) compiler.

// freettcn is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// freettcn is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with freettcn; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   translator.h
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#ifndef __MODULE_H__
#define __MODULE_H__

#include <map>
#include <string>
#include <memory>


namespace freettcn {

  namespace translator {
    
    class CDumper;
    class CIdentifier;
    
    class CModule {
    public:
      enum TLanguage {
        LANGUAGE_TTCN_3_2001,
        LANGUAGE_TTCN_3_2003,
        LANGUAGE_TTCN_3_2005
      };
      
      class CDefinition {
        std::auto_ptr<const CIdentifier> _id;
        const std::string _type;
      public:
        CDefinition(const CIdentifier *id, const std::string &type);
        virtual ~CDefinition();
        
        virtual void Dump(CDumper &dumper);
        
        const CIdentifier &Id() const;
        const std::string &Type() const;
      };
      
    private:
      typedef std::map<std::string, CDefinition *> CDefMap;
      
      std::auto_ptr<const CIdentifier> _id;
      TLanguage _language;
      CDefMap _definitionsMap;
      
    public:
      CModule(const CIdentifier *id, TLanguage language);
      ~CModule();
      
      void Register(CDefinition *def);
      const CDefinition *IdCheck(const CIdentifier &id) const;
      
      void Dump(CDumper &dumper);
    };
    
  } // namespace translator

} // namespace freettcn


inline const freettcn::translator::CIdentifier &freettcn::translator::CModule::CDefinition::Id() const
{
  return *_id;
}


inline const std::string &freettcn::translator::CModule::CDefinition::Type() const
{
  return _type;
}


#endif  // __MODULE_H__



// #include "identifier.h"

// namespace TTCN3 {
  
//   /**
//    * @brief TTCN-3 Module Node.
//    *
//    * Class contains all information about TTCN-3 Module Definition. It
//    * stores information about all TTCN-3 definitions and a control part (if exists).
//    */
//   class CModule : public CNamedNode {
//   public:
//     /**
//      * @brief TTCN-3 Definition Node.
//      *
//      * Class is a base class for all TTCN-3 module definitions.
//      */
//     class CDefinition : public CNamedNode {
//       CModule &module;
//     public:
//       CDefinition(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
//       ~CDefinition();
      
//       CModule &Module() { return module; }        /**< @brief Returns parent TTCN-3 module. */
//     };
    
//     /**
//      * @brief TTCN-3 Control Part Node.
//      *
//      * Class contains all information about TTCN-3 Module Control Part.
//      */
//     class CControl : public CNode {
//       CModule &module;
//     public:
//       CControl(CFile &f, const YYLTYPE &loc, CModule &mod);
//       ~CControl();
      
//       CModule &Module() { return module; }        /**< @brief Returns parent TTCN-3 module. */
      
//       void DumpTTCN3(FILE *fdout) const;
//       void DumpCPP(FILE *fdout) const;
//     };
    
//   private:
//     typedef std::list<CDefinition *> Container;
//     Container definitionList;
//     CControl *control;
    
//   public:
//     friend class CDefinition;
    
//     CModule(CFile &f, const YYLTYPE &loc, CIdentifier &id);
//     ~CModule();
    
//     void DumpTTCN3(FILE *fdout) const;
//     void DumpCPP(FILE *fdout) const;
//   };
// }

// #endif /* MODULE_H */
