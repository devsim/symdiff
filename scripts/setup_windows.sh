# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# Note: run this file using bash
CMAKE=/cygdrive/C/Program\ Files\ \(x86\)/CMake/bin/cmake.exe
SYMDIFF_CONFIG="win32"

/usr/bin/mkdir -p win32
(cd win32; "$CMAKE" -G "Visual Studio 14" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} ..)

/usr/bin/mkdir -p win64
(cd win64; "$CMAKE" -G "Visual Studio 14 Win64" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} ..)

libpath=`/usr/bin/cygpath -w $PWD/lib`
#echo $libpath
/usr/bin/mkdir -p bin
/usr/bin/cat << EOF > bin/symdiff.bat
@setlocal
@echo off
SET PYTHONPATH=$libpath;%PYTHONPATH%
python %*
EOF
/usr/bin/chmod +x bin/symdiff.bat

# TCLLIBPATH must always use forward slashes
libpath=`/usr/bin/cygpath -m $PWD/lib`
/usr/bin/cat << EOF > bin/symdiff_tcl.bat
@setlocal
@echo off
SET TCLLIBPATH="$libpath" %TCLLIBPATH%
tclsh %*
EOF
/usr/bin/chmod +x bin/symdiff_tcl.bat

