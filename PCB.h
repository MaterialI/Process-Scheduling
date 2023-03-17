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

//create a process
PCB* createProcess(enum Priority priority)
{
    
}
