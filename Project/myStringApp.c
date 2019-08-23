/*	Name:	Alex Geary
	ID:	1188083
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Heap.h"
#define TRUE 1
#define FALSE 0
#define FIRST 0
#define BEST 1
#define WORST 2
#define ARRAY_LENGTH 10000


// prototypes
int parseArgs(int argc, char **argv, size_t *allocMode);


int main(int argc, char **argv) {
	size_t heapSize, allocMode;
	HeapPointer heap;
	int maxIndex = 0;
	char **array = (char**)calloc(ARRAY_LENGTH, sizeof(char*));
	char *line = (char*)malloc(100000*sizeof(char));
	
	
	// parse program arguments and assign allocation mode
	if(parseArgs(argc, argv, &allocMode) == FALSE)
		return -1;
	
	// assign size of heap and create heap
	heapSize = atoi(argv[2]);
	heap = newHeap(heapSize, allocMode);
	
	/* read each line of input from file 
	until there are none left */
	printf("\n");
	int i = 0;
	while(fgets(line, 100000, stdin) != NULL) {
		// remove \r and \n from line of input
		if(line[strlen(line) - 2] == '\r')
			line[strlen(line) - 2] = '\0';
		
		/* IF line starts with '+' THEN allocate room on heap for it 
		and store the line in the first empty element of the array */
		if(line[0] == '+') {
			while(array[i] != NULL) i++;
			
			array[i] = allocateHeap(heap, strlen(line) - 1);
			if(array[i] == NULL) {
				printf("allocation failed!\n");
				heapStats(heap);
				return 0;
			}
			
			strcpy(array[i], line + 2);
			
			if(i > maxIndex) maxIndex = i;
				
		/* OTHERWISE, find the string that that matches the line 
		in the array if it exists and remove it from the array */
		} else {
			int deallocPos = 0;
			while(TRUE) {
				if(array[deallocPos] != NULL) {
					if(strncmp(array[deallocPos], line + 2, strlen(line) - 2) != 0) {
						if(deallocPos == maxIndex) {
							printf("string '%s' does not exist\n", line + 2);
							return 0;
						}
					} else {
						break;
					}
				}
				
				if(deallocPos != (ARRAY_LENGTH - 1)) {
					deallocPos++;
				} else {
					printf("array is full\n");
					return 0;
				}
			}
			
			if(deallocateHeap(heap, array[deallocPos]) == -1) {
				printf("'%s' deallocation failed\n", line + 2);
				return -1;
			}
			
			array[deallocPos] = NULL;
			i = 0;
		}
	}
	
	// print heap stats
	heapStats(heap);
	
	// free all allocated memory and terminate program
	free(line);
	free(array);
	destroyHeap(heap);
	return 0;
}


// parses the program arguments
int parseArgs(int argc, char **argv, size_t *allocMode) {
	int hasParsed = TRUE;
	char *usage;
	
	usage = "Usage: myStringApp -h <heapSize> -a <[first|best|worst]>\n";
	
	if(argc != 5) {
		printf("%s", usage);
		return FALSE;
	}
	
	if(strcmp(argv[1], "-h") != 0)
		hasParsed = FALSE;
	else if(argv[2] == NULL || atoi(argv[2]) == 0)
		hasParsed = FALSE;
	else
		if(strcmp(argv[3], "-a") != 0)
			hasParsed = FALSE;
	
	if(strcmp(argv[4], "first") == 0)
		*allocMode = FIRST;
	else if(strcmp(argv[4], "best") == 0)
		*allocMode = BEST;
	else if(strcmp(argv[4], "worst") == 0)
		*allocMode = WORST;
	else
		hasParsed = FALSE;
	
	if(hasParsed == FALSE) {
		printf("%s", usage);
		return FALSE;
	} else {
		return TRUE;
	}
}
