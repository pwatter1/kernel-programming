#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define N 10
#define MAX_LENGTH 180

int main()
{	
	char *procClockTimes[N];
	struct timeval gtodTimes[N];
	
	int i, b_read, dev;
		
	dev = open("/dev/mytimeDevice", O_RDONLY);
	if (dev < 0) {
		perror("Failed to open device\n");
		return errno;
	}
	
	for (i = 0; i < N; i++) {
		gettimeofday(&gtodTimes[i], 0);
		procClockTimes[i] = malloc(3000);
		b_read = read(dev, procClockTimes[i], MAX_LENGTH);
		
		if (b_read < 0) {	
			perror("Failed to read the device\n");
			return errno;
		}
	}
	
	for (i = 0; i < N; i++) {
		printf("-----------------------------------------\n");
		printf("KERNEL:\n%s", procClockTimes[i]);
		// convert gettimeofday into nanoseconds
		long int timea = (gtodTimes[i].tv_sec);
		long int timeb = (gtodTimes[i].tv_usec)*1000;
		printf("USERSPACE:\ngettimeofday: %ld %1d\n", timea, timeb);
	}
	printf("-----------------------------------------\n");
	
	return 0;
}
