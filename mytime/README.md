Author: Patrick Watters

Assn: Assn2 Part C

Files changed: mytimeDevice.c Makefile README.md testCharDevice.c

Sample output of ./test:

KERNEL:  
current_kernel_time: 1508723133 925681398  
getnstimeofday: 1508723133 921561957  
USERSPACE:  
gettimeofday: 1508723133 925641000  

KERNEL:  
current_kernel_time: 1508723133 926725604  
getnstimeofday: 1508723133 921561957  
USERSPACE:  
gettimeofday: 1508723133 926721000  

KERNEL:  
current_kernel_time: 1508723133 927560975  
getnstimeofday: 1508723133 921561957  
USERSPACE:  
gettimeofday: 1508723133 927557000  

KERNEL:  
current_kernel_time: 1508723133 928395840  
getnstimeofday: 1508723133 921561957  
USERSPACE:  
gettimeofday: 1508723133 928395000  


Journal:
Current_kernel_time() is meant for timekeeping. It returns a value not based on the system timer, but a value that is updated by a timer interrupt. Therefore, precision depends on timer interrupt period. Resulting in poor resolution. Getnstimeofday() will read the actual clock source to adjust the time value and will be a bit more accurate. They get their values from different sources and its expected that they wont be equal.
Gettimeofday() is a lib function that gets the number of seconds and microseconds. It returns a timeval struct just like Getnstimeofday(), but the latter returns nanoseconds instead of microseconds.Gettimeofday() will round in an attempt to make up accuracy.
    
As you increase the value of N in our test program, the difference between all the readings will increase due to actual clock updating and the kernel clock updating with the timer interrupts. 

Changing the init_module() to return -1 will cause an error that it couldnt permit the insertion of our module. You can only insert a module into the kernel as root.

