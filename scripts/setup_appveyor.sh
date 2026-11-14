# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# Note: run this file using bash
set -e
set -u
set -x
export PATH="/mingw64/bin:/usr/bin:${PATH}"
CMAKE=$(cygpath -w $(which cmake) )
CTEST=$(cygpath -w $(which ctest) )
SYMDIFF_CONFIG="appveyor"

if [ "$1" = x64 ]; then
GENERATOR="Visual Studio 18 2026"
AOPTION="x64"
BUILDDIR="win64"
TOOLSET="v145"
elif [ "$1" = clangx64 ]; then
GENERATOR="Visual Studio 18 2026"
AOPTION="x64"
BUILDDIR="clangwin64"
TOOLSET="ClangCL"
else
echo "Must specify x86 or x64 or clangx64"
exit -1
fi

export PYTHON3_BIN="${PYTHON3_BIN:-python}"
case "${PYTHON3_BIN}" in
    [A-Za-z]:\\*) export PYTHON3_BIN=$(cygpath -u "${PYTHON3_BIN}");;
esac
#export PYTHON3_INCLUDE=$(cygpath -w $(dirname $(find ${CONDA_PREFIX} -iname python3.lib | head -n 1)))
#export PYTHON3_ARCHIVE=$(cygpath -w $(find ${CONDA_PREFIX} -iname python3.lib | head -n 1))
export PYTHON3_INCLUDE=$(${PYTHON3_BIN} -c "import sysconfig; print(sysconfig.get_path('include'))")
export PYTHON3T_INCLUDE=${PYTHON3_INCLUDE}
export PYTHON3_ARCHIVE=$(${PYTHON3_BIN} -c "import sysconfig; import os; print(os.path.join(sysconfig.get_config_var('LIBDIR'),'python3.lib'))")
export PYTHON3T_ARCHIVE=$(${PYTHON3_BIN} -c "import sysconfig; import os; print(os.path.join(sysconfig.get_config_var('LIBDIR'),'python3t.lib'))")

mkdir -p ${BUILDDIR}
(
cd ${BUILDDIR};
"${CMAKE}" -G "${GENERATOR}" \
-A "${AOPTION}" \
-T "${TOOLSET}" \
-DTCLMAIN=OFF \
-DPYTHON3=ON  \
-DPYTHON3_INCLUDE=${PYTHON3_INCLUDE} \
-DPYTHON3_ARCHIVE=${PYTHON3_ARCHIVE} \
-DPYTHON3T=ON  \
-DPYTHON3T_INCLUDE=${PYTHON3T_INCLUDE} \
-DPYTHON3T_ARCHIVE=${PYTHON3T_ARCHIVE} \
..
)

libpath=`cygpath -w ${PWD}/lib`

mkdir -p bin
cat << EOF > bin/symdiff_py3.bat
@setlocal
@echo off
SET PYTHONIOENCODING=utf-8
SET PYTHONPATH=$libpath
python %*
EOF
chmod +x bin/symdiff_py3.bat

## TCLLIBPATH must always use forward slashes
#libpath=`/usr/bin/cygpath -m $PWD/lib`
#cat << EOF > bin/symdiff_tcl.bat
#@setlocal
#@echo off
#SET PATH=${CONDA_PREFIX};${CONDA_PREFIX}\\Library\\bin;%PATH%
#SET TCLLIBPATH="$libpath" %TCLLIBPATH%
#tclsh %*
#EOF
#chmod +x bin/symdiff_tcl.bat



# The // is so that MSYS does not consider it a path
(cd ${BUILDDIR} && ${CMAKE} --build . --config Release -- //m //nologo //verbosity:minimal)

(cd lib/symdiff && cp symdiff_py3_abi3.pyd symdiff_py3.pyd)

(cd ${BUILDDIR} && ${CTEST} --verbose)


mkdir -p stage/symdiff
cp lib/symdiff/__init__.py stage/symdiff
rsync -aP bdist_wheel/ stage
rsync -aP LICENSE NOTICE README.md examples doc stage

mkdir -p dist
for ABI in abi3 abi3t; do
    mkdir -p dist_${ABI}
    rsync -aP --exclude __pycache__ stage/ dist_${ABI}
    cp lib/symdiff/symdiff_py3_${ABI}.pyd dist_${ABI}/symdiff/symdiff_py3.pyd
    SYMDIFF_WHEEL_ABI="${ABI}" "${PYTHON3_BIN}" -m pip wheel --no-deps \
        --wheel-dir dist ./dist_${ABI}
done
