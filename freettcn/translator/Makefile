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


include ../../Makefile.defines

#
# directories
#
GEN_DIR = gen
SRC_DIR = src
BUILD_DIRS = $(SRC_DIR)

BIN_DIR = bin


# files
GRAMMAR_FILE = ttcn3.g
PARSER_C_FILE := $(patsubst %.g,%Parser.c,$(GRAMMAR_FILE))
PARSER_H_FILE := $(patsubst %.g,%Parser.h,$(GRAMMAR_FILE))
LEXER_C_FILE := $(patsubst %.g,%Lexer.c,$(GRAMMAR_FILE))
LEXER_H_FILE := $(patsubst %.g,%Lexer.h,$(GRAMMAR_FILE))
C_FILES = $(PARSER_C_FILE) $(LEXER_C_FILE)
GEN_FILES = $(C_FILES) $(PARSER_H_FILE) $(LEXER_H_FILE) $(patsubst %.g,%.tokens,$(GRAMMAR_FILE))
GEN_FILES_PATH = $(addprefix $(GEN_DIR)/, $(GEN_FILES))


# macros
O_FILES = $(addprefix $(BIN_DIR)/, $(patsubst %.c,%.o,$(C_FILES)))
DEPEND_FILES = $(patsubst %.c,%.d,$(C_FILES))


# targets
.PHONY: all install clean distclean tags

all: $(BIN_DIR)/$(TRANSLATOR_NAME)

generate: $(GEN_DIR)/$(PARSER_C_FILE)

compile: $(O_FILES)
	@$(call cmd,cmd_make,$(SRC_DIR))

install:
	@$(call cmd,cmd_translator_install)

clean:
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_clean,$(dir)))
	$(Q)$(RM) -f $(O_FILES) $(DEPEND_FILES) $(GEN_FILES_PATH)

distclean: clean
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_distclean,$(dir)))
	$(Q)$(RM) -f $(BIN_DIR)/*~
	$(Q)$(RM) -f $(GEN_DIR)/*~

tags:
	@$(call cmd,cmd_tags_h)
	@$(foreach dir, $(BUILD_DIRS), $(call cmd,cmd_make_tags,$(dir)))



# rules
$(BIN_DIR)/$(TRANSLATOR_NAME): generate compile

$(GEN_DIR)/$(PARSER_C_FILE): $(GEN_DIR)/%Parser.c: %.g
	@$(call cmd,cmd_antlr)

$(BIN_DIR)/%.o: $(GEN_DIR)/%.c
	@$(call cmd,cmd_cc_d_o)


# include depends files
-include $(C_FILES:.c=.d)




#generate: $(GEN_DIR)/$(GRAMMAR_C_FILE) $(GEN_DIR)/$(LEX_C_FILE)

#compile:
#	$(MAKE) -C $(SRC_DIR) $(PROG_NAME)
#	$(CPP) $(CFLAGS) $(O_FILES) $(LIBS) -o $(PROG_NAME)

# tags:
#	etags --declarations --members $(GRAMMAR_FILE) $(LEX_FILE) $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h

# classes:
# 	ebrowse -s $(SRC_DIR)/*.h $(SRC_DIR)/*.cpp

# doc:
# 	doxygen Doxyfile

# lines:
# 	wc -l `find . -type f`

# clobber: clean
# 	rm -rf *~ $(GEN_DIR)/* $(SRC_DIR)/*.d $(SRC_DIR)/*~ TAGS BROWSE

# clean:
# 	rm -rf $(LIB_DIR)/* $(PROG_NAME)

#tags:
#	etags --declarations --members $(GRAMMAR_FILE) $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h



# $(GEN_DIR)/$(PARSER_C_FILE): $(GEN_DIR)/%Parser.c: %.g
# 	$(ANTLR) -o $(GEN_DIR) $<

#$(GEN_DIR)/$(GRAMMAR_C_FILE): $(GEN_DIR)/%.tab.c: %.y
#	cd $(GEN_DIR); $(BISON) $(TOP_DIR)/$<; cd -

#$(GEN_DIR)/$(LEX_C_FILE): $(GEN_DIR)/%.yy.c: %.l
#	cd $(GEN_DIR); $(FLEX) $(TOP_DIR)/$<; cd -
