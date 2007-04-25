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


#endif /* __PORT_H__ */
