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
 * @file   ttcnArray.h
 * @author Mateusz Pusz
 * @date   Tue Apr 24 21:05:33 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TTCN_ARRAY_H__
#define __TTCN_ARRAY_H__

#include <freettcn/etsi/tci.h>
#include <freettcn/tools/nonAssignable.h>
#include <vector>
#include <memory>
#include <algorithm>

namespace freettcn {
  
  namespace ttcn3 {
    
    using namespace ORG_ETSI_TTCN3_TCI;
    
    template<class LIST, class ITEM>
    class CTTCNArray : CNonAssignable, public LIST {
      typedef std::vector<std::shared_ptr<const ITEM> > CArray;
      CArray _array;
    public:
      CTTCNArray() = default;
      CTTCNArray(const CTTCNArray &src) = default;
      CTTCNArray(CTTCNArray &&) = default;
      ~CTTCNArray() = default;
      LIST *clone() const override                  { return new CTTCNArray(*this); }
      
      Tsize size() const override                   { return _array.size(); }
      Tboolean empty() const override               { return _array.empty(); }
      const ITEM *get(Tsize p_index) const override { return _array.at(p_index).get(); }
      void clear() override                         { _array.clear(); }
      /// @todo spec defines 2 different functions for lists :-(
      void push_back(const ITEM &item)              { _array.push_back(std::shared_ptr<const ITEM>(item.clone())); }
      void add(const ITEM &item)                    { push_back(item); }

      Tboolean operator==(const LIST &list) const override;
      Tboolean operator<(const LIST &list) const override;
    };
    
    typedef CTTCNArray<ORG_ETSI_TTCN3_TCI::TciValueList, ORG_ETSI_TTCN3_TCI::TciValue> CValueArray;
    
  } // namespace ttcn3
  
} // namespace freettcn


template<class LIST, class ITEM>
Tboolean freettcn::ttcn3::CTTCNArray<LIST, ITEM>::operator==(const LIST &list) const
{
  int idx = 0;
  return _array.size() == list.size() &&
    std::all_of(_array.begin(), _array.end(),
                [&list, &idx](const std::shared_ptr<const ITEM> &item) { return *item == *list.get(idx++); } );
}


template<class LIST, class ITEM>
Tboolean freettcn::ttcn3::CTTCNArray<LIST, ITEM>::operator<(const LIST &list) const
{
  Tsize refSize = list.size();
  if(_array.size() < refSize)
    return true;
  else if(_array.size() > refSize)
    return false;
  else {
    int idx = 0;
    return std::all_of(_array.begin(), _array.end(),
                       [&list, &idx](const std::shared_ptr<const ITEM> &item) { return *item < *list.get(idx++); } );
  }
}

#endif /* __TTCN_ARRAY_H__ */
