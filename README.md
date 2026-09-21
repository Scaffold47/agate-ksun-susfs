# Hydrogen Kernel for Xiaomi 11T (agate)

This repository contains the kernel build I use on my own Xiaomi 11T. The aim is simple: keep the source, the KernelSU integration, the build process and the recovery path under my control instead of depending on random prebuilt kernels.

It is still an agate-specific kernel tree. The reusable KernelSU work lives separately in my KernelSU-Next fork so it can be maintained without tying it to one device.

## Current status

The current branch has been tested on a Xiaomi 11T with the following setup:

- Device: Xiaomi 11T
- Codename: agate
- Kernel tree: Linux 4.14.336
- ROM used for testing: crDroid 12.10 / Android 16
- KernelSU Next: legacy, built-in, manual hooks
- KernelSU userspace compatibility: UAPI 4
- SUSFS: v1.5.5, NON-GKI

The kernel currently boots normally on my device, KernelSU root works, manual hooks work, SUSFS initializes correctly, and the SUSFS userspace queries used by KernelSU Next Manager 3.4.0 work.

## KernelSU integration

KernelSU-Next is kept as a git submodule:

- Fork: https://github.com/Scaffold47/KernelSU-Next
- Branch: `legacy-uapi4-susfs-compat`

That branch contains the reusable compatibility work for older built-in/manual-hook kernels. The agate tree only carries the device/kernel integration around it.

The current compatibility work includes:

- UAPI 3 scoped su-session file descriptor support
- post-exec task_work handling for legacy 4.14 exec flow
- UAPI 4 userspace compatibility
- legacy SELinux hide fixes
- SUSFS v1.5.5 compatibility with the KernelSU Next 3.4 reboot ABI
- correct built-in runtime reporting without pretending to be a bundled LKM build

This is intentionally a backport on top of the legacy KernelSU line, not a wholesale merge of the current development branch.

## Reproducible build

The published tree has been tested from a completely fresh clone with a fresh submodule checkout and an empty output directory.

Clone it with the submodule:

```bash
git clone --branch agate-ksun-susfs --recurse-submodules \
  https://github.com/Scaffold47/agate-ksun-susfs.git

cd agate-ksun-susfs
```

Build:

```bash
./build.sh agate
```

The build script uses Proton Clang 15 and creates an AnyKernel3 flashable zip named similar to:

```text
HydrogenKernel-agate-YYYYMMDD-HHMM.zip
```

A clean-clone build was verified after publishing the current source. The firmware dependency in the old 4.14 build system was also fixed so a successful build no longer depends on generated files left behind by an older working tree.

## Submodule behavior

The repository pins KernelSU-Next to an exact gitlink commit. The branch entry in `.gitmodules` documents the branch that is maintained for this integration, but a normal `--recurse-submodules` clone checks out the exact commit recorded by the kernel tree.

This is intentional. Updating the compatibility branch does not silently change an already published kernel snapshot.

## Flashing and recovery

This is a custom kernel. Flashing it can cause a bootloop, soft brick, data loss or other problems if it is used on the wrong base or if recovery is not prepared in advance.

Before flashing:

- keep a known-working boot image from the exact ROM build currently installed
- make sure the bootloader is unlocked
- know how to enter fastboot and recovery
- have a working ADB/fastboot environment available
- do not touch firmware, NVRAM, NVDATA, persist, modem, LK or unrelated partitions to recover from a kernel-only problem

This source has been tested on my own setup. Do not assume it will work unchanged on another ROM, Android version, firmware base or device.

## Repository scope

Device-specific work belongs here:

- Xiaomi 11T / agate kernel source
- device defconfig
- MediaTek/Xiaomi kernel integration
- firmware build handling
- build and packaging scripts
- agate-specific KernelSU integration points

Generic KernelSU compatibility work belongs in the separate KernelSU-Next fork:

https://github.com/Scaffold47/KernelSU-Next/tree/legacy-uapi4-susfs-compat

That separation is deliberate. It keeps the reusable legacy KernelSU work useful outside this one device tree while keeping this repository honest about what is actually agate-specific.

## Credits

This work builds on code and research from many projects and developers, including:

- Xiaomi MT6893 device/kernel developers
- KernelSU Next contributors
- SUSFS by simonpunk
- devnoname120
- rio004
- ziad1101
- everyone who has contributed to the agate/amber kernel and device trees

Built, tested and maintained for my own device by Scaffold47.
