#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <linux/kernel.h>
#include <linux/types.h>

bool read_process_memory(pid_t pid, uintptr_t addr, void *buffer, size_t size);
bool write_process_memory(pid_t pid, uintptr_t addr, void *buffer, size_t size);

#endif /* _MEMORY_H_ */
//原作者JiangNight  源码存在严重问题 加载格机 重启  黑砖    加载失败  kernel pacni 各种问题
//泪心已经彻底修复优化
	//printk(KERN_INFO "[TearGame] QQ: 2254013571\n");
	//printk(KERN_INFO "[TearGame] Email: tearhacker@outlook.com\n");
//printk(KERN_INFO "[TearGame] Telegram: t.me/TearGame\n");
	//(KERN_INFO "[TearGame] GitHub: github.com/tearhacker\n");
	//原项目链接 https://github.com/Jiang-Night/Kernel_driver_hack
	//泪心驱动完整开源读写内核源码新项目链接 https://github.com/tearhacker/TearGame_KernelDriver_Android_WriteReadMemory
