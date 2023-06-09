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
    printf("The semaphore with id:%d and value:%d\n", semaphors[ID]->id, semaphors[ID]->value);
    return semaphors[ID];
}

//if value of the semaphore is <0 after testing and decrementing, we add the process to the waiting list
//and change the status of the process. 
void P( int id)
{
    if(semaphors[id]==0)
    {
        printf("The semaphore with the %d id dne", id);
        return 0;
    }
    Process* pr = get_Current_Running();
    if(pr->PID!=0)
    {   
        semaphors[id]->value--;
        if(semaphors[id]->value < 0)
        {
            printf("the process %d was blocked on semaphore %d\n",pr->PID, id);
            pr->processState = Blocked;
            List_append(semaphors[id]->waitingOnSem[pr->processPriority], pr);
            get_Next_Process();
        }
    }
}

//when called, increases the value. If it becomes non-negative it allowes the first element on the list to become 
//active and remove from waiting list.
void* V( int id)
{
    if(semaphors[id] == 0)
    {
        printf("The semaphore with the %d id dne", id);
        return 0;
    }
    Process* currenlyRunning = get_Current_Running();
    semaphors[id]->value++;
    int sum =semaphors[id]->waitingOnSem[0]->count;
    sum+=semaphors[id]->waitingOnSem[1]->count;
    sum+=semaphors[id]->waitingOnSem[2]->count;
    printf("SEMAPHORE COUNT %d\n", sum);
    if(semaphors[id]->value >=0 && sum!=0)
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
                printf("The process %d was swapped with %d", currenlyRunning->PID, aPr->PID);
                currenlyRunning->processState = Ready;
                put_aProcess(currenlyRunning);
                currenlyRunning = get_Next_Process();
                currenlyRunning->processState = Running;
                return;
            }
            else
            {
                printf("The process %d was put back on the ready queue\n");
                put_aProcess(aPr);
                return;
            }
        }
    }
    printf("The semaphore pid:%d doesn't have any waiting processes\n", id);

}
