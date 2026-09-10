// SPDX-License-Identifier: GPL-2.0
/* Compatibility bridge for the SUSFS v1.5.x userspace prctl protocol. */

#include <linux/cred.h>
#include <linux/string.h>
#include <linux/susfs.h>
#include <linux/uaccess.h>

#define KERNEL_SU_OPTION 0xDEADBEEF

extern bool is_ksu_domain(void);
extern bool is_zygote(const struct cred *cred);
#ifdef CONFIG_KSU_SUSFS_TRY_UMOUNT
extern void susfs_run_try_umount_for_current_mnt_ns(void);
#endif

bool susfs_is_current_ksu_domain(void)
{
	return is_ksu_domain();
}

bool susfs_is_current_zygote_domain(void)
{
	return is_zygote(current_cred());
}

static bool susfs_access_ok(const void __user *addr, unsigned long size)
{
	return access_ok(VERIFY_READ, addr, size);
}

static void susfs_put_error(unsigned long arg5, int error)
{
	int __user *result = (int __user *)arg5;

	if (susfs_access_ok(result, sizeof(error)) &&
	    copy_to_user(result, &error, sizeof(error)))
		pr_info("susfs: failed to copy command result\n");
}

static u64 susfs_enabled_features(void)
{
	u64 features = 0;

#ifdef CONFIG_KSU_SUSFS_SUS_PATH
	features |= BIT_ULL(0);
#endif
#ifdef CONFIG_KSU_SUSFS_SUS_MOUNT
	features |= BIT_ULL(1);
#endif
#ifdef CONFIG_KSU_SUSFS_AUTO_ADD_SUS_KSU_DEFAULT_MOUNT
	features |= BIT_ULL(2);
#endif
#ifdef CONFIG_KSU_SUSFS_AUTO_ADD_SUS_BIND_MOUNT
	features |= BIT_ULL(3);
#endif
#ifdef CONFIG_KSU_SUSFS_SUS_KSTAT
	features |= BIT_ULL(4);
#endif
#ifdef CONFIG_KSU_SUSFS_SUS_OVERLAYFS
	features |= BIT_ULL(5);
#endif
#ifdef CONFIG_KSU_SUSFS_TRY_UMOUNT
	features |= BIT_ULL(6);
#endif
#ifdef CONFIG_KSU_SUSFS_AUTO_ADD_TRY_UMOUNT_FOR_BIND_MOUNT
	features |= BIT_ULL(7);
#endif
#ifdef CONFIG_KSU_SUSFS_SPOOF_UNAME
	features |= BIT_ULL(8);
#endif
#ifdef CONFIG_KSU_SUSFS_ENABLE_LOG
	features |= BIT_ULL(9);
#endif
#ifdef CONFIG_KSU_SUSFS_HIDE_KSU_SUSFS_SYMBOLS
	features |= BIT_ULL(10);
#endif
#ifdef CONFIG_KSU_SUSFS_SPOOF_CMDLINE_OR_BOOTCONFIG
	features |= BIT_ULL(11);
#endif
#ifdef CONFIG_KSU_SUSFS_OPEN_REDIRECT
	features |= BIT_ULL(12);
#endif
#ifdef CONFIG_KSU_SUSFS_HAS_MAGIC_MOUNT
	features |= BIT_ULL(14);
#endif
	return features;
}

