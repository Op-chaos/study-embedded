#include <linux/init.h>
#include <linux/module.h>

void cleanup_module(void)
{
    printk(KERN_ALERT "Hi goodbye world!\n");
}

MODULE_LICENSE("GPL v2");
