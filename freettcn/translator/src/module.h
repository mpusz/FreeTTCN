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
        std::shared_ptr<const CIdentifier> _id;
        std::shared_ptr<CType> _type;
      public:
        CDefinition(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type);
        virtual ~CDefinition();
        
        virtual void Dump(CDumper &dumper) const;
        
        const CIdentifier &Id() const;
        std::shared_ptr<CType> Type() const;
      };
      
      
      class CDefinitionParameter : public CModule::CDefinition {
        std::shared_ptr<const CExpression> _expr;
      public:
        CDefinitionParameter(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, std::shared_ptr<const CExpression> expr);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionConstValue : public CModule::CDefinition {
        std::shared_ptr<const CExpression> _expr;
      public:
        CDefinitionConstValue(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, std::shared_ptr<const CExpression> expr);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionTypeLocal : public CModule::CDefinition {
        std::shared_ptr<CTypeLocal> _type;
      public:
        CDefinitionTypeLocal(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CTypeLocal> type);
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
        CDefinitionFormalParameter(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type, TDirection dir);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionMethod : public CModule::CDefinition {
        typedef std::deque<std::shared_ptr<const CDefinitionFormalParameter>> CParamList;
        CParamList _params;
      public:
        CDefinitionMethod(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type);
        ~CDefinitionMethod();
        void Register(std::shared_ptr<const CDefinitionFormalParameter> par);
      };
      
      
      class CDefinitionTestcase : public CModule::CDefinitionMethod {
      public:
        CDefinitionTestcase(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
      class CDefinitionTemplate : public CModule::CDefinitionMethod {
      public:
        CDefinitionTemplate(std::shared_ptr<const CIdentifier> id, std::shared_ptr<CType> type);
        virtual void Dump(CDumper &dumper) const;
      };
      
      
    private:
      typedef std::deque<std::shared_ptr<CDefinition>> CDefList;
      
      std::shared_ptr<const CIdentifier> _id;
      const TLanguage _language;
      CDefList _defList;
      
    public:
      CModule(std::shared_ptr<const CIdentifier> id, TLanguage language);
      ~CModule();
      
      void Register(std::shared_ptr<CDefinition> def);
//       const CDefinition *Id(const CIdentifier &id) const;
      
      void Dump(CDumper &dumper) const;
    };
    
  } // namespace translator

} // namespace freettcn


inline const freettcn::translator::CIdentifier &freettcn::translator::CModule::CDefinition::Id() const
{
  return *_id;
}


inline std::shared_ptr<freettcn::translator::CType> freettcn::translator::CModule::CDefinition::Type() const
{
  return _type;
}


#endif  // __MODULE_H__
