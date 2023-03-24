#include <stdio.h>
#include "list.h"
#include "Semaphore.h"
#include "PCB.h"

S** semaphors =NULL;




S* newSemaphore(int ID, int val)
{
    if(semaphors == 0)
    {
        semaphors = (S*)malloc(sizeof(S*)*3);
    }
    if(!(semaphors[ID] = malloc(sizeof(S))))
    {
        return 0;
    }
    semaphors[ID]->id = ID;
    semaphors[ID]->value = val;
    semaphors[ID]->waitingOnSem = malloc(sizeof(List*)*3);
    for(int i =0;i<3; i++)
        semaphors[ID]->waitingOnSem[i] = List_create();
    return semaphors[ID];
}

//if value of the semaphore is <0 after testing and decrementing, we add the process to the waiting list
//and change the status of the process. 
void P( int id)
{
    Process* pr = get_Current_Running();
    semaphors[id]->value--;
    if(semaphors[id]->value < 0)
    {
        pr->processState = Blocked;
        List_append(semaphors[id]->waitingOnSem[pr->processPriority], pr);
        get_Next_Process();
    }
}

//when called, increases the value. If it becomes non-negative it allowes the first element on the list to become 
//active and remove from waiting list.
void* V( int id)
{
    Process* currenlyRunning = get_Current_Running();
    semaphors[id]->value++;
    if(semaphors[id]->value >=0)
    {
        Process* aPr;
        if(List_count(semaphors[id]->waitingOnSem[0])!=0)
        {
            List_first(semaphors[id]->waitingOnSem[0]);
            aPr = List_remove(semaphors[id]->waitingOnSem[0]);
        }
        else if(List_count(semaphors[id]->waitingOnSem[1])!=0)
        {
            List_first(semaphors[id]->waitingOnSem[1]);
            aPr = List_remove(semaphors[id]->waitingOnSem[1]);
        }
        else if(List_count(semaphors[id]->waitingOnSem[2])!=0)
        {
            List_first(semaphors[id]->waitingOnSem[2]);
            aPr = List_remove(semaphors[id]->waitingOnSem[2]);
        }
        if(aPr!=0)
        {
            if(aPr->PID > currenlyRunning->PID)
            {
                currenlyRunning->processState = Ready;
                put_aProcess(currenlyRunning);
                currenlyRunning = get_Next_Process();
                currenlyRunning->processState = Running;
            }
            else
            {
                put_aProcess(aPr);
            }
        }
    }

}
