//原作者JiangNight  源码存在严重问题 加载格机 重启  黑砖    加载失败  kernel pacni 各种问题
//泪心已经彻底修复优化
	//printk(KERN_INFO "[TearGame] QQ: 2254013571\n");
	//printk(KERN_INFO "[TearGame] Email: tearhacker@outlook.com\n");
//printk(KERN_INFO "[TearGame] Telegram: t.me/TearGame\n");
	//(KERN_INFO "[TearGame] GitHub: github.com/tearhacker\n");
	//原项目链接 https://github.com/Jiang-Night/Kernel_driver_hack
	//泪心驱动完整开源读写内核源码新项目链接 https://github.com/tearhacker/TearGame_KernelDriver_Android_WriteReadMemory

#include "memory.h"
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/sched/mm.h>
#include <linux/pid.h>

bool read_process_memory(pid_t pid, uintptr_t addr, void *buffer, size_t size)
{
	struct task_struct *task;
	struct pid *pid_struct;
	int bytes_read;
	void *kbuf;

	if (size == 0 || size > (1024 * 1024)) // 限制最大1MB
		return false;

	pid_struct = find_get_pid(pid);
	if (!pid_struct)
		return false;

	task = get_pid_task(pid_struct, PIDTYPE_PID);
	put_pid(pid_struct);
	if (!task)
		return false;

	kbuf = kmalloc(size, GFP_KERNEL);
	if (!kbuf) {
		put_task_struct(task);
		return false;
	}

	bytes_read = access_process_vm(task, addr, kbuf, size, FOLL_FORCE);
	put_task_struct(task);

	if (bytes_read != size) {
		kfree(kbuf);
		return false;
	}

	if (copy_to_user(buffer, kbuf, size)) {
		kfree(kbuf);
		return false;
	}

	kfree(kbuf);
	return true;
}

bool write_process_memory(pid_t pid, uintptr_t addr, void *buffer, size_t size)
{
	struct task_struct *task;
	struct pid *pid_struct;
	int bytes_written;
	void *kbuf;

	if (size == 0 || size > (1024 * 1024)) // 限制最大1MB
		return false;

	pid_struct = find_get_pid(pid);
	if (!pid_struct)
		return false;

	task = get_pid_task(pid_struct, PIDTYPE_PID);
	put_pid(pid_struct);
	if (!task)
		return false;

	kbuf = kmalloc(size, GFP_KERNEL);
	if (!kbuf) {
		put_task_struct(task);
		return false;
	}

	if (copy_from_user(kbuf, buffer, size)) {
		kfree(kbuf);
		put_task_struct(task);
		return false;
	}

	bytes_written = access_process_vm(task, addr, kbuf, size, FOLL_FORCE | FOLL_WRITE);
	put_task_struct(task);
	kfree(kbuf);

	return (bytes_written == size);
}
