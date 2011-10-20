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
#include <freettcn/etsi/tri.h>
#include <freettcn/tools/nonAssignable.h>
#include <vector>
#include <memory>
#include <algorithm>

namespace freettcn {
  
#ifdef ISSUE_0005949
    
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
    const ITEM *get(Tindex index) const override  { return _array.at(index).get(); }
    void clear() override                         { _array.clear(); }
    void push_back(const ITEM &item) override     { _array.push_back(std::shared_ptr<const ITEM>(item.clone())); }

    Tboolean operator==(const LIST &list) const override;
    Tboolean operator<(const LIST &list) const override;
  };
    

  template<class LIST, class ITEM>
  Tboolean CTTCNArray<LIST, ITEM>::operator==(const LIST &list) const
  {
    int idx = 0;
    return _array.size() == list.size() &&
      std::all_of(_array.begin(), _array.end(),
                  [&list, &idx](const std::shared_ptr<const ITEM> &item) { return *item == *list.get(idx++); } );
  }
    
    
  template<class LIST, class ITEM>
  Tboolean CTTCNArray<LIST, ITEM>::operator<(const LIST &list) const
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


  typedef CTTCNArray<ORG_ETSI_TTCN3_TCI::TciModuleIdList,        ORG_ETSI_TTCN3_TCI::TciModuleId>        CTciModuleIdArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TCI::TciModuleParameterList, ORG_ETSI_TTCN3_TCI::TciModuleParameter> CTciModuleParameterArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TCI::TciParameterList,       ORG_ETSI_TTCN3_TCI::TciParameter>       CTciParameterArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TCI::TciParameterTypeList,   ORG_ETSI_TTCN3_TCI::TciParameterType>   CTciParameterTypeArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TCI::TciTestCaseIdList,      ORG_ETSI_TTCN3_TCI::TciTestCaseId>      CTciTestCaseIdArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TCI::TciValueDifferenceList, ORG_ETSI_TTCN3_TCI::TciValueDifference> CTciValueDifferenceArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TCI::TciValueList,           ORG_ETSI_TTCN3_TCI::TciValue>           CTciValueArray;

  typedef CTTCNArray<ORG_ETSI_TTCN3_TRI::TriComponentIdList,     ORG_ETSI_TTCN3_TRI::TriComponentId>     CTriComponentIdArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TRI::TriPortIdList,          ORG_ETSI_TTCN3_TRI::TriPortId>          CTriPortIdArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TRI::TriAddressList,         ORG_ETSI_TTCN3_TRI::TriAddress>         CTriAddressArray;
  typedef CTTCNArray<ORG_ETSI_TTCN3_TRI::TriParameterList,       ORG_ETSI_TTCN3_TRI::TriParameter>       CTriParameterArray;
    
