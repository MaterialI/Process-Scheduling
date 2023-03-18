all: kernel

kernel: Queue.o Semaphore.o PCB.o  list.o 
	gcc -Wall -o kernel Queue.o Semaphore.o PCB.o  list.o  Kernel.c

Queue.o: Queue.h Queue.c list.o  
	gcc -Wall -c Queue.h Queue.c list.o 

PCB.o: PCB.h PCB.c list.o  
	gcc -Wall -c PCB.h PCB.c list.o

Semaphore.o: Semaphore.h Semaphore.c Semaphore.o  
	gcc -Wall -c Semaphore.h Semaphore.c list.o

clean: 
	rm -f *.o
