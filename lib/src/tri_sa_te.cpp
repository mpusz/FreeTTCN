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

extern "C" {
#include "freettcn/tri_sa_te.h"
  /// @todo Remove header below
#include "freettcn/tci_te_cd.h"
}


void triEnqueueMsg(const TriPortId* tsiPortId,
                   const TriAddress* sutAddress,
                   const TriComponentId* componentId,
                   const TriMessage* receivedMessage)
{
  /// @todo Handle message properly
  if (TciValue value = tciDecode(*receivedMessage, 0)) {
//     void tliMReceive_m(String am,
//                        int ts,
//                        String src,
//                        int line,
//                        TriComponentId c,
//                        TriPortId port,
//                        TciValue msgValue,
//                        TciValueTemplate msgTmpl,
//                        TriAddress address,
//                        TciValueTemplate addressTmpl);

//     void tliMReceive_c(String am,
//                        int ts,
//                        String src,
//                        int line,
//                        TriComponentId c,
//                        TriPortId port,
//                        TciValue msgValue,
//                        TciValueTemplate msgTmpl,
//                        TriComponentId from,
//                        TciNonValueTemplate fromTmpl);
  }
  else {
// void tliMMismatch_m(String am,
//                     int ts,
//                     String src,
//                     int line,
//                     TriComponentId c,
//                     TriPortId port,
//                     TciValue msgValue,
//                     TciValueTemplate msgTmpl,
//                     TciValueDifferenceList diffs,
//                     TriAddress address,
//                     TciValueTemplate addressTmpl);

//     void tliMMismatch_c(String am,
//                         int ts,
//                         String src,
//                         int line,
//                         TriComponentId c,
//                         TriPortId port,
//                         TciValue msgValue,
//                         TciValueTemplate msgTmpl,
//                         TciValueDifferenceList diffs,
//                         TriComponentId from,
//                         TciNonValueTemplate fromTmpl);
  }
}
