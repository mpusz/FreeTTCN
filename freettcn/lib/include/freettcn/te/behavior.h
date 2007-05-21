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
 * @file   behavior.h
 * @author Mateusz Pusz
 * @date   Wed Apr 25 11:01:46 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

#include <freettcn/te/testComponent.h>
extern "C" {
#include <freettcn/ttcn3/tci.h>
}
#include <string>


namespace freettcn {

  namespace TE {
    
    class CModule;
    
    class CBehavior {
    public:
      enum {
        ERROR           = 0,
        END,
        WAIT,
        GUARD_TIMEOUT,
        OFFSET_AUTO,
        OFFSET_START    = 10
      };
      
    private:
      CModule &_module;
      TciBehaviourIdType _id;
    public:
      CBehavior(CModule &module, const char *name);
      virtual ~CBehavior();
      
      const TciBehaviourIdType &Id() const;
      
      virtual int Run(freettcn::TE::CTestComponentType::CInstanceLocal &comp, unsigned int offset) const = 0;
    };

  } // namespace TE
  
} // namespace freettcn


#endif /* __BEHAVIOR_H__ */
