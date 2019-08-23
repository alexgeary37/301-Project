/*	Name:	Alex Geary
	ID:	1188083
*/

#include <stdlib.h>
#include "ListNode.h"

ListNodePointer newListNode(ListNodePointer next, InfoPointer info) {
	ListNodePointer nodeP = malloc(sizeof(ListNode));
	nodeP->next = next;
	nodeP->info = info;
	return nodeP;
}

void destroyListNode(ListNodePointer this) {
	free(this->info);
	free(this);
}
