# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# Note: run this file using bash
set -e
export PATH="/mingw64/bin:/usr/bin:${PATH}"
CMAKE=$(cygpath -w $(which cmake) )
CTEST=$(cygpath -w $(which ctest) )
SYMDIFF_CONFIG="appveyor"

if [ "$1" = x86 ]; then
GENERATOR="Visual Studio 18 2026"
AOPTION="Win32"
BUILDDIR="win32"
TOOLSET="v143"
elif [ "$1" = x64 ]; then
GENERATOR="Visual Studio 18 2026"
AOPTION="x64"
BUILDDIR="win64"
TOOLSET="v143"
elif [ "$1" = clangx64 ]; then
GENERATOR="Visual Studio 18 2026"
AOPTION="x64"
BUILDDIR="clangwin64"
TOOLSET="ClangCL"
else
echo "Must specify x86 or x64 or clangx64"
exit -1
fi

export PYTHON3_BIN=python
#export PYTHON3_INCLUDE=$(cygpath -w $(dirname $(find ${CONDA_PREFIX} -iname python3.lib | head -n 1)))
#export PYTHON3_ARCHIVE=$(cygpath -w $(find ${CONDA_PREFIX} -iname python3.lib | head -n 1))
export PYTHON3_INCLUDE=$(${PYTHON3_BIN} -c "import sysconfig; print(sysconfig.get_path('include'))")
export PYTHON3_ARCHIVE=$(cygpath -w ${CONDA_PREFIX}/libs/python3.lib)

mkdir -p ${BUILDDIR}
(cd ${BUILDDIR}; "${CMAKE}" -G "${GENERATOR}" -A "${AOPTION}" -T "${TOOLSET}" -DANACONDA_PATH="${CONDA_PREFIX}" -DTCLMAIN=OFF -DPYTHON3=ON -DPYTHON3_INCLUDE=${PYTHON3_INCLUDE} -DPYTHON3_ARCHIVE=${PYTHON3_ARCHIVE} ..)

libpath=`cygpath -w ${PWD}/lib`

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

(rsync -avP --exclude __pycache__ lib/symdiff bdist_wheel/)
(rsync -avP --exclude __pycache__ LICENSE NOTICE README.md examples doc bdist_wheel)
pip install --upgrade wheel
(cd bdist_wheel && pip wheel .)
mkdir -p dist
(mv bdist_wheel/*.whl dist)
