#include <stdio.h>
#include "list.h"
#include "Queue.h"
#include "Queue.h"

// Desc Creates a new Queue

List* Queue_create(){
    List* qList = List_create();
    if(qList == NULL) return NULL;
    Queue* newQueue = malloc(sizeof(newQueue));
    if(newQueue != NULL) return NULL;
    newQueue->qList = qList;
    return qList;
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
