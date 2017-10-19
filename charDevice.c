#include <linux/module.h>    // all kernel modules
#include <linux/kernel.h>    // for log infos
#include <linux/init.h>      // __init and __exit macros
#include <linux/device.h>
#include <linux/fs.h>

MODULE_AUTHOR("Watters");
MODULE_DESCRIPTION("Assn2 Part C char device driver module");

static int majorNumber = 0;
static const char device_name[] = "mytimeCharDriver";
static struct file_operations simple_fops = { .owner = THIS_MODULE, .read = device_read, };

int register_device(void) 
{
	int result = 0;
	printk(KERN_NOTICE "mytimeCharDriver: register_device() has been called\n");
	result = register_chrdev(0, device_name, &simple_fops);
	if (result < 0) {
		printk(KERN_WARNING "mytimeCharDriver: failed to register device with error = %i\n", result);
		return result;
	}
	majorNumber = result;
	printk(KERN_NOTICE "mytimeCharDriver: registered with major number = %i\n", majorNumber);
	return 0;
}

void unregister_device(void)
{
	printk(KERN_NOTICE "mytimeCharDriver: unregister_device() is called" );
	if(majorNumber != 0)
	{
      		unregister_chrdev(majorNumber, device_name);
	}
}

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
