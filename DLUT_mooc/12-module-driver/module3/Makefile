# $ sudo –i
# make
# insmod normal.ko number=123
# insmod test.ko
# lsmod
# less /var/log/kern.log
# rmmod test   // 需要先卸载依赖模块
# rmmod normal
KVERS = $(shell uname -r)

obj-m += normal.o

build: kernel_modules

kernel_modules:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) clean
