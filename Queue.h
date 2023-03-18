#include "list.h"
#include <stdio.h>


#ifndef _QUEUE_H_
#define _QUEUE_H_


// Using the Adapter Design Pattern. The list interface will used to create this Queue


// Queue Struct 
typedef struct Queue_ADT Queue;
struct Queue_ADT{
    List* qList;
};


// Desc Creates a new Queue

Queue* Queue_create();

//Desc: Returns the count of elements in the Queue

int Queue_count(Queue* Q);

// Desc : Inserts to the tail of the Queue 
int Enqueue(Queue* Q, void* pItem);


// Desc: Removes from the head of the queue 
// it assumes that the current item in the head is the head
int Dequeue(Queue* Q);


// Delete Queue. pItemFreeFn is a pointer to a routine that frees an item. 
typedef void (*FREE_FN)(void* pItem);
void Queue_free(Queue* Q, FREE_FN pItemFreeFn);



// Searches for an item in a  Queue. pComparisonArg is a pointer to a routine that compares an item. 
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* Queue_search(Queue* Q, COMPARATOR_FN pComparator, void* pComparisonArg);


#endif