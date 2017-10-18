#include <linux/module.h>    // all kernel modules
#include <linux/kernel.h>    // for log infos
#include <linux/init.h>      // __init and __exit macros

MODULE_AUTHOR("Watters");
MODULE_DESCRIPTION("Assn2 Part C char device driver module");

static int __init device_init(void)
{
    printk(KERN_INFO "Starting up char device module!\n");
    // Non-zero return means module couldn't be loaded
    return 0;
}

static void __exit device_cleanup(void)
{
    printk(KERN_INFO "Cleaning up char device module.\n");
}

module_init(device_init);
module_exit(device_cleanup);
