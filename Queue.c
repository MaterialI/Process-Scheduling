#include <stdio.h>
#include "list.h"
#include "Queue.h"
#include "Queue.h"

// Desc Creates a new Queue

Queue* Queue_create(){
    List* qList = List_create();
    if(qList == NULL) return NULL;
    Queue* newQueue = malloc(sizeof(newQueue)); // To Do : Add the malloc check 
    if(newQueue != NULL) return NULL;
    newQueue->qList = qList;
    return newQueue;
}





// Desc Returns the list inisde the Queue. Shoud be static so that the list is protected 

static List* Get_List(Queue* Q){
    return Q->qList;
}

//Desc: Returns the count of elements in the Queue

int Queue_count(Queue* Q){
    return List_count(Q->qList);
}

// Desc : Inserts to the tail of the Queue 
int Enqueue(Queue* Q, void* pItem){
    return List_prepend(Q->qList, pItem);
}


// Desc: Removes from the head of the queue 
// it assumes that the current item in the head is the head
void* Dequeue(Queue* Q){
    List_first(Q->qList);
    return List_remove(Q->qList);
}

// Desc: Remove the current item in the queue (supports the kill command) 
void* Dequeue_Current(Queue* Q){
    return List_remove(Q->qList);
}


// Delete Queue. pItemFreeFn is a pointer to a routine that frees an item. 
typedef void (*FREE_FN)(void* pItem);
void Queue_free(Queue* Q, FREE_FN pItemFreeFn){
    return List_free(Q->qList ,pItemFreeFn );
}



// Searches for an item in a  Queue. pComparisonArg is a pointer to a routine that compares an item. 
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* Queue_search(Queue* Q, COMPARATOR_FN pComparator, void* pComparisonArg){
    return List_search(Q->qList ,pComparator, pComparisonArg);
}

// Desc: Searches for an item in an array of queues 

typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* Queues_search(Queue** Q, int size, COMPARATOR_FN pComparator, void* pComparisonArg){
    for(int i = 0 ; i < size ; i++){
        Queue_search(Q[i] , pComparator , pComparisonArg);
    }
}



// Desc: Removes the first Item in an array of Queues and returns it 

void* Quues_Head(Queue** Q , int size){
    void* item; 
    for(int i = 0 ; i < size ; i++){
        item = Dequeue(Q[i]);
        if(item != NULL){return item;}
    }

    return NULL;
}

void Print_Queue(Queue* Q){
    
 Print_List(Q->qList);

}


void Print_Queues(Queue** Q , int size){

for (int i = 0 ; i < size; i++){
    Print_List(Q[i]->qList);
}

}


static void Print_List(List* plist){
Node* current = plist->pFirstNode; 
int i = 0 ;
    while (current != NULL)
{
    printf("%d ",current->pItem);
    current = current->pNext;
    i++;
}

}