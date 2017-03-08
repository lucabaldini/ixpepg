#!/bin/bash

# See this stackoverflow question
# http://stackoverflow.com/questions/59895/getting-the-source-directory-of-a-bash-script-from-within
# for the magic in this command
SETUP_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export IXPESWROOT=$SETUP_DIR
export IXPESWPYMODULES=$IXPESWROOT/ixpeswpy
export PYTHONPATH=$IXPESWROOT:$PYTHONPATH
export IXPEEXT=/home/alberto/xpe/ixpeExt

echo "IXPESWROOT set to " $IXPESWROOT
echo "IXPEEXT set to " $IXPEEXT

