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

