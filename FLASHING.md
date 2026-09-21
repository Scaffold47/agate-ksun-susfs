Flashing

this build was tested on crdroid 12 10 for xiaomi 11t agate amber

use this at your own risk

a custom kernel can cause a bootloop soft brick data loss or other problems

before flashing

use an unlocked bootloader

keep the boot image from the exact rom build you are currently using

make sure fastboot works

make sure recovery works

know which slot is active

do not touch unrelated firmware partitions

installation

boot into recovery

open apply update

open apply from adb

sideload the kernel zip

reboot after installation finishes

rollback

if the device does not boot enter fastboot

restore the boot image from the exact rom build you were using

if you have a known working rescue slot you can also return to that slot

kernel problems do not require restoring nvram nvdata persist modem lk or other firmware partitions

never use random boot images from another rom version
