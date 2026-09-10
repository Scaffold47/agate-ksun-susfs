# Building

This repository contains the kernel source used for the public Xiaomi 11T agate build

The tested build uses KernelSU Next legacy with manual hooks and SusFS 1 5 5

## Requirements

A Linux system with git curl make ccache and the usual Android kernel build dependencies is recommended

The build script uses Proton Clang 15 and downloads it automatically to the toolchains directory in your home folder if it is not already there

## Clone the source

```bash
git clone --recurse-submodules https://github.com/Scaffold47/agate-ksun-susfs.git
cd agate-ksun-susfs
```

KernelSU Next is kept as a submodule and the local compatibility changes are stored as a patch

Apply the patch before building

```bash
git -C KernelSU-Next apply ../patches/ksun-v3.2.0-legacy-agate.patch
```

## Prepare the tree

This kernel tree expects one generated firmware config marker that may be missing on a fresh build directory

```bash
mkdir -p out/include/config/extra/firmware
touch out/include/config/extra/firmware/dir.h
```

## Build

```bash
./build.sh agate
```

Do not use the old ksu build flag from the original Hydrogen script

KernelSU Next is already integrated into this source and the tested public build was made without that flag

When the build finishes successfully the script creates an AnyKernel flashable zip in the source directory

## Notes

The public build was tested on Xiaomi 11T agate with crDroid 12 10 and Android 16

The current source uses Linux 4 14 336 KernelSU Next 3 2 0 legacy manual hooks and SusFS 1 5 5

A successful compile does not guarantee compatibility with another ROM firmware base or Android version
