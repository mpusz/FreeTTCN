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

/**
 * @file   tci_te_ch.cpp
 * @author Mateusz Pusz
 * @date   Mon Apr  9 22:18:51 2007
 * 
 * @brief  
 * 
 * 
 */


extern "C" {
#include <freettcn/ttcn3/tci_te_ch.h>
}
#include <freettcn/ch/ch.h>


TriComponentId tciCreateTestComponentReq(TciTestComponentKindType kind,
                                         TciType componentType,
                                         String name)
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.TestComponentCreateReq(kind, componentType, name);
}


void tciStartTestComponentReq(TriComponentId component,
                              TciBehaviourIdType behavior,
                              TciParameterListType parameterList)
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.TestComponentStartReq(component, behavior, parameterList);
}


void tciConnectReq(TriPortId fromPort, TriPortId toPort)
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.ConnectReq(fromPort, toPort);
}


void tciDisconnectReq(TriPortId fromPort,
                      TriPortId toPort)
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.DisconnectReq(fromPort, toPort);
}


void tciMapReq(TriPortId fromPort, TriPortId toPort)
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.MapReq(fromPort, toPort);
}


void tciUnmapReq(TriPortId fromPort, TriPortId toPort)
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.UnmapReq(fromPort, toPort);
}

void tciTestComponentTerminatedReq(TriComponentId component,
                                   TciVerdictValue verdict)
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.TestComponentTerminatedReq(component, verdict);
}



void tciExecuteTestCaseReq(TciTestCaseIdType testCaseId,
                           TriPortIdList tsiPortList)
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.TestCaseExecuteReq(testCaseId, tsiPortList);
}


void tciResetReq()
{
  freettcn::CH::CComponentHandler &ch = freettcn::CH::CComponentHandler::Instance();
  return ch.ResetReq();
}
