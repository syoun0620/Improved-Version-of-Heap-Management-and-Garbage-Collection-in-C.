/*
 *  Sukwhan(David) Youn
 *  Heap Management & Garbage Collection
 *  heapmgr.c
 *  I built a heap manager for C, replacing the function malloc and free
 *  with my improved version myalloc and myfree.
 */

#include "heapmgr.h"
#include <stdio.h>
#include <stdlib.h>

int *start;
int *startdigit;
int *sentinel;

// is the block at location p allocated?
int  isAllocated(int *p){
	int temp = *p%2;
	return temp != 0;
	// return 0 if *p is even number. 
	// return 1 if *p is odd number. 
}

// return a pointer to the block that follows p
int* nextBlock(int *p){
	int* temp = p;
	temp = temp + ((*temp)/4);
	return temp;
}

// return a pointer to the first block on the heap
int *firstBlock(){
	return start;
}

// return a pointer to the sentinel block
int *lastBlock(){
	return sentinel;
}

/* 
 *  The function initmemory initializes the heap manager. It calls malloc to get memory,
 *  and initializes that memory to correspond to 2 blocks: a large free block, and a 
 *  sentinel block (of size 0) at the end of memory. The argument to initmemory specifies 
 *  how many bytes the heap manager must be able to allocate. 
 */
void  initmemory(int size){ 
	size = size+12;
	while (size%8 != 0){
		size++;
	}
	int *whole = (int *)malloc(size);
	start = whole+1;
	*start = size-8;

	sentinel = whole + (size/4) -1;
	*sentinel = 0;
}

/*
 *  The function myalloc behaves exactly the same as malloc. The code for myalloc should 
 *  scan the implicit list of blocks for a sufficiently large unallocated block. 
 *  If it cannot find one, it returns NULL. Otherwise, it uses the first one it finds, 
 *  splitting it into an allocated block and an unallocated block.
 */
void *myalloc(int length){
	length = length+4;
	while (length%8 != 0){
		length++;
	}
	int *temp = start;

	while (*temp != 0){
		if (*temp >= length && !isAllocated(temp)){
			if (*temp > length){
				int leftover = *temp - length;
				*temp = length +1; // want to return this temp.
				int* temp2 = temp;
				temp2 = temp2 + (length/4);
				*temp2 = leftover;
				return temp;
			}
			else {
				*temp = *temp +1;
				return temp;
			}
		}
		temp = temp + (*temp)/4;
	}
	return NULL;
}

// The code for myfree behaves the same as free. It should simply mark the specified
block as unallocated.
void  myfree(void *ptr){
	int *ip = (int*) ptr;
	*ip = *ip-1;
}

/* 
 *  coalescing will occur only when the user requests it. The function coalesce coalesces 
 *  all adjoining free blocks in the block list. This function can be called if myalloc 
 *  returns NULL, in order to create larger blocks.
 */
void  coalesce(){
	int* ptr = firstBlock();
	int* next = nextBlock(ptr);
	while (next != lastBlock()){
		if (!isAllocated(ptr) && !isAllocated(next)){
			*ptr = *ptr + *next;
		}
		else{
			ptr = nextBlock(ptr);
		}
		next = nextBlock(ptr);
	}
}   

/* 
 *  The function printallocation prints the current size and allocation of each block.
 *  This function will be useful for debugging purposes.
 */
void  printallocation(){
	int i = 0;
	int *pointer;
	pointer = start;
	while (*pointer != 0){
		if (*pointer %2 ==0){ 
			printf("Block %d: size %2d         unallocated \n",i, *pointer);
		}
		else if (*pointer%2 ==1){
			if (*pointer %4 ==3)
				printf("Block %d: size %2d         allocated \n",i, *pointer-3);
			else 
				printf("Block %d: size %2d         allocated \n",i, *pointer-1);
		}
		i++;
		pointer = pointer + (*pointer/4);
	}
	printf("\n");
}

