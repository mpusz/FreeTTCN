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
 * @file   cd.h
 * @author Mateusz Pusz
 * @date   Wed May 30 08:03:44 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __CD_H__
#define __CD_H__

extern "C" {
// #include <freettcn/ttcn3/tri.h>
#include <freettcn/ttcn3/tci.h>
}
#include <freettcn/tools/logMask.h>
#include <freettcn/tools/entity.h>
#include <list>


namespace freettcn {
  
  namespace CD {
    
    class CLogMask : public freettcn::CLogMask {
    public:
      CLogMask(bool enabled = true);
      ~CLogMask();
    };
    

    class CCodec;
    
    class CCodingDecoding : public freettcn::CEntity {
      static CCodingDecoding *_instance;
      
      typedef std::list<const CCodec *> TCodecList;
      
      TCodecList _codecList;
      
      CCodingDecoding& operator=(CCodingDecoding&);  // Disallowed
      CCodingDecoding(const CCodingDecoding&);       // Disallowed
      
      virtual const CCodec &Codec(TciValue value, unsigned int &valueId) const throw(ENotFound);
      
    public:
      static CCodingDecoding &Instance() throw(ENotFound);
      
      CCodingDecoding();
      virtual ~CCodingDecoding();
      
      void Register(const CCodec *codec);
      
      TciValue Decode(const BinaryString &message, TciType decHypothesis) const;
      BinaryString Encode(TciValue value) const;
    };
    
  } // namespace CD
  
} // namespace freettcn


#endif /* __CD_H__ */
