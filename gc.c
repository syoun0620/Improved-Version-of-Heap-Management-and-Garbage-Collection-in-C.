/*
 *  Sukwhan(David) Youn
 *  Heap Management & Garbage Collection
 *  gc.c
 *  a function that determines which blocks in your heap are inaccessible from the 
 *  stack, and then to deallocate those blocks.
 *  Also, the function coalesce unallocated blocks after it finishes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "gc.h"
#include "heapmgr.h"

void *stackBottom() {
   unsigned long bottom;
   FILE *statfp = fopen("/proc/self/stat", "r");
   fscanf(statfp,
          "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
          "%*u %*u %*u %*u %*u %*u %*d %*d "
          "%*d %*d %*d %*d %*u %*u %*d "
          "%*u %*u %*u %lu", &bottom);
   fclose(statfp);
   return (void *) bottom;
}

void gc(){
	int x = 1; //random number to use its pointer.
	int *pointer1 = &x;

	while (pointer1<=(int*)stackBottom()){
		mark((int *)*pointer1);
		pointer1++;
	}
	sweep();
}

//mark if accessible.
void mark(void *p){
  if ((int *)p < firstBlock() || (int *)p > lastBlock()){
    return;
  }
  int *b = p;

  if (isAllocated(b)){
    *b = *b+2;
    while (b < nextBlock(b)){
      mark((int *)*b);
      b++;
    }
  }
}
void sweep(){
	int *ptr = firstBlock();
	while (*ptr != 0){ //while (ptr != lastBlock()){
  //if the pointer is not allocated and not marked, deallocate. 
		if (*ptr%2!=0 && *ptr%4!=3){ 
			myfree(ptr); 
		}
		ptr = nextBlock(ptr);
	}
	coalesce();
}