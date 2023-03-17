#include <stdio.h>
#include "list.h"
#include "Queue.h"
enum State {Running, Ready,  Blocked};
enum Priority {High = 0, Medium = 1, Low = 2};

struct PCB
{
    enum State processState; 
    enum Priority processPriority;
    int PID; 
    List* incomingMessages;
};

//C
//create a process Pass priority from a main file and pass static pid to the process 
//(it will first increment the value and after assign it to the process)
//the last argument will be the appropriate ready queue (high, medium, low)

PCB* createProcess(enum Priority, int&, Queue**);

//F
//Copy the currently running process and put it on the ready Q corresponding to the original process' priority.
//Attempting to Fork the "init" process should fail. 
//Pass the process to the fork function, pass the integer of current PID, pass the readyQueue corresponding to it;
PCB* forkProcess(PCB*,int&, Queue**);

//K
//kill the named process and remove it from the system.
//pass the process, 
void killProcess(int, Queue**);