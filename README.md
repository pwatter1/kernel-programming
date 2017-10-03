# kernel-programming - CS350 Kernel Assignment

## Part A: Installing, configuring, and compiling Linux Kernel 4.4.1

Download, compile and boot your kernel as explained lab04.pptx and instructions .

## Part B: System Calls

Now, using the concepts learned in the class, implement and test a system call that returns the current system time by means of a call-by-reference argument. More specifically, your system call should have the following prototype as seen by user-level applications.

int my_xtime(struct timespec *current_time);
struct timespec is defined in include/linux/time.h as follows:
struct timespec {
        time_t  tv_sec;         /* seconds */
        long    tv_nsec;        /* nanoseconds */
};
The system call should first verify that user memory space, pointed to by current_time, is valid and writable. If not, is should return a failure (EFAULT) to the user process. If the memory-check succeeds, then it should copy the contents of the kernel's xtime variable to user space address (pointed to by current_time argument). The system call should also print the current time in nanoseconds, to the console using the printk() function.
Also write a user-level application which calls your new system call my_xtime(...) and prints out the time obtained from the call-by-reference argument.

## Part C: Kernel Module

Implement a kernel module that creates a /dev/mytime character device. The character device should support the read() operation. When read() is called, it should return a single string that contains the result both current_kernel_time() and getnstimeofday() functions in the kernel. For example, the output should be as follows:

current_kernel_time: 378959784 384958
getnstimeofday: 378959784 384990
Also, provide a user-level application program that compares the resolution of time reported by your module with that reported by user-level gettimeofday() library routine. Understand and explain the reason for any difference in your journal.
One such application could be written as follows (please fill in the missing code):

#define N ...

struct timeval gtodTimes[N];
char *procClockTimes[N];

...
/* allocate memory for character buffers HERE before you use them */

fd = open("/dev/mytime", O_RDONLY);
/* check for errors HERE */

for( i=0; i < N; i++)
{
	gettimeofday(&gtodTimes[i], 0);
	bytes_read = read(fd, procClockTime[i], MAX_LENGTH);
	/* check for errors HERE */
}

close(fd);

for(i=0; i < N; i++) {
	printf("...", gtodTimes[i], procClockTime[i]);
	/* fix the output format appropriately in the above line */
}

Run the user-level program for various values of N (both very small and very large). In your journal, explain the reason for any differences that you observe between the three timing mechanisms. 


Now, change the module so that init_module() returns -1, recompile, and retest. What happens? Why?
