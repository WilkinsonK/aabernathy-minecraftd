#!/bin/bash

# Exits if incorrect number of arguments passed
# this script.
if [[ $# < 2 ]]; then
    echo "recieved $# arguments, expected 2."
    exit 1
fi

# Generates a configuration file usable in the
# distributable location.
CONF_ROOT=$1
CONF_PATH=$CONF_ROOT/$2


# Exit with error if dist directory does not
# exist.
if [ ! -d $CONF_ROOT ]; then
    echo "no directory '${CONF_ROOT}' found."
    exit 1
fi

# Exit with error if config file exists. Avoid
# any overwrites.
if [ -f $CONF_PATH ]; then
    echo "no file '${CONF_PATH}' found."
    exit 1
fi


touch $CONF_PATH

# First rule. Dir root of tool executables.
echo $(pwd)/$CONF_ROOT/bin >> $CONF_PATH
