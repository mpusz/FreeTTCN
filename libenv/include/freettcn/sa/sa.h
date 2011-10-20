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
 * @file   sa.h
 * @author Mateusz Pusz
 * @date   Thu Mar 29 19:16:34 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __SA_H__
#define __SA_H__

extern "C" {
#include <freettcn/ttcn3/tri.h>
}
#include <freettcn/tools/logMask.h>
#include <freettcn/tools/entity.h>

namespace freettcn {
  
  namespace SA {
    
    class CLogMask : public freettcn::CLogMask {
    public:
      enum TSACommands {
        CMD_SA_M_SEND_M,
        CMD_SA_M_SEND_M_BC,
        CMD_SA_M_SEND_M_MC,
        CMD_SA_M_DETECTED_M,
    
        CMD_SA_PR_CALL_M,
        CMD_SA_PR_CALL_M_BC,
        CMD_SA_PR_CALL_M_MC,
        CMD_SA_PR_GET_CALL_DETECTED_M,
        CMD_SA_PR_REPLY_M,
        CMD_SA_PR_REPLY_M_BC,
        CMD_SA_PR_REPLY_M_MC,
        CMD_SA_PR_GET_REPLY_DETECTED_M,
        CMD_SA_PR_RAISE_M,
        CMD_SA_PR_RAISE_M_BC,
        CMD_SA_PR_RAISE_M_MC,
        CMD_SA_PR_CATCH_DETECTED_M,
        CMD_SA_PR_CATCH_M,
    
        CMD_SA_P_MAP,
        CMD_SA_P_UNMAP,
    
        CMD_SA_NUM                                    /**< should be the last one on the list */
      };

      explicit CLogMask(bool enabled = true);
      ~CLogMask();
    };


    class CSUTAdaptor : public freettcn::CEntity {
      static CSUTAdaptor *_instance;

    public:
      static CSUTAdaptor &Instance();
      
      CSUTAdaptor();
      virtual ~CSUTAdaptor();
      
      TriStatus Reset();
      
      TriStatus TestCaseExecute(const TriTestCaseId &testCaseId, const TriPortIdList &tsiPortList);

      TriStatus Map(const TriPortId &compPortId, const TriPortId &tsiPortId);
      TriStatus Unmap(const TriPortId &compPortId, const TriPortId &tsiPortId);
      
      TriStatus Send(const TriComponentId &componentId, const TriPortId &tsiPortId, const TriAddress *sutAddress, const TriMessage &sendMessage);
    };
    
  } // namespace SA
  
} // namespace freettcn


// void MessageReceived();

#endif /* __SA_H__ */

