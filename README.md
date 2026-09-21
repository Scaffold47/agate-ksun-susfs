Xiaomi 11T Agate Kernel

this is the kernel build i use on my own xiaomi 11t

the goal is to have a kernel that i can build myself modify myself and recover without depending on random prebuilt kernels

current build

xiaomi 11t

agate amber

crdroid 12 10

android 16

linux 4 14 336

kernelsu next 3 2 0 legacy

manual hooks

susfs 1 5 5

current status

boots normally

kernelsu root works

manual hooks work

susfs initializes during boot

susfs userspace communication works

tested on my own device before publishing

important

use this at your own risk

flashing a custom kernel can cause bootloops soft bricks data loss or other problems

this build was tested only on the configuration listed above

do not assume that it will work on another rom another android version another firmware base or another device

always keep a working boot image from the exact rom build you are using

make sure your bootloader is unlocked before doing anything

know how to enter fastboot and recovery before flashing

do not flash firmware nvram nvdata persist modem lk or other unrelated partitions because of a kernel problem

if you do not know how to recover a failed boot then do not flash this kernel

building

clone the source

initialize the kernelsu next submodule

apply the kernelsu compatibility patch from the patches directory

build with agate defconfig

the included build script produces an anykernel flashable zip

credits

xiaomi mt6893 dev

kernelsu next

simonpunk susfs

devnoname120

rio004

ziad1101

everyone who worked on the agate kernel and device trees

built and tested by Scaffold47
