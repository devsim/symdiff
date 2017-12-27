# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
CMAKE="cmake"
CMAKE_CXX_FLAGS=""
CXX="/usr/bin/g++"
CC="/usr/bin/gcc"
TCL_ARCHIVE="/usr/lib/libtclstub8.5.a"
TCL_INCLUDE="/usr/include"
TCL_BIN="/usr/bin/tclsh8.5"
PYTHON_ARCHIVE="${HOME}/anaconda/lib/libpython2.7.dylib"
PYTHON_INCLUDE="${HOME}/anaconda/include/python2.7"
PYTHON_BIN="${HOME}/anaconda/bin/python"
#-DCMAKE_OSX_ARCHITECTURES="i386;x86_64" \
for TYPE in debug release; do
    NAME=osx_${TYPE}
    mkdir ${NAME}
    (cd $NAME; ${CMAKE} \
        -DCMAKE_CXX_FLAGS:STRING="${CMAKE_CXX_FLAGS}" \
        -DCMAKE_BUILD_TYPE=${TYPE}  \
        -DCMAKE_CXX_COMPILER=${CXX}  \
        -DCMAKE_C_COMPILER=${CC}  \
        -DPYTHON_INCLUDE=${PYTHON_INCLUDE}  \
        -DPYTHON_ARCHIVE=${PYTHON_ARCHIVE}  \
        -DPYTHON_BIN=${PYTHON_BIN}  \
        -DTCL_INCLUDE=${TCL_INCLUDE}  \
        -DTCL_ARCHIVE=${TCL_ARCHIVE}  \
        -DTCL_BIN=${TCL_BIN} \
        ..)
done
mkdir -p bin

cat << EOF > bin/symdiff
#!/bin/bash
set -e
progname="\$0"
curdir=\`dirname "\$progname"\`
export DYLD_LIBRARY_PATH=\${curdir}/../lib
export PYTHONPATH=\${curdir}/../lib
${PYTHON_BIN} \$*
EOF
chmod +x bin/symdiff

cat << EOF > bin/symdiff_tcl
#!/bin/bash
set -e
progname="\$0"
curdir=\`dirname "\$progname"\`
export DYLD_LIBRARY_PATH=\${curdir}/../lib
export TCLLIBPATH=\${curdir}/../lib
${TCL_BIN} \$*
EOF
chmod +x bin/symdiff_tcl

