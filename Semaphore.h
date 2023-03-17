#include <stdio.h>
#include "list.h"
#include "PCB.h"
struct Semaphore
{
    int value;
    List* waitingOnSem;
};

//if value of the semaphore is <0 after testing and decrementing, we add the process to the waiting list
//and change the status of the process. 
void P(Semaphore*, PCB*);

//when called, increases the value. If it becomes non-negative it allowes the first element on the list to become 
//active and remove from waiting list.
void V(Semaphore*, PCB*);