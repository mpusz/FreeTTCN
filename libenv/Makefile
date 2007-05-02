#
# Copyright (C) 2007 Mateusz Pusz
#
# This file is part of freettcnenv (Free TTCN Environment) library.

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


include ../Makefile.defines


#
# directories
#
PA_DIR = pa
SA_DIR = sa
CD_DIR = cd
CH_DIR = ch
TM_DIR = tm
TL_DIR = tl
BUILD_DIRS = $(TM_DIR) $(PA_DIR) $(SA_DIR) $(CD_DIR) $(CH_DIR) $(TL_DIR)

BIN_DIR = bin

#DOC_DIR = doc


# libraries
LIB_FILE_NAME = $(LIB_ENV_NAME)
LIB_FULL_NAME = $(LIB_FILE_NAME).so.$(VERSION)
INCLUDE_LIBS = $(addsuffix .a, $(addprefix lib, $(BUILD_DIRS)))


# targets
.PHONY: all install clean distclean tags

all:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make,$(dir)))
	@$(call cmd,cmd_lib_link)

install:
	@$(call cmd,cmd_lib_install)
	@$(call cmd,cmd_h_install)

clean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_clean,$(dir)))
	$(Q)$(RM) -f $(BIN_DIR)/$(LIB_FULL_NAME)

distclean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_distclean,$(dir)))
	$(Q)$(RM) -f $(BIN_DIR)/*~
	$(Q)$(RM) -f $(BIN_DIR)/$(LIB_FULL_NAME)

# 	$(Q)$(MAKE) -C $(SRC_DIR) TOP_DIR=$(TOP_DIR)/.. clobber;
# 	$(Q)$(RM) -f *~ TAGS BROWSE
# 	$(Q)$(RM) -rf $(DOC_DIR)/tags.xml $(DOC_DIR)/html
#	$(RM) -f $(DIR_NAME).tar.gz

tags:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_tags,$(dir)))
	@$(call cmd,cmd_tags_h)

# doc:
# 	$(DOXYGEN) $(DOC_DIR)/Doxyfile



#classes:
#	ebrowse -s include/ttcn3/*.h *.h *.cpp
#
#lines:
#	wc -l *.cpp

