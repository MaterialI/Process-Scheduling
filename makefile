all: kernel

kernel: PCB.o Queue.o Semaphore.o  Queue.o list.o
	gcc -Wall -g -o kernel Queue.o Semaphore.o PCB.o list.o Kernel.c

Queue.o:  Queue.c  
	gcc -Wall -g -c Queue.c 

Semaphore.o:  Semaphore.c 
	gcc -Wall -g -c Semaphore.c 

PCB.o: PCB.c 
	gcc -Wall -g -c  PCB.c 

clean: 
	find . -name "*.o" | grep -v "list.o" | xargs rm

