#!/bin/bash

THIS_SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
# readlink resolves path
KRXIMPEXP=`readlink -f $THIS_SCRIPT_DIR"/../../"`

echo 'Script directory: '$THIS_SCRIPT_DIR
echo 'Source directory: '$KRXIMPEXP

g++ \
    -I $KRXIMPEXP'/src/Meta/'    \
    -I $KRXIMPEXP'/src/MetaCpp/' \
    -I $KRXIMPEXP'/src/tstl/'    \
    -I $KRXIMPEXP'/src/gfx/'     \
    $KRXIMPEXP'/src/wxImpExpUI/'*.cpp \
    `wx-config --cxxflags` `wx-config --libs`

