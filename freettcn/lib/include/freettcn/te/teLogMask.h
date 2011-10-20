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
 * @file   teLogMask.h
 * @author Mateusz Pusz
 * @date   Mon May  7 13:58:29 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TELOGMASK_H__
#define __TELOGMASK_H__

#include <freettcn/tools/logMask.h>


namespace freettcn {

  namespace TE {
    
    class CLogMask : public freettcn::CLogMask {
    public:
      enum TTECommands {
        CMD_TE_TC_EXECUTE,
        CMD_TE_TC_START,
        CMD_TE_TC_STOP,
        
        CMD_TE_CTRL_START,
        CMD_TE_CTRL_STOP,
        
        CMD_TE_M_MISMATCH_M,                          /**< communication with the SUT */
        CMD_TE_M_MISMATCH_C,                          /**< intercomponent communication */
        CMD_TE_M_RECEIVE_M,                           /**< communication with the SUT */
        CMD_TE_M_RECEIVE_C,                           /**< intercomponent communication */
    
        CMD_TE_PR_GET_CALL_MISMATCH_M,                /**< communication with the SUT */
        CMD_TE_PR_GET_CALL_MISMATCH_C,                /**< intercomponent communication */
        CMD_TE_PR_GET_CALL_M,                         /**< communication with the SUT */
        CMD_TE_PR_GET_CALL_C,                         /**< intercomponent communication */
        CMD_TE_PR_GET_REPLY_MISMATCH_M,               /**< communication with the SUT */
        CMD_TE_PR_GET_REPLY_MISMATCH_C,               /**< intercomponent communication */
        CMD_TE_PR_GET_REPLY_M,                        /**< communication with the SUT */
        CMD_TE_PR_GET_REPLY_C,                        /**< intercomponent communication */
        CMD_TE_PR_GET_CATCH_MISMATCH_M,               /**< communication with the SUT */
        CMD_TE_PR_GET_CATCH_MISMATCH_C,               /**< intercomponent communication */
        CMD_TE_PR_GET_CATCH_TIMEOUT,
    
        CMD_TE_C_CREATE,
        CMD_TE_C_START,
        CMD_TE_C_RUNNING,
        CMD_TE_C_ALIVE,
        CMD_TE_C_STOP,
        CMD_TE_C_DONE_MISMATCH,
        CMD_TE_C_DONE,
        CMD_TE_C_KILLED_MISMATCH,
        CMD_TE_C_KILLED,
        CMD_TE_C_TERMINATED,
    
        CMD_TE_P_CLEAR,
        CMD_TE_P_STOP,
        CMD_TE_P_HALT,
    
        CMD_TE_T_TIMEOUT_MISMATCH,
        CMD_TE_T_TIMEOUT,
    
        CMD_TE_S_ENTER,
        CMD_TE_S_LEAVE,
    
        CMD_TE_VAR,
    
        CMD_TE_MODULE_PAR,
    
        CMD_TE_GET_VERDICT,
        CMD_TE_SET_VERDICT,
    
        CMD_TE_A_ENTER,
        CMD_TE_A_LEAVE,
        CMD_TE_A_NOMATCH,
        CMD_TE_A_REPEAT,
        CMD_TE_A_DEFAULTS,
        CMD_TE_A_ACTIVATE,
        CMD_TE_A_DEACTIVATE,
        CMD_TE_A_WAIT,
    
        CMD_TE_ACTION,
    
        CMD_TE_MATCH,
        CMD_TE_MATCH_MISMATCH,
    
        CMD_TE_INFO,
    
        CMD_TE_NUM                                    /**< should be the last one on the list */
      };
  
      explicit CLogMask(bool enabled = true);
      ~CLogMask() = default;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TELOGMASK_H__ */
