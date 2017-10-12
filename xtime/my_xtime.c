#include <linux/syscalls.h>
#include <linux/time.h>
#include <linux/init.h>
#include <linux/signal.h>
#include <linux/module.h>

asmlinkage long my_xtime(struct timespec *current_time) {
	
	//verify user memspace
	if (!access_ok(VERIFY_READ, current_time, sizeof(current_time))) {
		return -EFAULT;
	}
	
	struct timespec tv;
	do_gettimeofday(&tv);

	unsigned long time;
	int hr, min, tmp1, tmp2;
	
	time = tv.tv_sec;
	tmp1 = time/60;
	min = tmp1%60;
	tmp2 = time1/60;
	hr = (tmp2%24) -4;

	printk(KERN_NOTICE "Current time %d:%d\n", hr, min);
	
	if (copy_to_user(current_time, %time, sizeof(time)) != 0) {
		return -EFAULT;
	}

	return 0;
}
