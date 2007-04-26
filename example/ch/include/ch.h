//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) usage example.

// This example is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This example is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this example; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   ch.h
 * @author Mateusz Pusz
 * @date   Tue Apr 10 19:43:39 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __CH_H__
#define __CH_H__

extern "C" {
#include "freettcn/tri.h"
#include "freettcn/tci.h"
}
#include "tools.h"

namespace freettcn {
  
  namespace CH {

    class CLogMask : public freettcn::CLogMask {
    public:
      CLogMask(bool enabled = true);
      ~CLogMask();
    };
    
    
    class CComponentHandler : public freettcn::CEntity {
      static CComponentHandler *_instance;
      
    protected:
      virtual TriComponentId TestComponentCreate(TciTestComponentKindType kind, TciType componentType, String name);
      virtual void TestComponentStart(const TriComponentId &component, const TciBehaviourIdType &behavior, const TciParameterListType &parameterList);
      virtual void TestComponentTerminated(const TriComponentId &component, TciVerdictValue verdict);

      virtual void TestCaseExecute(const TciTestCaseIdType &testCaseId, const TriPortIdList &tsiPortList);

      virtual void Connect(const TriPortId &fromPort, const TriPortId &toPort);
      virtual void Disconnect(const TriPortId &fromPort, const TriPortId &toPort);
      virtual void Map(const TriPortId &fromPort, const TriPortId &toPort);
      virtual void Unmap(const TriPortId &fromPort, const TriPortId &toPort);
    public:
      static CComponentHandler &Instance() throw(ENotFound);
      
      CComponentHandler();
      virtual ~CComponentHandler();
      
      void ResetReq();
      
      TriComponentId TestComponentCreateReq(TciTestComponentKindType kind, TciType componentType, String name);
      void TestComponentStartReq(const TriComponentId &component, const TciBehaviourIdType &behavior, const TciParameterListType &parameterList); 
      void TestComponentTerminatedReq(const TriComponentId &component, TciVerdictValue verdict);
      
      void TestCaseExecuteReq(const TciTestCaseIdType &testCaseId, const TriPortIdList &tsiPortList);

      void ConnectReq(const TriPortId &fromPort, const TriPortId &toPort);
      void DisconnectReq(const TriPortId &fromPort, const TriPortId &toPort);
      void MapReq(const TriPortId &fromPort, const TriPortId &toPort);
      void UnmapReq(const TriPortId &fromPort, const TriPortId &toPort);
    };
    
  } // namespace CH
  
} // namespace freettcn


#endif /* __CH_H__ */
