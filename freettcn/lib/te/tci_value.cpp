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


static const freettcn::TE::CType *TypeGet(TciType inst);
static freettcn::TE::CType::CInstance *ValueGet(TciValue inst);

static freettcn::TE::CIntegerType::CInstance *IntegerGet(TciValue inst);
static freettcn::TE::COctetstringType::CInstance *OctetstringGet(TciValue inst);
static freettcn::TE::CRecordType::CInstance *RecordGet(TciValue inst);
static freettcn::TE::CBooleanType::CInstance *BooleanGet(TciValue inst);
static freettcn::TE::CVerdictType::CInstance *VerdictGet(TciValue inst);



/* *********************************** T Y P E *********************************** */

const freettcn::TE::CType *TypeGet(TciType inst)
{
  if (!inst)
    throw freettcn::ECastFailed();
  
  return static_cast<const freettcn::TE::CType *>(inst);
}

TciModuleIdType tciGetDefiningModule(TciType inst)
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

String tciGetName(TciType inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return const_cast<char *>(type->Name());
}

TciTypeClassType tciGetTypeClass(TciType inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return type->Class();
}

TciValue tciNewInstance(TciType inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return type->InstanceCreate();
}

String tciGetTypeEncoding(TciType inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return const_cast<char *>(type->Encoding());
}

String tciGetTypeEncodingVariant(TciType inst)
{
  const freettcn::TE::CType *type = TypeGet(inst);
  return const_cast<char *>(type->EncodingVariant());
}



/* ********************************** V A L U E ********************************** */

freettcn::TE::CType::CInstance *ValueGet(TciValue inst)
{
  if (!inst)
    throw freettcn::ECastFailed();
  return static_cast<freettcn::TE::CType::CInstance *>(inst);
}

TciType tciGetType(TciValue inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  return &const_cast<freettcn::TE::CType &>(val->Type());
}

Boolean tciNotPresent(TciValue inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  return val->Omit();
}




/* ******************************** I N T E G E R  ******************************* */

freettcn::TE::CIntegerType::CInstance *IntegerGet(TciValue inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::CIntegerType::CInstance *integer = dynamic_cast<freettcn::TE::CIntegerType::CInstance *>(val);
  if (!integer)
    throw freettcn::ECastFailed();
  return integer;
}


String tciGetIntAbs(TciValue inst)
{
  freettcn::TE::CIntegerType::CInstance *integer = IntegerGet(inst);
  return const_cast<char *>(integer->AbsValue());
}


void tciSetIntAbs(TciValue inst, String value)
{
  freettcn::TE::CIntegerType::CInstance *integer = IntegerGet(inst);
  integer->AbsValue(value);
}


// void tciSetIntNumberOfDigits(TciValue inst, unsigned long int dig_num)
// {
//   if (!inst)
//     throw freettcn::ECastFailed();
  
//   freettcn::TE::CType::CInstance *val = static_cast<freettcn::TE::CType::CInstance *>(inst);
//   freettcn::TE::CIntegerValue *integer = dynamic_cast<freettcn::TE::CIntegerValue *>(val);
//   if (!integer)
//     throw freettcn::ECastFailed();
  
//   integer->DigitsNum(dig_num);
// }


// void tciSetIntSign(TciValue inst, Boolean sign)
// {
//   if (!inst)
//     throw freettcn::ECastFailed();
  
//   freettcn::TE::CType::CInstance *val = static_cast<freettcn::TE::CType::CInstance *>(inst);
//   freettcn::TE::CIntegerValue *integer = dynamic_cast<freettcn::TE::CIntegerValue *>(val);
//   if (!integer)
//     throw freettcn::ECastFailed();
  
//   integer->Sign(sign);
// }





/* *************************** O C T E T S T R I N G ***************************** */

freettcn::TE::COctetstringType::CInstance *OctetstringGet(TciValue inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::COctetstringType::CInstance *string = dynamic_cast<freettcn::TE::COctetstringType::CInstance *>(val);
  if (!string)
    throw freettcn::ECastFailed();
  return string;
}

String tciGetOStringValue(TciValue inst)
{
  const freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  return const_cast<char *>(string->Value());
}

void tciSetOStringValue(TciValue inst, String value)
{
  freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  string->Value(value);
}

int tciGetOStringOctetValue(TciValue inst, unsigned long int position)
{
  const freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  return string->Element(position);
}

void tciSetOStringOctetValue(TciValue inst, unsigned long int position, int value)
{
  freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  string->Element(position, value);
}

unsigned long int tciGetOStringLength(TciValue inst)
{
  const freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  return string->Length();
}

void tciSetOStringLength(TciValue inst, unsigned long int len)
{
  freettcn::TE::COctetstringType::CInstance *string = OctetstringGet(inst);
  string->Length(len);
}




/* ******************************** R E C O R D ********************************** */

freettcn::TE::CRecordType::CInstance *RecordGet(TciValue inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::CRecordType::CInstance *record = dynamic_cast<freettcn::TE::CRecordType::CInstance *>(val);
  if (!record)
    throw freettcn::ECastFailed();
  return record;
}

TciValue tciGetRecFieldValue(TciValue inst, String fieldName)
{
  const freettcn::TE::CRecordType::CInstance *record = RecordGet(inst);
  return &record->Field(fieldName);
}

// void tciSetRecFieldValue(TciValue inst, String fieldName, TciValue value)
// {
// }

char** tciGetRecFieldNames(TciValue inst)
{
  const freettcn::TE::CRecordType::CInstance *record = RecordGet(inst);
  return const_cast<char **>(record->FieldNames());
}

void tciSetFieldOmitted(TciValue inst, String fieldName)
{
  const freettcn::TE::CRecordType::CInstance *record = RecordGet(inst);
  record->Field(fieldName).Omit(true);
}




/* ******************************* B O O L E A N ********************************* */

freettcn::TE::CBooleanType::CInstance *BooleanGet(TciValue inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::CBooleanType::CInstance *boolean = dynamic_cast<freettcn::TE::CBooleanType::CInstance *>(val);
  if (!boolean)
    throw freettcn::ECastFailed();
  return boolean;
}

Boolean tciGetBooleanValue(TciValue inst)
{
  const freettcn::TE::CBooleanType::CInstance *boolean = BooleanGet(inst);
  return boolean->Value();
}

void tciSetBooleanValue(TciValue inst, Boolean value)
{
  freettcn::TE::CBooleanType::CInstance *boolean = BooleanGet(inst);
  boolean->Value(static_cast<freettcn::TE::TVerdict>(value));
}



/* ******************************* V E R D I C T ********************************* */

freettcn::TE::CVerdictType::CInstance *VerdictGet(TciValue inst)
{
  freettcn::TE::CType::CInstance *val = ValueGet(inst);
  freettcn::TE::CVerdictType::CInstance *verdict = dynamic_cast<freettcn::TE::CVerdictType::CInstance *>(val);
  if (!verdict)
    throw freettcn::ECastFailed();
  return verdict;
}

int tciGetVerdictValue(TciValue inst)
{
  const freettcn::TE::CVerdictType::CInstance *verdict = VerdictGet(inst);
  return verdict->Value();
}

void tciSetVerdictValue(TciValue inst, int verdict)
{
  freettcn::TE::CVerdictType::CInstance *verdictVal = VerdictGet(inst);
  verdictVal->Value(static_cast<freettcn::TE::TVerdict>(verdict));
}
