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
 * @file   expression.h
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include "module.h"
#include <string>
#include <memory>


namespace freettcn {

  namespace translator {

    class CDumper;
    class CType;
    class CIdentifier;
    
    class CExpression {
    public:
      virtual ~CExpression() = 0;
      
      virtual std::shared_ptr<const CType> Type() const = 0;
      virtual bool Constant() const = 0;
      virtual void Dump(CDumper &dumper) const = 0;
    };
    
    
    class CExpressionValue : public CExpression {
      std::shared_ptr<const CType> _type;
      const std::string _value;
    public:
      CExpressionValue(std::shared_ptr<const CType> type, const char *value);
      virtual std::shared_ptr<const CType> Type() const { return _type; }
      virtual bool Constant() const { return true; }
      virtual void Dump(CDumper &dumper) const;
    };
    
    
    class CExpressionDef : public CExpression {
      const CModule::CDefinition &_def;
    public:
      CExpressionDef(const CModule::CDefinition &def);
      virtual std::shared_ptr<const CType> Type() const;
      virtual bool Constant() const;
      virtual void Dump(CDumper &dumper) const;
    };
    
    
    class CExpressionSingle : public CExpression {
    public:
      enum TOperation {
        OPERATION_NOT_SET,
        OPERATION_NOT,
        OPERATION_BIT_NOT,
        OPERATION_PLUS,
        OPERATION_MINUS,
        OPERATION_BRACES
      };
    private:
      const TOperation _operation;
      const std::shared_ptr<const CExpression> _expr;
    public:
      CExpressionSingle(TOperation operation, std::shared_ptr<const CExpression> expr);
      virtual std::shared_ptr<const CType> Type() const { return _expr->Type(); }
      virtual bool Constant() const { return _expr->Constant(); }
      virtual void Dump(CDumper &dumper) const;
    };
    
    
    class CExpressionPair : public CExpression {
    public:
      enum TOperation {
        OPERATION_NOT_SET,
        OPERATION_OR,
        OPERATION_XOR,
        OPERATION_AND,
        OPERATION_EQUALS,
        OPERATION_NOT_EQUALS,
        OPERATION_LESS,
        OPERATION_MORE,
        OPERATION_NOT_LESS,
        OPERATION_NOT_MORE,
        OPERATION_SHIFT_LEFT,
        OPERATION_SHIFT_RIGHT,
        OPERATION_SHIFT_LEFT_STR,
        OPERATION_SHIFT_RIGHT_STR,
        OPERATION_BIT_OR,
        OPERATION_BIT_XOR,
        OPERATION_BIT_AND,
        OPERATION_ADD,
        OPERATION_SUBTRACT,
        OPERATION_STRING_ADD,
        OPERATION_MULTIPLY,
        OPERATION_DIVIDE,
        OPERATION_MODULO,
        OPERATION_REMINDER
      };
    private:
      const TOperation _operation;
      const std::shared_ptr<const CExpression> _expr1;
      const std::shared_ptr<const CExpression> _expr2;
    public:
      CExpressionPair(TOperation operation, std::shared_ptr<const CExpression> expr1, std::shared_ptr<const CExpression> expr2);
      virtual std::shared_ptr<const CType> Type() const;
      virtual bool Constant() const { return _expr1->Constant() && _expr2->Constant(); }
      virtual void Dump(CDumper &dumper) const;
    };
    
  } // namespace translator

} // namespace freettcn


#endif  // __EXPRESSION_H__
