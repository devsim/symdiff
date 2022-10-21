#!/bin/bash
set -e
docker run -it -d --name manylinux2014 quay.io/pypa/manylinux2014_x86_64 &&
(cd .. && tar czf symdiff.tgz symdiff && docker cp symdiff.tgz manylinux2014:/root/) &&
docker exec manylinux2014 bash -c "git config --global --add safe.directory /root/symdiff"
docker exec manylinux2014 bash -c "cd /root && tar xzf symdiff.tgz";
docker exec manylinux2014 bash -c "cd /root/symdiff && bash scripts/build_manylinux2014.sh";
(for i in $(docker exec manylinux2014 bash -c "ls /root/symdiff/*.whl"); do docker cp manylinux2014:${i} .; done)
docker stop manylinux2014
