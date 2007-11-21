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


#include "freettcn/sa/sa.h"

extern "C" {
#include <freettcn/ttcn3/tri_sa_te.h>
#include <freettcn/ttcn3/tci_tl.h>
}
#include <freettcn/tools/timeStamp.h>



freettcn::SA::CLogMask::CLogMask(bool enabled /* true */):
  freettcn::CLogMask(CMD_SA_NUM, enabled)
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
  /// @todo Reset of SA
  return TRI_OK;
}


TriStatus freettcn::SA::CSUTAdaptor::TestCaseExecute(const TriTestCaseId &testCaseId, const TriPortIdList &tsiPortList)
{
  return TRI_OK;
}


TriStatus freettcn::SA::CSUTAdaptor::Map(const TriPortId &compPortId, const TriPortId &tsiPortId)
{
  if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_SA_P_MAP)) {
    TriComponentId comp = { { 0 } };
    // log
    tliPMap(0, TimeStamp().Get(), 0, 0, comp, compPortId.compInst, compPortId, tsiPortId.compInst, tsiPortId);
  }
  
  /// @todo mapping on SA
  return TRI_OK;
}


TriStatus freettcn::SA::CSUTAdaptor::Unmap(const TriPortId &compPortId, const TriPortId &tsiPortId)
{
  if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_SA_P_UNMAP)) {
    TriComponentId comp = { { 0 } };
    // log
    tliPUnmap(0, TimeStamp().Get(), 0, 0, comp, compPortId.compInst, compPortId, tsiPortId.compInst, tsiPortId);
  }
  
  /// @todo unmapping on SA
  return TRI_OK;
}


TriStatus freettcn::SA::CSUTAdaptor::Send(const TriComponentId &componentId,
                                          const TriPortId &tsiPortId,
                                          const TriAddress *sutAddress,
                                          const TriMessage &sendMessage)
{
  /// @todo sending on SA

#warning "Packet sending removed"
//   int sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
//   //setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

//   struct sockaddr_in servaddr = { 0 };
//   servaddr.sin_family = AF_INET;
//   servaddr.sin_port = htons(123);
//   if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
//     err_quit("inet_pton error for %s", argv[1]);
    
//   len_inet = sizeof(servaddr);
  
//   sendto(sockfd, sendMessage.data, ceil(sendMessage.bits / 8.0), 0, pr->sasend, pr->salen);
  

  return TRI_OK;
}
