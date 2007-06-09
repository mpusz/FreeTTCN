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
 * @file   port.cpp
 * @author Mateusz Pusz
 * @date   Wed May  2 17:46:49 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/te/port.h"
#include "freettcn/te/module.h"
extern "C" {
#include <freettcn/ttcn3/tci_te_ch.h>
#include <freettcn/ttcn3/tci_te_cd.h>
#include <freettcn/ttcn3/tri_te_sa.h>
}
#include <cmath>
#include <iostream>


freettcn::TE::CPortType::CPortType(const freettcn::TE::CModule &module, const char *name, TType type):
  _type(type), _inAll(false), _outAll(false)
{
  _id.moduleName = module.Id().moduleName;
  _id.objectName = const_cast<char *>(name);
  _id.aux = 0;
}

freettcn::TE::CPortType::~CPortType()
{
}

void freettcn::TE::CPortType::TypeAdd(const CType &type, TDirection dir) throw(EOperationFailed)
{
  if (dir == IN || dir == INOUT) {
    if (_inAll) {
      std::cout << "ERROR: Cannot add IN type for port because ALL flag is selected!!!" << std::endl;
      throw EOperationFailed();
    }
    _inList.push_back(&type);
  }
  if (dir == OUT || dir == INOUT) {
    if (_outAll) {
      std::cout << "ERROR: Cannot add OUT type for port because ALL flag is selected!!!" << std::endl;
      throw EOperationFailed();
    }
    _outList.push_back(&type);
  }
}


/// Usage of @b all is deprecated
void freettcn::TE::CPortType::TypeAddAll(TDirection dir) throw(EOperationFailed)
{
  if (dir == IN || dir == INOUT) {
    if (_inList.size()) {
      std::cout << "ERROR: Cannot set ALL flag for port because IN types are given!!!" << std::endl;
      throw EOperationFailed();
    }
    _inAll = true;
  }
  if (dir == OUT || dir == INOUT) {
    if (_outList.size()) {
      std::cout << "ERROR: Cannot set ALL flag for port because OUT types are given!!!" << std::endl;
      throw EOperationFailed();
    }
    _outAll = true;
  }
}

const QualifiedName &freettcn::TE::CPortType::Id() const
{
  return _id;
}





/* ******************************** P O R T   I N F O *********************************** */

freettcn::TE::CPortInfo::CPortInfo(const CPortType &type, const char *name, int portIdx):
  _type(type), _name(name), _portIdx(portIdx)
{
}

const freettcn::TE::CPortType &freettcn::TE::CPortInfo::Type() const
{
  return _type;
}

const char *freettcn::TE::CPortInfo::Name() const
{
  return _name;
}

int freettcn::TE::CPortInfo::PortIdx() const
{
  return _portIdx;
}




/* ************************************* P O R T **************************************** */

freettcn::TE::CPort::CPort(const CPortInfo &portInfo, const CTestComponentType::CInstanceLocal &component):
  _portInfo(portInfo), _component(component), _status(STARTED)
{
  _id.compInst = _component.Id();
  _id.portName = const_cast<char *>(_portInfo.Name());
  _id.portIndex = _portInfo.PortIdx();
  _id.portType = _portInfo.Type().Id();
  _id.aux = 0;
}


freettcn::TE::CPort::~CPort()
{
}


const TriPortId &freettcn::TE::CPort::Id() const
{
  return _id;
}


void freettcn::TE::CPort::Connect(TConnectionList &list, const TriPortId &remoteId) throw(EOperationFailed)
{
  for(TConnectionList::iterator it=list.begin(); it!=list.end(); ++it) {
    // check if remote port component is on the list already
    if ((*it)->compInst.compInst.bits == remoteId.compInst.compInst.bits &&
        !memcmp((*it)->compInst.compInst.data, remoteId.compInst.compInst.data,
                static_cast<int>(ceil((*it)->compInst.compInst.bits / 8.0)))) {
      std::cout << "ERROR: Cannot connect port with more than one port on the other component!!!" << std::endl;
      throw EOperationFailed();
    }
  }
  
  // add connection
  list.push_back(&remoteId);
}


void freettcn::TE::CPort::Disconnect(TConnectionList &list, const TriPortId &remoteId) throw(ENotFound)
{
  for(TConnectionList::iterator it=list.begin(); it!=list.end(); ++it) {
    if (*it == &remoteId) {
      list.erase(it);
      return;
    }
  }
  
  std::cout << "ERROR: Port not found!!!" << std::endl;
  throw ENotFound();
}


void freettcn::TE::CPort::Connect(const TriPortId &remoteId) throw(EOperationFailed)
{
  // check if it is not a SYSTEM component
  if (_component.Kind() == TCI_SYS_COMP) {
    std::cout << "ERROR: Cannot connect SYSTEM port (use 'map' instead)!!!" << std::endl;
    throw EOperationFailed();
  }
  
  // check if that port is not mapped
  if (_mapList.size()) {
    std::cout << "ERROR: Cannot connect a port that is mapped already!!!" << std::endl;
    throw EOperationFailed();
  }
  
  Connect(_connectList, remoteId);
}


void freettcn::TE::CPort::Disconnect(const TriPortId &remoteId) throw(ENotFound)
{
  Disconnect(_connectList, remoteId);
}


void freettcn::TE::CPort::Map(const TriPortId &remoteId) throw(EOperationFailed)
{
  // check if it is not a connection within SYSTEM component
  if (_component.Kind() == TCI_SYS_COMP &&
      _component.Id().compInst.bits == remoteId.compInst.compInst.bits &&
      !memcmp(_component.Id().compInst.data, remoteId.compInst.compInst.data,
              static_cast<int>(ceil(_component.Id().compInst.bits / 8.0)))) {
    std::cout << "ERROR: Cannot map 2 ports of SYSTEM component with each other!!!" << std::endl;
    throw EOperationFailed();
  }
  
  // check if that port is not connected
  if (_connectList.size()) {
    std::cout << "ERROR: Cannot map a port that is connected already!!!" << std::endl;
    throw EOperationFailed();
  }
  
  Connect(_mapList, remoteId);
}

void freettcn::TE::CPort::Unmap(const TriPortId &remoteId) throw(ENotFound)
{
  Disconnect(_mapList, remoteId);
}


void freettcn::TE::CPort::Send(const CType::CInstance &value) const throw(EOperationFailed)
{
  // check if value type is allowed
  
  // send message to connected components
  for(TConnectionList::const_iterator it=_connectList.begin(); it!=_connectList.end(); ++it) {
    tciSendConnected(Id(), (*it)->compInst, const_cast<void *>(static_cast<const void *>(&value)));
  }
  
  // send message to mapped components
  for(TConnectionList::const_iterator it=_mapList.begin(); it!=_mapList.end(); ++it) {
    const BinaryString str = tciEncode(const_cast<void *>(static_cast<const void *>(&value)));
    triSend(&_id.compInst, (*it), 0, &str);
  }
}
