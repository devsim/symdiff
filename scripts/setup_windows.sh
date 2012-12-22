# Any copyright is dedicated to the Public Domain.
# http://creativecommons.org/publicdomain/zero/1.0/
CMAKE=/cygdrive/C/Program\ Files\ \(x86\)/CMake\ 2.8/bin/cmake.exe

mkdir -p win32/src/tclcomp/Release
mkdir -p win32/src/tclcomp/Debug
rsync -rv --exclude .svn lib win32/src/tclcomp/
(cd win32; "$CMAKE" -G "Visual Studio 10" ..)
rsync -rv --exclude .svn lib win32/tclcomp/


