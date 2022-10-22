#!/bin/bash
set -e

if [ "${1}" = "gcc" ]
  then
  # try to fix build error
  #export HOMEBREW_NO_INSTALL_CLEANUP=1
  #brew update > /dev/null;
  #if brew ls --versions gcc > /dev/null;
  #then
  #brew outdated gcc || brew upgrade gcc;
  #else
  ## the overwrite is to fix the linking issue seen on travis ci
  #brew install gcc || brew link --overwrite gcc;
  #fi
  export CMAKE="cmake"
  export CMAKE_CXX_FLAGS=""
  export CC=/usr/local/bin/gcc-9;
  export CXX=/usr/local/bin/g++-9;
  export F77=/usr/local/bin/gfortran-9;
#  brew unlink gcc && brew link gcc

  # https://github.com/Microsoft/LightGBM/pull/1560
  # removes symlink
  #rm -f '/usr/local/include/c++'
  # fix "fatal error: _stdio.h: No such file or directory"
# try moving to osx_image: xcode10.1
#  sudo softwareupdate -i "Command Line Tools (macOS High Sierra version 10.13) for Xcode-9.3"

elif [ "${1}" = "clang" ]
  then
  export CMAKE="cmake"
  export CMAKE_CXX_FLAGS=""
  export CC=/usr/bin/gcc;
  export CXX=/usr/bin/g++;
  export F77="";
else
  echo "ERROR: FIRST ARGUMENT MUST BE gcc OR clang";
  exit 1;
fi


#minimal conda environments to prevent linking against the wrong libraries
if [ "${1}" = "gcc" ]
then
# now opt for explicit dll load of mkl
conda create  -y --name python3_symdiff_build python=3 cmake nomkl
fi

#This version does not use pardiso
if [ "${1}" = "clang" ]
then
conda create  -y --name python3_symdiff_build python=3 cmake nomkl
fi
source activate python3_symdiff_build

export PYTHON3_BIN=python
export PYTHON3_INCLUDE=$(python -c "from sysconfig import get_paths as gp; print(gp()['include'])")
export PYTHON3_ARCHIVE=""

# SYMDIFF build
if [ "${1}" = "gcc" ]
then
(bash scripts/symdiff_macos.sh && cd osx_release && make -j4 && make test)
elif [ "${1}" = "clang" ]
then
(bash  scripts/symdiff_macos.sh && cd osx_release && make -j4 && make test)
fi

(rsync -avP --exclude __pycache__ lib/symdiff bdist_wheel/)
(rsync -avP --exclude __pycache__ LICENSE NOTICE README.md examples doc bdist_wheel)
(cd bdist_wheel && pip wheel .)
(mv bdist_wheel/*.whl .)



