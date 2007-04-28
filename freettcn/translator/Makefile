include Makefile.macros


# targets
.PHONY: all generate compile tags classes doc lines clean clobber

all: $(PROG_NAME)

generate: $(GEN_DIR)/$(GRAMMAR_C_FILE) $(GEN_DIR)/$(LEX_C_FILE)

compile:
	$(MAKE) -C $(SRC_DIR) $(PROG_NAME)
	$(CPP) $(CFLAGS) $(O_FILES) -o $(PROG_NAME)

tags:
	etags --declarations --members $(GRAMMAR_FILE) $(LEX_FILE) $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h

classes:
	ebrowse -s $(SRC_DIR)/*.h $(SRC_DIR)/*.cpp

doc:
	doxygen Doxyfile

lines:
	wc -l `find . -type f`

clobber: clean
	rm -rf *~ $(GEN_DIR)/* $(SRC_DIR)/*.d $(SRC_DIR)/*~ TAGS BROWSE

clean:
	rm -rf $(LIB_DIR)/* $(PROG_NAME)


# rules
$(PROG_NAME): generate compile

$(GEN_DIR)/$(GRAMMAR_C_FILE): $(GEN_DIR)/%.tab.c: %.y
	cd $(GEN_DIR); $(BISON) $(TOP_DIR)/$<; cd -

$(GEN_DIR)/$(LEX_C_FILE): $(GEN_DIR)/%.yy.c: %.l
	cd $(GEN_DIR); $(FLEX) $(TOP_DIR)/$<; cd -
