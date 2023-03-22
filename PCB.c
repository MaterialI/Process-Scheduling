#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "list.h"
#include "PCB.h"

//C
//create a process 
//what to pass: Pass priority from a main file and pass static pid to the process 
//(it will first increment the value and after assign it to the process)
//the last argument will be the appropriate ready queue (high, medium, low)

Process* createProcess(short pr, unsigned int* pid, Queue** Qs)
{
    Process* aNew;
    if(!(aNew = (Process*)malloc(sizeof(Process))))
    {
        return 0;
    }
    //to insert in the appropriate list
   // List_preprend(Qs[pr]->qList, aNew);
    aNew->processPriority = pr;
    if(!(aNew->incomingMessages = (Queue*)malloc(sizeof(Queue))))
    {
        return 0;
    }
    aNew->processState = Ready;
    aNew->PID = (*pid)++;
    return aNew;
}


//F
//Copy the currently running process and put it on the ready Q corresponding to the original process' priority.
//Attempting to Fork the "init" process should fail. 
//what to pass: Pass the process to the fork function, pass the integer of current PID, pass the readyQueue corresponding to it;

Process* forkProcess(Process* current, unsigned int* pid, Queue** Qs)
{
    Process* aNew;
    if(!(aNew = (Process*)malloc(sizeof(Process))))
    {
        return 0;
    }
    if(!(aNew->incomingMessages = (Queue*)malloc(sizeof(Queue))))
    {
        return 0;
    }
   // List_preprend(Qs[current->processPriority]->qList, aNew);
    aNew->PID = (*pid)++;
    aNew->processPriority = current->processPriority;
    aNew->processState = Ready;
    return aNew;
}


//K
//kill the named process and remove it from the system.
//pass the process PID, and Queueueueueues
//in case of success, returns 0, failure returns -1

int killProcess(Process* currentRunning, unsigned int pid, Queue** Qs, Queue** srQs)
{
    if(currentRunning->PID == pid)
    {
        currentRunning->processState = Blocked;
        free(currentRunning);
        currentRunning = Dequeue(Qs);  //dequeue has to return the ptr to returned obj
        currentRunning ->processState = Running;
        
    }
    Process* currentP = Queues_search(Qs,3,comparePCBs, pid);
    if(currentP != 0){
        //List_remove(Qs);
        Process* toRemove = Dequeue_Current(Qs[currentP->processPriority]);
        if(toRemove == 0)
        {
            return -1;
        }
        free(toRemove);
    }   
    else
    {
        currentP = searchReadyQueue(srQs, pid, 2);
        if(currentP !=0)
        {
           // List_remove(srQs);
            free(currentP);    
        }
        else
        {
            return -1;
        }
    }
    return 0;
    
}


//E
//exit 
//killes, exterminates, obliterates the process
//what to pass: just pass the pointer and the array of queues
//in case of success, returns 0, failure returns -1

int exitProcess(Process* current, Queue** Qs)
{
    if(current != 0)
    {    
        current->processState = Blocked;
        free(current);
        return 0;
    }
    else
    {
        return -1;
    }
    //do we put another process from waiting queue to the running state?.
}


//Q
//Time quantum
//time quantum of running process expires.
//what to pass: Process pointer and queues pointers
//in case of success, returns 0, failure returns -1

int quantumProcess(Process* running, Queue** Ready_Queues)
{
     running->processState = Ready;
    Enqueue(Ready_Queues[running->processPriority],running);
    running = Dequeue()
}


//S
//Send
//send a message to another process - block until reply
//what to pass: Pointer to current Process, pid (pid of process to send message to), 
//char *msg (nullterminated message string, 40 char max); 
//in case of success, returns 0, failure returns -1

int sendProcess(Process*, unsigned int sPID, char* msg);


//R
//Receive
//receive a message - block until one arrives

char* receiveProcess(Process*);


//Y
//Reply unblocks sender and delivers reply
//int pid (pid of process to make the reply to), char *msg 
//(nullterminated reply string, 40 char max)

int replyProcess(Process*, unsigned int rPID, char* msg);



//takes a ptr to the element and returns the true if the element pointed at by the ptr
//and the int
int comparePCBs(Process* toFind, int pid)
{
    if(toFind->PID  == pid)
    {
        return true;
    }
    else 
        return false;
}