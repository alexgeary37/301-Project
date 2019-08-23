/*	Name:	Alex Geary
	ID:	1188083
*/

#ifndef HEAP_H
#define HEAP_H
#include "FreeList.h"
#include "AllocList.h"

typedef struct Heap {
	FreeListPointer freeList;
	AllocListPointer allocList;
	void *heapBuffer;
	size_t usedSize, freeSize, allocMode;
	// allocMode - 0 first fit, 1 best fit, 2 worst fit
} Heap;

typedef Heap *HeapPointer;

// function declarations
HeapPointer newHeap(size_t heapSize, size_t allocMode);
void destroyHeap(HeapPointer this);
void *allocateHeap(HeapPointer this, size_t allocSize);
size_t deallocateHeap(HeapPointer this, void *p);
void heapStats(HeapPointer this);

#endif
