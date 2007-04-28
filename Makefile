#
# Copyright (C) 2007 Mateusz Pusz
#
# This file is part of freettcn (Free TTCN) project.

# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This file is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this file; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


#
# tools
#
MAKE = make
CPP = g++ -g -Wall
AR = ar -c
CP = cp
RM = rm
SED = sed
ECHO = echo
TOUCH = touch
TAGS = etags --declarations --members
DOXYGEN = doxygen
TAR = tar

#
# directories
#
ifndef $(TOP_DIR)
TOP_DIR = .
endif
BIN_DIR = $(TOP_DIR)/bin
LIB_DIR = $(TOP_DIR)/../lib


#
# varaibles
#
MAKEFLAGS += -rR --no-print-directory

ifeq ($(BUILD_VERBOSE),1)
  quiet =
  Q =
else
  quiet=quiet_
  Q = @
endif

# If the user is running make -s (silent mode), suppress echoing of commands
ifneq ($(findstring s,$(MAKEFLAGS)),)
  quiet=silent_
endif


#
# Command template
#
# If quiet is set, only print short version of command
#
cmd = @$(if $($(quiet)$(1)),printf "$($(quiet)$(1))\n" &&) $($(1))


# start compilation
quiet_cmd_make = \nBUILD  $(2)
      cmd_make = $(MAKE) -C $(2) TOP_DIR=$(TOP_DIR)/.. all


TRANSLATOR_DIR = translator
LIB_DIR = lib
ENV_LIB_DIR = libenv
EXAMPLE_DIR = example



# targets
.PHONY: help translator lib libenv example clean distclean dist


help:
	@$(ECHO) "'freettcn' project contains 3 basic modules:"
	@$(ECHO) " - TTCN code interpreter + C++ code generator + libfreettcn.so library (TE)"
	@$(ECHO) " - TTCN environment library (TM, TL, CH, CD, SA, PA)"
	@$(ECHO) " - usage example"
	@$(ECHO) ""
	@$(ECHO) "Only the first module is necessary to compile "

translator:

lib: translator
	$(call cmd,cmd_make,$(LIB_DIR))

libenv: lib
	$(call cmd,cmd_make,$(ENV_LIB_DIR))


# all: $(BIN_DIR)/$(PROG_NAME)

# main:
# 	$(call cmd,cmd_make_main)

# modules:
# 	$(foreach mod, $(MOD_FILES), $(call cmd,cmd_make_mod))

# $(LIB_DIRS):
# 	$(call cmd,cmd_make_lib)

# tags:
# 	$(Q)for dir in $(LIB_DIRS); do \
# 	  $(MAKE) -C $$dir TOP_DIR=$(TOP_DIR)/.. DIR_NAME=$$dir TAG_DIR=$(PWD) tags; \
# 	done
# 	$(Q)for mod in $(MOD_FILES); do \
# 	  $(MAKE) -C $(MOD_DIR) TOP_DIR=$(TOP_DIR)/.. MODULE=$$mod tags; \
# 	done
# 	$(MAKE) -C $(MAIN_DIR) TOP_DIR=$(TOP_DIR)/.. tags;

# doc:
# 	$(DOXYGEN) $(DOC_DIR)/Doxyfile

# clobber:
# 	$(Q)for dir in $(LIB_DIRS); do \
# 	  $(MAKE) -C $$dir TOP_DIR=$(TOP_DIR)/.. DIR_NAME=$$dir clobber; \
# 	done
# 	$(Q)for mod in $(MOD_FILES); do \
# 	  $(MAKE) -C $(MOD_DIR) TOP_DIR=$(TOP_DIR)/.. MODULE=$$mod clobber; \
# 	done
# 	$(Q)$(MAKE) -C $(MAIN_DIR) TOP_DIR=$(TOP_DIR)/.. clobber;
# 	$(Q)$(RM) -f *~ TAGS BROWSE
# 	$(Q)$(RM) -f $(DOC_DIR)/tags.xml $(DOC_DIR)/html

# dist: clobber
# 	$(Q)$(TAR) -cvzf $(DIR_NAME).tar.gz ../$(DIR_NAME)

# clean:
# 	$(Q)for dir in $(LIB_DIRS); do \
# 	  $(MAKE) -C $$dir TOP_DIR=$(TOP_DIR)/.. DIR_NAME=$$dir clean; \
# 	done
# 	$(Q)for mod in $(MOD_FILES); do \
# 	  $(MAKE) -C $(MOD_DIR) TOP_DIR=$(TOP_DIR)/.. MODULE=$$mod clean; \
# 	done
# 	$(Q)$(MAKE) -C $(MAIN_DIR) TOP_DIR=$(TOP_DIR)/.. clean;


# # rules
# $(BIN_DIR)/$(PROG_NAME): $(LIB_DIRS) modules main
