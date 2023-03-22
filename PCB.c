#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "list.h"
#include "PCB.h"

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
    if(!(aNew->incomingMessagesReceived = (Queue*)malloc(sizeof(Queue))))
    {
        return 0;
    }
    if(!(aNew->incomingMessagesReplied = (Queue*)malloc(sizeof(Queue))))
    {
        return 0;
    }
    aNew->processState = Ready;
    aNew->PID = (*pid)++;
    if(Qs != 1)
    {
        Enqueue(Qs[pr], aNew);
    }
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
    if(!(aNew->incomingMessagesReceived = (Queue*)malloc(sizeof(Queue))))
    {
        return 0;
    }
     if(!(aNew->incomingMessagesReplied = (Queue*)malloc(sizeof(Queue))))
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
    Process* toRemove;
    if(currentP != 0){
        //List_remove(Qs);
        toRemove = Dequeue_Current(Qs[currentP->processPriority]);
        if(toRemove == 0)
        {
            return -1;
        }
        free(toRemove);
    }   
    else //the search is splitted into 2 subsearches to distinguish the queues, where we found the element;
    {
        int qInd = 0;
        currentP = Queue_search(srQs[0],comparePCBs, pid);
        Process* currentP1 = Queue_search(srQs[1], comparePCBs, pid);
        if(currentP1 != 0)
        {
            qInd = 1;
            currentP = currentP1;
        }
        if(currentP !=0)
        {

            toRemove = Dequeue_Current(srQs[qInd]);
           // List_remove(srQs);
            free(toRemove);    
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

void* quantumProcess(Process* running, Queue** Ready_Queues)
{
     running->processState = Ready; // First we change the process 
    Enqueue(Ready_Queues[running->processPriority],running);
    running = Quues_Head(Ready_Queues , 3);  // Put this routine in some funciton
    if(running != NULL)
        running->processState = Running;
    return running;
}


//S
//Send
//send a message to another process - block until reply
//what to pass: Pointer to current Process, pid (pid of process to send message to), 
//char *msg (nullterminated message string, 40 char max); 
//in case of success, returns 0, failure returns -1

int sendProcess(Queue** Ready_Queues , Queue** Waiting_Queues ,  Process* running, unsigned int sPID, char* msg){
   
   // Case 1 : The process is blocked on receive 

   // This code should be refactored !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   // Add the return current function 

    Process* sP = Queue_search(Waiting_Queues[0] , comparePCBs , sPID); 
    if (sP  != NULL){
        sP == Dequeue_Current(Waiting_Queues[0]);
        sP->processState == Ready; 
        Enqueue(Ready_Queues[sP->processPriority] , sP);
        return 0 ;
    } 

    // Case 2  : The process is not on the receive queue //(blocked on send queue)
    else if (sP == NULL){
         sP = Queue_search(Waiting_Queues[1] , comparePCBs , sPID);  
         if(sP != NULL){
             Enqueue(Ready_Queues[sP->processPriority] , sP);
             return 0 ;
         }
    }

    else {    // The process is in the ready state 
        sP = Queues_search(Ready_Queues , 3, comparePCBs , sPID);
        if(sP != NULL){
            Enqueue(Ready_Queues[sP->processPriority] , sP);
            return 0 ;
        }
        else {
            // Send faild 
            return -1;
        }
    }
}


//R
//Receive
//receive a message - block until one arrives

void receiveProcess(Process* running , Queue** Waiting_Queues){
    if(running->incomingMessagesReceived->qList->count == 0){
        Enqueue(Waiting_Queues[0] , running);  // If we haven't received everthing. We just put the process on the ready queue 
    }
    else {  // if not then we remove the first element on the icomming messages queue and display it
        char* msg = Dequeue(running->incomingMessagesReceived);
        printf("Incomming Message : msg\n\n");
    }
}


//Y
//Reply unblocks sender and delivers reply
//int pid (pid of process to make the reply to), char *msg 
//(nullterminated reply string, 40 char max)

int replyProcess(Process* running , unsigned int rPID, char* msg , Queue* Senders_Blocked){
    Process* Ps = Queue_search(Senders_Blocked , comparePCBs , rPID);
    if(Ps == NULL){return -1;} //reply fails}
    else {
        Ps = Dequeue_Current(Senders_Blocked);
        Enqueue(Ps->incomingMessagesReplied,msg); 
        return 0 ; 
        // To do : Check if the message is greater then 40 
    }
}


int Procinfo (int PID , Queue** Ready_Queues , Queue** Waiting_Queues){
    Process* sPID = Queues_search(Ready_Queues  , 3, comparePCBs,PID);
    if(sPID == NULL){
        sPID = Queues_search(Waiting_Queues , 2 , comparePCBs , PID);
    }
    
    if(sPID != NULL){
        printf("%d" , sPID->processState);
        return 0 ;
    }
    else {
        return -1;
    }
    
}


void Totalinfo (Queue** Ready_Queue  , Queue** Waiting_Queue ){
    Print_Queues(Ready_Queue, 3);
    Print_Queues(Waiting_Queue , 2);
}



// Function will return the next running prcess from thre ready queues

Process* Next_Running_Process(Queue** Ready_Queue , int size){
    return Quues_Head(Ready_Queue , size);
}