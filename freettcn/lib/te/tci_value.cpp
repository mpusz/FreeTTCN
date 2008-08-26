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
#include "freettcn/ttcn3/tci_value.h"
}
#include "freettcn/te/type.h"
#include "freettcn/te/basicTypes.h"
#include "freettcn/te/record.h"
#include "freettcn/te/module.h"
#include "freettcn/tools/exception.h"


static const freettcn::TE::CType *TypeGet(Type inst);
static freettcn::TE::CType::CInstance *ValueGet(Value inst);

static freettcn::TE::CIntegerType::CInstance *IntegerGet(Value inst);
static freettcn::TE::COctetstringType::CInstance *OctetstringGet(Value inst);
static freettcn::TE::CRecordType::CInstance *RecordGet(Value inst);
static freettcn::TE::CBooleanType::CInstance *BooleanGet(Value inst);
static freettcn::TE::CVerdictType::CInstance *VerdictGet(Value inst);



/* *********************************** T Y P E *********************************** */

const freettcn::TE::CType *TypeGet(Type inst)
{
  if (!inst)
    throw freettcn::ECastFailed(E_DATA, "Instance not given!!!");
  
  return static_cast<const freettcn::TE::CType *>(inst);
}

TciModuleIdType tciGetDefiningModule(Type inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
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

String tciGetName(Type inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return const_cast<char *>(type->Name());
}

TciTypeClassType tciGetTypeClass(Type inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return type->Class();
}

Value tciNewInstance(Type inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return type->InstanceCreate();
}

String tciGetTypeEncoding(Type inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return const_cast<char *>(type->Encoding());
}

String tciGetTypeEncodingVariant(Type inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return const_cast<char *>(type->EncodingVariant());
}



/* ********************************** V A L U E ********************************** */

freettcn::TE::CType::CInstance *ValueGet(Value inst)
{
  if (!inst)
    throw freettcn::ECastFailed(E_DATA, "Instance not given!!!");
  return static_cast<freettcn::TE::CType::CInstance *>(inst);
}

Type tciGetType(Value inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  return &const_cast<freettcn::TE::CType &>(val->Type());
}

Boolean tciNotPresent(Value inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  return val->Omit();
}




/* ******************************** I N T E G E R  ******************************* */

freettcn::TE::CIntegerType::CInstance *IntegerGet(Value inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::CIntegerType::CInstance *integer = dynamic_cast<freettcn::TE::CIntegerType::CInstance *>(val);
  if (!integer)
    throw freettcn::ECastFailed(E_DATA, "Given instance is not of integer type!!!");
  return integer;
}


String tciGetIntAbs(Value inst)
{
  freettcn::TE::CIntegerType::CInstance *integer = IntegerGet(inst);
  return const_cast<char *>(integer->AbsValue());
}


void tciSetIntAbs(Value inst, String value)
{
  freettcn::TE::CIntegerType::CInstance *integer = IntegerGet(inst);
  integer->AbsValue(value);
}


// void tciSetIntNumberOfDigits(Value inst, unsigned long int dig_num)
// {
//   if (!inst)
//     throw ECastFailed();
  
//   freettcn::TE::CType::CInstance *val = static_cast<freettcn::TE::CType::CInstance *>(inst);
//   freettcn::TE::CIntegerValue *integer = dynamic_cast<freettcn::TE::CIntegerValue *>(val);
//   if (!integer)
//     throw ECastFailed();
  
//   integer->DigitsNum(dig_num);
// }


// void tciSetIntSign(Value inst, Boolean sign)
// {
//   if (!inst)
//     throw ECastFailed();
  
//   freettcn::TE::CType::CInstance *val = static_cast<freettcn::TE::CType::CInstance *>(inst);
//   freettcn::TE::CIntegerValue *integer = dynamic_cast<freettcn::TE::CIntegerValue *>(val);
//   if (!integer)
//     throw ECastFailed();
  
//   integer->Sign(sign);
// }





/* *************************** O C T E T S T R I N G ***************************** */

freettcn::TE::COctetstringType::CInstance *OctetstringGet(Value inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::COctetstringType::CInstance *string = dynamic_cast<freettcn::TE::COctetstringType::CInstance *>(val);
  if (!string)
    throw freettcn::ECastFailed(E_DATA, "Given instance is not of octetstring type!!!");
  return string;
}

String tciGetOStringValue(Value inst)
{
  const freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  return const_cast<char *>(string->Value());
}

void tciSetOStringValue(Value inst, String value)
{
  freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  string->Value(value);
}

int tciGetOStringOctetValue(Value inst, unsigned long int position)
{
  const freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  return string->Element(position);
}

void tciSetOStringOctetValue(Value inst, unsigned long int position, int value)
{
  freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  string->Element(position, value);
}

unsigned long int tciGetOStringLength(Value inst)
{
  const freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  return string->Length();
}

void tciSetOStringLength(Value inst, unsigned long int len)
{
  freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  string->Length(len);
}




/* ******************************** R E C O R D ********************************** */

freettcn::TE::CRecordType::CInstance *RecordGet(Value inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::CRecordType::CInstance *record = dynamic_cast<freettcn::TE::CRecordType::CInstance *>(val);
  if (!record)
    throw freettcn::ECastFailed(E_DATA, "Given instance is not of record type!!!");
  return record;
}

Value tciGetRecFieldValue(Value inst, String fieldName)
{
  const freettcn::TE::CRecordType::CInstance *record = RecordGet(inst);
  return &record->Field(fieldName);
}

// void tciSetRecFieldValue(Value inst, String fieldName, Value value)
// {
// }

char** tciGetRecFieldNames(Value inst)
{
  const freettcn::TE::CRecordType::CInstance *record = RecordGet(inst);
  return const_cast<char **>(record->FieldNames());
}

void tciSetFieldOmitted(Value inst, String fieldName)
{
  const freettcn::TE::CRecordType::CInstance *record = RecordGet(inst);
  record->Field(fieldName).Omit(true);
}




/* ******************************* B O O L E A N ********************************* */

freettcn::TE::CBooleanType::CInstance *BooleanGet(Value inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::CBooleanType::CInstance *boolean = dynamic_cast<freettcn::TE::CBooleanType::CInstance *>(val);
  if (!boolean)
    throw freettcn::ECastFailed(E_DATA, "Given instance is not of boolean type!!!");
  return boolean;
}

Boolean tciGetBooleanValue(Value inst)
{
  const freettcn::TE::CBooleanType::CInstance *boolean = BooleanGet(inst);
  return boolean->Value();
}

void tciSetBooleanValue(Value inst, Boolean value)
{
  freettcn::TE::CBooleanType::CInstance *boolean = BooleanGet(inst);
  boolean->Value(static_cast<freettcn::TE::TVerdict>(value));
}



/* ******************************* V E R D I C T ********************************* */

freettcn::TE::CVerdictType::CInstance *VerdictGet(Value inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::CVerdictType::CInstance *verdict = dynamic_cast<freettcn::TE::CVerdictType::CInstance *>(val);
  if (!verdict)
    throw freettcn::ECastFailed(E_DATA, "Given instance is not of verdict type!!!");
  return verdict;
}

int tciGetVerdictValue(Value inst)
{
  const freettcn::TE::CVerdictType::CInstance *verdict = VerdictGet(inst);
  return verdict->Value();
}

void tciSetVerdictValue(Value inst, int verdict)
{
  freettcn::TE::CVerdictType::CInstance *verdictVal = VerdictGet(inst);
  verdictVal->Value(static_cast<freettcn::TE::TVerdict>(verdict));
}
