#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <errno.h>

int main(void) 
{
	struct timespec ts;
	int retVal;

	retVal = syscall(326, &ts);
	printf("Function return value: %d \n
		Errno number: %d \n
		Time: %ld\n", 
		retVal, errno, ts.tv_sec*1000000000UL + ts.tv_nsec);
	return 0;
}
