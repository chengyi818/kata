/*=============================================================================
#     FileName: hello.c
#         Desc: my char driver
#       Author: ChengYi
#        Email: chengyi818@foxmail.com
#     HomePage:
#      Created: 2017-02-16 19:12:05
#      Version: 0.0.1
#   LastChange: 2017-02-16 19:12:05
#      History:
#               0.0.1 | ChengYi | init
=============================================================================*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void) {
    printk(KERN_ALERT "I bear a charmed life.\n");
    return 0;
}

static void hello_exit(void) {
    printk(KERN_ALERT "Out, out, brief candle!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("chengyi");
MODULE_DESCRIPTION("A Hello, world module");
