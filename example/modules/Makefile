#
# Copyright (C) 2007 Mateusz Pusz
#
# This file is part of freettcn (Free TTCN) usage example.

# This example is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This example is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this example; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

include ../../Makefile.defines


BIN_DIR = ../bin

# files
MODULE_CPP_FILE = $(patsubst %.ttcn,%.cpp,$(MODULE))
MODULE_DEPEND_FILE = $(patsubst %.ttcn,%.d,$(MODULE))
MODULE_O_FILE = $(BIN_DIR)/$(patsubst %.ttcn,%.o,$(MODULE))


# targets
.PHONY: mod tags distclean clean

mod: $(MODULE_O_FILE)

clean:
	$(Q)$(RM) -f $(MODULE_O_FILE) $(MODULE_DEPEND_FILE)

distclean: clean
	$(Q)$(RM) -f *~ include/*~

tags:
#	$(TAGS) --append --output=$(TAG_DIR)/TAGS *.cpp


# rules
$(BIN_DIR)/%.o: %.cpp
	@$(call cmd,cmd_cc_d_o)

%.cpp: %.ttcn
	@$(call cmd,cmd_ttcn_cc)


# include depends files
-include $(MODULE_CPP_FILE:.cpp=.d)
