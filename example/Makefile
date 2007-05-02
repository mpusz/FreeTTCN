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

include ../Makefile.defines


PROG_NAME = ttcn_example
MOD_FILES = icmp.ttcn

#
# directories
#
MODULES_DIR = modules
MAIN_DIR = main
BUILD_DIRS = $(MODULES_DIR) $(MAIN_DIR)

BIN_DIR = bin

export MOD_FILES PROG_NAME

# targets
.PHONY: all main modules clean distclean tags

all: $(BIN_DIR)/$(PROG_NAME)

main:
	@$(call cmd,cmd_make,$(MAIN_DIR))

modules:
	@$(foreach mod, $(MOD_FILES), $(call cmd,cmd_make_mod,$(mod)))

clean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_clean,$(dir)))

distclean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_distclean,$(dir)))
	$(Q)$(RM) -f $(BIN_DIR)/*~

tags:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_tags,$(dir)))

# doc:
# 	$(DOXYGEN) $(DOC_DIR)/Doxyfile


# rules
$(BIN_DIR)/$(PROG_NAME): modules main
