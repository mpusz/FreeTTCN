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
 * @file   triTimerDuration.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TRI_TIMER_ID_H__
#define __TRI_TIMER_ID_H__

#include <freettcn/etsi/tri.h>
#include <freettcn/tools/nonAssignable.h>
#include <memory>


namespace freettcn {

  namespace ttcn3 {
    
    using namespace ORG_ETSI_TTCN3_TRI;

    class CTriTimerDuration : CNonAssignable, public ORG_ETSI_TTCN3_TRI::TriTimerDuration {
      Tfloat _duration;
    public:
      CTriTimerDuration(Tfloat duration): _duration(duration) {}
      CTriTimerDuration(const CTriTimerDuration &) = default;
      CTriTimerDuration(CTriTimerDuration &&) = default;
      ~CTriTimerDuration() = default;
#ifdef TTCN_LIST_IFACE_FIXED
      TriTimerDuration *clone() const override               { return new CTriTimerDuration(*this); }
#else
      TriTimerDuration *cloneTimerDuration() override const  { return new CTriTimerDuration(*this); }
#endif
      
      Tfloat getDuration() const override           { return _duration; }
      void setDuration(Tfloat duration) override    { _duration = duration; }
      
      Tboolean operator==(const TriTimerDuration &timd) const override  { return _duration == timd.getDuration(); }
      Tboolean operator<(const TriTimerDuration &timd) const override   { return _duration < timd.getDuration(); }
    };
        
  } // namespace ttcn3
  
} // namespace freettcn

#endif /* __TRI_TIMER_ID_H__ */
