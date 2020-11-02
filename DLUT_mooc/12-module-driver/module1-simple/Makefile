# $ sudo –i
# make
# insmod hello.ko
# lsmod
# rmmod hello
# lsmod
# less /var/log/kern.log | tail -5    // printk 会将print信息输出到系统日志文件中

KVERS = $(shell uname -r)  # 将shell命令返回值赋给 KVERS
						   # uname -r 获得当前Linux版本号，进而获取内核源码树目录

obj-m += hello.o  # 以模块形式编译该程序

build: kernel_modules

kernel_modules:     # 编译规则
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) clean
