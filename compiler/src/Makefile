include ../Makefile.macros


TOP_DIR = ..
INCLUDE_DIRS = -I$(TOP_DIR)/$(GEN_DIR) -I.

LIB_FILES =  $(addprefix $(TOP_DIR)/, $(O_FILES))

# targets
.PHONY: all bin tags classes doc clean clobber

all:
	$(MAKE) -C $(TOP_DIR) all

tags:
	$(MAKE) -C $(TOP_DIR) tags

classes:
	$(MAKE) -C $(TOP_DIR) classes

doc:
	$(MAKE) -C $(TOP_DIR) doc

clobber:
	$(MAKE) -C $(TOP_DIR) clobber

clean:
	$(MAKE) -C $(TOP_DIR) clean


# rules
$(PROG_NAME): $(LIB_FILES)

$(TOP_DIR)/$(LIB_DIR)/%.o: $(TOP_DIR)/$(GEN_DIR)/%.c
	$(CPP) -c $(CFLAGS) $(INCLUDE_DIRS) $< -o $@

$(TOP_DIR)/$(LIB_DIR)/%.o: %.cpp
	$(CPP) -c $(CFLAGS) $(INCLUDE_DIRS) $< -o $@

$(TOP_DIR)/$(GEN_DIR)/%.d: $(TOP_DIR)/$(GEN_DIR)/%.c
	$(CPP) -MM $(CFLAGS) $(INCLUDE_DIRS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(TOP_DIR)/$(LIB_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.d: %.cpp
	$(CPP) -MM $(CFLAGS) $(INCLUDE_DIRS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(TOP_DIR)/$(LIB_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# include depends files
include $(addprefix $(TOP_DIR)/$(GEN_DIR)/, $(C_FILES:.c=.d))
include $(CPP_FILES:.cpp=.d)
