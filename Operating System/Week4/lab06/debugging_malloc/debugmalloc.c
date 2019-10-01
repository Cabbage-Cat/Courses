#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "dmhelper.h"
#include <stdio.h>
unsigned int BKDRHash(char* str){
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
	while (*str){
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

typedef struct Node{
	int size;
	struct Node* next;
	unsigned int hashcode;
	char* filename;
	int linenum;
	int fence;
}Node;

Node* ll = NULL;
Node** pll = &ll;
int heap_error_flag = 0;
/* Wrappers for malloc and free */

void *MyMalloc(size_t size, char *filename, int linenumber) {
	Node* u = (Node*)malloc(sizeof(Node) + size + sizeof(int));
	u->size = size;  u->fence = 0x1A1A1A1A; u->next = ll; u->filename = filename; u->linenum = linenumber;
	u->hashcode = BKDRHash(filename) + linenumber; 
	*((int*)((char*)(u + 1) + size)) = 0x1A1A1A1A;
	*pll = u;
	return u+1;
}

void MyFree(void *ptr, char *filename, int linenumber) {
	Node* u = (Node*)ptr - 1;
	Node* cur_node = *pll; int find_flag = 0;
	while (cur_node != NULL) {
		if (cur_node == u) { find_flag = 1; break; }
		cur_node = cur_node->next;
	}
	if (!find_flag) { heap_error_flag = 1; error(4, filename, linenumber); return; }
	unsigned int hashcode = BKDRHash(u->filename) + u->linenum;
	if (hashcode != u->hashcode) { heap_error_flag = 1; error(3,filename,linenumber); }
	if (cur_node->fence != 0x1A1A1A1A) { heap_error_flag = 1; error(1, filename, linenumber); return; }
	if (*((int*)((char*)(cur_node + 1) + cur_node->size)) != 0x1A1A1A1A) { heap_error_flag = 1; errorfl(2,u->filename,u->linenum,filename,linenumber); return; }
	if (*pll == cur_node) { 
		*pll = cur_node->next; 
		free((void*)cur_node);
		return; }
	
	Node* lastnode = *pll;
	while (lastnode->next != NULL) {
		if (lastnode->next == cur_node) {
			lastnode->next = cur_node->next;
			free((void*)cur_node);
			break;
		}
		lastnode = lastnode->next;
	}
}

void printblock(int size, char* filename, int linenum){
	printf("%d bytes, created at %s, line %d\n", size, filename, linenum);
}

/* returns number of bytes allocated using MyMalloc/MyFree:
	used as a debugging tool to test for memory leaks */
int AllocatedSize() {
	int res = 0;
	Node* u = *pll;
	while (u != NULL) {
		res += u->size;
		u = u->next;
	}
	return res;
}



/* Optional functions */

/* Prints a list of all allocated blocks with the
	filename/line number when they were MALLOC'd */
void PrintAllocatedBlocks() {
	printf("Currently allocated blocks:\n");
	Node* u = *pll;
	while (u != NULL) {
		printblock(u->size, u->filename, u->linenum);
		u = u->next;
	}
	return;
}

/* Goes through the currently allocated blocks and checks
	to see if they are all valid.
	Returns -1 if it receives an error, 0 if all blocks are
	okay.
*/
int HeapCheck() {
	Node* u = *pll;
	while (u != NULL) {
		MyFree(u+1, u->filename, u->linenum);
		u = u->next;
	}
	if (heap_error_flag) return -1;
	return 0;
}
