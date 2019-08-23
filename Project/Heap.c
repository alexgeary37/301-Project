/*	Name:	Alex Geary
	ID:	1188083
*/

#include <stdlib.h>
#include "Heap.h"
#include <stdio.h>
#define TRUE 1
#define FIRST 0
#define BEST 1
#define WORST 2

typedef Heap *HeapPointer;

HeapPointer newHeap(size_t heapSize, size_t allocMode) {
	HeapPointer heapP = malloc(sizeof(Heap));
	heapP->freeList = newFreeList(heapSize);
	heapP->allocList = newAllocList();
	heapP->heapBuffer = malloc(heapSize);
	heapP->usedSize = 0;
	heapP->freeSize = heapSize;
	heapP->allocMode = allocMode;
	return heapP;
}

void destroyHeap(HeapPointer this) {
	if(this->freeList != NULL)
		destroyFreeList(this->freeList);
	if(this->allocList != NULL)
		destroyAllocList(this->allocList);
	if(this->heapBuffer != NULL)
		free(this->heapBuffer);
	free(this);
}

void *allocateHeap(HeapPointer this, size_t allocSize) {
	size_t allocatedPosition, newAllocPos;
	
	if(this->allocMode == FIRST)
		allocatedPosition = allocateFirstFitFreeList(this->freeList, allocSize);
	else if(this->allocMode == BEST)
		allocatedPosition = allocateBestFitFreeList(this->freeList, allocSize);
	else
		allocatedPosition = allocateWorstFitFreeList(this->freeList, allocSize);
	
	if(allocatedPosition == -1)
		return NULL;
	
	newAllocPos = addAllocList(this->allocList, allocatedPosition, allocSize);
	
	this->usedSize += allocSize;
	this->freeSize -= allocSize;
	
	return this->heapBuffer + newAllocPos;
}

size_t deallocateHeap(HeapPointer this, void *p) {
	size_t pos, size;
	
	ListNodePointer cur = this->allocList->head;
	
	//find memory chunk's id in the AllocList
	while(TRUE) {
		if(cur->info->pos != p - this->heapBuffer)
			if(cur->next != NULL)
				cur = cur->next;
			else
				return -1;
		else
			break;
	}
	
	pos = cur->info->pos;
	size = cur->info->size;
	
	if(removeAllocList(this->allocList, pos) == -1)
		return -1;
	
	//pass pos and size to FreeList deallocation function
	deallocateFreeList(this->freeList, pos, size);
	
	this->usedSize -= size;
	this->freeSize += size;
	
	return p - this->heapBuffer;
}

void heapStats(HeapPointer this) {
	size_t numHoles = countFreeHoles(this->freeList);
	
	printf("Ratio of the heap used: %f\n", (float)this->usedSize / 
			((float)this->usedSize + (float)this->freeSize));
	printf("Number of free holes: %zu\n", numHoles);
	printf("Average size of the free holes: %f\n", (float) this->freeSize / numHoles);
	printf("Number of allocated chunks: %zu\n", countAllocChunks(this->allocList));
}
