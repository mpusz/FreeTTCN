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
#include "freettcn/te/te.h"
#include "freettcn/te/module.h"
#include "freettcn/te/port.h"
#include "freettcn/te/timer.h"
#include "freettcn/te/command.h"
#include "freettcn/te/sourceData.h"
#include "freettcn/tools/logMask.h"
#include "freettcn/tools/timeStamp.h"
#include "freettcn/tools/tools.h"
extern "C" {
#include "freettcn/ttcn3/tci_te_ch.h"
#include "freettcn/ttcn3/tci_tl.h"
}
#include <iostream>



freettcn::TE::CTestComponentType::CTestComponentType(const freettcn::TE::CModule *module, const char *name) :
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
  freettcn::TE::CType::CInstance(type, false), _module(0), _startTimer(0),
  _status(NOT_INITED), _verdict(VERDICT_NONE)
{
}


freettcn::TE::CTestComponentType::CInstance::~CInstance()
{
  if (_startTimer)
    delete _startTimer;
  
  _controlStack.Clear();
  
  if (_status != NOT_INITED)
    _module->TestComponentLocalRemove(*this);
}


freettcn::TE::CModule &freettcn::TE::CTestComponentType::CInstance::Module() const throw(ENotInited)
{
  if (_status == NOT_INITED)
    throw CTestComponentType::CInstance::ENotInited();
  
  return *_module;
}


freettcn::TE::CTestComponentType::CInstance::TStatus freettcn::TE::CTestComponentType::CInstance::Status() const
{
  return _status;
}

void freettcn::TE::CTestComponentType::CInstance::Status(TStatus status)
{
  _status = status;
}

void freettcn::TE::CTestComponentType::CInstance::Init(CModule &module, TciTestComponentKindType kind, const char *name)
{
  _module = &module;
  _kind = kind;
  
  _id.compInst = InstanceId();
  _id.compName = const_cast<char *>(name);
  _id.compType = Type().Id();
  
  /// @todo init var scope
  /// @todo init timer scope
  /// @todo init port scope
  
  _status = BLOCKED;
  
  // perform component specific initialization
  Initialize();
  
  _module->TestComponentLocalAdd(*this);
}


const TriComponentId &freettcn::TE::CTestComponentType::CInstance::Id() const throw(CTestComponentType::CInstance::ENotInited)
{
  if (_status == NOT_INITED)
    throw CTestComponentType::CInstance::ENotInited();
  return _id;
}


TciTestComponentKindType freettcn::TE::CTestComponentType::CInstance::Kind() const throw(CTestComponentType::CInstance::ENotInited)
{
  if (_status == NOT_INITED)
    throw CTestComponentType::CInstance::ENotInited();
  return _kind;
}


void freettcn::TE::CTestComponentType::CInstance::Start(const CBehavior &behavior, TciParameterListType parameterList) throw(CTestComponentType::CInstance::ENotInited)
{
  if (_status == NOT_INITED)
    throw CTestComponentType::CInstance::ENotInited();
  
  // schedule executing test component
  _startTimer = new freettcn::TE::CTimer(*this, true, new CTimer::CCmdComponentRun(behavior), 0);
  _startTimer->Start();
  _status = ACTIVE;
}


void freettcn::TE::CTestComponentType::CInstance::Run()
{
  if (_status == BLOCKED)
    // blocked components do not run commands
    return;
  
  // get top command from the stack
  while(CCommand *cmd = _controlStack.First())
    // run the command
    if (cmd->Run()) {
      // next command should be run - dequeue finished command
      _controlStack.Dequeue();
      
      if (_status == BLOCKED)
        // blocked components do not run commands
        return;
    }
    else
      // command did not finish
      return;
  
  // test component done
  if (_kind != TCI_ALIVE_COMP)
    delete this;
}


void freettcn::TE::CTestComponentType::CInstance::Done(const CSourceData &srcData)
{
  /// @todo Return verdict
  TciVerdictValue verdictVal = 0;
  
  freettcn::TE::CTTCNExecutable &te = freettcn::TE::CTTCNExecutable::Instance();
  if (te.Logging() && te.LogMask().Get(freettcn::CLogMask::CMD_TE_C_TERMINATED)) {
    // log
    tliCTerminated(0, te.TimeStamp().Get(), const_cast<char *>(srcData.Source()), srcData.Line(), Id(), verdictVal);
  }
  
  tciTestComponentTerminatedReq(Id(), verdictVal);
  
  // clear control stack
//   CCommand *cmd = _controlStack.First();
//   _controlStack
  /// @todo May be a problem with the last command
//   _controlStack.Clear();
}


void freettcn::TE::CTestComponentType::CInstance::TimerAdd(const CTimer &timer, bool implicit /* false */)
{
  TTimerList &list = implicit ? _implicitTimers : _explicitTimers;
  list.push_back(&timer);
}


void freettcn::TE::CTestComponentType::CInstance::TimerRemove(const CTimer &timer, bool implicit /* false */) throw(ENotFound)
{
  TTimerList &list = implicit ? _implicitTimers : _explicitTimers;
  
  for(TTimerList::iterator it=list.begin(); it!=list.end(); ++it) {
    if (*it == &timer) {
      list.erase(it);
      return;
    }
  }
  
  std::cout << "ERROR: Timer not found!!!" << std::endl;
  throw ENotFound();
}


// void freettcn::TE::CTestComponentType::CInstance::Map(const freettcn::TE::CPort &fromPort, const freettcn::TE::CPort &toPort) throw(freettcn::TE::CTestComponentType::CInstance::ENotInited)
// {
//   if (_status == NOT_INITED)
//     throwfreettcn::TE::CTestComponentType::CInstance::ENotInited();
// }


// void freettcn::TE::CTestComponentType::CInstance::Verdict(VerdictType_t value)
// {
//   if (_status == NOT_INITED)
//     throwfreettcn::TE::CTestComponentType::CInstance::ENotInited();
// }


void freettcn::TE::CTestComponentType::CInstance::Enqueue(CCommand *cmd)
{
  _controlStack.Enqueue(cmd);
}






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

