# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
CMAKE="/usr/bin/cmake"
CXX="/usr/bin/g++"
CC="/usr/bin/gcc"
TCL_ARCHIVE="/usr/lib/libtclstub.a"
TCL_INCLUDE="/usr/include/tcl8.5"
TCL_BIN="/usr/bin/tclsh8.5"
PYTHON_ARCHIVE="/usr/lib/libpython2.7.so"
PYTHON_INCLUDE="/usr/include/python2.7"
PYTHON_BIN="/usr/bin/python"
for TYPE in debug release; do
ARCH=`uname -m`
#  for ARCH in i386 x86_64; do
    NAME=linux_${ARCH}_${TYPE}
    mkdir ${NAME}
    (cd $NAME; ${CMAKE} -DCMAKE_OSX_ARCHITECTURES="i386;x86_64" -DCMAKE_BUILD_TYPE=${TYPE} -DCMAKE_CXX_COMPILER=${CXX} -DCMAKE_C_COMPILER=${CC} -DPYTHON_INCLUDE=${PYTHON_INCLUDE} -DPYTHON_ARCHIVE=${PYTHON_ARCHIVE} -DPYTHON_BIN=${PYTHON_BIN} -DTCL_INCLUDE=${TCL_INCLUDE} -DTCL_ARCHIVE=${TCL_ARCHIVE} -DTCL_BIN=${TCL_BIN}  ..)
#  done
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

cat << EOF > bin/symdiff_tcl
#!/bin/bash
set -e
progname="\$0"
curdir=\`dirname "\$progname"\`
export TCLLIBPATH=\${curdir}/../lib
${TCL_BIN} \$*
EOF
chmod +x bin/symdiff_tcl

