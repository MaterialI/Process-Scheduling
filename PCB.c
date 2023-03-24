#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "PCB.h"

 Process* Current_Running;

 Process* init;
 unsigned int PID = 0 ; 

 List* pHigh = NULL;
 List* pNorm = NULL;
 List* pLow = NULL;
 List* pReceive = NULL; 
 List* pSend = NULL;



void display_OS_Info(){
    printf("The latest id is : %d\n", PID);
    printf("The current running  id is : %d\n" , Current_Running->PID);
}
Process* init_Process(short processState , int processPriority , unsigned int PID){
      Process* aNew;
    if(!(aNew = (Process*)malloc(sizeof(Process))))
    {
        return 0;
    }
    
    aNew->processPriority = processPriority;
    if(!(aNew->outcomingMessages = (List*)malloc(sizeof(List))))
    {
        return 0;
    }
    if(!(aNew->incomingMessagesReplied = (Queue*)malloc(sizeof(Queue))))
    {
        return 0;
    }
    aNew->processState =processState;
    aNew->PID = PID;
    return aNew;
}

Process* get_Current_Running(){
    return Current_Running;
}

void* start_OS(){
    init = init_Process(Running , 0 , PID);
    Current_Running = init; 
        pHigh = List_create();
        pNorm = List_create();
        pLow = List_create();
        pReceive = List_create();
        pSend = List_create();
        printf("New Lists\n"); // Debugging 
    
}

Process* createProcess(short pr )
{
 
    Process* aNew = init_Process(Ready , pr , ++PID);
   printf("current pr %d:", aNew->PID); // Debugging 
   //*************
    if(pr == High){    List_append(pHigh , aNew);}
    else if (pr == Medium) {List_append(pNorm,aNew);}  // Put this routine in some function
    else {List_append(pLow,aNew);}
    //*****************

     if(Current_Running == init)
     { get_Next_Process();}  // To Do : Create a function that gets the next Process to run
    return aNew;

}



Process* forkProcess( )
{
   
   // List_preprend(Qs[current->processPriority]->qList, aNew);

   if (Current_Running == init){return -1; } // Fork Failed
   Process* aNew = init_Process(Ready , Current_Running->processPriority , ++PID);

    //*************
    int pr = Current_Running->processPriority;
    if(pr == High){    List_append(pHigh , aNew);}
    else if (pr == Medium) {List_append(pNorm,aNew);}  // Put this routine in one  function for reusibillity 
    else {List_append(pLow,aNew);}
    //***************** 
    return aNew;
}


// To Do: 1- write a search by ID function. 
int killProcess(unsigned int PID){

    // Case 1: Trying to kill the Init while our ready or blocked process are running 
    if (PID == 0 && pcb_Count() == true){
        
        printf("System Error!\n. More Kernel and User Operations on the Kernel cannot be terminated!!\n");
        return-1;
    }
    //Case 2 : Trying to kill the Init while the Init is the only Process in the system
    else if (PID == 0 && pcb_Count() == false){
        printf("This Action will exit/kill the Init. \n The simulation is now terminated\n");
        exit(0); // Terminate the program
    }
    // Case 3 is the targer process is the current running process 
    if(Current_Running->PID == PID){
        free(Current_Running);
        Current_Running = NULL;
        get_Next_Process();
        return 0 ;
    }
    // Case 4 : if the process is on the ready queues 

    //********************************
    Process* pCurrent = search_By_ID(pHigh , PID); 
    
    if (pCurrent == NULL){pCurrent = search_By_ID(pNorm , PID);}  // To Do Put this code in a routine        
    if(pCurrent == NULL){pCurrent =search_By_ID(pLow , PID);}
   
     //********************************

      //********************************
    if(pCurrent != NULL){
        free(pCurrent);         // Put this routine in a function
        return 0 ;
    }
     //********************************
    // Case 5 : if the process is on the Blocked Queues 
    else{

        //***********************
          pCurrent = search_By_ID(pReceive , PID); 
         if (pCurrent == NULL){pCurrent = search_By_ID(pSend , PID);}  // Put this code in a routine 
         //****************************************************
    }
    //*************************
      if(pCurrent != NULL){
        free(pCurrent);         // Put this routine in a function
        return 0 ;
    }
    //*************************************************
}


// Exit 

int exitProcess(){

        killProcess(Current_Running->PID);

}



// Quantum 

