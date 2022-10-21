#!/bin/bash
set -e

# Centos Specific
#https://fedoraproject.org/wiki/EPEL
#yum install -y git bison flex zlib-static zlib-devel sqlite-devel python3 python3-devel
#yum install -y centos-release-scl
#yum install -y devtoolset-9-gcc devtoolset-9-gcc-c++ devtoolset-9-libquadmath-devel devtoolset-9-gcc-gfortran make
#yum install -y epel-release
#yum install -y cmake3
yum install -y bison flex rsync

export CMAKE="cmake"
export CMAKE_CXX_FLAGS=""
export CXX="g++"

export PYTHON3_BIN=python3.7
export PIP_BIN=/opt/python/cp37-cp37m/bin/pip
${PIP_BIN} install wheel auditwheel
export PYTHON3_INCLUDE=$(${PYTHON3_BIN} -c "from sysconfig import get_paths as gp; print(gp()['include'])")
export PYTHON3_ARCHIVE=""

# SYMDIFF build
(bash scripts/symdiff_centos.sh && cd linux_x86_64_release && make -j2 && make test);
(rsync -avP --exclude __pycache__ lib/symdiff bdist_wheel/)
(rsync -avP --exclude __pycache__ LICENSE NOTICE README.md README examples doc bdist_wheel)
(cd bdist_wheel && ${PIP_BIN} wheel .)
(cd bdist_wheel && auditwheel repair *.whl)
(mv bdist_wheel/wheelhouse/*.whl .)

