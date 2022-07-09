# Include the configuration file.
include make.conf

# Define unset macros for use in this build.
# Setting this outside of `make.conf` as these
# values are project specific and most likely
# won't translate well to other projects.
CFLAGS += 								 \
	-DV_SOURCE_DIR="\"$(PROJECT_ROOT)\"" \
	-DV_DEBUG_MODE=$(CDEBUG)


all: build
.PHONEY: all

clean:
> rm -rf $(BLD_ROOT)
.PHONEY: clean

build: $(BLD_ROOT) $(BLD_ROOT).hash $(INST_ROOT)mserver
.PHONEY: build

# Prepare build distributable.
$(BLD_ROOT):
> @[ -d $@objs ] || mkdir -p $@objs
> @[ -d $@bin ] || mkdir -p $@bin

# Generate the primary sentinel file.
$(BLD_ROOT).hash: $(BLD_OBJECT_FILES)
> @echo "generate hash sentinel..."
> mkdir -p $(@D)
> echo "$$(pwgen -1As)" > $@

# Builds executable binary from object files.
$(INST_ROOT)mserver: $(BLD_OBJECT_FILES)
> @echo "compile binary from objects..."
> $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Builds object files from related source files.
$(BLD_ROOT)objs/%.o: $(SRC_ROOT)%.c
> @echo "building '$(*F)'..."
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
