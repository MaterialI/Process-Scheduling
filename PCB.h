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
//create a process 
//what to pass: Pass priority from a main file and pass static pid to the process 
//(it will first increment the value and after assign it to the process)
//the last argument will be the appropriate ready queue (high, medium, low)

PCB* createProcess(enum Priority, int&, Queue**);


//F
//Copy the currently running process and put it on the ready Q corresponding to the original process' priority.
//Attempting to Fork the "init" process should fail. 
//what to pass: Pass the process to the fork function, pass the integer of current PID, pass the readyQueue corresponding to it;

PCB* forkProcess(PCB*,int&, Queue**);


//K
//kill the named process and remove it from the system.
//pass the process PID, and Queueueueueues
//in case of success, returns 0, failure returns -1

int killProcess(int, Queue**);


//E
//exit 
//killes, exterminates, obliterates the process
//what to pass: just pass the pointer and the array of queues
//in case of success, returns 0, failure returns -1

int exitProcess(PCB*, Queue**);


//Q
//Time quantum
//time quantum of running process expires.
//what to pass: Pcb pointer and queues pointers
//in case of success, returns 0, failure returns -1

int quantumProcess(PCB*, Queue**);


//S
//Send
//send a message to another process - block until reply
//what to pass: Pointer to current PCB, pid (pid of process to send message to), 
//char *msg (nullterminated message string, 40 char max); 
//in case of success, returns 0, failure returns -1

int sendProcess(PCB*, int sPID, char* msg);


//R
//Receive
//receive a message - block until one arrives

char* receiveProcess(PCB*);


//Y
//Reply unblocks sender and delivers reply
//int pid (pid of process to make the reply to), char *msg 
//(nullterminated reply string, 40 char max)

int replyProcess(PCB*, int rPID, char* msg);
