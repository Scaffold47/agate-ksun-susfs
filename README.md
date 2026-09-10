# Xiaomi 11T Agate Kernel

Custom kernel project for Xiaomi 11T agate and amber
Built for my own device and shared after testing
Focused on a reproducible KernelSU Next and SusFS setup

## Current build
Device Xiaomi 11T
Codename agate amber
ROM crDroid 12 10
Android 16
Kernel Linux 4 14 336
KernelSU Next 3 2 0 legacy
Hook mode manual
SusFS 1 5 5

## Working
Boot
KernelSU root
Manual hooks
SusFS kernel initialization
SusFS userspace communication

## Warning
Use this at your own risk
Custom kernels can cause bootloops soft bricks data loss or other problems
Only the setup above was tested
Keep the boot image from the exact ROM build you are using
Make sure fastboot and recovery work before flashing
Do not touch firmware nvram nvdata persist modem or lk because of a kernel problem
If you cannot recover a failed boot do not flash this build

## Build and flash
Build instructions are in BUILDING md
Flash and rollback instructions are in FLASHING md

## Source notes
Kernel source is based on the Xiaomi MT6893 development tree
KernelSU Next is kept as a submodule
Local KernelSU compatibility changes are stored in the patches directory
No stock boot images firmware dumps nvram backups or personal device data are included

## Credits
Xiaomi MT6893 Dev
KernelSU Next
simonpunk
SusFS contributors
devnoname120
rio004
ziad1101
everyone who worked on the agate kernel and device trees

Built and tested by Scaffold47
