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
 * @file   buffer.h
 * @author Mateusz Pusz
 * @date   Wed May 30 18:03:27 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __BUFFER_H__
#define __BUFFER_H__

extern "C" {
#include <freettcn/ttcn3/types.h>
}

#include <freettcn/tools/exception.h>
#include <deque>

namespace freettcn {
  
  namespace CD {
    
    class CBuffer {
    public:
      enum TByteOrder {
        BYTE_ORDER_BIG_ENDIAN,                        /**< default network byte order */
        BYTE_ORDER_LITTLE_ENDIAN,
        BYTE_ORDER_HOST                               /**< byte order of current host */
      };
      class EBufferTooShort : public EOperationFailed {};
      
    private:
      typedef std::deque<unsigned char> CBufferArray;
      
      const TByteOrder _hostByteOrder;
      const TByteOrder _byteOrder;
      
      CBufferArray _buffer;
      unsigned short _lastOctetBits;
      
      mutable BinaryString *__message;
      
      void BytePack(unsigned char byte, unsigned short bitLength = 8);
      unsigned char ByteUnpack(unsigned short bitLength = 8);
      
    public:
      CBuffer(const BinaryString message, TByteOrder byteOrder = BYTE_ORDER_BIG_ENDIAN);
      CBuffer(TByteOrder byteOrder = BYTE_ORDER_BIG_ENDIAN);
      ~CBuffer();
      
      unsigned long BitLength() const;
      const BinaryString &Message() const;
      
      void UIntPack(unsigned long value, unsigned short bitLength) throw(EOperationFailed);
      unsigned long UIntUnpack(unsigned short bitLength) throw(EOperationFailed);
      
      void IntPack(long value, unsigned short bitLength) throw(EOperationFailed);
      long IntUnpack(unsigned short bitLength) throw(EOperationFailed);
      
      void RawDataPack(const unsigned char buffer[], unsigned int bitLength, TByteOrder byteOrder = BYTE_ORDER_BIG_ENDIAN);
      void RawDataPack(const CBuffer &buffer);
      
//       const unsigned char *Get(unsigned long bitLength) throw(EOperationFailed, EBufferTooShort) = 0;
    };
    
    
//     class CInteger {
//       long value;
//     public:
//       //    CInteger;
//       TciValue TciValueCreate() const;
//       TciValue TciValueSet(TciValue) const;
      
//       friend freettcn::CBuffer &operator>>(freettcn::CBuffer &, CInteger &, unsigned short);
//       //     friend std::istream& operator>>(std::istream&, Date&);
//     };
    
    
//     class CDecoder {
//     public:
//       CDecoder();
//       const unsigned char *Buffer(unsigned long len) const;
//       CInteger Integer(unsigned short len, bool signedValue = false) const throw(CBuffer::EBufferTooShort);
//     };
    
//     class EDecodeFailure : public EOperationFailed {};
//     class EEncodeFailure : public EOperationFailed {};
    
//     class CType {
//       TciValue value;
//     public:
//       CType(TciValue v);
//       virtual ~CType() = 0;
//       TciValue Value() const;
//       virtual void Decode(freettcn::CBuffer &buffer) throw(EDecodeFailure);
//       virtual void Encode(freettcn::CBuffer &buffer) const throw(EEncodeFailure);
//     };
    
//     class CRecord : public CType {
//       std::vector<CType *> list;
//     public:
      
//     };
    
//     class CRecordOf : public CType {
//       std::vector<CType *> list;
//     public:
      
//     };
    
  } // namespace CD

} // namespace freettcn


// namespace IP {
  
//   class CICMPDataType : public freettcn::CD::CUnion {
    
//   };
  
//   class CICMPType : public freettcn::CD::CRecord {
//     freettcn::CD::CInteger msgType;
//     freettcn::CD::CInteger code;
//     freettcn::CD::CInteger crc;
//     ICMPDataType data;

// //     enum Idx {
// //       TYPE
// //       IP_SRC_ADDRESS,
// //       IP_DST_ADDRESS
// //     };
// //     CIPAddress srcAddress;
// //     CIPAddress dstAddress;

//   public:
//     CICMPType(TciValue v);
//   };
  
// };


#endif /* __BUFFER_H__ */
