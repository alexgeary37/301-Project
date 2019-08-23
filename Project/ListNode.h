/*	Name:	Alex Geary
	ID:	1188083
*/

#ifndef LISTNODE_H
#define LISTNODE_H
#include "Info.h"

typedef struct ListNode {
	struct ListNode *next;
	InfoPointer info;
} ListNode;

typedef ListNode *ListNodePointer;

ListNodePointer newListNode(ListNodePointer next, InfoPointer info);
void destroyListNode(ListNodePointer nodeP);

#endif
