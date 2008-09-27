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

#include <stack>
#include <deque>
#include <string>
#include <memory>


namespace freettcn {

  namespace translator {
    
    class CDumper;
    class CIdentifier;
    class CExpression;
    class CType;
    class CTypeLocal;
    
    class CModule {
    public:
      enum TLanguage {
        LANGUAGE_TTCN_3_2001,
        LANGUAGE_TTCN_3_2003,
        LANGUAGE_TTCN_3_2005
      };
      
      class CDefinition {
        const std::auto_ptr<const CIdentifier> _id;
        CType &_type;
      public:
        CDefinition(const CIdentifier *id, CType &type);
        virtual ~CDefinition();
        
        virtual void Dump(CDumper &dumper) const;
        
        const CIdentifier &Id() const;
        CType &Type() const;
      };
      
      
      class CDefinitionParameter : public CModule::CDefinition {
        const std::auto_ptr<const CExpression> _expr;
      public:
        CDefinitionParameter(const CIdentifier *id, CType &type, const CExpression *expr);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionConstValue : public CModule::CDefinition {
        const std::auto_ptr<const CExpression> _expr;
      public:
        CDefinitionConstValue(const CIdentifier *id, CType &type, const CExpression *expr);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionTypeLocal : public CModule::CDefinition {
        std::auto_ptr<CTypeLocal> _type;
      public:
        CDefinitionTypeLocal(const CIdentifier *id, CTypeLocal *type);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionFormalParameter : public CModule::CDefinition {
      public:
        enum TDirection {
          DIRECTION_IN,
          DIRECTION_OUT,
          DIRECTION_INOUT
        };
      private:
        const TDirection _dir;
      public:
        CDefinitionFormalParameter(const CIdentifier *id, CType &type, TDirection dir);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionMethod : public CModule::CDefinition {
        typedef std::deque<const CDefinitionFormalParameter *> CParamList;
        CParamList _params;
      public:
        CDefinitionMethod(const CIdentifier *id, CType &type);
        ~CDefinitionMethod();
        void Register(const CDefinitionFormalParameter *par);
      };
      
      
      class CDefinitionTestcase : public CModule::CDefinitionMethod {
      public:
        CDefinitionTestcase(const CIdentifier *id, CType &type);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionTemplate : public CModule::CDefinitionMethod {
      public:
        CDefinitionTemplate(const CIdentifier *id, CType &type);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
    private:
      typedef std::deque<CDefinition *> CDefList;
      
      const std::auto_ptr<const CIdentifier> _id;
      const TLanguage _language;
      CDefList _defList;
      
    public:
      CModule(const CIdentifier *id, TLanguage language);
      ~CModule();
      
      void Register(CDefinition *def);
//       const CDefinition *Id(const CIdentifier &id) const;
      
      void Dump(CDumper &dumper) const;
    };
    
  } // namespace translator

} // namespace freettcn


inline const freettcn::translator::CIdentifier &freettcn::translator::CModule::CDefinition::Id() const
{
  return *_id;
}


inline freettcn::translator::CType &freettcn::translator::CModule::CDefinition::Type() const
{
  return _type;
}


#endif  // __MODULE_H__
