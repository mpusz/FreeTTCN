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
 * @file   buffer.cpp
 * @author Mateusz Pusz
 * @date   Wed May 30 18:04:30 2007
 * 
 * @brief  
 * 
 * 
 */

#include "freettcn/cd/buffer.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <netinet/in.h>



freettcn::CD::CBuffer::CBuffer(const BinaryString message, TByteOrder byteOrder /* BYTE_ORDER_BIG_ENDIAN */) :
  _hostByteOrder((htons(1) == 1) ? BYTE_ORDER_BIG_ENDIAN : BYTE_ORDER_LITTLE_ENDIAN),
  _byteOrder((byteOrder == BYTE_ORDER_HOST) ? _hostByteOrder : byteOrder),
  __message(0)
{
  if (message.bits) {
    _buffer.assign(&message.data[0], &message.data[static_cast<unsigned int>(ceil(message.bits / 8.0))]);
    _lastOctetBits = ((message.bits - 1) % 8) + 1;
  }
  else {
    _lastOctetBits = 8;
  }
}


freettcn::CD::CBuffer::CBuffer(TByteOrder byteOrder /* BYTE_ORDER_BIG_ENDIAN */) :
  _hostByteOrder((htons(1) == 1) ? BYTE_ORDER_BIG_ENDIAN : BYTE_ORDER_LITTLE_ENDIAN),
  _byteOrder(byteOrder),
  _lastOctetBits(8), __message(0)
{
}


freettcn::CD::CBuffer::~CBuffer()
{
  if (__message) {
    if (__message->data)
      delete[] __message->data;
    delete __message;
  }
}


unsigned long freettcn::CD::CBuffer::BitLength() const
{
  return _buffer.size() * 8 - (8 - _lastOctetBits);
}


const BinaryString &freettcn::CD::CBuffer::Message() const
{
  if (__message) {
    if (__message->data)
      delete[] __message->data;
    delete __message;
  }
  
  __message = new BinaryString;
  __message->bits = BitLength();
  __message->aux = 0;
  if (__message->bits) {
    __message->data = new unsigned char[_buffer.size()];
    for(unsigned long i=0; i<_buffer.size(); i++)
      __message->data[i] = _buffer[i];
  }
  else
    __message->data= 0;
  
  return *__message;
}


void freettcn::CD::CBuffer::BytePack(unsigned char byte, unsigned short bitLength /* 8 */)
{
  if (bitLength != 8) {
    // mask it to be sure that proper value is given
    byte &= (0x1 << bitLength) - 1;
    
    // align the value to the left
    byte <<= 8 - bitLength;
  }
  
  if (_lastOctetBits != 8) {
    // pack the rest of the byte
    unsigned short bits = std::min(static_cast<unsigned short>(8 - _lastOctetBits), bitLength);
    unsigned char tmpByte = byte >> (8 - bits);
    _buffer[_buffer.size() - 1] |=  tmpByte;
    _lastOctetBits += bits;
    if (_lastOctetBits != 8)
      // the end of the data
      return;
    byte <<= bits;
    bitLength -= bits;
  }
  
  // pack new byte
  _buffer.push_back(byte);
  _lastOctetBits = bitLength;
}


unsigned char freettcn::CD::CBuffer::ByteUnpack(unsigned short bitLength /* 8 */)
{
}


void freettcn::CD::CBuffer::UIntPack(unsigned long value, unsigned short bitLength) throw(EOperationFailed)
{
  if (!bitLength || value >= static_cast<unsigned long>(1 << bitLength)) {
    std::cout << "ERROR: Incorrect value: " << value << " given for bitLength: " << bitLength << "!!!" << std::endl;
    throw EOperationFailed();
  }
  
  if (bitLength > sizeof(unsigned long) * 8) {
    std::cout << "ERROR: bitLength: " << bitLength << " too big for " << sizeof(unsigned long) * 8 << " byte value!!!" << std::endl;
  }
  
  // store value
  unsigned char *ptr = reinterpret_cast<unsigned char *>(&value);
  unsigned short byteLength = static_cast<unsigned short>(ceil(bitLength / 8.0));
  for(unsigned short i=0; i<byteLength; i++) {
    if (_hostByteOrder == _byteOrder)
      BytePack(ptr[i], (i < byteLength - 1) ? 8 : (((bitLength - 8 * i) - 1) % 8 + 1));
    else
      // swap bytes
      BytePack(ptr[byteLength - 1 - i], i ? 8 : (((bitLength - 8 * i) - 1) % 8 + 1));
  }
}


unsigned long freettcn::CD::CBuffer::UIntUnpack(unsigned short bitLength) throw(EOperationFailed)
{
//   if (bitLength <= 8) {
//     return *Get(bitLength);
//   }
//   else {
//     unsigned long val = 0;
//     const unsigned char *valPtr = Get(bitLength);
//     unsigned short idx=0;
    
//     while(bitLength - idx * 8 > 8) {
//       if (idx)
//         val <<= 8;
//       val |= valPtr[idx++];
//     }
    
//     return val;
//   }
}


void freettcn::CD::CBuffer::RawDataPack(const unsigned char buffer[], unsigned int bitLength, TByteOrder byteOrder /* BYTE_ORDER_BIG_ENDIAN */)
{
  unsigned short byteLength = static_cast<unsigned short>(ceil(bitLength / 8.0));
  for(unsigned short i=0; i<byteLength; i++)
    BytePack(buffer[i], (i < byteLength - 1) ? 8 : (((bitLength - 8 * i) - 1) % 8 + 1));
}



// freettcn::CD::CHexBuffer::CHexBuffer(const BinaryString message, TByteOrder byteOrder /* BYTE_ORDER_BIG_ENDIAN */) :
//   CBuffer(message, byteOrder), _currPtr(_data)
// {
// }



// const unsigned char *freettcn::CD::CHexBuffer::Get(unsigned long bitLength) throw(EOperationFailed, EBufferTooShort)
// {
//   if (BitLength() < bitLength)
//     throw EBufferTooShort();
  
//   const unsigned char *ptr = _currPtr;
  
//   _currPtr += bitLength / 8;
  
//   return ptr;
// }



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
