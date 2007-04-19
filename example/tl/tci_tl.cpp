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


extern "C" {
#include "freettcn/tci_tl.h"
}

#include <iostream>
#include <iomanip>

void tliMDetected_m(String am,
                    int ts,
                    String src,
                    int line,
                    TriComponentId c,
                    TriPortId port,
                    TriMessage msg,
                    TriAddress address)
{
  using namespace std;
  
  cout << "[" << ts << "][SA] New message detected";
  if (*src)
    cout << " [" << src << ":" << line << "]";
  cout << ":" << endl;
  if (*am)
    cout << "[SA] - Note: " << am << endl;
  cout << "[SA] - To: " << port.compInst.compName << "." << port.portName << ":" << port.portIndex
       << " [" << port.compInst.compType.moduleName << "." << port.compInst.compType.objectName << "]" << endl;
  cout << "[SA] - From: " << c.compName
       << " [" << c.compType.moduleName << "." << c.compType.objectName << "]" << endl;
  cout << "[SA] - Data:";

  int oldFill=cout.fill('0');
  for(int i=0; i<msg.bits / 8; i++) {
    if (!(i % 8)) {
      if (!(i % 16))
        cout << endl << "       ";
      else
        cout << "  ";
    }
    else
      cout << " ";
    cout << hex << setw(2) << static_cast<unsigned short>(msg.data[i]);
  }
  cout.fill(oldFill);
  cout << endl;
}
