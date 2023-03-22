#include <stdio.h>
#include "list.h"
#include "Semaphore.h"

void* newSemaphore(int ID, int val)
{
    S* anew;
    if(!(anew = (S*)malloc(sizeof(S))))
    {
        return 0;
    }
    anew->id = ID;
    anew->value = val;
    return anew;
}

//if value of the semaphore is <0 after testing and decrementing, we add the process to the waiting list
//and change the status of the process. 
void P(S** semaphors, Process* pr, int id)
{
    S* Semaphore = semaphors[id];
    //what happens to the waiting on sem processes????
    //which state are they?
    //if they are ready, are they stored on the ready queue?
    //if not, whare are they stored?
    //thus we need to have a unified queue, needn't we?
    Semaphore->value--;
    if(Semaphore->value < 0)
    {
        pr->processState = Blocked;
        Enqueue(Semaphore->waitingOnSem[pr->PID], pr);
    }
}

//when called, increases the value. If it becomes non-negative it allowes the first element on the list to become 
//active and remove from waiting list.
void* V(S** semaphors,Queue** Qs, Process* currenlyRunning, int id)
{
    S* Semaphore = semaphors[id];
    Semaphore->value++;
    if(Semaphore->value >=0)
    {
        if(((Process*)Dequeue(Semaphore->waitingOnSem))==0)
        {
            //after unblocking the process which was waiting on the blocked queue on semaphore, do we put it in the ready queue as the first process to call?
            Process* aPr = Quues_Head(Semaphore->waitingOnSem, 3);
            if(aPr->PID>currenlyRunning->PID)
            {
                currenlyRunning->processState = Ready;
                Enqueue(Qs[currenlyRunning->PID], currenlyRunning);
                currenlyRunning = Quues_Head(Qs, 3);
                currenlyRunning->processState = Running;
            }
            else
            {
                Enqueue(Qs[aPr->processPriority], aPr);
            }
        }
    }

}
