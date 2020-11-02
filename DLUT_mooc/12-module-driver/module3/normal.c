#include <linux/init.h>
#include <linux/module.h>

static int number = 100;   // 定义模块参数
module_param(number, int, S_IRUGO);  // module_param这是一个宏，并名number是一个模块参数，可以被修改

// __init 进行系统优化：如果这个模块不是动态加载方式加载到内核中，而是直接编译到内核，
// 一旦加载之后，就会把模块加载函数的空间释放掉，以提升系统性能
static int __init normal_init(void)  // 自定义的模块加载函数名normal_init
{
    printk(KERN_INFO "the number is: %d\n", number);
    return 0;
}
module_init(normal_init);   // 对性的模块加载函数说明
// __exit进行系统优化：如果这个模块不是动态加载方式加载到内核中，而是直接编译到内核，
// 一旦加载之后，那么该模块不存在卸载，次函数不起作用，直接忽视掉，以提升系统性能
static void __exit normal_exit(void)
{
    printk(KERN_INFO "module normal finished!\n");
}
module_exit(normal_exit);

void justatry(void)  // 自定义函数
{
	printk(KERN_INFO "just a try!\n");
}

EXPORT_SYMBOL_GPL(justatry);  // 进行声明，表明这个函数可以被内核和内核模块使用

MODULE_LICENSE("GPL v2");
