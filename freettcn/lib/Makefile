#
# Copyright (C) 2007 Mateusz Pusz
#
# This file is part of freettcn (Free TTCN) library.

# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 2.1 of the License, or
# (at your option) any later version.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public License
# along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


include Makefile.defines


#
# directories
#
TE_DIR     = $(LONG_DIR_NAME)/te
TOOLS_DIR  = $(LONG_DIR_NAME)/tools
BIN_DIR    = $(LONG_DIR_NAME)/bin

BUILD_DIRS = $(TOOLS_DIR) $(TE_DIR) 


# libraries
LIB_FILE_NAME = $(LIB_NAME)
LIB_FULL_NAME = $(LIB_FILE_NAME).so.$(VERSION)
INCLUDE_LIBS = $(addsuffix .a, $(addprefix lib, $(notdir $(BUILD_DIRS))))


# targets
.PHONY: all install clean distclean tags

all:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make,$(dir)))
	@$(call cmd,cmd_lib_link)

install:
	@$(call cmd,cmd_lib_install)
	@$(call cmd,cmd_h_install)
	$(Q)$(INSTALL) -d $(H_INSTALL_DIR)/$(PROJECT_NAME)/ttcn3
	$(Q)$(INSTALL) -p -m 644 $(LONG_DIR_NAME)/$(LOCAL_FREETTCN_H_DIR)/ttcn3/*.h $(H_INSTALL_DIR)/$(PROJECT_NAME)/ttcn3

clean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_clean,$(dir)))
	$(Q)$(RM) -f $(BIN_DIR)/$(LIB_FULL_NAME)

distclean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_distclean,$(dir)))
	$(Q)$(RM) -f $(BIN_DIR)/*~
	$(Q)$(RM) -f $(BIN_DIR)/$(LIB_FULL_NAME)

tags:
	@$(call cmd,cmd_tags_h)
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_tags,$(dir)))
