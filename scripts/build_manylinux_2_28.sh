#!/bin/bash
set -e
set -u
export DEVSIM_ARCH=$(uname -m)
yum install -y bison flex rsync

export CMAKE="cmake"
export CMAKE_CXX_FLAGS=""
export CXX="g++"
export PYTHON3_BIN="${PYTHON3_BIN:-/opt/python/cp315-cp315/bin/python}"
export PIP_BIN=pip

${PYTHON3_BIN} -mvenv venv
source ./venv/bin/activate
${PIP_BIN} install wheel auditwheel
export PYTHON3_INCLUDE=$(${PYTHON3_BIN} -c "from sysconfig import get_paths as gp; print(gp()['include'])")
export PYTHON3_ARCHIVE=""
export PYTHON3T_INCLUDE="${PYTHON3T_INCLUDE:-${PYTHON3_INCLUDE}}"
export PYTHON3T_ARCHIVE=${PYTHON3T_ARCHIVE:-}

# SYMDIFF build
(bash scripts/symdiff_centos.sh && cd linux_${DEVSIM_ARCH}_release && make -j2 && make test);



mkdir -p stage/symdiff
cp lib/symdiff/__init__.py stage/symdiff
rsync -aP bdist_wheel/ stage
rsync -aP CHANGES.md CITATION.cff CITATION.md doc examples LICENSE NOTICE README.md stage

mkdir -p dist
for ABI in abi3 abi3t; do
    mkdir -p dist_${ABI}
    rsync -aP --exclude __pycache__ --exclude "*.so" stage/ dist_${ABI}
    cp linux_$(uname -m)_release/src/pycomp/symdiff_py3.${ABI}.so dist_${ABI}/symdiff
    STAGING_DIR="dist_${ABI}"
    SYMDIFF_WHEEL_ABI="${ABI}" "${PYTHON3_BIN}" -m pip wheel --no-deps --wheel-dir dist "./${STAGING_DIR}"
done
auditwheel repair dist/*.whl
mv wheelhouse/*.whl .
