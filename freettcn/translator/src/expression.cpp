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
 * @file   expression.cpp
 * @author Mateusz Pusz
 * @date   
 * 
 * @brief  
 * 
 * 
 */


#include "expression.h"
#include "identifier.h"
#include "type.h"
#include "dumper.h"
#include "freettcn/tools/exception.h"
#include <sstream>


freettcn::translator::CExpression::~CExpression()
{
}



freettcn::translator::CExpressionValue::CExpressionValue(std::shared_ptr<const CType> type, const char *value):
  _type(type), _value(value)
{
  if(!value)
    throw ENotInitialized(E_DATA, "Expression value not specified!!!");
}


void freettcn::translator::CExpressionValue::Dump(CDumper &dumper) const
{
  dumper.Print(_value);
}



freettcn::translator::CExpressionDef::CExpressionDef(const CModule::CDefinition &def):
  _def(def)
{
}


std::shared_ptr<const freettcn::translator::CType> freettcn::translator::CExpressionDef::Type() const
{
  return _def.Type();
}


bool freettcn::translator::CExpressionDef::Constant() const
{
  /// @todo implement constant from definition
  return true;
}


void freettcn::translator::CExpressionDef::Dump(CDumper &dumper) const
{
  dumper.Print(_def.Id().Name());
}




freettcn::translator::CExpressionSingle::CExpressionSingle(TOperation operation, std::shared_ptr<const CExpression> expr):
  _operation(operation), _expr(expr)
{
  if(operation == OPERATION_NOT_SET)
    throw ENotInitialized(E_DATA, "Single expression operation not specified!!!");
  if(!expr)
    throw ENotInitialized(E_DATA, "Expression not specified!!!");
}


void freettcn::translator::CExpressionSingle::Dump(CDumper &dumper) const
{
  /// @todo implement dumper
}




freettcn::translator::CExpressionPair::CExpressionPair(TOperation operation, std::shared_ptr<const CExpression> expr1, std::shared_ptr<const CExpression> expr2):
  _operation(operation), _expr1(expr1), _expr2(expr2)
{
  if(operation == OPERATION_NOT_SET)
    throw ENotInitialized(E_DATA, "Pair expression operation not specified!!!");
  if(!expr1)
    throw ENotInitialized(E_DATA, "Left expression not specified!!!");
  if(!expr2)
    throw ENotInitialized(E_DATA, "Right expression not specified!!!");
}


std::shared_ptr<const freettcn::translator::CType> freettcn::translator::CExpressionPair::Type() const
{
  switch(_operation) {
  case OPERATION_OR:
  case OPERATION_XOR:
  case OPERATION_AND:
  case OPERATION_EQUALS:
  case OPERATION_NOT_EQUALS:
  case OPERATION_LESS:
  case OPERATION_MORE:
  case OPERATION_NOT_LESS:
  case OPERATION_NOT_MORE:
    return CTypePredefined::Boolean();
    
  case OPERATION_SHIFT_LEFT:
  case OPERATION_SHIFT_RIGHT:
  case OPERATION_SHIFT_LEFT_STR:
  case OPERATION_SHIFT_RIGHT_STR:
    return _expr1->Type();

  case OPERATION_BIT_OR:
  case OPERATION_BIT_XOR:
  case OPERATION_BIT_AND:
    /// @todo which side to choose?
    return _expr1->Type();
    
  case OPERATION_ADD:
  case OPERATION_SUBTRACT:
  case OPERATION_STRING_ADD:
  case OPERATION_MULTIPLY:
  case OPERATION_DIVIDE:
  case OPERATION_MODULO:
  case OPERATION_REMINDER:
    /// @todo which side to choose?
    return _expr1->Type();
    
  default:
    {
      std::stringstream stream;
      stream << "Unknown operation type: " << _operation << "!!!";
      throw EOperationFailed(E_DATA, stream.str());
    }
  }
}


void freettcn::translator::CExpressionPair::Dump(CDumper &dumper) const
{
  /// @todo implement dumper
}
