//
// Copyright (C) 2007 Mateusz Pusz
//
// This file is part of freettcn (Free TTCN) usage example.

// This example is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This example is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this example; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**
 * @file   decoder.h
 * @author Mateusz Pusz
 * @date   Fri Apr  6 17:52:20 2007
 * 
 * @brief  
 * 
 */

#ifndef __DECODER_H__
#define __DECODER_H__

extern "C" {
#include "freettcn/types.h"
}

#include "exception.h"

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
      
    protected:
      unsigned char const * const _data;
      const unsigned long _dataBitLength;
      const TByteOrder _byteOrder;
      
    public:  
      CBuffer(const BinaryString message, TByteOrder byteOrder = BYTE_ORDER_BIG_ENDIAN);
      //  CBuffer(const unsigned char *data, unsigned long dataLen, TByteOrder byteOrder = BYTE_ORDER_BIG_ENDIAN);
      virtual ~CBuffer();
      
      const BinaryString Message() const;
      
      unsigned long UIntGet(unsigned short bitLength, TByteOrder byteOrder = BYTE_ORDER_HOST);
      long IntGet(unsigned short bitLength, TByteOrder byteOrder = BYTE_ORDER_HOST);
      
      virtual unsigned long BitLength() const = 0;
      virtual const unsigned char *Get(unsigned long bitLength) throw(EOperationFailed, EBufferTooShort) = 0;
    };
    
    
    class CHexBuffer : public CBuffer {
      unsigned char const * _currPtr;
    public:
      CHexBuffer(const BinaryString message, TByteOrder byteOrder = BYTE_ORDER_BIG_ENDIAN);
      
      virtual unsigned long BitLength() const;
      virtual const unsigned char *Get(unsigned long bitLength) throw(EOperationFailed, EBufferTooShort);
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
    
    class EDecodeFailure : public EOperationFailed {};
    class EEncodeFailure : public EOperationFailed {};
    
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


#endif /* __DECODER_H__ */
