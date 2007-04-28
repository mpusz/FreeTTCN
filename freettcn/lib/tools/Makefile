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

include ../../../Makefile.defines


BIN_DIR = ../bin

# files
# CPP_FILES = type.cpp value.cpp log.cpp sourceData.cpp modulesContainer.cpp \
# 	tci_value.cpp tci_tm_te.cpp tci_ch_te.cpp \
# 	tri_sa_te.cpp \
# 	te.cpp initObject.cpp module.cpp testComponent.cpp behavior.cpp testCase.cpp
CPP_O_FILES := $(patsubst %.cpp,%.o,$(CPP_FILES))
O_FILES = $(addprefix $(BIN_DIR)/, $(patsubst %.cpp,%.o,$(CPP_FILES)))
DEPEND_FILES = $(patsubst %.cpp,%.d,$(CPP_FILES))

H_FILES_PATH = include
LIB_H_FILES_PATH = $(H_FILES_PATH)/$(LIB_NAME)
INCLUDE_DIRS = -I$(H_FILES_PATH)



#
# Commands
#

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


# targets
.PHONY: all tags clobber clean

all:

tags:
	$(call cmd,cmd_tags)

clobber: clean
	$(Q)$(RM) -f *~ $(H_FILES_PATH)/*~ $(LIB_H_FILES_PATH)/*~ $(DEPEND_FILES)

clean:
	$(Q)$(RM) -f $(O_FILES) $(BIN_DIR)/$(LIB_FILE_NAME).so $(BIN_DIR)/$(LIB_FILE_NAME).so.$(VERSION_1) $(BIN_DIR)/$(LIB_FILE_NAME).so.$(VERSION)


# rules
$(BIN_DIR)/$(LIB_FILE_NAME).so.$(VERSION): $(O_FILES)
	$(call cmd,cmd_link)

$(BIN_DIR)/%.o: %.cpp
	$(call cmd,cmd_cc_d_o)

# include depends files
-include $(CPP_FILES:.cpp=.d)
