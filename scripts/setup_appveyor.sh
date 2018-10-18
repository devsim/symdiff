# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# Note: run this file using bash
CMAKE=/cygdrive/C/Program\ Files\ \(x86\)/CMake/bin/cmake.exe
SYMDIFF_CONFIG="appveyor"

#/usr/bin/mkdir -p win32
#(cd win32; "$CMAKE" -G "Visual Studio 14" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} ..)

/usr/bin/mkdir -p win64
(cd win64; "$CMAKE" -G "Visual Studio 15 2017 Win64" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} -DTCLMAIN=ON -DPYTHON3=ON ..)
#(cd win64; "$CMAKE" -G "Visual Studio 14 Win64" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} -DTCLMAIN=ON ..)

libpath=`/usr/bin/cygpath -w $PWD/lib`

python2path='c:\Miniconda-x64\python'
#echo $libpath
/usr/bin/mkdir -p bin
/usr/bin/cat << EOF > bin/symdiff.bat
@setlocal
@echo off
SET PATH=c:\\Miniconda-x64;c:\\Miniconda-x64\\Library\\bin;%PATH%
SET PYTHONPATH=$libpath
$python2path %*
EOF
/usr/bin/chmod +x bin/symdiff.bat

python3path='c:\Miniconda36-x64\python'
/usr/bin/cat << EOF > bin/symdiff_py3.bat
@setlocal
@echo off
SET PATH=c:\\Miniconda36-x64;c:\\Miniconda36-x64\\Library\\bin;%PATH%
SET PYTHONIOENCODING=utf-8
SET PYTHONPATH=$libpath
$python3path %*
EOF
/usr/bin/chmod +x bin/symdiff_py3.bat

# TCLLIBPATH must always use forward slashes
libpath=`/usr/bin/cygpath -m $PWD/lib`
/usr/bin/cat << EOF > bin/symdiff_tcl.bat
@setlocal
@echo off
SET PATH=c:\\Miniconda-x64;c:\\Miniconda-x64\\Library\\bin;%PATH%
SET TCLLIBPATH="$libpath" %TCLLIBPATH%
tclsh %*
EOF
/usr/bin/chmod +x bin/symdiff_tcl.bat

