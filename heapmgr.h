/*
 *  Sukwhan(David) Youn
 *  Heap Management & Garbage Collection
 *  heapmgr.h
 *  I built a heap manager for C, replacing the function malloc and free
 *  with my improved version myalloc and myfree.
 */

void  initmemory(int size);  // initialize a simulated heap
void *myalloc(int length);   // allocate a block of length (or more) bytes
void  myfree(void *ptr);     // free an allocated block
void  coalesce();            // go through the heap, coalescing unallocated blocks
void  printallocation();  // print info about the simulated heap, for debugging purposes

int  isAllocated(int *p);  // is the block at location p allocated?
int *nextBlock(int *p);    // return a pointer to the block that follows p
int *firstBlock();         // return a pointer to the first block on the heap
int *lastBlock();          // return a pointer to the sentinel block





