#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mallocPlus.h"

/**
 *CS 214 Systems Programming
 *Assignment 1: Memory Allocation++
 *due 2/26/2017
 *
 *@author Thurgood Kilper
 *@author Andrew Pagano
 */

block *head = (void*)myBlock;

/**
 *MALLOC implementation
 *@param s: size of the memory to be allocated
 */
void *mallocPlus(size_t s)
{
    block *curr, *prev;

    /**initialize the head memory block*/
    if(!(head->size)){
        head->size=5000-sizeof(block);
        head->isFree=1;
        head->next=NULL;
    }

    curr=head;

    /**iterate through blocks that are too small*/
    while((((curr->size)<s)||((curr->isFree)==0))&&(curr->next!=NULL)){
        prev=curr;
        curr=curr->next;
    }

    /**found a memory block of the requested size -> no split needed*/
    if((curr->size) == s){
        curr->isFree=0;
        printf("Memory allocated (%s, line: %d)\n", __FILE__, __LINE__);
        return (void*)(++curr);
    }

    /**found a memory block larger than requested -> split the block*/
    if((curr->size) > (s+sizeof(block))){
        splitBlock(curr, s);
        printf("Memory allocated by split (%s, line: %d)\n", __FILE__, __LINE__);
        return (void*)(++curr);
    }

    /**requested memory is not available*/
    printf("requested memory not available (%s, line: %d)\n", __FILE__, __LINE__);
    return NULL;

}

/**
 *Turn leftover block space into a new free block
 *@param bigBlock: The block to be split
 *@param s: amount of memory requested
 */
void splitBlock(block *bigBlock, size_t s)
{
    /**create a new block that holds the leftover free memory*/
    block * newBlock=(void*)((void*)bigBlock
                    + s
                    + sizeof(block));
    newBlock->size=(bigBlock->size)
                    - s
                    - sizeof(block);
    newBlock->isFree=1;
    newBlock->next=bigBlock->next;

    bigBlock->size=s;
    bigBlock->next=newBlock;
    bigBlock->isFree=0;
}

/**
 *FREE implentation (SET TO INT FOR TESTING PURPOSES)
 *sets pointer block to free and then calls for merging of free memory
 *@param ptr: the pointer to be freed
 */
int freePlus(void* ptr)
{
    /**check that pointer is within memory bounds*/
    if((ptr>=(void*)myBlock)&&(ptr<=(void*)(myBlock+5000))){
        block * curr=ptr;
        --curr;
		if(curr->isFree == 1){
			printf("invalid mallocPlus pointer (%s, line: %d)\n", __FILE__, __LINE__);
   			return 0;
		}
        curr->isFree=1;
        combineFreeBlocks();
        printf("memory freed successfully (%s, line: %d)\n", __FILE__, __LINE__);
        return 1;
    }
    else printf("invalid mallocPlus pointer (%s, line: %d)\n", __FILE__, __LINE__);
    return 0;
}

/**
 *iterate through block list and combine neighboring free blocks
 */
void combineFreeBlocks()
{
    block *curr, *next;
    curr=head;
    next=head->next;
    while(curr != NULL && next != NULL){
        if((curr->isFree==1)
           && (next->isFree==1)){
            curr->size+=(next->size)+sizeof(block);
            curr->next=next->next;
        }
        curr=next;
        next=curr->next;
    }
}



//******************
void printMall(){

	block * tree;
	tree = head;
	int s=0;
	printf("\nsize:");
	if(tree->next==NULL){
		printf(" %d ",tree->isFree); s++;
	}
	while(tree->next!=NULL){
		printf("%d ",tree->isFree);
		tree = tree->next; s++;
	}printf("\ns++<> %d\n", s);
	printf("block: %d\n",sizeof(block));

}


