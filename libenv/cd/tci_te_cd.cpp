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
}
#include "freettcn/cd/cd.h"

// #include <cstring>
// #include <cstdio>



Value tciDecode(BinaryString message,
                Type         decHypothesis)
{
  freettcn::CD::CCodingDecoding &cd = freettcn::CD::CCodingDecoding::Instance();
  return cd.Decode(message, decHypothesis);
}


BinaryString tciEncode(Value value)
{
  freettcn::CD::CCodingDecoding &cd = freettcn::CD::CCodingDecoding::Instance();
  return cd.Encode(value);
}






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



