# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# Note: run this file using bash
CMAKE=/cygdrive/C/Program\ Files\ \(x86\)/CMake/bin/cmake.exe
SYMDIFF_CONFIG="win32"

mkdir -p win32
(cd win32; "$CMAKE" -G "Visual Studio 14" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} ..)

mkdir -p win64
(cd win64; "$CMAKE" -G "Visual Studio 14 Win64" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} ..)

#libpath=`cygpath -w $PWD/lib`
#PYTHON_BIN="C:\Python27\python.exe"
##echo $libpath
#mkdir -p bin
#cat << EOF > bin/symdiff.bat
#@setlocal
#@echo off
#SET PATH="$libpath";%PATH%
#SET PYTHONPATH="$libpath";%PYTHONPATH%
#${PYTHON_BIN} %*
#EOF
#chmod +x bin/symdiff.bat
##
##cat << EOF > bin/symdiff_tcl
###!/bin/bash
##set -e
##progname="\$0"
##curdir=\`dirname "\$progname"\`
##export TCLLIBPATH=\${curdir}/../lib
##${TCL_BIN} \$*
##EOF
##chmod +x bin/symdiff_tcl
##
