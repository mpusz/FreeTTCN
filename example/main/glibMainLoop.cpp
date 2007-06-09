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


#include "glibMainLoop.h"


freettcn::example::CGlibMainLoop::CGlibMainLoop():
  _loop(0)
{
}

freettcn::example::CGlibMainLoop::~CGlibMainLoop()
{
  if (_loop)
    g_main_loop_quit(_loop);
}

void freettcn::example::CGlibMainLoop::Start()
{
  // create main event loop
  _loop = g_main_loop_new(0, FALSE);
  g_main_loop_run(_loop);
}

void freettcn::example::CGlibMainLoop::Stop()
{
  g_main_loop_quit(_loop);
  g_main_loop_unref(_loop);
  _loop = 0;
}
