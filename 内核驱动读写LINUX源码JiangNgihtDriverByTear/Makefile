#
# TearGame Driver Makefile
#

# 模块名称 - 使用 obj-m 编译为可加载模块
obj-m := TearGame.o

# 多文件模块，指定组成模块的目标文件
TearGame-objs := entry.o memory.o process.o

# 内核源码目录
KDIR ?= $(HOME)/gki-kernel/common
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm64 LLVM=1 LLVM_IAS=1 modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm64 LLVM=1 clean
	rm -f *.ko *.o *.mod *.mod.c .*.cmd modules.order Module.symvers

.PHONY: all clean
