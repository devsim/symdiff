# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# Note: run this file using bash
set -e
export PATH="/usr/bin:${PATH}"
CMAKE=$(cygpath -w $(which cmake) )
CTEST=$(cygpath -w $(which ctest) )
SYMDIFF_CONFIG="appveyor"

if [ "$1" = x86 ]; then
GENERATOR="Visual Studio 16 2019"
AOPTION="Win32"
BUILDDIR="win32"
elif [ "$1" = x64 ]; then
GENERATOR="Visual Studio 16 2019"
AOPTION="x64"
BUILDDIR="win64"
else
echo "Must specify x86 or x64"
exit -1
fi


mkdir -p ${BUILDDIR}
(cd ${BUILDDIR}; "${CMAKE}" -G "${GENERATOR}" -A "${AOPTION}" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} -DTCLMAIN=ON -DPYTHON3=ON -DANACONDA_PATH="${CONDA_PREFIX}" ..)

libpath=`cygpath -w ${PWD}/lib`

#echo $libpath
# TODO: fix to use conda activate
mkdir -p bin
cat << EOF > bin/symdiff_py3.bat
@setlocal
@echo off
SET PATH=${CONDA_PREFIX};${CONDA_PREFIX}\\Library\\bin;%PATH%
SET PYTHONIOENCODING=utf-8
SET PYTHONPATH=$libpath
python %*
EOF
chmod +x bin/symdiff_py3.bat

# TCLLIBPATH must always use forward slashes
libpath=`/usr/bin/cygpath -m $PWD/lib`
cat << EOF > bin/symdiff_tcl.bat
@setlocal
@echo off
SET PATH=${CONDA_PREFIX};${CONDA_PREFIX}\\Library\\bin;%PATH%
SET TCLLIBPATH="$libpath" %TCLLIBPATH%
tclsh %*
EOF
chmod +x bin/symdiff_tcl.bat



# The // is so that MSYS does not consider it a path
(cd ${BUILDDIR} && ${CMAKE} --build . --config Release -- //m //nologo //verbosity:minimal)

(cd ${BUILDDIR} && ${CTEST} --verbose)

