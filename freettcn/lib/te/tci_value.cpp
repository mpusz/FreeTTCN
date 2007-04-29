//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) library.

// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


extern "C" {
#include <freettcn/ttcn3/tci_value.h>
}
#include <freettcn/te/value.h>
#include <freettcn/te/type.h>
#include <freettcn/te/module.h>


TciModuleIdType tciGetDefiningModule(TciType inst)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  const freettcn::TE::CType *type = static_cast<const freettcn::TE::CType *>(inst);
  if (const freettcn::TE::CModule *module = type->DefiningModule())
    // user defined type
    return module->Id();
  else {
    // TTCN-3 base type
    TciModuleIdType moduleId;
    moduleId.moduleName = 0;
    moduleId.objectName = 0;
    moduleId.aux = 0;
    
    return moduleId;
  }
}


String tciGetName(TciType inst)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  const freettcn::TE::CType *type = static_cast<const freettcn::TE::CType *>(inst);
  return type->Name();
}


TciTypeClassType tciGetTypeClass(TciType inst)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  const freettcn::TE::CType *type = static_cast<const freettcn::TE::CType *>(inst);
  return type->Class();
}


TciValue tciNewInstance(TciType inst)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  const freettcn::TE::CType *type = static_cast<const freettcn::TE::CType *>(inst);
  return type->InstanceCreate();
}




TciType tciGetType(TciValue inst)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  freettcn::TE::CValue *val = static_cast<freettcn::TE::CValue *>(inst);
  return &const_cast<freettcn::TE::CType &>(val->Type());
}



void tciSetIntAbs(TciValue inst, String value)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  freettcn::TE::CValue *val = static_cast<freettcn::TE::CValue *>(inst);
  freettcn::TE::CIntegerValue *integer = dynamic_cast<freettcn::TE::CIntegerValue *>(val);
  if (!integer)
    throw freettcn::ECastFailed();
  
  integer->AbsValue(value);
}


void tciSetIntNumberOfDigits(TciValue inst, unsigned long int dig_num)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  freettcn::TE::CValue *val = static_cast<freettcn::TE::CValue *>(inst);
  freettcn::TE::CIntegerValue *integer = dynamic_cast<freettcn::TE::CIntegerValue *>(val);
  if (!integer)
    throw freettcn::ECastFailed();
  
  integer->DigitsNum(dig_num);
}


void tciSetIntSign(TciValue inst, Boolean sign)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  freettcn::TE::CValue *val = static_cast<freettcn::TE::CValue *>(inst);
  freettcn::TE::CIntegerValue *integer = dynamic_cast<freettcn::TE::CIntegerValue *>(val);
  if (!integer)
    throw freettcn::ECastFailed();
  
  integer->Sign(sign);
}


TciValue tciGetRecFieldValue(TciValue inst, String fieldName)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  const freettcn::TE::CValue *val = static_cast<const freettcn::TE::CValue *>(inst);
  const freettcn::TE::CRecordValue *record = dynamic_cast<const freettcn::TE::CRecordValue *>(val);
  if (!record)
    throw freettcn::ECastFailed();
  
  return record->Field(fieldName);
}
