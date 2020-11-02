# $ sudo –i
# make
# ls
# insmod test.ko
# rmmod test
# less /var/log/kern.log | tail -5

KVERS = $(shell uname -r)

obj-m += test.o
test-objs := t1.o t2.o   # 列出所有目标文件

build: kernel_modules

kernel_modules:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) clean
