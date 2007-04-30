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


# dist
quiet_cmd_dist = DIST $(2)
      cmd_dist = 



# targets
.PHONY: help all freettcn freettcn_install env env_install example clean distclean dist


help:
	@$(ECHO) ""
	@$(ECHO) "'freettcn' project compilation and instalation needs following steps:"
	@$(ECHO) ""
	@$(ECHO) " - make distclean              (optional)'"
	@$(ECHO) " - make freettcn"
	@$(ECHO) " - su -c 'make freettcn_install'"
	@$(ECHO) " - make env                    (optional)"
	@$(ECHO) " - su -c 'make env_install'    (optional)"
	@$(ECHO) " - make example                (optional)"
	@$(ECHO) ""

all: freettcn freettcn_install env env_install example

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

dist: distclean
	@$(call cmd,cmd_dist)