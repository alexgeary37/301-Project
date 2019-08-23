/*	Name:	Alex Geary
	ID:	1188083
*/

#ifndef ALLOCLIST_H
#define ALLOCLIST_H
#include "ListNode.h"

typedef struct AllocList {
	ListNodePointer head;
} AllocList;

typedef AllocList *AllocListPointer;

AllocListPointer newAllocList();
InfoPointer newInfo(size_t pos, size_t size);
void destroyAllocList(AllocListPointer this);
size_t addAllocList(AllocListPointer this, size_t allocPos, size_t allocSize);
size_t removeAllocList(AllocListPointer this, size_t allocPos);
size_t countAllocChunks(AllocListPointer this);
int printAllocList(AllocListPointer this);

#endif
