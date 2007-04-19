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

/**
 * @file   tci_ch_te.cpp
 * @author Mateusz Pusz
 * @date   Mon Apr  9 22:25:54 2007
 * 
 * @brief  
 * 
 * 
 */

extern "C" {
#include "freettcn/tci_ch_te.h"
}
#include "te.h"
#include <iostream>


TriComponentId tciCreateTestComponent(TciTestComponentKindType kind,
                                      TciType componentType,
                                      String name)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  
  if (kind == TCI_CTRL_COMP && componentType) {
    std::cout << "ERROR: 'componentType' given for Control component!!!" << std::endl;

    // return dummy data
    TriComponentId ctrlId;
    ctrlId.compInst.data = 0;
    ctrlId.compInst.bits = 0;
    ctrlId.compInst.aux = 0;
    ctrlId.compName = 0;
    ctrlId.compType.moduleName = 0;
    ctrlId.compType.objectName = 0;
    ctrlId.compType.aux = 0;
    
    return ctrlId;
  }
  
  return te.TestComponentCreate(kind, componentType, name);
}


void tciStartTestComponent(TriComponentId component,
                           TciBehaviourIdType behavior,
                           TciParameterListType parameterList)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.TestComponentStart(component, behavior, parameterList);
}



void tciConnect(TriPortId fromPort,
                TriPortId toPort)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.Connect(fromPort, toPort);
}


void tciDisconnect(TriPortId fromPort,
                   TriPortId toPort)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.Disconnect(fromPort, toPort);
}


void tciMap(TriPortId fromPort,
            TriPortId toPort)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.Map(fromPort, toPort);
}


void tciUnmap(TriPortId fromPort,
              TriPortId toPort)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.Unmap(fromPort, toPort);
}


void tciTestComponentTerminated(TriComponentId component,
                                TciVerdictValue verdict)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.TestComponentTerminated(component, verdict);
}


void tciExecuteTestCase(TciTestCaseIdType testCaseId, TriPortIdList tsiPortList)
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();

  // get active module
  const freettcn::TE::CModule &module = te.RootModule();
  module.TestCase(testCaseId.objectName).Execute(testCaseId, tsiPortList);
}


void tciReset()
{
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  te.Reset();
}
