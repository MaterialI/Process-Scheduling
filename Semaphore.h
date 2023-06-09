#include <stdio.h>
#include "PCB.h"
#include "list.h"

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

typedef struct Semaphore S;
struct Semaphore
{
    int id;
    int value;
    List** waitingOnSem;
};

//Initialize the named semaphore with the value given. ID's can take a value
//from 0 to 4. This can only be done once for a semaphore - subsequent attempts result in error.
S* newSemaphore(int,int);

//if value of the semaphore is <0 after testing and decrementing, we add the process to the waiting list
//and change the status of the process. 
void P(int);

//when called, increases the value. If it becomes non-negative it allowes the first element on the list to become 
//active and remove from waiting list.
void* V(int);

#endif
