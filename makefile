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
BUILD_ROOT := build

# List of files in the tools dir. These files
# will be assumed to be ready-to-compile.
BUILD_TOOLS := $(shell find project/tools -type f)

build: $(BUILD_ROOT)/.hash $(BUILD_ROOT)/bin $(BUILD_ROOT)/plugins
.PHONEY: build

clean:
> rm -rf $(BUILD_ROOT)
.PHONEY: clean

$(BUILD_ROOT)/.hash: $(BUILD_TOOLS)
> @ # Execute in silence.
> build_root=$(@D)
> mkdir -p $${build_root}
> echo "$$(pwgen -1As)" > $${build_root}/.hash

$(BUILD_ROOT)/bin:
> @[ -d $(@D)/bin ] || mkdir -p $(@D)/bin

$(BUILD_ROOT)/plugins:
> @[ -d $(@D)/plugins ] || mkdir -p $(@D)/plugins
