# Configure the shell used for this makefile.
SHELL := bash

# Use one shell for whole process instead of a
# new shell for every new line/instruction.
.ONESHELL:

# Configures the shell such that it will do the
# following:
# -e: fail and exit when sub-command fails
# -u: fail when undefined variable names are
# used.
# -o pipefail: prevents errors in a pipeline from
# being masked. If any command in a pipeline
# fails, the return-code of the pipeline is the
# failing return-code.
.SHELLFLAGS := -eu -o pipefail -c

# Deletes the target file if its rule fails. Will
# ensure it'll properly re-run the failed rule.
.DELETE_ON_ERROR:

# Alerts the user if some variable name has not
# been defined.
MAKEFLAGS += --warn-undefined-variables

# No black magic.
MAKEFLAGS += --no-builtin-rules

# Sets the .RECIPEPREFIX to a custom string.
# .RECIPEPREFIX explains newline behavior for
# instructions belonging to a rule.
ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please Use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

# Compiler configuration.
CCOMPILER := gcc
CCOMPILER_ARGS := 

# Root directory of build/distribution.
BUILD_ROOT := dist

# Root directory of project scripts.
SCRIPTS_ROOT := project/scripts

# Root directory of project tool files.
TOOLS_ROOT :=project/tools

# List of files in the tools dir. These files
# will be assumed to be ready-to-compile.
BUILD_TOOLS := $(shell find $(TOOLS_ROOT) -type f)


build: $(BUILD_ROOT)/.hash structure config
.PHONEY: build


# Remove build objects.
clean:
> rm -rf $(BUILD_ROOT)
.PHONEY: clean


# Sentinel. Generates a hash file as a build
# stamp.
$(BUILD_ROOT)/.hash: $(BUILD_TOOLS)
> @ # Execute in silence.
> mkdir -p $(@D)
> echo "$$(pwgen -1As)" > $(@D)/.hash


# Generates distribution config file(s).
config:
> @
> [ -f $(BUILD_ROOT)/.config ] || $(SCRIPTS_ROOT)/initconfig.bash $(BUILD_ROOT) .config


# Generates the internal structure of the
# distribution.
structure:
> @
> [ -d $(BUILD_ROOT)/bin ] || mkdir -p $(BUILD_ROOT)/bin
> [ -d $(BUILD_ROOT)/plugins ] || mkdir -p $(BUILD_ROOT)/plugins
