# Include the configuration file.
include make.conf

# Define unset macros for use in source.
CFLAGS += 								 \
	-DV_SOURCE_DIR="\"$(PROJECT_ROOT)\"" \
	-DV_DEBUG_MODE=$(CDEBUG)

BLD_SOURCE_FILES := $(wildcard $(SRC_ROOT)/*.c)
BLD_OBJECT_FILES := $(BLD_SOURCE_FILES:$(SRC_ROOT)/%.c=$(BLD_ROOT)/objs/%.o)
BLD_DEPEND_FILES := $(BLD_OBJECT_FILES:.o=.d)

# Include all dependency files in makefile.
-include $(BLD_DEPEND_FILES)

all: build
.PHONEY: all

clean:
> rm -rf $(BLD_ROOT)
.PHONEY: clean

build: $(BLD_ROOT) $(BLD_ROOT)/.hash
.PHONEY: build

$(BLD_ROOT)/.hash: $(BLD_SOURCE_FILES) $(BLD_ROOT)/bin/mserver
> @echo "generate hash sentinel..."
> mkdir -p $(@D)
> echo "$$(pwgen -1As)" > $(@D)/.hash

$(BLD_ROOT)/bin/mserver: $(BLD_OBJECT_FILES)
> @echo "compile binary from objects..."
> $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BLD_ROOT):
> @[ -d $@/objs ] || mkdir -p $@/objs
> @[ -d $@/bin ] || mkdir -p $@/bin

$(BLD_ROOT)/objs/%.o: $(SRC_ROOT)/%.c
> @echo "building $$(basename -- $@)..."
> $(CC) $(CFLAGS) -o $@ -c $<
