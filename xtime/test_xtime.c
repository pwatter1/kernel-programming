#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <linux/unistd.h>



int main(void) {

	struct timespec ts;
	int ret;

	while(1)
	{
		ret = syscall(326, &ts);
		printf("ret=%d time= %ld\n", ret, ts.tv_sec*1000000000UL + ts.tv_nsec);
		sleep(1);
	}
	return 0;
}
