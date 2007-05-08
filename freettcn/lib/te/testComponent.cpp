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
 * @file   testComponent.cpp
 * @author Mateusz Pusz
 * @date   Wed Apr 25 13:38:56 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/testComponent.h"
#include "freettcn/te/module.h"
#include "freettcn/te/port.h"
#include "freettcn/te/timer.h"
#include "freettcn/tools/tools.h"




freettcn::TE::CTestComponentType::CTestComponentType(const freettcn::TE::CModule *module, String name) :
  freettcn::TE::CType(module, name, TCI_COMPONENT_TYPE, "", "", ""),
  __portIdList(0)
{
}


freettcn::TE::CTestComponentType::~CTestComponentType()
{
  Purge(_portIdList);
  
  if (__portIdList)
    delete[] __portIdList;
}


void freettcn::TE::CTestComponentType::Register(const CPortType &portType, const char *name, int portIdx /* -1 */)
{
  TriPortId *portId = new TriPortId;
  
  memset(&portId->compInst, 0, sizeof(TriComponentId));
  portId->portName = const_cast<char *>(name);
  portId->portIndex = portIdx;
  portId->portType = portType.Id();
  portId->aux = 0;
  
  _portIdList.push_back(portId);
}


TriPortIdList freettcn::TE::CTestComponentType::Ports() const
{
  TriPortIdList portList;
  portList.length = _portIdList.size();
  if (!__portIdList) {
    __portIdList = new TriPortId *[portList.length];
    
    unsigned int i=0;
    for(TPortIdList::const_iterator it=_portIdList.begin(); it!=_portIdList.end(); ++it, i++)
      __portIdList[i] = const_cast<TriPortId*>(*it);
  }
  portList.portIdList = __portIdList;
  
  return portList;
}




freettcn::TE::CTestComponentType::CInstance::CInstance(const CType &type):
  freettcn::TE::CType::CInstance(type, false), _inited(false), _module(0)
{
}


freettcn::TE::CTestComponentType::CInstance::~CInstance()
{
  Purge(_explicitTimers);
  Purge(_implicitTimers);
}


void freettcn::TE::CTestComponentType::CInstance::Init(freettcn::TE::CModule &module, TciTestComponentKindType kind, String name)
{
  _module = &module;
  _kind = kind;
  
  _id.compInst = InstanceId();
  _id.compName = name;
  _id.compType = Type().Id();
  
  // perform component specific initialization
  Initialize();
  
  // register in a module
  _module->TestComponentAdd(*this);
  
  _inited = true;
}


const TriComponentId &freettcn::TE::CTestComponentType::CInstance::Id() const throw(freettcn::TE::CTestComponentType::CInstance::ENotInited)
{
  return _id;
}


void freettcn::TE::CTestComponentType::CInstance::Start(const freettcn::TE::CBehavior &behavior, TciParameterListType parameterList) throw(freettcn::TE::CTestComponentType::CInstance::ENotInited)
{
  // schedule executing test component
  //   Timer().Start();
}


// void freettcn::TE::CTestComponentType::CInstance::Map(const freettcn::TE::CPort &fromPort, const freettcn::TE::CPort &toPort) throw(freettcn::TE::CTestComponentType::CInstance::ENotInited)
// {
// }


// void freettcn::TE::CTestComponentType::CInstance::Verdict(VerdictType_t value)
// {
// }






freettcn::TE::CControlComponentType::CControlComponentType():
  freettcn::TE::CTestComponentType(0 , "_ControlComponentType_")
{
}

freettcn::TE::CControlComponentType::CInstance *freettcn::TE::CControlComponentType::InstanceCreate(bool omit /* false */) const
{
  return new freettcn::TE::CControlComponentType::CInstance(*this);
}



freettcn::TE::CControlComponentType::CInstance::CInstance(const freettcn::TE::CType &type):
  freettcn::TE::CTestComponentType::CInstance(type)
{
}

void freettcn::TE::CControlComponentType::CInstance::Initialize()
{
}