bool susfs_handle_prctl(int option, unsigned long arg2,
			unsigned long arg3, unsigned long arg4,
			unsigned long arg5, long *result)
{
	int error = 0;
	(void)arg4;

	if ((u32)option != KERNEL_SU_OPTION)
		return false;

	*result = 0;
	if (current_uid().val != 0)
		return true;

	switch (arg2) {
#ifdef CONFIG_KSU_SUSFS_SUS_PATH
	case CMD_SUSFS_ADD_SUS_PATH:
		if (!susfs_access_ok((void __user *)arg3,
				     sizeof(struct st_susfs_sus_path)))
			error = -EFAULT;
		else
			error = susfs_add_sus_path((void __user *)arg3);
		break;
#endif
#ifdef CONFIG_KSU_SUSFS_SUS_MOUNT
	case CMD_SUSFS_ADD_SUS_MOUNT:
		if (!susfs_access_ok((void __user *)arg3,
				     sizeof(struct st_susfs_sus_mount)))
			error = -EFAULT;
		else
			error = susfs_add_sus_mount((void __user *)arg3);
		break;
#endif
#ifdef CONFIG_KSU_SUSFS_SUS_KSTAT
	case CMD_SUSFS_ADD_SUS_KSTAT:
	case CMD_SUSFS_ADD_SUS_KSTAT_STATICALLY:
		if (!susfs_access_ok((void __user *)arg3,
				     sizeof(struct st_susfs_sus_kstat)))
			error = -EFAULT;
		else
			error = susfs_add_sus_kstat((void __user *)arg3);
		break;
	case CMD_SUSFS_UPDATE_SUS_KSTAT:
		if (!susfs_access_ok((void __user *)arg3,
				     sizeof(struct st_susfs_sus_kstat)))
			error = -EFAULT;
		else
			error = susfs_update_sus_kstat((void __user *)arg3);
		break;
#endif
#ifdef CONFIG_KSU_SUSFS_TRY_UMOUNT
	case CMD_SUSFS_ADD_TRY_UMOUNT:
		if (!susfs_access_ok((void __user *)arg3,
				     sizeof(struct st_susfs_try_umount)))
			error = -EFAULT;
		else
			error = susfs_add_try_umount((void __user *)arg3);
		break;
	case CMD_SUSFS_RUN_UMOUNT_FOR_CURRENT_MNT_NS:
		susfs_run_try_umount_for_current_mnt_ns();
		break;
#endif
#ifdef CONFIG_KSU_SUSFS_SPOOF_UNAME
	case CMD_SUSFS_SET_UNAME:
		if (!susfs_access_ok((void __user *)arg3,
				     sizeof(struct st_susfs_uname)))
			error = -EFAULT;
		else
			error = susfs_set_uname((void __user *)arg3);
		break;
#endif
#ifdef CONFIG_KSU_SUSFS_ENABLE_LOG
	case CMD_SUSFS_ENABLE_LOG:
		if (arg3 > 1)
			error = -EINVAL;
		else
			susfs_set_log(arg3 == 1);
		break;
#endif
#ifdef CONFIG_KSU_SUSFS_SPOOF_CMDLINE_OR_BOOTCONFIG
	case CMD_SUSFS_SET_CMDLINE_OR_BOOTCONFIG:
		if (!susfs_access_ok((void __user *)arg3,
				     SUSFS_FAKE_CMDLINE_OR_BOOTCONFIG_SIZE))
			error = -EFAULT;
		else
			error = susfs_set_cmdline_or_bootconfig((void __user *)arg3);
		break;
#endif
#ifdef CONFIG_KSU_SUSFS_OPEN_REDIRECT
	case CMD_SUSFS_ADD_OPEN_REDIRECT:
		if (!susfs_access_ok((void __user *)arg3,
				     sizeof(struct st_susfs_open_redirect)))
			error = -EFAULT;
		else
			error = susfs_add_open_redirect((void __user *)arg3);
		break;
#endif
	case CMD_SUSFS_SHOW_VERSION:
		if (!susfs_access_ok((void __user *)arg3, sizeof(SUSFS_VERSION)))
			error = -EFAULT;
		else if (copy_to_user((void __user *)arg3, SUSFS_VERSION,
				      sizeof(SUSFS_VERSION)))
			error = -EFAULT;
		break;
	case CMD_SUSFS_SHOW_ENABLED_FEATURES: {
		u64 features = susfs_enabled_features();
		if (!susfs_access_ok((void __user *)arg3, sizeof(features)))
			error = -EFAULT;
		else if (copy_to_user((void __user *)arg3, &features,
				      sizeof(features)))
			error = -EFAULT;
		break;
	}
	case CMD_SUSFS_SHOW_VARIANT:
		if (!susfs_access_ok((void __user *)arg3, sizeof(SUSFS_VARIANT)))
			error = -EFAULT;
		else if (copy_to_user((void __user *)arg3, SUSFS_VARIANT,
				      sizeof(SUSFS_VARIANT)))
			error = -EFAULT;
		break;
	default:
		error = -EINVAL;
		break;
	}

	susfs_put_error(arg5, error);
	return true;
}
