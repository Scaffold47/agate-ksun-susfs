# Xiaomi 11T Agate Kernel

This is the kernel I use on my own Xiaomi 11T. I built it because I wanted a setup I could understand, rebuild and recover myself instead of depending on random prebuilts.

The current build combines KernelSU Next legacy with manual hooks and SusFS support. It was built from source and tested on my own device before being shared here.

## Current build

**Device:** Xiaomi 11T

**Codename:** agate / amber

**ROM:** crDroid 12.10

**Android:** 16

**Kernel:** Linux 4.14.336

**KernelSU Next:** 3.2.0 legacy

**Hook mode:** Manual

**SusFS:** 1.5.5

## Current status

The kernel boots normally on my test device. KernelSU root works, manual hooks are active and SusFS initializes correctly during boot.

SusFS userspace communication was also tested after boot and the kernel reports SusFS 1.5.5 as initialized.

## Important

Use this at your own risk. Flashing a custom kernel can cause bootloops, soft bricks, data loss or other problems.

This build was tested on the configuration shown above. Other ROMs, Android versions and firmware bases have not been tested yet.

Always keep a working boot image from the exact ROM build you are using. Make sure fastboot and recovery both work before flashing anything.

A kernel problem should not require touching firmware, nvram, nvdata, persist, modem or lk. If you do not know how to recover a failed boot, do not flash this build.

## Building

Build instructions are available in [BUILDING.md](BUILDING.md)

The repository keeps KernelSU Next as a submodule and stores the local compatibility changes in the patches directory so the setup can be reproduced from source.

## Flashing and rollback

Installation and recovery notes are available in [FLASHING.md](FLASHING.md)

Keep your original boot image somewhere safe before testing the kernel.

## Source notes

The kernel source is based on the Xiaomi MT6893 development tree.

KernelSU Next is integrated through the legacy branch with manual hooks. SusFS support is integrated into the 4.14 kernel tree together with the userspace communication bridge needed by the current setup.

No stock boot images, firmware dumps, nvram backups or personal device data are included in this repository.

## Credits

Thanks to Xiaomi MT6893 Dev, KernelSU Next, simonpunk, the SusFS contributors, devnoname120, rio004, ziad1101 and everyone who worked on the agate kernel and device trees.

Built and tested by Scaffold47
