//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcnenv (Free TTCN Environment) library.

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


#include <freettcn/sa/sa.h>

extern "C" {
#include <freettcn/ttcn3/tri_sa_te.h>
#include <freettcn/ttcn3/tci_tl.h>
}


freettcn::SA::CLogMask::CLogMask(bool enabled /* true */):
  freettcn::CLogMask(freettcn::LOG_SA_NUM, enabled)
{
}

freettcn::SA::CLogMask::~CLogMask()
{
}


freettcn::SA::CSUTAdaptor *freettcn::SA::CSUTAdaptor::_instance = 0;

freettcn::SA::CSUTAdaptor &freettcn::SA::CSUTAdaptor::Instance() throw(ENotFound)
{
  if (_instance)
    return *_instance;
  
  throw ENotFound();
}

freettcn::SA::CSUTAdaptor::CSUTAdaptor()
{
  _instance = this;
}

freettcn::SA::CSUTAdaptor::~CSUTAdaptor()
{
  //  Clear();
  _instance = 0;
}


TriStatus freettcn::SA::CSUTAdaptor::Reset()
{
  return TRI_OK;
}


TriStatus freettcn::SA::CSUTAdaptor::TestCaseExecute(const TriTestCaseId &testCaseId, const TriPortIdList &tsiPortList)
{
  return TRI_OK;
}


TriStatus freettcn::SA::CSUTAdaptor::Map(const TriPortId &compPortId, const TriPortId &tsiPortId)
{
  return TRI_OK;
}


TriStatus freettcn::SA::CSUTAdaptor::Unmap(const TriPortId &compPortId, const TriPortId &tsiPortId)
{
  return TRI_OK;
}


// void MessageReceived()
// {
//   TriPortId portId;
//   unsigned char portIdData[] = { 12, 34 };
//   portId.compInst.compInst.data = portIdData;
//   portId.compInst.compInst.bits = 16;
//   portId.compInst.compName = "teComp";
//   portId.compInst.compType.moduleName = "IP";
//   portId.compInst.compType.objectName = "IP_TE";
//   portId.compInst.compType.aux = 0;
//   portId.portName = "IPPort";
//   portId.portIndex = 0;
//   portId.portType.moduleName = "IP";
//   portId.portType.objectName = "IPPort";
//   portId.portType.aux = 0;
//   portId.aux = 0;

//   TriAddress sutAddress;
//   unsigned char sutAddressData[] = { 0x5a, 0x5a, 0x5a, 0x5a };
//   sutAddress.data = sutAddressData;
//   sutAddress.bits = 32;
//   sutAddress.aux = 0;

//   TriComponentId componentId;
//   unsigned char componentIdData[] = { 23, 45 };
//   componentId.compInst.data = componentIdData;
//   componentId.compInst.bits = 16;
//   componentId.compInst.aux = 0;
//   componentId.compName = "saComp";
//   componentId.compType.moduleName = "IP";
//   componentId.compType.objectName = "IP_SA";
//   componentId.compType.aux = 0;

//   TriMessage receivedMessage;
//   unsigned char receivedMessageData[] = { 0x00, 0x00, 0xba, 0xba,
//                                           0x55, 0x55, 0x00, 0x00,
//                                           0x00, 0x00, 0xba, 0xba,
//                                           0x55, 0x55, 0x00, 0x00,
//                                           0x55, 0x55, 0x00, 0x00 };
//   receivedMessage.data = receivedMessageData;
//   receivedMessage.bits = sizeof(receivedMessageData) * 8;
//   receivedMessage.aux = 0;

//   tliMDetected_m("", 12345, "", 0, componentId, portId, receivedMessage, sutAddress);

//   triEnqueueMsg(&portId, &sutAddress, &componentId, &receivedMessage);
// }
