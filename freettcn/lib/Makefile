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
BIN_DIR = bin
#DOC_DIR = doc


#
# Commands
#

# start library compilation
quiet_cmd_make_lib = \nBUILD_LIB  $(BIN_DIR)/$(LIB_FULL_NAME)
      cmd_make_lib = $(MAKE) -C $(SRC_DIR) TOP_DIR=$(TOP_DIR)/.. all

# compile source file, create depend file *.d
quiet_cmd_cc_d_o = CC_D_O     $<
      cmd_cc_d_o = $(CPP) -MMD -MF $*.d_ -c -fPIC $(INCLUDE_DIRS) $< -o $@ && \
                   $(CP) $*.d_ $*.d && \
	           $(SED) -e 's/\#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $*.d_ >> $*.d && \
	           $(RM) -f $*.d_

# link program
quiet_cmd_link = LINK       $(BIN_DIR)/$(LIB_FULL_NAME)
      cmd_link = $(CPP) -shared -Wl,-export-dynamic,-soname,$(LIB_FILE_NAME).so.$(VERSION_1) -o $(BIN_DIR)/$(LIB_FULL_NAME) $(O_FILES) && \
	         $(LN) -sf $(PWD)/bin/lib$(LIB_NAME).so.$(VERSION) $(PWD)/bin/lib$(LIB_NAME).so.$(VERSION_1) && \
	         $(LN) -sf $(PWD)/bin/lib$(LIB_NAME).so.$(VERSION_1) $(PWD)/bin/lib$(LIB_NAME).so

# make tags
quiet_cmd_tags = TAGS
      cmd_tags = $(TAGS) --append --output=$(TAG_DIR)/TAGS $(LIB_H_FILES_PATH)/*.h $(H_FILES_PATH)/*.h *.cpp



# targets
.PHONY: all install tags doc clobber dist clean

all:
	$(call cmd,cmd_make_lib)

install:
	$(LDCONFIG) -n $(BIN_DIR)

tags:
	$(Q)$(MAKE) -C $(SRC_DIR) TOP_DIR=$(TOP_DIR)/.. TAG_DIR=$(PWD) tags;

doc:
	$(DOXYGEN) $(DOC_DIR)/Doxyfile

clobber:
	$(Q)$(MAKE) -C $(SRC_DIR) TOP_DIR=$(TOP_DIR)/.. clobber;
	$(Q)$(RM) -f *~ TAGS BROWSE
	$(Q)$(RM) -rf $(DOC_DIR)/tags.xml $(DOC_DIR)/html
#	$(RM) -f $(DIR_NAME).tar.gz

# dist: clobber
# 	tar -cvzf $(DIR_NAME).tar.gz ../$(DIR_NAME)

clean:
	$(Q)$(MAKE) -C $(SRC_DIR) TOP_DIR=$(TOP_DIR)/.. clean

#classes:
#	ebrowse -s include/ttcn3/*.h *.h *.cpp
#
#lines:
#	wc -l *.cpp

