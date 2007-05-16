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
 * @file   verdict.h
 * @author Mateusz Pusz
 * @date   Sun May 13 19:34:48 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __VERDICT_H__
#define __VERDICT_H__

#include <freettcn/te/type.h>

namespace freettcn {

  namespace TE {
    
    enum TVerdict {
      VERDICT_NONE      = TCI_VERDICT_NONE,
      VERDICT_PASS      = TCI_VERDICT_PASS,
      VERDICT_INCONC    = TCI_VERDICT_INCONC,
      VERDICT_FAIL      = TCI_VERDICT_FAIL,
      VERDICT_ERROR     = TCI_VERDICT_ERROR
    };
    
    class CVerdictType : public CType {
    public:
      class CInstance : public CType::CInstance {
        TVerdict _value;
      public:
        CInstance(const CType &type);
        CInstance(const CType &type, TVerdict value);
        
        TVerdict Value() const throw(EOmitSet);
        void Value(TVerdict value);
      };
      
      CVerdictType();
      virtual CInstance *InstanceCreate() const;
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __VERDICT_H__ */
