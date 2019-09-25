
#include <stdio.h>
#include <stdlib.h>

int main()
{

	char* ss1 = "0123456789";
	char ss2[] = "0123456789";
	char ss3[100] = "0123456789";

	int ss4[100];

	char q1[] = "abc";
	char q2[] = "a\n";
	char* q3 = "a\n";

	char *str1 = (char*) malloc(100);
	void *str2 = (void*) malloc(100);

	printf("sizeof(ss1) is %d\n", sizeof(ss1));
	printf("sizeof(ss2) is %d\n", sizeof(ss2));
	printf("sizeof(ss3) is %d\n", sizeof(ss3));
	printf("sizeof(ss4) is %d\n", sizeof(ss4));

	printf("sizeof(q1) is %d\n", sizeof(q1));
	printf("sizeof(q2) is %d\n", sizeof(q2));
	printf("sizeof(q3) is %d\n", sizeof(q3));

	printf("sizeof(str1) is %d\n", sizeof(str1));
	printf("sizeof(str2) is %d\n", sizeof(str2));
	printf("sizeof'a' is %d\n", sizeof('a'));


	free(str1);
	free(str2);

	return 0;
}
