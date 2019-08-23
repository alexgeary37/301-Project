/*	Name:	Alex Geary
	ID:	1188083
*/

#include <stdlib.h>
#include "Info.h"

InfoPointer newInfo(size_t pos, size_t size) {
	InfoPointer infoP = malloc(sizeof(Info));
	infoP->pos = pos;
	infoP->size = size;
	return infoP;
}
