/*	Name:	Alex Geary
	ID:	1188083
*/

#ifndef INFO_H
#define INFO_H

typedef struct Info {
	size_t pos, size;
} Info;

typedef Info *InfoPointer;

InfoPointer newInfo(size_t pos, size_t size);

#endif
