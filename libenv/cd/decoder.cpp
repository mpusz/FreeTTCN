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


#include "freettcn/cd/decoder.h"
#include <cmath>


freettcn::CD::CBuffer::CBuffer(const BinaryString message, TByteOrder byteOrder /* BYTE_ORDER_BIG_ENDIAN */) :
  _data(message.data), _dataBitLength(message.bits), _byteOrder(byteOrder)
{
}


freettcn::CD::CBuffer::~CBuffer()
{
}


unsigned long freettcn::CD::CBuffer::UIntGet(unsigned short bitLength, TByteOrder byteOrder /* BYTE_ORDER_HOST */)
{
  if (bitLength <= 8) {
    return *Get(bitLength);
  }
  else {
    unsigned long val = 0;
    const unsigned char *valPtr = Get(bitLength);
    unsigned short idx=0;
    
    while(bitLength - idx * 8 > 8) {
      if (idx)
        val <<= 8;
      val |= valPtr[idx++];
    }
    
    return val;
  }
}



freettcn::CD::CHexBuffer::CHexBuffer(const BinaryString message, TByteOrder byteOrder /* BYTE_ORDER_BIG_ENDIAN */) :
  CBuffer(message, byteOrder), _currPtr(_data)
{
}



unsigned long freettcn::CD::CHexBuffer::BitLength() const
{
  return _dataBitLength - (_currPtr - _data) * 8;
}



const unsigned char *freettcn::CD::CHexBuffer::Get(unsigned long bitLength) throw(EOperationFailed, EBufferTooShort)
{
  if (BitLength() < bitLength)
    throw EBufferTooShort();
  
  const unsigned char *ptr = _currPtr;
  
  _currPtr += bitLength / 8;
  
  return ptr;
}



// CInteger CDecoder::Integer(CBuffer::iterator &it, unsigned short len, bool signedValue = false) const throw(EBufferTooShort)
// {
//   if (buffer.Length() < len)
//     throw EBufferTooShort();
  
//   unsigned char *intBuffer = new unsigned char[ceil(len * buffer.Unit() / 8.0)];
//   buffer.Get(it, intBuffer, len);
  
//   if ();
  
//   delete[] intBuffer;
  
//   it += len;
// }




// IP::CICMPType::CICMPType(TciValue v) :
//   freettcn::CD::CRecord(v),
//   msgType(tciGetRecFieldValue(v, "msgType"), 8),
//   code(tciGetRecFieldValue(v, "code"), 8),
//   crc(tciGetRecFieldValue(v, "crc"), 16),
//   data(tciGetRecFieldValue(v, "data"))
// {
// }


// void IP::CICMPType::Decode(freettcn::CBuffer &buffer) throw(EDecodeFailure)
// {
//   msgType.Decode(buffer);
//   code.Decode(buffer);
//   crc.Decode(buffer);
//   data.Decode(buffer);
// }
