/*
 *  Sukwhan(David) Youn
 *  Heap Management & Garbage Collection
 *  gc.h
 *  a function that determines which blocks in your heap are inaccessible from the 
 *  stack, and then to deallocate those blocks.
 *  Also, the function coalesce unallocated blocks after it finishes.
 */

void gc(); // perform garbage collection on the heap
void *stackBottom();
void mark(void *p);
void sweep();
