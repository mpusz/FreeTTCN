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

  enum TTCNEntity {
    ENTITY_TE,
    ENTITY_TM,
    ENTITY_TL,
    ENTITY_CH,
    ENTITY_CD,
    ENTITY_SA,
    ENTITY_PA
  };
  
  enum LogTECommands {
    LOG_TE_TC_EXECUTE,
    LOG_TE_TC_START,
    LOG_TE_TC_STOP,
    
    LOG_TE_CTRL_START,
    LOG_TE_CTRL_STOP,
    
    LOG_TE_M_MISMATCH_M,                          /**< communication with the SUT */
    LOG_TE_M_MISMATCH_C,                          /**< intercomponent communication */
    LOG_TE_M_RECEIVE_M,                           /**< communication with the SUT */
    LOG_TE_M_RECEIVE_C,                           /**< intercomponent communication */
    
    LOG_TE_PR_GET_CALL_MISMATCH_M,                /**< communication with the SUT */
    LOG_TE_PR_GET_CALL_MISMATCH_C,                /**< intercomponent communication */
    LOG_TE_PR_GET_CALL_M,                         /**< communication with the SUT */
    LOG_TE_PR_GET_CALL_C,                         /**< intercomponent communication */
    LOG_TE_PR_GET_REPLY_MISMATCH_M,               /**< communication with the SUT */
    LOG_TE_PR_GET_REPLY_MISMATCH_C,               /**< intercomponent communication */
    LOG_TE_PR_GET_REPLY_M,                        /**< communication with the SUT */
    LOG_TE_PR_GET_REPLY_C,                        /**< intercomponent communication */
    LOG_TE_PR_GET_CATCH_MISMATCH_M,               /**< communication with the SUT */
    LOG_TE_PR_GET_CATCH_MISMATCH_C,               /**< intercomponent communication */
    LOG_TE_PR_GET_CATCH_TIMEOUT,
    
    LOG_TE_C_CREATE,
    LOG_TE_C_START,
    LOG_TE_C_RUNNING,
    LOG_TE_C_ALIVE,
    LOG_TE_C_STOP,
    LOG_TE_C_DONE_MISMATCH,
    LOG_TE_C_DONE,
    LOG_TE_C_KILLED_MISMATCH,
    LOG_TE_C_KILLED,
    LOG_TE_C_TERMINATED,
    
    LOG_TE_P_CLEAR,
    LOG_TE_P_STOP,
    LOG_TE_P_HALT,
    
    LOG_TE_T_TIMEOUT_MISMATCH,
    LOG_TE_T_TIMEOUT,
    
    LOG_TE_S_ENTER,
    LOG_TE_S_LEAVE,
    
    LOG_TE_VAR,
    
    LOG_TE_MODULE_PAR,
    
    LOG_TE_GET_VERDICT,
    LOG_TE_SET_VERDICT,
    
    LOG_TE_A_ENTER,
    LOG_TE_A_LEAVE,
    LOG_TE_A_NOMATCH,
    LOG_TE_A_REPEAT,
    LOG_TE_A_DEFAULTS,
    LOG_TE_A_ACTIVATE,
    LOG_TE_A_DEACTIVATE,
    LOG_TE_A_WAIT,
    
    LOG_TE_ACTION,
    
    LOG_TE_MATCH,
    LOG_TE_MATCH_MISMATCH,
    
    LOG_TE_INFO,
    
    LOG_TE_NUM                                    /**< should be the last one on the list */
  };
  
  enum LogTMCommands {
    LOG_TM_TC_STARTED,
    LOG_TM_TC_TERMINATED,
    
    LOG_TM_CTRL_TERMINATED,
    
    LOG_TM_LOG,
    
    LOG_TM_NUM                                    /**< should be the last one on the list */
  };
  
  enum LogCHCommands {
    LOG_CH_M_SEND_C,
    LOG_CH_M_SEND_C_BC,
    LOG_CH_M_SEND_C_MC,
    LOG_CH_M_DETECTED_C,
    
    LOG_CH_PR_CALL_C,
    LOG_CH_PR_CALL_C_BC,
    LOG_CH_PR_CALL_C_MC,
    LOG_CH_PR_GET_CALL_DETECTED_C,
    LOG_CH_PR_REPLY_C,
    LOG_CH_PR_REPLY_C_BC,
    LOG_CH_PR_REPLY_C_MC,
    LOG_CH_PR_GET_REPLY_DETECTED_C,
    LOG_CH_PR_RAISE_C,
    LOG_CH_PR_RAISE_C_BC,
    LOG_CH_PR_RAISE_C_MC,
    LOG_CH_PR_CATCH_DETECTED_C,
    LOG_CH_PR_CATCH_C,
    
    LOG_CH_P_CONNECT,
    LOG_CH_P_DISCONNECT,

    LOG_CH_NUM                                    /**< should be the last one on the list */
  };
  
  enum LogSACommands {
    LOG_SA_M_SEND_M,
    LOG_SA_M_SEND_M_BC,
    LOG_SA_M_SEND_M_MC,
    LOG_SA_M_DETECTED_M,
    
    LOG_SA_PR_CALL_M,
    LOG_SA_PR_CALL_M_BC,
    LOG_SA_PR_CALL_M_MC,
    LOG_SA_PR_GET_CALL_DETECTED_M,
    LOG_SA_PR_REPLY_M,
    LOG_SA_PR_REPLY_M_BC,
    LOG_SA_PR_REPLY_M_MC,
    LOG_SA_PR_GET_REPLY_DETECTED_M,
    LOG_SA_PR_RAISE_M,
    LOG_SA_PR_RAISE_M_BC,
    LOG_SA_PR_RAISE_M_MC,
    LOG_SA_PR_CATCH_DETECTED_M,
    LOG_SA_PR_CATCH_M,
    
    LOG_SA_P_MAP,
    LOG_SA_P_UNMAP,
    
    LOG_SA_NUM                                    /**< should be the last one on the list */
  };
  
  enum LogPACommands {
    LOG_PA_PR_CATCH_TIMEOUT_DETECTED,
    
    LOG_PA_T_TIMEOUT_DETECTED,
    LOG_PA_T_START,
    LOG_PA_T_STOP,
    LOG_PA_T_READ,
    LOG_PA_T_RUNNING,
    
    LOG_PA_NUM                                    /**< should be the last one on the list */
  };


  class CLogMask {
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
