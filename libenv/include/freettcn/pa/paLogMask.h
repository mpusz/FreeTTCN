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
 * @file   paLogMask.h
 * @author Mateusz Pusz
 * @date   Mon May  7 13:57:52 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __PALOGMASK_H__
#define __PALOGMASK_H__

#include <freettcn/tools/logMask.h>

namespace freettcn {
  
  namespace PA {
    
    class CLogMask : public freettcn::CLogMask {
    public:
      enum TPACommands {
        CMD_PA_PR_CATCH_TIMEOUT_DETECTED,
    
        CMD_PA_T_TIMEOUT_DETECTED,
        CMD_PA_T_START,
        CMD_PA_T_STOP,
        CMD_PA_T_READ,
        CMD_PA_T_RUNNING,
    
        CMD_PA_NUM                                    /**< should be the last one on the list */
      };

      explicit CLogMask(bool enabled = true);
      ~CLogMask();
    };
    
  } // namespace PA
  
} // namespace freettcn


#endif /* __PALOGMASK_H__ */
