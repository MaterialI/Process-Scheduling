all: kernel

kernel: PCB.o Queue.o Semaphore.o  Queue.o list.o
	gcc -Wall -o kernel Queue.o Semaphore.o PCB.o list.o Kernel.c

Queue.o:  Queue.c  
	gcc -Wall -c Queue.c 

Semaphore.o:  Semaphore.c 
	gcc -Wall -c Semaphore.c 

PCB.o: PCB.c 
	gcc -Wall -c  PCB.c 

clean: 
	rm -f *.o