#else // ISSUE_0005949
    
  template<class LIST, class ITEM>
  class CTTCNArray : CNonAssignable, public LIST {
  protected:
    /// @todo needed for child classes
    typedef std::vector<std::shared_ptr<const ITEM> > CArray;
  private:
    CArray _array;
  protected:
    /// @todo protected members needed to provide interface for child classes that has to
    /// exist because of TCI and TRI inconsistency
    CArray &Array()             { return _array; }
    const CArray &Array() const { return _array; }
  public:
    CTTCNArray() = default;
    CTTCNArray(const CTTCNArray &src) = default;
    CTTCNArray(CTTCNArray &&) = default;
    ~CTTCNArray() = default;
      
    Tsize size() const override                   { return _array.size(); }
      
    /// @todo TTCN spec is not consistent in naming of is empty method so we need
    // to provide both of them and not use override keyword because always one of
    // them will break the compilation
    Tboolean empty() const                        { return _array.empty(); }
    Tboolean isEmpty() const                      { return empty(); }
      
    void clear() override                         { _array.clear(); }
  };
    

  template<class LIST, class ITEM>
  class CTciArray : public CTTCNArray<LIST, ITEM> {
  public:
    /// @todo get cannot be put in the base class because TCI and TRI specs
    /// have conflicting signatures for that method
    LIST *clone() const override                  { return new CTciArray(*this); }
      
    /// @todo get cannot be put in the base class because TCI and TRI specs
    /// have conflicting signatures for that method. Moreover TCI interface
    /// is not consistent in terms af method argument type (3 different
    /// declarations) so 2 methods are needed ond override keyword cannot be used
    const ITEM *get(Tsize index) const            { return this->Array().at(index).get(); }
    const ITEM *get(Tinteger index) const         { return this->Array().at(index).get(); }

    /// needed to put here as get() method returns different values for TRI and TCI
    Tboolean operator==(const LIST &list) const override;
    Tboolean operator<(const LIST &list) const override;
      
    /// @todo TTCN spec is not consistent in naming of add new item method so we need
    // to provide both of them and not use override keyword because always one of
    // them will break the compilation
    // Morover they cannot be used in TRI as there is no one clone() named method
    void push_back(const ITEM &item)              { this->Array().push_back(std::shared_ptr<const ITEM>(item.clone())); }
    void add(const ITEM &item)                    { push_back(item); }
  };
    
    
  template<class LIST, class ITEM>
  Tboolean CTciArray<LIST, ITEM>::operator==(const LIST &list) const
  {
    int idx = 0;
    return this->Array().size() == list.size() &&
      std::all_of(this->Array().begin(), this->Array().end(),
                  [&list, &idx](const std::shared_ptr<const ITEM> &item) { return *item == *list.get(idx++); } );
  }
    
    
  template<class LIST, class ITEM>
  Tboolean CTciArray<LIST, ITEM>::operator<(const LIST &list) const
  {
    Tsize refSize = list.size();
    if(this->Array().size() < refSize)
      return true;
    else if(this->Array().size() > refSize)
      return false;
    else {
      int idx = 0;
      return std::all_of(this->Array().begin(), this->Array().end(),
                         [&list, &idx](const std::shared_ptr<const ITEM> &item) { return *item < *list.get(idx++); } );
    }
  }


  typedef CTciArray<ORG_ETSI_TTCN3_TCI::TciModuleIdList,        ORG_ETSI_TTCN3_TCI::TciModuleId>        CTciModuleIdArray;
  typedef CTciArray<ORG_ETSI_TTCN3_TCI::TciModuleParameterList, ORG_ETSI_TTCN3_TCI::TciModuleParameter> CTciModuleParameterArray;
  typedef CTciArray<ORG_ETSI_TTCN3_TCI::TciParameterList,       ORG_ETSI_TTCN3_TCI::TciParameter>       CTciParameterArray;
  typedef CTciArray<ORG_ETSI_TTCN3_TCI::TciParameterTypeList,   ORG_ETSI_TTCN3_TCI::TciParameterType>   CTciParameterTypeArray;
  typedef CTciArray<ORG_ETSI_TTCN3_TCI::TciTestCaseIdList,      ORG_ETSI_TTCN3_TCI::TciTestCaseId>      CTciTestCaseIdArray;
  typedef CTciArray<ORG_ETSI_TTCN3_TCI::TciValueDifferenceList, ORG_ETSI_TTCN3_TCI::TciValueDifference> CTciValueDifferenceArray;
  typedef CTciArray<ORG_ETSI_TTCN3_TCI::TciValueList,           ORG_ETSI_TTCN3_TCI::TciValue>           CTciValueArray;
    
    
  template<class LIST, class ITEM>
  class CTriArray : public CTTCNArray<LIST, ITEM> {
  protected:
    typedef ITEM CItemType;
  public:
    /// @todo get cannot be put in the base class because TCI and TRI specs
    /// have conflicting signatures for that method
    const ITEM &get(Tsize index) const override   { return *this->Array().at(index); }

    /// needed to put here as get() method returns different values for TRI and TCI
    Tboolean operator==(const LIST &list) const override;
    Tboolean operator<(const LIST &list) const override;
  };
    
    
  template<class LIST, class ITEM>
  Tboolean CTriArray<LIST, ITEM>::operator==(const LIST &list) const
  {
    int idx = 0;
    return this->Array().size() == list.size() &&
      std::all_of(this->Array().begin(), this->Array().end(),
                  [&list, &idx](const std::shared_ptr<const ITEM> &item) { return *item == list.get(idx++); } );
  }
    
    
  template<class LIST, class ITEM>
  Tboolean CTriArray<LIST, ITEM>::operator<(const LIST &list) const
  {
    Tsize refSize = list.size();
    if(this->Array().size() < refSize)
      return true;
    else if(this->Array().size() > refSize)
      return false;
    else {
      int idx = 0;
      return std::all_of(this->Array().begin(), this->Array().end(),
                         [&list, &idx](const std::shared_ptr<const ITEM> &item) { return *item < list.get(idx++); } );
    }
  }
    
    
  /// @todo below classes needed to provide class specific clone method which is
  /// again not consistent with TCI interfaces
  class CTriComponentIdArray : public CTriArray<ORG_ETSI_TTCN3_TRI::TriComponentIdList, ORG_ETSI_TTCN3_TRI::TriComponentId> {
  public:
    TriComponentIdList *cloneComponentIdList() const override { return new CTriComponentIdArray(*this); }
    void add(const CItemType &item) override                  { this->Array().push_back(std::shared_ptr<const CItemType>(item.cloneComponentId())); }
  };
    
    
  class CTriPortIdArray : public CTriArray<ORG_ETSI_TTCN3_TRI::TriPortIdList, ORG_ETSI_TTCN3_TRI::TriPortId> {
  public:
    TriPortIdList *clonePortIdList() const override { return new CTriPortIdArray(*this); }
    void add(const CItemType &item) override        { this->Array().push_back(std::shared_ptr<const CItemType>(item.clonePortId())); }
  };
    
    
  class CTriAddressArray : public CTriArray<ORG_ETSI_TTCN3_TRI::TriAddressList, ORG_ETSI_TTCN3_TRI::TriAddress> {
  public:
    TriAddressList *cloneAddressList() const override { return new CTriAddressArray(*this); }
    void add(const CItemType &item) override          { this->Array().push_back(std::shared_ptr<const CItemType>(item.cloneAddress())); }
  };


  class CTriParameterArray : public CTriArray<ORG_ETSI_TTCN3_TRI::TriParameterList, ORG_ETSI_TTCN3_TRI::TriParameter> {
  public:
    TriParameterList *cloneParameterList() const override { return new CTriParameterArray(*this); }
    void add(const CItemType &item) override              { this->Array().push_back(std::shared_ptr<const CItemType>(item.cloneParameter())); }
  };
    
#endif // ISSUE_0005949

} // namespace freettcn


#endif /* __TTCN_ARRAY_H__ */
