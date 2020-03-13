EXTRA_CFLAGS = -Wa,--defsym,SPECIAL_WonderTradeGenerateMon=$(SPECIAL_WonderTradeGenerateMon)

EXTRA_ARMIPS_FLAGS = -equ SPECIAL_WonderTradeGenerateMon $(SPECIAL_WonderTradeGenerateMon)

# ------------------------------------------------------------------------------

# SRC_FILES = $(wildcard src/*.c)
SRC_OBJ_FILES = $(SRC_FILES:src/%.c=build/src/%.o)

DATA_FILES = $(wildcard data/*.s)
DATA_OBJ_FILES = $(DATA_FILES:data/%.s=build/data/%.o)

ifeq ($(INSERT_EXAMPLE_SCRIPT),false)
	OBJ_FILES = $(SRC_OBJ_FILES)
else
	OBJ_FILES = $(SRC_OBJ_FILES) $(DATA_OBJ_FILES)
endif

# ------------------------------------------------------------------------------

build/data/%.o: data/%.s charmap.txt
	@mkdir -p build/data
	(echo '#line 1 "$<"' && $(PREPROC) "$<" charmap.txt) | $(CC) $(CFLAGS) -x assembler-with-cpp -o "$@" -

build/dep/data/%.d: data/%.s
	@mkdir -p build/dep/data
	@$(SCANINC) -I "" $< | awk '{print "$(<:data/%.s=build/data/%.o) $@ : "$$0}' > "$@"
	
include $(DATA_FILES:data/%.s=build/dep/data/%.d)
