# Include the configuration file.
include make.conf

# Define unset macros for use in this build.
# Setting this outside of `make.conf` as these
# values are project specific and most likely
# won't translate well to other projects.
CFLAGS += 								 \
	-DV_SOURCE_DIR="\"$(PROJECT_ROOT)\"" \
	-DV_DEBUG_MODE=$(CDEBUG)

# Required build files and dependencies.
BLD_SOURCE_FILES := 				\
	$(wildcard $(SRC_ROOT)/*.c) 	\
	$(wildcard $(SRC_ROOT)/lib/*.c)
BLD_OBJECT_FILES := $(BLD_SOURCE_FILES:$(SRC_ROOT)/%.c=$(BLD_ROOT)objs/%.o)
BLD_DEPEND_FILES := $(BLD_OBJECT_FILES:.o=.d)

# Include all dependency files in makefile.
-include $(BLD_DEPEND_FILES)


all: build
.PHONEY: all

clean:
> rm -rf $(BLD_ROOT)
.PHONEY: clean

build: $(BLD_ROOT).hash $(INST_ROOT)mserver
.PHONEY: build

# Generate the primary sentinel file.
$(BLD_ROOT).hash: $(BLD_OBJECT_FILES)
> @echo "generate hash sentinel..."
> mkdir -p $(@D)
> echo "$$(pwgen -1As)" > $@

# Builds executable binary from object files.
$(INST_ROOT)mserver: $(BLD_OBJECT_FILES)
> @echo "compile binary from objects..."
> [ -d $(@D) ] || mkdir -p $(@D)
> $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Builds object files from related source files.
$(BLD_ROOT)objs/%.o: $(SRC_ROOT)%.c
> @echo "building '$(*F)'..."
> @[ -d $(@D) ] || mkdir -p $(@D)
> $(CC) $(CFLAGS) -o $@ -c $<

# Builds the target library from source. This is
# assuming that the source is built using
# autotools.
$(BLD_ROOT)%.libhash: $(BLD_ROOT) $(shell find $(INC_ROOT)% -type f)
> dist_root=$(INC_ROOT)$*/$(INC_DISTNAME)

> @[ -d $$dist_root ] || mkdir $$dist_root
> cd $$dist_root
> $$dist_root/../configure

> echo "Library $*: building lib..."
> $(MAKE) -C $$dist_root

> echo "Library $*: generating hash sentinel..."
> echo "$$(pwgen -1As)" > $@
