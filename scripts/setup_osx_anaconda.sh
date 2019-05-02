# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
CMAKE="cmake"
CMAKE_CXX_FLAGS=""
CXX="/usr/bin/g++"
CC="/usr/bin/gcc"
TCL_ARCHIVE="/usr/lib/libtclstub8.5.a"
TCL_INCLUDE="/usr/include"
TCL_BIN="${HOME}/anaconda/bin/tclsh8.6"
PYTHON_ARCHIVE="${HOME}/anaconda/lib/libpython2.7.dylib"
PYTHON_INCLUDE="${HOME}/anaconda/include/python2.7"
PYTHON_BIN="${HOME}/anaconda/bin/python"
PYTHON3_ARCHIVE="${HOME}/anaconda/envs/python36/lib/libpython3.6m.dylib"
PYTHON3_INCLUDE="${HOME}/anaconda/envs/python36/include/python3.6m"
PYTHON3_BIN="${HOME}/anaconda/envs/python36/bin/python"
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
        -DPYTHON3_INCLUDE=${PYTHON3_INCLUDE}  \
        -DPYTHON3_ARCHIVE=${PYTHON3_ARCHIVE}  \
        -DPYTHON3_BIN=${PYTHON3_BIN}  \
        -DTCL_INCLUDE=${TCL_INCLUDE}  \
        -DTCL_ARCHIVE=${TCL_ARCHIVE}  \
        -DTCL_BIN=${TCL_BIN} \
        -DPYTHON3=ON \
        ..)
done
mkdir -p bin

cat << EOF > bin/symdiff
#!/bin/bash
set -e
progname="\$0"
curdir=\`dirname "\$progname"\`
export PYTHONPATH=\${curdir}/../lib
${PYTHON_BIN} \$*
EOF
chmod +x bin/symdiff

cat << EOF > bin/symdiff_py3
#!/bin/bash
set -e
progname="\$0"
curdir=\`dirname "\$progname"\`
export PYTHONPATH=\${curdir}/../lib
${PYTHON3_BIN} \$*
EOF
chmod +x bin/symdiff_py3

cat << EOF > bin/symdiff_tcl
#!/bin/bash
set -e
progname="\$0"
curdir=\`dirname "\$progname"\`
export TCLLIBPATH=\${curdir}/../lib
${TCL_BIN} \$*
EOF
chmod +x bin/symdiff_tcl

