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

#
# directories
#
GEN_DIR   = $(LONG_DIR_NAME)/gen
SRC_DIR   = $(LONG_DIR_NAME)/src
TOOLS_DIR = $(LONG_DIR_NAME)/../lib/include
DOC_DIR   = $(LONG_DIR_NAME)/doc
BIN_DIR   = $(LONG_DIR_NAME)/bin

BUILD_DIRS = $(SRC_DIR)



# files
GRAMMAR_FILE = ttcn3.g
PARSER_C_FILE := $(patsubst %.g,%Parser.c,$(GRAMMAR_FILE))
PARSER_H_FILE := $(patsubst %.g,%Parser.h,$(GRAMMAR_FILE))
LEXER_C_FILE := $(patsubst %.g,%Lexer.c,$(GRAMMAR_FILE))
LEXER_H_FILE := $(patsubst %.g,%Lexer.h,$(GRAMMAR_FILE))
C_FILES = $(PARSER_C_FILE) $(LEXER_C_FILE)
GEN_FILES = $(C_FILES) $(PARSER_H_FILE) $(LEXER_H_FILE) $(patsubst %.g,%.tokens,$(GRAMMAR_FILE))


#
# defines
#
INCLUDE_DIRS = -I$(GEN_DIR) -I$(SRC_DIR) -I$(TOOLS_DIR)


# macros
O_FILES = $(addprefix $(BIN_DIR)/, $(patsubst %.c,%.o,$(C_FILES)))
DEPEND_FILES = $(addprefix $(BIN_DIR)/, $(patsubst %.c,%.d,$(C_FILES)))
GEN_FILES_PATH = $(addprefix $(GEN_DIR)/, $(GEN_FILES))


# targets
.PHONY: all install clean distclean tags doc linktools

all: $(BIN_DIR)/$(TRANSLATOR_NAME)

generate: $(GEN_FILES_PATH)

compile: $(O_FILES) linktools
	@$(call cmd,cmd_make,$(SRC_DIR))

install:
	@$(call cmd,cmd_translator_install)

clean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_clean,$(dir)))
	$(Q)$(RM) -f $(O_FILES) $(DEPEND_FILES) $(GEN_FILES_PATH) $(SRC_DIR)/exception.cpp

distclean: clean
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_distclean,$(dir)))
	$(Q)$(RM) -f $(BIN_DIR)/*~
	$(Q)$(RM) -f $(GEN_DIR)/*~
	$(Q)$(RM) -rf $(DOC_DIR)/html

tags: linktools
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_tags,$(dir)))

doc:
	$(Q)$(SED) -i -e 's/\(PROJECT_NUMBER.*=\).*/\1 $(VERSION)/' doc/Doxyfile
	$(Q)$(DOXYGEN) $(DOC_DIR)/Doxyfile

linktools:
	@$(LN) -sf ../../lib/tools/exception.cpp $(SRC_DIR)/exception.cpp

# rules
$(BIN_DIR)/$(TRANSLATOR_NAME): generate compile

$(GEN_FILES_PATH): $(LONG_DIR_NAME)/$(GRAMMAR_FILE)
#$(GEN_DIR)/$(PARSER_C_FILE): $(GEN_DIR)/%Parser.c: $(LONG_DIR_NAME)/%.g
	@$(call cmd,cmd_antlr)

$(BIN_DIR)/%.o: $(GEN_DIR)/%.c
	@$(call cmd,cmd_cc_d_o)


# include depends files
-include $(addprefix $(BIN_DIR)/,$(C_FILES:.c=.d))
