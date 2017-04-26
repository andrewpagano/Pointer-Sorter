#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_

#include<stdio.h>
#include<stddef.h>

#define malloc(x) mallocPlus(x,__LINE__,__FILE__)
#define free(x) freePlus(x,__LINE__,__FILE__)

/**
 *CS 214 Systems Programming
 *Assignment 1: Memory Allocation++
 *due 2/26/2017
 *
 *@author Thurgood Kilper
 *@author Andrew Pagano
 */

/**main memory*/
static char myBlock[5000];

/**
 *struct that holds memory metadata | uses linked list implementation:
 *Holds the size of the memory block and a pointer to the next chunk of memory
 *isFree = 1 if the memory block is free
 */
typedef struct memBlock{
    size_t              size;   /**4 bytes*/
    struct memBlock*    next;   /**4 bytes*/
    int                 isFree; /**4 byte*/
} block;

/**head node block*/
block *head;// = (void*)myBlock;

/**function declarations*/
void *mallocPlus(size_t s);
int freePlus(void* ptr);
void splitBlock(block *bigBlock, size_t s);
void combineFreeBlocks();
void printMall();

#endif // MYMALLOC_H_
