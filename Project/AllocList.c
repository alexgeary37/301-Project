/*	Name:	Alex Geary
	ID:	1188083
*/

#include <stdlib.h>
#include "AllocList.h"
#include <stdio.h>
#define TRUE 1

AllocListPointer newAllocList() {
	AllocListPointer listP = malloc(sizeof(AllocList));
	listP->head = NULL;
	return listP;
}

void destroyAllocList(AllocListPointer this) {
	if(this->head != NULL)
		destroyListNode(this->head);
	free(this);
}

size_t addAllocList(AllocListPointer this, size_t allocPos, size_t allocSize) {
	ListNodePointer cur, newNode;
	
	newNode = newListNode(NULL, newInfo(allocPos, allocSize));
	
	if(this->head == NULL) {
		this->head = newNode;
	} else {
		cur = this->head;
		while(cur->next != NULL)
			cur = cur->next;
		
		cur->next = newNode;
	}
	
	return allocPos;
}

size_t removeAllocList(AllocListPointer this, size_t allocPos) {	
	size_t removedChunkSize;
	
	if(this->head == NULL)
		return -1;
	
	ListNodePointer cur = this->head;
	ListNodePointer prev = cur;
	
	while(TRUE) {
		if(cur->info->pos != allocPos) {
			if(cur->next == NULL)
				return -1;
			prev = cur;
			cur = cur->next;
		} else {
			if(cur == this->head)
				if(this->head->next != NULL)
					this->head = this->head->next;
				else
					this->head = NULL;
			else
				if(cur->next != NULL)
					prev->next = cur->next;
				else
					prev->next = NULL;
			
			removedChunkSize = cur->info->size;
			destroyListNode(cur);
			return removedChunkSize;
		}
	}
}

size_t countAllocChunks(AllocListPointer this) {
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

int printAllocList(AllocListPointer this) {
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
