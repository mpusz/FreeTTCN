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


include ../../Makefile.defines


#
# directories
#
TE_DIR = te
TOOLS_DIR = tools
BUILD_DIRS = $(TOOLS_DIR) $(TE_DIR) 

TTCN3_H_DIR = include/ttcn3
#DOC_DIR = doc



# # make tags
# quiet_cmd_tags = TAGS
#       cmd_tags = $(TAGS) --append --output=$(TAG_DIR)/TAGS $(LIB_H_FILES_PATH)/*.h $(H_FILES_PATH)/*.h *.cpp



# targets
.PHONY: all install clean distclean tags

all:
	$(Q)$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make,$(dir)))

install:
	$(INSTALL) $(BIN_DIR)/$(LIB_FULL_NAME) $(LIB_INSTALL_DIR)
	$(LDCONFIG) -n $(LIB_INSTALL_DIR)
	$(LN) -sf $(LIB_FILE_NAME).so.$(VERSION_1) $(LIB_INSTALL_DIR)/$(LIB_FILE_NAME).so
	$(INSTALL) -d $(H_INSTALL_DIR)/$(PROJECT_NAME) $(H_INSTALL_DIR)/$(PROJECT_NAME)/ttcn3 \
	           $(H_INSTALL_DIR)/$(PROJECT_NAME)/te $(H_INSTALL_DIR)/$(PROJECT_NAME)/tools
	$(INSTALL) -m 644 $(TTCN3_H_DIR)/* $(H_INSTALL_DIR)/$(PROJECT_NAME)/ttcn3

clean:
	$(Q)$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_clean,$(dir)))

distclean:
	$(Q)$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_distclean,$(dir)))
# 	$(Q)$(MAKE) -C $(SRC_DIR) TOP_DIR=$(TOP_DIR)/.. clobber;
# 	$(Q)$(RM) -f *~ TAGS BROWSE
# 	$(Q)$(RM) -rf $(DOC_DIR)/tags.xml $(DOC_DIR)/html
#	$(RM) -f $(DIR_NAME).tar.gz

tags:
# 	$(Q)$(MAKE) -C $(SRC_DIR) TOP_DIR=$(TOP_DIR)/.. TAG_DIR=$(PWD) tags;

# doc:
# 	$(DOXYGEN) $(DOC_DIR)/Doxyfile



#classes:
#	ebrowse -s include/ttcn3/*.h *.h *.cpp
#
#lines:
#	wc -l *.cpp

