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

extern "C" {
#include <freettcn/ttcn3/tci_te_cd.h>
#include <freettcn/ttcn3/tci_tl.h>
#include <freettcn/ttcn3/tci_value.h>
}

#include "freettcn/cd/decoder.h"
#include <cstring>
#include <cstdio>



// freettcn::CBuffer &operator>>(freettcn::CBuffer &buffer, IP::CPingMessage &msg)
// {
//   freettcn::CInteger integer;
  
//   buffer >> integer(1);
// }


// {  
//   //  TTCN3::HexstringDecoder::iterator it = decoder.begin();
//   TciValue recordValue = tciNewInstance(decHypothesis);
//   TciValue recordOfValue = tciGetRecFieldValue(recordValue, "srcIPAddr");
//   if (recordOfValue == 0) {
//     // error
//     return recordValue;
//   }
  
//   TciType recordElemType = tciGetRecOfElementType(recordOfValue);
//   try {
//     // decode source IP Address
//     for (unsigned int i=0; i<4; i++) {
//       freettcn::CInteger integer;
      
//       buffer >> integer(1);
//       buffer >> record(freettcn::CInteger(1));

//       freettcn::CInteger integer = decoder.Integer(it, 1);
//       tciAppendRecOfFieldValue(recordOfValue, integer.TciValueCreate());
//     }
//   }
//   catch(freettcn::CBuffer::EBufferTooShort) {
//     // error
//   }
// //   tliDecode(String am,
// //             int ts,
// //             String src,
// //             int line,
// //             TriComponentId c,
// //             TriMessage msg,
// //             TriStatus decoderFailure,
// //             TciValue val,
// //             String codec);

  
//   return recordValue;
// }


TciValue tciDecode(BinaryString message,
                   TciType decHypothesis)
{
  if (tciGetTypeClass(decHypothesis) == TCI_ANYTYPE_TYPE) {
//   tliDecode(String am,
//             int ts,
//             String src,
//             int line,
//             TriComponentId c,
//             TriMessage msg,
//             TriStatus decoderFailure,
//             TciValue val,
//             String codec);
    
    return tciNewInstance(decHypothesis);
  }
  
  try {
    freettcn::CD::CHexBuffer buffer(message);
    
    // check against decHypothesis
    if (!strcmp(tciGetName(decHypothesis), "ICMPType")) {
//       IP::CICMPType icmpMsg(tciNewInstance(decHypothesis));
//       icmpMsg.Decode(buffer);
//       return icmpMsg.Value();
      
      TciValue icmpMsg = tciNewInstance(decHypothesis);
      char str[10];

//       TciValue msgType = tciGetRecFieldValue(icmpMsg, "msgType");
//       if (!msgType)
//         throw freettcn::CD::EDecodeFailure();
//       tciSetIntSign(msgType, 1);
//       sprintf(str, "%lu", buffer.UIntGet(8));
//       tciSetIntAbs(msgType, str);
      
//       TciValue code = tciGetRecFieldValue(icmpMsg, "code");
//       if (!code)
//         throw freettcn::CD::EDecodeFailure();
//       tciSetIntSign(code, 1);
//       sprintf(str, "%lu", buffer.UIntGet(8));
//       tciSetIntAbs(msgType, str);
      
//       TciValue crc = tciGetRecFieldValue(icmpMsg, "crc");
//       if (!crc)
//         throw freettcn::CD::EDecodeFailure();
//       tciSetIntSign(crc, 1);
//       sprintf(str, "%lu", buffer.UIntGet(16));
//       tciSetIntAbs(msgType, str);

      return icmpMsg;
    }
    else {
      // unknown type
//   tliDecode(String am,
//             int ts,
//             String src,
//             int line,
//             TriComponentId c,
//             TriMessage msg,
//             TriStatus decoderFailure,
//             TciValue val,
//             String codec);
      
      return 0;
    }
  }
  catch(freettcn::CD::EDecodeFailure) {
//   tliDecode(String am,
//             int ts,
//             String src,
//             int line,
//             TriComponentId c,
//             TriMessage msg,
//             TriStatus decoderFailure,
//             TciValue val,
//             String codec);
    
    return 0;
  }
  catch(freettcn::EOperationFailed) {
//   tliDecode(String am,
//             int ts,
//             String src,
//             int line,
//             TriComponentId c,
//             TriMessage msg,
//             TriStatus decoderFailure,
//             TciValue val,
//             String codec);
    
    return 0;
  }
}
