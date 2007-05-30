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
 * @file   cd.cpp
 * @author Mateusz Pusz
 * @date   Wed May 30 08:43:35 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/cd/cd.h"
#include "freettcn/cd/internalCodec.h"
#include "freettcn/tools/tools.h"
extern "C" {
// #include <freettcn/ttcn3/tci_cd_te.h>
#include <freettcn/ttcn3/tci_tl.h>
}
#include <freettcn/tools/timeStamp.h>

#include <iostream>



freettcn::CD::CLogMask::CLogMask(bool enabled /* true */):
  freettcn::CLogMask(CMD_CD_NUM, enabled)
{
}

freettcn::CD::CLogMask::~CLogMask()
{
}


freettcn::CD::CCodingDecoding *freettcn::CD::CCodingDecoding::_instance = 0;

freettcn::CD::CCodingDecoding &freettcn::CD::CCodingDecoding::Instance() throw(ENotFound)
{
  if (_instance)
    return *_instance;
  
  throw ENotFound();
}

freettcn::CD::CCodingDecoding::CCodingDecoding()
{
  _instance = this;
  
  Register(new CInternalCodec);
}

freettcn::CD::CCodingDecoding::~CCodingDecoding()
{
  //  Clear();
  _instance = 0;
  
  Purge(_codecList);
}


void freettcn::CD::CCodingDecoding::Register(const CCodec *codec)
{
  _codecList.push_back(codec);
}


const freettcn::CD::CCodec &freettcn::CD::CCodingDecoding::Codec(TciValue value, unsigned int &valueId) const throw(ENotFound)
{
  for(TCodecList::const_iterator it=_codecList.begin(); it!=_codecList.end(); ++it)
    if ((*it)->CapabilityCheck(value, valueId))
      return *(*it);
  
  std::cout << "ERROR: Codec not found for given value!!!" << std::endl;
  throw ENotFound();
}



TciValue freettcn::CD::CCodingDecoding::Decode(const BinaryString &message, TciType decHypothesis) const
{
//   if (tciGetTypeClass(decHypothesis) == TCI_ANYTYPE_TYPE) {
// //   tliDecode(String am,
// //             int ts,
// //             String src,
// //             int line,
// //             TriComponentId c,
// //             TriMessage msg,
// //             TriStatus decoderFailure,
// //             TciValue val,
// //             String codec);
    
//     return tciNewInstance(decHypothesis);
//   }
  
//   try {
//     freettcn::CD::CHexBuffer buffer(message);
    
//     // check against decHypothesis
//     if (!strcmp(tciGetName(decHypothesis), "ICMPType")) {
// //       IP::CICMPType icmpMsg(tciNewInstance(decHypothesis));
// //       icmpMsg.Decode(buffer);
// //       return icmpMsg.Value();
      
//       TciValue icmpMsg = tciNewInstance(decHypothesis);
//       char str[10];

// //       TciValue msgType = tciGetRecFieldValue(icmpMsg, "msgType");
// //       if (!msgType)
// //         throw freettcn::CD::EDecodeFailure();
// //       tciSetIntSign(msgType, 1);
// //       sprintf(str, "%lu", buffer.UIntGet(8));
// //       tciSetIntAbs(msgType, str);
      
// //       TciValue code = tciGetRecFieldValue(icmpMsg, "code");
// //       if (!code)
// //         throw freettcn::CD::EDecodeFailure();
// //       tciSetIntSign(code, 1);
// //       sprintf(str, "%lu", buffer.UIntGet(8));
// //       tciSetIntAbs(msgType, str);
      
// //       TciValue crc = tciGetRecFieldValue(icmpMsg, "crc");
// //       if (!crc)
// //         throw freettcn::CD::EDecodeFailure();
// //       tciSetIntSign(crc, 1);
// //       sprintf(str, "%lu", buffer.UIntGet(16));
// //       tciSetIntAbs(msgType, str);

//       return icmpMsg;
//     }
//     else {
//       // unknown type
// //   tliDecode(String am,
// //             int ts,
// //             String src,
// //             int line,
// //             TriComponentId c,
// //             TriMessage msg,
// //             TriStatus decoderFailure,
// //             TciValue val,
// //             String codec);
      
//       return 0;
//     }
//   }
//   catch(freettcn::CD::EDecodeFailure) {
// //   tliDecode(String am,
// //             int ts,
// //             String src,
// //             int line,
// //             TriComponentId c,
// //             TriMessage msg,
// //             TriStatus decoderFailure,
// //             TciValue val,
// //             String codec);
    
//     return 0;
//   }
//   catch(freettcn::EOperationFailed) {
// //   tliDecode(String am,
// //             int ts,
// //             String src,
// //             int line,
// //             TriComponentId c,
// //             TriMessage msg,
// //             TriStatus decoderFailure,
// //             TciValue val,
// //             String codec);
    
//     return 0;
//   }
  
  /// @todo Decode operation
  return 0;
}


BinaryString freettcn::CD::CCodingDecoding::Encode(TciValue value) const
{
  // obtain codec for value
  unsigned int valueId = 0;
  const CCodec &codec = Codec(value, valueId);
  
  // encode
  TriMessage buffer = { 0 };
  codec.Encode(valueId, value, buffer);
  
  if (Logging() && LogMask().Get(freettcn::CLogMask::CMD_CD_ENCODE)) {
    TriComponentId comp = { { 0 } };
    
    tliEncode(0, TimeStamp().Get(), 0, 0, comp, value, TRI_OK, buffer, const_cast<char *>(codec.Name()));
  }
  
  return buffer;
}
