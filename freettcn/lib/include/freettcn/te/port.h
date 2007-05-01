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
 * @file   port.h
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:00:26 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __PORT_H__
#define __PORT_H__

extern "C" {
// #include "freettcn/tci.h"
// #include "freettcn/tri.h"
}
// #include "tools.h"
// #include "ttcn_values.h"
// #include <string>
// #include <vector>


namespace freettcn {
  
  namespace TE {
    
    class CPort {
      class CState {
        // STATUS
        //  - STARTED
        //  - STOPPED
        // CONNECTIONS_LIST - keeps track of connections between the different ports in the test system
        // VALUE_QUEUE - not yet consumed messages, calls, replies and exceptions
        // SNAP_VALUE - when a snapshot is taken the first element from VALUE_QUEUE is copied (NULL if VALUE_QUEUE is empty or STATUS = STOPPED)
      };
    public:
      void Send();
    };
    
  } // namespace TE
  
} // namespace freettcn



//   class Parameter {
//     enum TPassingMode {
//       IN = 0,
//       INOUT = 1,
//       OUT = 2
//     };
//     PassingMode mode;
//     BinaryString par;
//   public:
//     PassingMode PassingMode() const { return mode; }
//     const BinaryString &Par() const { return par; }
//   };
  
//   class Timer {
//   protected:
//     BinaryString Id() const;
//   public:
//     virtual void Start(double duration) throw(EOperationFailed) = 0;
//     virtual void Stop() throw(EOperationFailed) = 0;
//     virtual double Read() const throw(EOperationFailed) = 0;
//     virtual bool Running() const throw(EOperationFailed) = 0;
//     virtual void TimeOut() const = 0;
//   };
  
//   class PA {
//   public:
//     virtual void Reset() throw(EOperationFailed) = 0;
//   };
  
  
  
//   class Port {
//   public:
//     enum TMode {
//       FREE,
//       MAPPED,
//       CONNECTED
//     };
//   private:
//     const TriComponentId* componentId;
//     const TriPortId* compPortId;
//     const TriPortId* tsiPortId;
//     Mode mode;
//   public:
//     // Connection handling
//     virtual void Map(const TriPortId* tsiPortId) throw(EOperationFailed) = 0;
//     virtual void Unmap(const TriPortId* tsiPortId) throw(EOperationFailed) = 0;
    
//     // Message based communication
//     virtual void MsgSend(const TriAddress* sutAddress,
//                          const TriMessage* sendMessage) throw(EOperationFailed) = 0;
//     virtual void MsgSendBC(const TriMessage* sendMessage) throw(EOperationFailed) = 0;
//     virtual void MsgSendMC(const TriAddressList* sutAddresses,
//                            const TriMessage* sendMessage) throw(EOperationFailed) = 0;
//     virtual void MsgEnqueue(const TriAddress* sutAddress,
//                             const TriMessage* receivedMessage) = 0;
    
//     // Procedure based communication
//     virtual void ProcCall(const TriAddress* sutAddress,
//                           const TriSignatureId* signatureId,
//                           const TriParameterList* parameterList) throw(EOperationFailed) = 0;
//     virtual void ProcCallBC(const TriSignatureId* signatureId,
//                             const TriParameterList* parameterList) throw(EOperationFailed) = 0;
//     virtual void ProcCallMC(const TriAddressList* sutAddresses,
//                             const TriSignatureId* signatureId,
//                             const TriParameterList* parameterList) throw(EOperationFailed) = 0;
//     virtual void ProcCallEnqueue(const TriAddress* sutAddress,
//                                  const TriSignatureId* signatureId,
//                                  const TriParameterList* parameterList) = 0;
//     virtual const TriParameter* ProcReply(const TriAddress* sutAddress,
//                                           const TriSignatureId* signatureId,
//                                           const TriParameterList* parameterList) throw(EOperationFailed) = 0;
//     virtual const TriParameter* ProcReplyBC(const TriSignatureId* signatureId,
//                                             const TriParameterList* parameterList) throw(EOperationFailed) = 0;
//     virtual const TriParameter* ProcReplyMC(const TriAddressList* sutAddresses,
//                                             const TriSignatureId* signatureId,
//                                             const TriParameterList* parameterList) throw(EOperationFailed) = 0;
//     virtual void ProcReplyEnqueue(const TriAddress* sutAddress,
//                                   const TriSignatureId* signatureId,
//                                   const TriParameterList* parameterList,
//                                   const TriParameter* returnValue) = 0;
//     virtual void ProcRaise(const TriAddress* sutAddress,
//                            const TriSignatureId* signatureId,
//                            const TriException* exception) throw(EOperationFailed) = 0;
//     virtual void ProcRaiseBC(const TriSignatureId* signatureId,
//                              const TriException* exception) throw(EOperationFailed) = 0;
//     virtual void ProcRaiseMC(const TriAddressList* sutAddresses,
//                              const TriSignatureId* signatureId,
//                              const TriException* exception) throw(EOperationFailed) = 0;
//     virtual void ProcExceptionEnqueue(const TriAddress* sutAddress,
//                                       const TriSignatureId* signatureId,
//                                       const TriException* exception) = 0;
//   };


#endif /* __PORT_H__ */
