#include <stdio.h>
#include "Queue.h"
#ifndef _PCB_H_
#define _PCB_H_
enum State {Running = 1, Ready =0,  Blocked =-1};
enum Priority {High = 0, Medium = 1, Low = 2};

typedef struct PCB Process;
struct PCB
{
    short processState; 
    int processPriority;
    unsigned int PID; 
    Queue* incomingMessagesReceived;
    Queue* incomingMessagesReplied; 
};

Process* Current_Running;


Process* Init;
unsigned int PID = 0 ; 

List* pHigh = NULL;
List* pNorm = NULL;
List* pLow = NULL;
List* pReceive = NULL; 
List* pSend = NULL;


Process* Init_Process(short , int  , unsigned int );

//C
//create a process 
//what to pass: Pass priority from a main file and pass static pid to the process 
//(it will first increment the value and after assign it to the process)
//the last argument will be the appropriate ready queue (high, medium, low)

Process* createProcess(short pr);


//F
//Copy the currently running process and put it on the ready Q corresponding to the original process' priority.
//Attempting to Fork the "init" process should fail. 
//what to pass: Pass the process to the fork function, pass the integer of current PID, pass the readyQueue corresponding to it;

Process* forkProcess( unsigned int* pid);



//K
//kill the named process and remove it from the system.
//pass the process PID, and Queueueueueues
//in case of success, returns 0, failure returns -1

int killProcess( unsigned int);

#endif