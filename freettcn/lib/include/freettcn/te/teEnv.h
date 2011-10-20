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
 * @file   teEnv.h
 * @author Mateusz Pusz
 * @date   Sat Apr  7 22:10:55 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __TE_ENV_H__
#define __TE_ENV_H__

#include <freettcn/tools/nonCopyable.h>

namespace ORG_ETSI_TTCN3_TCI {
  class TciCdProvided;
  class TciChProvided;
  class TciTlProvided;
  class TciTmProvided;
}

namespace ORG_ETSI_TTCN3_TRI {
  class TriCommunicationSA;
  class TriPlatformPA;
}

namespace freettcn {
  
  namespace TE {
    
    using namespace ORG_ETSI_TTCN3_TCI;
    using namespace ORG_ETSI_TTCN3_TRI;
    
    class CEnvironment : CNonCopyable {
      TciTmProvided &_tm;
      TciChProvided &_ch;
      TciCdProvided &_cd;
      TriCommunicationSA &_sa;
      TriPlatformPA &_pa;
      TciTlProvided &_tl;
    public:
      CEnvironment(TciTmProvided &tm, TciChProvided &ch, TciCdProvided &cd, 
                   TriCommunicationSA &sa, TriPlatformPA &pa, TciTlProvided &tl):
        _tm(tm), _ch(ch), _cd(cd), _sa(sa), _pa(pa), _tl(tl) {}
      TciTmProvided &TM() const      { return _tm; }
      TciChProvided &CH() const      { return _ch; }
      TciCdProvided &CD() const      { return _cd; }
      TriCommunicationSA &SA() const { return _sa; }
      TriPlatformPA &PA() const      { return _pa; }
      TciTlProvided &TL() const      { return _tl; }
    };
    
  } // namespace TE
  
} // namespace freettcn


#endif /* __TE_ENV_H__ */
