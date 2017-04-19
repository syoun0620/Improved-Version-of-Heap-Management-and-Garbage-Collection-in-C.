/*
 *  Sukwhan(David) Youn
 *  Heap Management & Garbage Collection
 *  GarbageCollectionTest.c
 *  a function that determines which blocks in your heap are inaccessible from the 
 *  stack, and then to deallocate those blocks.
 *  Also, the function coalesce unallocated blocks after it finishes.
 */
#include "heapmgr.h"
#include "gc.h"
#include <stdio.h>

int main() {
   char *p;
   initmemory(100);

   printf("malloc 4\n");
   p = (char *)myalloc(4);
   printallocation();

   printf("malloc 6; the malloc 4 is now garbage\n");
   p = (char *)myalloc(6);
   printallocation();

   printf("malloc 22; the malloc 6 is now garbage\n");
   p = (char *)myalloc(22);
   printallocation();

   printf("gc: Should free the first two blocks and coalesce them\n"); 
   gc();
   printallocation();
}
