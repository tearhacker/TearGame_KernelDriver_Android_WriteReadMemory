#include <linux/module.h>
#include <linux/tty.h>
#include <linux/miscdevice.h>
#include "comm.h"
#include "memory.h"
#include "process.h"
//原作者JiangNight  源码存在严重问题 加载格机 重启  黑砖    加载失败  kernel pacni 各种问题
//泪心已经彻底修复优化
	//printk(KERN_INFO "[TearGame] QQ: 2254013571\n");
	//printk(KERN_INFO "[TearGame] Email: tearhacker@outlook.com\n");
//printk(KERN_INFO "[TearGame] Telegram: t.me/TearGame\n");
	//(KERN_INFO "[TearGame] GitHub: github.com/tearhacker\n");

	//原项目链接 https://github.com/Jiang-Night/Kernel_driver_hack
	//泪心驱动完整开源读写内核源码新项目链接 https://github.com/tearhacker/TearGame_KernelDriver_Android_WriteReadMemory

#define DEVICE_NAME "TearGame"

int dispatch_open(struct inode *node, struct file *file)
{
	return 0;
}

int dispatch_close(struct inode *node, struct file *file)
{
	return 0;
}

long dispatch_ioctl(struct file *const file, unsigned int const cmd, unsigned long const arg)
{
	static COPY_MEMORY cm;
	static MODULE_BASE mb;
	static char key[0x100] = {0};
	static char name[0x100] = {0};
	static bool is_verified = false;

	if (cmd == OP_INIT_KEY && !is_verified)
	{
		if (copy_from_user(key, (void __user *)arg, sizeof(key) - 1) != 0)
		{
			return -1;
		}
	}
	switch (cmd)
	{
	case OP_READ_MEM:
	{
		if (copy_from_user(&cm, (void __user *)arg, sizeof(cm)) != 0)
		{
			return -1;
		}
		if (read_process_memory(cm.pid, cm.addr, cm.buffer, cm.size) == false)
		{
			return -1;
		}
		break;
	}
	case OP_WRITE_MEM:
	{
		if (copy_from_user(&cm, (void __user *)arg, sizeof(cm)) != 0)
		{
			return -1;
		}
		if (write_process_memory(cm.pid, cm.addr, cm.buffer, cm.size) == false)
		{
			return -1;
		}
		break;
	}
	case OP_MODULE_BASE:
	{
		if (copy_from_user(&mb, (void __user *)arg, sizeof(mb)) != 0 || copy_from_user(name, (void __user *)mb.name, sizeof(name) - 1) != 0)
		{
			return -1;
		}
		mb.base = get_module_base(mb.pid, name);
		if (copy_to_user((void __user *)arg, &mb, sizeof(mb)) != 0)
		{
			return -1;
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

struct file_operations dispatch_functions = {
	.owner = THIS_MODULE,
	.open = dispatch_open,
	.release = dispatch_close,
	.unlocked_ioctl = dispatch_ioctl,
};

struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dispatch_functions,
};

int __init driver_entry(void)
{
	int ret;
	printk(KERN_INFO "=============================================\n");
	printk(KERN_INFO "[TearGame] Driver loading...\n");
	printk(KERN_INFO "[TearGame] Author: 泪心 (Tear)\n");
	printk(KERN_INFO "[TearGame] QQ: 2254013571\n");
	printk(KERN_INFO "[TearGame] Email: tearhacker@outlook.com\n");
	printk(KERN_INFO "[TearGame] Telegram: t.me/TearGame\n");
	printk(KERN_INFO "[TearGame] GitHub: github.com/tearhacker\n");
	printk(KERN_INFO "=============================================\n");
	
	ret = misc_register(&misc);
	if (ret == 0) {
		printk(KERN_INFO "[TearGame] Device registered: /dev/%s\n", DEVICE_NAME);
		printk(KERN_INFO "[TearGame] Driver loaded successfully!\n");
	} else {
		printk(KERN_ERR "[TearGame] Failed to register device! ret=%d\n", ret);
	}
	return ret;
}

void __exit driver_unload(void)
{
	printk(KERN_INFO "[TearGame] Driver unloading...\n");
	misc_deregister(&misc);
	printk(KERN_INFO "[TearGame] Device /dev/%s unregistered\n", DEVICE_NAME);
	printk(KERN_INFO "[TearGame] Goodbye! - by 泪心\n");
}

module_init(driver_entry);
module_exit(driver_unload);

MODULE_DESCRIPTION("TearGame Memory Driver - t.me/TearGame");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("泪心 QQ:2254013571");
