#include <linux/init.h>
#include <linux/module.h>   // .ko为生成的内核模块文件

int init_module(void) // 加载
{
    printk(KERN_ALERT "hello world!\n");  // 内核空间输出函数
    return 0;
}

void cleanup_module(void) // 卸载
{
    printk(KERN_ALERT "goodbye world!\n");
}

MODULE_LICENSE("GPL v2");  // 许可证声明
