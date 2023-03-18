all: kernel

kernel: Queue.o Semaphore.o PCB.o  list.o 
	gcc -Wall -o kernel Queue.o Semaphore.o PCB.o  list.o  Kernel.c

Queue.o: Queue.h Queue.c list.o  
	gcc -Wall -c Queue.h Queue.c list.o 

PCB.o: PCB.h PCB.c   
	gcc -Wall -c PCB.h PCB.c 

Semaphore.o: Semaphore.h Semaphore.c   
	gcc -Wall -c Semaphore.h Semaphore.c 

clean: 
	rm -f *.o
