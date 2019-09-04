#include <stdio.h>
#include <string.h>

#define MAXLINE_LENGTH 80

char Buffer[MAXLINE_LENGTH];

char * readString(void)
{
    int nextInChar;
    int nextLocation;
	
    printf("Input> ");
    nextLocation = 0;
    while ((nextInChar = getchar()) != '\n' &&
		nextInChar != EOF) {
        Buffer[nextLocation++] = nextInChar;
    }
    return Buffer;
}


int main(int argc, char * argv[]) 
{
	char * newString;
	do {
		newString = readString();
		printf("%s\n", newString);
	} while (strncmp(newString, "exit", 4));
	return 0;
}



