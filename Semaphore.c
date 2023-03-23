#include <stdio.h>
#include "list.h"
#include "Semaphore.h"

S* newSemaphore(S** semaphors, int ID, int val)
{
    if(!(semaphors[ID] = (S*)malloc(sizeof(S))))
    {
        return 0;
    }
    semaphors[ID]->id = ID;
    semaphors[ID]->value = val;
    semaphors[ID]->waitingOnSem = malloc(sizeof(Queue*)*3);
    for(int i =0;i<3; i++)
        semaphors[ID]->waitingOnSem[i] = Queue_create() ;
    return semaphors[ID];
}

//if value of the semaphore is <0 after testing and decrementing, we add the process to the waiting list
//and change the status of the process. 
void P(S** semaphors, Queue** Qs, Process* pr, int id)
{
    semaphors[id]->value--;
    if(semaphors[id]->value < 0)
    {
        pr->processState = Blocked;
        Enqueue(semaphors[id]->waitingOnSem[pr->processPriority], pr);
        pr = Quues_Head(Qs, 3);
    }
}

//when called, increases the value. If it becomes non-negative it allowes the first element on the list to become 
//active and remove from waiting list.
void* V(S** semaphors,Queue** Qs, Process* currenlyRunning, int id)
{
    
    semaphors[id]->value++;
    if(semaphors[id]->value >=0)
    {
        Process* aPr = Quues_Head(semaphors[id]->waitingOnSem, 3);
        if(aPr!=0)
        {
            if(aPr->PID > currenlyRunning->PID)
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
