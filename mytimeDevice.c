#include <linux/module.h>    // all kernel modules
#include <linux/kernel.h>    // for log infos
#include <linux/init.h>      // __init and __exit macros
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>     // copy_to_user() 
#include <linux/time.h>
#include <linux/vmalloc.h>

#define CLASS_NAME "mytimeCharDeviceClass"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Watters");
MODULE_DESCRIPTION("Assn2 Part C char device driver module");

static int majorNumber = 0;
static const char device_name[] = "mytimeDevice";
static struct class* mytimeCharDeviceClass = NULL;
static struct device* mytimeCharDevice = NULL;

static ssize_t read(struct file *fptr, char __user *user_buffer, size_t count, loff_t *position)
{
	struct timespec ts1, ts2;
	
	getnstimeofday(&ts1);	
	ts2 = current_kernel_time();
	
	long int time1a = ts1.tv_sec;
	long int time1b = ts1.tv_nsec;
	long int time2a = ts2.tv_sec;
	long int time2b = ts2.tv_nsec;

	char* buffer = kzalloc(count, GFP_KERNEL);
		
	if (!access_ok(VERIFY_WRITE, user_buffer, count)) {
		printk(KERN_ERR "access_ok() faile din mytimeCharDevice()\n");
		return -EFAULT;
	}

	buffer = sprintf("current_kernel_time: %ld %ld\n getnstimeofday: %ld %ld\n", time1a, time1b, time2a, time2b);	
	
	if (copy_to_user(user_buffer, buffer, strlen(buffer)+1) != 0) {
		printk(KERN_ERR "copy_to_user() failed in mytimeCharDriver\n");
		return -EFAULT;
	}
	
	printk(KERN_NOTICE "current_kernel_time: %ld %ld\n getnstimeofday: %ld %ld\n", time1a, time1b, time2a, time2b);
	return 0;
}

static struct file_operations simple_fops = { .owner = THIS_MODULE, .read = read, };

int register_device(void) 
{
	int result = 0;
	printk(KERN_NOTICE "mytimeDevice: register_device() has been called\n");
	
	result = register_chrdev(0, device_name, &simple_fops);
	
	if (result < 0) {
		printk(KERN_WARNING "mytimeDevice: failed to register device with error = %i\n", result);
		return result;
	}
	
	majorNumber = result;
	printk(KERN_NOTICE "mytimeDevice: registered with major number = %i\n", majorNumber);
	
	// register the device class
	mytimeCharDeviceClass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(mytimeCharDeviceClass)) {
		unregister_chrdev(majorNumber, device_name);
		printk(KERN_ALERT "Failed to register the device class\n");
		return PTR_ERR(mytimeCharDeviceClass);
	}
	// register the device driver
	mytimeCharDevice = device_create(mytimeCharDeviceClass, NULL, MKDEV(majorNumber, 0), NULL, device_name);
	if (IS_ERR(mytimeCharDevice)) {
		class_destroy(mytimeCharDeviceClass);
		unregister_chrdev(majorNumber, device_name);
		printk(KERN_ALERT "Failed to create the device\n");
		return PTR_ERR(mytimeCharDevice);
	}
	
	printk(KERN_INFO "mytimeDevice: device class registered and created correctly\n");
	return 0;
}

static int __init device_init(void)
{
     	int result = 0;
    	printk(KERN_NOTICE "mytimeDevice: Initialization started" );
      	result = register_device();
    	return result;
}

static void __exit device_cleanup(void)
{	
	device_destroy(mytimeCharDeviceClass, MKDEV(majorNumber, 0));    
	class_unregister(mytimeCharDeviceClass);                     
   	class_destroy(mytimeCharDeviceClass);     
    	unregister_chrdev(majorNumber, device_name);
	printk(KERN_NOTICE "mytimeDevice: Exiting\n");
}

module_init(device_init);
module_exit(device_cleanup);