int  quantumProcess(){

    if(Current_Running == init){
        return -1;
    }
    Process* pCurrent = Current_Running;
    get_Next_Process();
    //********** 
    if(Current_Running->PID == High){List_append(pHigh , pCurrent);}
    else if(Current_Running->PID == Medium){List_append(pNorm , pCurrent);} //Put this in a function 
    else if(Current_Running->PID == Low){List_append(pLow , pCurrent);}
    //****************************
    return 0;
}

Process* search_By_ID(List* pList , int PID){
        List_first(pList);
        Node* current = pList->pCurrentNode;
    if(current == NULL){return NULL;}

    while (current)
    {   Process* toCompare = current->pItem;
        if(comparePCB(toCompare->PID , PID) == true){
            printf("Found a match !!!!!!!!\n"); // Debegiing 
            pList->pCurrentNode = current;
            return List_remove(pList);
        }
        else {
            current = current->pNext;
        }
    }
    
    printf("No Match Found !!!!!!!!!!!\n"); // Debugginf 
    pList->pCurrentNode = LIST_OOB_END;
    return NULL;
}


Process* search_By_rPId(List* pList , int rPID){
        List_first(pList);
        Node* current = pList->pCurrentNode;
    if(current == NULL){return NULL;}

    while (current)
    {   Process* toCompare = current->pItem;
        if(comparePCB(toCompare->outcomingPID , rPID) == true){
            printf("Found a match !!!!!!!!\n"); // Debegiing 
            pList->pCurrentNode = current;
            return List_curr(pList);
        }
        else {
            current = current->pNext;
        }
    }
    
    printf("No Match Found !!!!!!!!!!!\n"); // Debugginf 
    pList->pCurrentNode = LIST_OOB_END;
    return NULL;
}


 bool comparePCB(int toCompare , int pid){
    if(toCompare == pid){return true;}
    return false;
}


void get_Next_Process(){
    if(pHigh->count != 0){
        List_first(pHigh);
        Current_Running = List_remove(pHigh);
        Current_Running->processState = Running;
    }
    else if (pNorm->count != 0) {
        List_first(pNorm);
        Current_Running = List_remove(pNorm);
        Current_Running->processState = Running;
    }
    else if(pLow->count!= 0){
        List_first(pLow);
        Current_Running =  List_remove(pLow);
        Current_Running->processState = Running;
    }
    else {Current_Running = init;}
}

bool put_aProcess(Process* pr)
{
    if(pr == 0)
    {
        return;
    }
    int success = 1;
    if(pr->PID == 0)
    {
        success*=List_append(pHigh, pr);
        pr->processState = Ready;
    }
    if(pr->PID == 1)
    {
        success*= List_append(pNorm, pr);
        pr->processState = Ready;
    }
    if(pr->PID == 2)
    {
        success*= List_append(pLow, pr);
        pr->processState = Ready;
    }
    if(success<0)
    {
        return false;
    }
    return true;
}


bool pcb_Count(){
    if(pHigh->count == 0 && pNorm->count == 0 && pLow->count == 0 && pReceive->count == 0 && pSend->count == 0){
        return false;
    }
    return true;
}

void sendProcess(int rPID, char* msg)
{
    Current_Running ->outcomingPID = rPID;
    Process* receiver = search_By_ID(pReceive, rPID);
    if(receiver!=0)
    {
        printf("The receiver pid:%d received a message: %s\n", rPID, msg);
        printf("The receive process was returned to %d Ready queue\n");
        List_remove(pReceive);
        receiver->processState = Ready;
        put_aProcess(receiver); 
    }
    else{
        List_append(Current_Running->outcomingMessages, msg);
    }
    printf("The process, pid: %d is blocked on send queue\n", Current_Running->PID);
    Current_Running->processState = Blocked;
    List_append(pSend, Current_Running);
    get_Next_Process();
    return;
    
}

void receiveProcess()
{
    Process* sender = (Process*)search_By_rPId(pSend, Current_Running->PID);
    if(sender == 0)
    {
        printf("The process, pid: %d is blocked on receive queue\n", Current_Running->PID);
        Current_Running->processState = Blocked;
        List_append(pReceive, sender);
        get_Next_Process();
    }
    else
    {
        printf("The message was received by %d, from %d, the message\n%s", Current_Running->PID, sender->PID, sender->outcomingMessages);
    }
}

bool replyProcess(int sPID, char* msg)
{
    Process* sender = search_By_ID(pSend, sPID);
    if(sender == 0)
    {
        printf("Reply was unsuccessful, none send process was found with pid:%d", sPID);
        return 0;
    }
    printf("The message was received by %d, from %d, the message\n%s", sender->PID, Current_Running->PID, msg);
    sender->processState = Ready;
    put_aProcess(sender);
    return 1;
}

