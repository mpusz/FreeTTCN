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
 * @file   logMask.h
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:35:01 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __LOGMASK_H__
#define __LOGMASK_H__

#include <vector>

namespace freettcn {

  class CLogMask {
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
  
    enum TTMCommands {
      CMD_TM_TC_STARTED,
      CMD_TM_TC_TERMINATED,
    
      CMD_TM_CTRL_TERMINATED,
    
      CMD_TM_LOG,
    
      CMD_TM_NUM                                    /**< should be the last one on the list */
    };
  
    enum TCHCommands {
      CMD_CH_M_SEND_C,
      CMD_CH_M_SEND_C_BC,
      CMD_CH_M_SEND_C_MC,
      CMD_CH_M_DETECTED_C,
    
      CMD_CH_PR_CALL_C,
      CMD_CH_PR_CALL_C_BC,
      CMD_CH_PR_CALL_C_MC,
      CMD_CH_PR_GET_CALL_DETECTED_C,
      CMD_CH_PR_REPLY_C,
      CMD_CH_PR_REPLY_C_BC,
      CMD_CH_PR_REPLY_C_MC,
      CMD_CH_PR_GET_REPLY_DETECTED_C,
      CMD_CH_PR_RAISE_C,
      CMD_CH_PR_RAISE_C_BC,
      CMD_CH_PR_RAISE_C_MC,
      CMD_CH_PR_CATCH_DETECTED_C,
      CMD_CH_PR_CATCH_C,
    
      CMD_CH_P_CONNECT,
      CMD_CH_P_DISCONNECT,

      CMD_CH_NUM                                    /**< should be the last one on the list */
    };
    
    enum TCDCommands {
      CMD_CD_ENCODE,
      CMD_CD_DECODE,
      
      CMD_CD_NUM                                    /**< should be the last one on the list */
    };
    
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
  
    enum TPACommands {
      CMD_PA_PR_CATCH_TIMEOUT_DETECTED,
    
      CMD_PA_T_TIMEOUT_DETECTED,
      CMD_PA_T_START,
      CMD_PA_T_STOP,
      CMD_PA_T_READ,
      CMD_PA_T_RUNNING,
    
      CMD_PA_NUM                                    /**< should be the last one on the list */
    };

  private:
    unsigned short _num;
    std::vector<bool> _array;
  public:
    CLogMask(unsigned short num, bool enabled = true);
    virtual ~CLogMask() = 0;
    
    void Set(bool enabled);
    void Set(unsigned short idx, bool enabled);
    bool Get(unsigned short idx);
  };

} // namespace freettcn


#endif /* __LOGMASK_H__ */
