#include <stdio.h>
#include "list.h"
#include "PCB.h"
#include "Semaphore.h"
//if value of the semaphore is <0 after testing and decrementing, we add the process to the waiting list
//and change the status of the process. 
void P(S* Semaphore, Process* pr)
{
    //what happens to the waiting on sem processes????
    //which state are they?
    //if they are ready, are they stored on the ready queue?
    //if not, whare are they stored?
    //thus we need to have a unified queue, needn't we?
}

//when called, increases the value. If it becomes non-negative it allowes the first element on the list to become 
//active and remove from waiting list.
void V(S* Semaphore, Process* pr)
{

}