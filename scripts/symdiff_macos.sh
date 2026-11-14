# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
for TYPE in debug release; do
    NAME=osx_${TYPE}
    mkdir ${NAME}
    (cd $NAME; ${CMAKE} \
        ${ARCH_ARG} \
        -DCMAKE_CXX_FLAGS:STRING="${CMAKE_CXX_FLAGS}" \
        -DCMAKE_BUILD_TYPE=${TYPE} \
        -DCMAKE_CXX_COMPILER=${CXX} \
        -DPYTHON3=ON \
        -DPYTHON3_INCLUDE=${PYTHON3_INCLUDE} \
        -DPYTHON3T=ON \
        -DPYTHON3T_INCLUDE=${PYTHON3T_INCLUDE} \
        -DTCLMAIN=OFF \
        ..)
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

cat << EOF > bin/symdiff_py3
#!/bin/bash
set -e
progname="\$0"
curdir=\`dirname "\$progname"\`
export PYTHONPATH=\${curdir}/../lib
${PYTHON3_BIN} \$*
EOF
chmod +x bin/symdiff_py3

#cat << EOF > bin/symdiff_tcl
##!/bin/bash
#set -e
#progname="\$0"
#curdir=\`dirname "\$progname"\`
#export TCLLIBPATH=\${curdir}/../lib
#${TCL_BIN} \$*
#EOF
#chmod +x bin/symdiff_tcl

