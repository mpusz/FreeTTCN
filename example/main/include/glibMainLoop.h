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
 * @file   glibMainLoop.h
 * @author Mateusz Pusz
 * @date   Fri May 11 10:56:31 2007
 * 
 * @brief  
 * 
 * 
 */

#ifndef __GLIBMAINLOOP_H__
#define __GLIBMAINLOOP_H__

#include "cliTestManagement.h"
#include <glib.h>


class CGlibMainLoop : public CCLITestManagement::CMainLoop {
  GMainLoop *_loop;
public:
  CGlibMainLoop();
  ~CGlibMainLoop();
  virtual void Start();
  virtual void Stop();
};


#endif /* __GLIBMAINLOOP_H__ */
