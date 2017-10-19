#include <linux/module.h>    // all kernel modules
#include <linux/kernel.h>    // for log infos
#include <linux/init.h>      // __init and __exit macros
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>     // copy_to_user() 
#include <linux/time.h>


MODULE_AUTHOR("Watters");
MODULE_DESCRIPTION("Assn2 Part C char device driver module");


static int majorNumber = 0;
static const char device_name[] = "mytimeCharDriver";
static struct file_operations simple_fops = { .owner = THIS_MODULE, .read = device_read, };

static ssize_t read(struct file *fptr, char __user *user_buffer, size_t count, loff_t *position)
{
	struct timespec ts1, ts2;
	getnstimeofday(&ts1);	
	ts2 = current_kernel_time();
	
	long int time1a = ts1.tv_sec * 1000000000UL;
	long int time1b = ts1.tv_nsec;
	long int time2a = ts2.tv_sec * 1000000000UL;
	long int time2b = ts2.tv_nsec;

	char* buffer = vmalloc(256);
	buffer = sprintf("current_kernel_time: %ld %ld\n getnstimeofday: %ld %ld\n", time1a, time1b, time2a, time2b);	
	
	if (copy_to_user(user_buffer, buffer, strlen(buffer)+1) != 0) {
		printk(KERN_ERR "copy_to_user() failed in mytimeCharDriver\n");
		return -EFAULT;
	}
	
	printk(KERN_NOTICE "current_kernel_time: %ld %ld\n getnstimeofday: %ld %ld\n", time1a, time1b, time2a, time2b);
	return 0;
}

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
     	int result = 0;
    	printk(KERN_NOTICE "mytimeCharDriver: Initialization started" );
      	result = register_device();
    	return result;
}

static void __exit device_cleanup(void)
{
    	printk(KERN_NOTICE "mytimeCharDriver: Exiting\n");
	unregister_device();
}

module_init(device_init);
module_exit(device_cleanup);
