#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "dmhelper.h"
#include <stdio.h>


/* Wrappers for malloc and free */

void *MyMalloc(size_t size, char *filename, int linenumber) {
	return (malloc(size));
}

void MyFree(void *ptr, char *filename, int linenumber) {
	free(ptr);	
}

/* returns number of bytes allocated using MyMalloc/MyFree:
	used as a debugging tool to test for memory leaks */
int AllocatedSize() {
	return 0;
}



/* Optional functions */

/* Prints a list of all allocated blocks with the
	filename/line number when they were MALLOC'd */
void PrintAllocatedBlocks() {
	return;
}

/* Goes through the currently allocated blocks and checks
	to see if they are all valid.
	Returns -1 if it receives an error, 0 if all blocks are
	okay.
*/
int HeapCheck() {
	return 0;
}
