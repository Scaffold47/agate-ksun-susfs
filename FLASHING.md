# Flashing

This build was tested on crDroid 12.10 with Android 16 on the Xiaomi 11T agate and amber device family.

Use it at your own risk. A custom kernel can cause a bootloop, soft brick, data loss or other problems if something goes wrong.

## Before flashing

Your bootloader must already be unlocked.

Keep a copy of the boot image from the exact ROM build you are using. Make sure both fastboot and recovery work before you start, and know which slot is active on your device.

Do not flash unrelated firmware partitions while testing this kernel.

## Installation

Boot into recovery and open the update menu.

Choose Apply from ADB, then sideload the kernel zip from your computer.

```bash
adb sideload your_kernel_file.zip
```

When the installation finishes, reboot normally.

The included AnyKernel package repacks the current boot image and replaces the kernel while keeping the existing ramdisk layout.

## Rollback

If the device does not boot, enter fastboot and restore the boot image from the exact ROM build you were using.

If you already have a known working rescue slot, switching back to that slot is also an option.

A kernel problem should not require restoring nvram, nvdata, persist, modem, lk or other firmware partitions.

Do not use a random boot image from another ROM or another version. The safest rollback image is always the one from your exact installed ROM build.
