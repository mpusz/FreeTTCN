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


include Makefile.defines


# directories
FREETTCN_DIR = freettcn
ENV_DIR = libenv
EXAMPLE_DIR = example
BUILD_DIRS = $(FREETTCN_DIR) $(ENV_DIR) $(EXAMPLE_DIR)
DOC_DIR = doc


# targets
.PHONY: help freettcn freettcn_install env env_install example clean distclean dist all tags classes doc


help:
	@$(ECHO) ""
	@$(ECHO) "'freettcn' project compilation and instalation needs following steps:"
	@$(ECHO) ""
	@$(ECHO) " - make distclean              (optional)'"
	@$(ECHO) " - make freettcn"
	@$(ECHO) " - sudo make freettcn_install"
	@$(ECHO) " - make env                    (optional)"
	@$(ECHO) " - sudo make env_install       (optional)"
	@$(ECHO) " - make example                (optional)"
	@$(ECHO) ""

freettcn:
	@$(ECHO) ""
	@$(ECHO) "Building 'freettcn'..."
	@$(call cmd,cmd_make,$(FREETTCN_DIR))

freettcn_install:
	@$(ECHO) ""
	@$(ECHO) "Installing 'freettcn'..."
	@$(call cmd,cmd_make_install,$(FREETTCN_DIR))

env:
	@$(ECHO) ""
	@$(ECHO) "Building 'freettcnenv'..."
	@$(call cmd,cmd_make,$(ENV_DIR))

env_install:
	@$(ECHO) ""
	@$(ECHO) "Installing 'freettcnenv'..."
	@$(call cmd,cmd_make_install,$(ENV_DIR))

example:
	@$(ECHO) ""
	@$(ECHO) "Building example..."
	@$(call cmd,cmd_make,$(EXAMPLE_DIR))

clean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_clean,$(dir)))

distclean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_distclean,$(dir)))
	$(Q)$(RM) -f TAGS BROWSE $(PROJECT_NAME)-$(VERSION).tar.gz *~
	$(Q)$(RM) -rf $(DOC_DIR)/html # $(DOC_DIR)/tags.xml 

dist: distclean
	@$(call cmd,cmd_dist)

all: freettcn freettcn_install env env_install example

tags:
	$(Q)$(RM) -f TAGS
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_tags,$(dir)))
	@$(call cmd,cmd_ebrowse)

classes:
	$(Q)$(EBROWSE) -s freettcn/lib/include/freettcn/*/*.h freettcn/lib/*/*.cpp libenv/include/freettcn/*/*.h example/*/*.cpp #libenv/*/*.cpp

doc:
	$(Q)$(SED) -i -e 's/\(PROJECT_NUMBER.*=\).*/\1 $(VERSION)/' doc/Doxyfile
	$(Q)$(DOXYGEN) $(DOC_DIR)/Doxyfile
