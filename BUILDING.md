Building

requirements

linux

git

curl

make

clang compatible build environment

android kernel build dependencies

source setup

    git clone --recurse-submodules YOUR_REPOSITORY_URL

    cd agate-ksun-susfs

    git -C KernelSU-Next apply ../patches/ksun-v3.2.0-legacy-agate.patch

firmware marker

    mkdir -p out/include/config/extra/firmware

    touch out/include/config/extra/firmware/dir.h

build

    ./build.sh agate

the final anykernel zip will be created in the source directory

the released build was tested with kernelsu next legacy manual hooks and susfs on xiaomi 11t agate
