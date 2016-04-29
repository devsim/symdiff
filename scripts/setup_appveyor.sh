# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/

# Note: run this file using bash
CMAKE=/cygdrive/C/Program\ Files\ \(x86\)/CMake/bin/cmake.exe
SYMDIFF_CONFIG="appveyor"

#mkdir -p win32
#(cd win32; "$CMAKE" -G "Visual Studio 14" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} ..)

mkdir -p win64
(cd win64; "$CMAKE" -G "Visual Studio 14 Win64" -DSYMDIFF_CONFIG=${SYMDIFF_CONFIG} -DTCLMAIN=ON ..)

