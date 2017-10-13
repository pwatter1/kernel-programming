#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/time.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/signal.h>


asmlinkage long sys_my_xtime(struct timespec *current_time) 
{
	// verify user memspace
	// VERIFY_WRITE tests both writable and readable
	if (!access_ok(VERIFY_WRITE, current_time, sizeof(current_time))) {
                printk(KERN_ERR "access_ok() failed in xtime()\n");
		return -EFAULT;
        }

	struct timespec ts;
	ts = current_kernel_time();	

	if (copy_to_user(current_time, &ts, sizeof(ts)) != 0) {
		printk(KERN_ERR "copy_to_user() failed in xtime()\n");
		return -EFAULT;
	}

	long int time = ts.tv_sec * 1000000000UL + ts.tv_nsec;

	printk(KERN_NOTICE "Current kernel time: %ld\n", time);

	return 0;
}

