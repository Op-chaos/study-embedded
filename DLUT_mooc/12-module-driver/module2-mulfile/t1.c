#include <linux/init.h>
#include <linux/module.h>

int init_module(void)
{
    printk(KERN_ALERT "Hi,hello world\n");
    return 0;
}

MODULE_LICENSE("GPL v2");
