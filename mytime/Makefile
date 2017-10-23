obj-m += mytimeDevice.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	gcc testCharDevice.c -o test
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean

