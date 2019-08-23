/*	Name:	Alex Geary
	ID:	1188083
*/

#include <stdlib.h>
#include "FreeList.h"
#include <stdio.h>
#define TRUE 1

FreeListPointer newFreeList(size_t maxSize) {
	FreeListPointer listP = malloc(sizeof(FreeList));	
	listP->head = newListNode(NULL, newInfo(0, maxSize));
	return listP;
}

void destroyFreeList(FreeListPointer this) {
	if(this->head != NULL)
		destroyListNode(this->head);
	free(this);
}

size_t getAllocatedPosition(FreeListPointer this, ListNodePointer allocSlot, 
		ListNodePointer prevAllocSlot, size_t allocatedPosition, size_t allocSize) {
	
	if(allocSize == allocSlot->info->size) {
	
		if(allocSlot->next != NULL) {
			if(allocSlot == this->head)
				this->head = this->head->next;
			else
				prevAllocSlot->next = allocSlot->next;
		} else {
			prevAllocSlot->next = NULL;
			if(allocSlot == this->head)
				this->head = NULL;
		}
		
		destroyListNode(allocSlot);
		return allocatedPosition;
	
	} else {
		allocSlot->info->pos += allocSize;
		allocSlot->info->size -= allocSize;
	}
	
	return allocatedPosition;
}

size_t allocateFirstFitFreeList(FreeListPointer this, size_t allocSize) {
	ListNodePointer cur = this->head;
	ListNodePointer prev = cur;
	
	while(allocSize > cur->info->size) {
		if(cur->next != NULL) {
			prev = cur;
			cur = cur->next;
		} else {
			return -1;
		}
	}
	
	return getAllocatedPosition(this, cur, prev, 
			cur->info->pos, allocSize);
}

size_t allocateBestFitFreeList(FreeListPointer this, size_t allocSize) {
	ListNodePointer allocSlot, prevAllocSlot;
	
	ListNodePointer cur = this->head;
	ListNodePointer prev = cur;
	size_t freeSlotSize = 0;
	size_t allocatedPosition = -1;
	
	while(TRUE) {
		if(allocSize <= cur->info->size) {
			if(freeSlotSize == 0)
				freeSlotSize = cur->info->size;
				
			if((cur->info->size - allocSize) < freeSlotSize) {
				freeSlotSize = (cur->info->size - allocSize);
				allocatedPosition = cur->info->pos;
				prevAllocSlot = prev;
				allocSlot = cur;
				if(allocSize == cur->info->size)
					break;
			}
		}
		
		if(cur->next != NULL) {
			prev = cur;
			cur = cur->next;
		} else {
			if(allocatedPosition == -1)
				return -1;
			else
				break;
		}
	}
	
	return getAllocatedPosition(this, allocSlot, prevAllocSlot, 
			allocatedPosition, allocSize);
}

size_t allocateWorstFitFreeList(FreeListPointer this, size_t allocSize) {
	ListNodePointer allocSlot, prevAllocSlot;
	
	ListNodePointer cur = this->head;
	ListNodePointer prev = cur;
	size_t freeSlotSize = 0;
	size_t allocatedPosition = -1;
	
	while(TRUE) {
		if(allocSize <= cur->info->size && (cur->info->size) > freeSlotSize) {
			freeSlotSize = cur->info->size;
			allocatedPosition = cur->info->pos;
			prevAllocSlot = prev;
			allocSlot = cur;
		}
		
		if(cur->next != NULL) {
			prev = cur;
			cur = cur->next;
		} else {
			if(allocatedPosition == -1)
				return -1;
			else
				break;
		}
	}
	
	return getAllocatedPosition(this, allocSlot, prevAllocSlot, 
			allocatedPosition, allocSize);
}

int deallocateFreeList(FreeListPointer this, size_t allocPos, size_t allocSize) {
	ListNodePointer newNode, prev, cur;
	
	// IF list is empty then create new head
	if(this->head == NULL) {
		this->head = newListNode(NULL, newInfo(allocPos, allocSize));
	} else {
		
		cur = this->head;
		prev = cur;
		while(cur->info->pos < allocPos) {
			prev = cur;
			cur = cur->next;
		}
		
		if((allocPos + allocSize) == cur->info->pos) {
			if(allocPos == (prev->info->pos + prev->info->size)) {
				// merge with prev and next
				prev->info->size += (allocSize + cur->info->size);
				if(cur->next != NULL)
					prev->next = cur->next;
				else
					prev->next = NULL;
				destroyListNode(cur);
			} else {
				// merge with next
				cur->info->pos -= allocSize;
				cur->info->size += allocSize;
			}
		} else if(allocPos == (prev->info->pos + prev->info->size)) {
			// 3 merge with prev
			prev->info->size += allocSize;
		} else {
			// don't merge
			newNode = newListNode(cur, newInfo(allocPos, allocSize));
			
			if(cur == this->head)
				this->head = newNode;
			else
				prev->next = newNode;
		}
	}
	
	return 0;
}

size_t countFreeHoles(FreeListPointer this) {
	if(this->head == NULL) return 0;
	
	size_t numHoles = 1;
	ListNodePointer cur = this->head;
	
	while(TRUE) {
		if(cur->next != NULL) {
			cur = cur->next;
			numHoles++;
		} else {
			break;
		}
	}
	
	return numHoles;
}

int printFreeList(FreeListPointer this) {
	if(this == NULL || this->head == NULL) return -1;
	
	ListNodePointer cur = this->head;	
	int i = 1;
	while(TRUE) {
		printf("Node %d pos: %zu size: %zu\n", i, cur->info->pos, cur->info->size);
		if(cur->next != NULL)
			cur = cur->next;
		else
			break;
		i++;
	}
	
	return 0;
}
