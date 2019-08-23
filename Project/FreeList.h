/*	Name:	Alex Geary
	ID:	1188083
*/

#ifndef FREELIST_H
#define FREELIST_H
#include "ListNode.h"

typedef struct FreeList {
	ListNodePointer head;
} FreeList;

typedef FreeList *FreeListPointer;

FreeListPointer newFreeList(size_t maxSize);
InfoPointer newInfo(size_t pos, size_t size);
void destroyFreeList(FreeListPointer this);
size_t allocateFirstFitFreeList(FreeListPointer this, size_t allocSize);
size_t allocateBestFitFreeList(FreeListPointer this, size_t allocSize);
size_t allocateWorstFitFreeList(FreeListPointer this, size_t allocSize);
int deallocateFreeList(FreeListPointer this, size_t allocPos, size_t allocSize);
size_t countFreeHoles(FreeListPointer this);
int printFreeList(FreeListPointer this);

#endif
