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


# files
CPP_FILES = cliTestManagement.cpp glibMainLoop.cpp glibPlatformAdaptor.cpp main.cpp

# defines
BIN_DIR = ../bin
INCLUDE_DIRS = -Iinclude `pkg-config --cflags glib-2.0`

# macros
O_FILES = $(addprefix $(BIN_DIR)/, $(patsubst %.cpp,%.o,$(CPP_FILES)))
DEPEND_FILES = $(patsubst %.cpp,%.d,$(CPP_FILES))

# modules
MODULES_O_FILES = $(addprefix $(BIN_DIR)/, $(foreach mod,$(MODULES),$(mod).o $(mod)_cd.o))



# targets
.PHONY: all clean distclean tags 

all: $(O_FILES)
	@$(call cmd,cmd_example_link)

clean:
	$(Q)$(RM) -f $(LIB_PATH) $(O_FILES) $(DEPEND_FILES)
	$(Q)$(RM) -f $(BIN_DIR)/$(EXAMPLE_NAME)

distclean: clean
	$(Q)$(RM) -f *~ include/*~

tags:
	@$(call cmd,cmd_tags_cpp)


# rules
$(BIN_DIR)/%.o: %.cpp
	@$(call cmd,cmd_cc_d_o)

# include depends files
-include $(CPP_FILES:.cpp=.d)
