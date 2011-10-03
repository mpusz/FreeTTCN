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
 * @file   entity.h
 * @author Mateusz Pusz
 * @date   Mon Apr 30 20:38:47 2007
 * 
 * @brief  TTCN-3 entities base class declaration
 * 
 */

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <freettcn/tools/nonCopyable.h>

namespace freettcn {
  
  class CTimeStampMgr;
  class CLogMask;
  
  
  /**
   * @brief Base class for all TTCN-3 entities
   * 
   * freettcn::CEntity Class is a base class for all TTCN-3 entities (TE,
   * TM, SA, ...). It holds global @b logging flag that enables logging feature
   * on given entity. User can specify detailed @b logMask that defines
   * which events should trigger log messages in runtime (logging everything 
   * may be expensive).@n
   * If logging is enabled user also should provide a reference to a class
   * that will handle @b timestamping (see freettcn::CTimeStamp for more info).
   * That class is responsible for collecting, interpreting and printing
   * timestamps.
   */
  class CEntity : CNonCopyable {
  public:
    /**
     * @brief TTCN-3 entity type
     */
    enum TType {
      TYPE_TE,                                    /**< @brief TTCN Executable */
      TYPE_TM,                                    /**< @brief Test Management */
      TYPE_CH,                                    /**< @brief Component Handler */
      TYPE_CD,                                    /**< @brief Coding Decoding */
      TYPE_SA,                                    /**< @brief SUT Adaptor */
      TYPE_PA,                                    /**< @brief Platform Adaptor */
      TYPE_TL                                     /**< @brief Test Logging */
    };
    
  private:
    bool _logging;                                /**< @brief global logging mask */
    CTimeStampMgr *_ts;                           /**< @brief class responsible for
                                                     handling system timestamps */
    CLogMask *_logMask;                           /**< @brief class that specifies
                                                     which events should be logged */

  public:
    CEntity();
    virtual ~CEntity() = 0;
    
    CTimeStampMgr &TimeStampMgr() const;
    CLogMask &LogMask() const;
    bool Logging() const;
    void LogEnable(CTimeStampMgr &ts, CLogMask &logMask);
    void LogDisable();
  };
  
} // namespace freettcn


#endif /* __ENTITY_H__ */
