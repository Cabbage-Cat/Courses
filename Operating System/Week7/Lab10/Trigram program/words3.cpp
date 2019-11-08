#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "time.h"

#define streql(s1, s2) (strcmp(s1, s2) == 0)


FILE *inp;
//�ֵ京���ַ��ܸ����������ظ��Ĵ�
int wordcount = 0;
// we don't know how many words there will be, so 
// for simplicity, just allocate a big array:
char *words[100000];
// this array points to strings that are allocated
// on the heap


void fatal(char *msg)
{
    printf("FATAL ERROR: %s\n", msg);
    exit(1);
}


void opentext(char *filename)
{
    inp = fopen(filename, "r");
    if (!inp) fatal("file open failed");
}


// getword -- return true if you got a word
//
//����һ������
int getword(char *word)
{
    int index = 0;
    int c = getc(inp);
    if (c <= 0) return false;
    // scan to alpha
    while (!isalpha(c)) {
		c = getc(inp);
		if (c <= 0) return false;
    }
    // scan to non-alpha and save in word
    while (isalpha(c) && (c >= 0)) {
		word[index++] = c;
		c = getc(inp);
    }
    word[index] = 0;	/* eos */
    /* be careful if c is eof indication *///���ܰ�һ���ַ��˻ص����������÷�int ungetc
    if (c >= 0) ungetc(c, inp);
    return true;
}


// string_to_heap -- move a string to the heap
//***********�˴��޸��ˣ���ͬ��word
char *string_to_heap(char *s)
{
	//�ж��ֵ����Ƿ��Ѿ��иõ��ʣ�����У����ظõ����ַ�����ַ���������ռ��½��ַ����������½���ַ
	for (int i = 0; i < wordcount; i++) {
		if (streql(s, words[i])) {
			return words[i];
		}
	}
    char *h = (char *) malloc(strlen(s) + 1);
    if (!h) fatal("no more memory for words");
    strcpy(h, s);
    return h;
}


// readwords -- read words to array
//
void readwords()
{
	// each word goes here first:
	//��ʼһ����������getword(word)��������һ�����ʴ���û�����
    char word[1024];
    while (getword(word)) {
		// then we figure out how much memory was
		// really needed, allocate that on the heap,
		// copy word to the heap memory, and save
		// a pointer in words array:
		//�ж�word�Ƿ����ֵ���û�еĵ��ʣ����û��������ֵ䣬�����ֵ䵥������+1��
		//��������´���������¼�ϴ��ַ�����ַ������ֵ+1
		//���������е��ʶ��������ֵ䣬�ظ��Ĳ�����ռ�ֻʹ�õ�һ�μ�¼ʱ���ڵĵ�ַ������"is"���ֹ���
		//��ԭ��"is"����ĵ�ַ�������¼���ֵ䣬ʡȥ�˷���ռ�Ĳ���
		words[wordcount] = string_to_heap(word);//***********�˴��޸��ˣ���ͬ��word
		wordcount++;
    }
}



// countpairs -- how many pairs (word1, word2)
//
//�ж��Ƿ���word0,word1��������������ֵ������м���ֵ+1
int countpairs(char *word1, char *word2)
{
    int count = 0;
    int i;
    for (i = 0; i < wordcount; i++) {
		// find word1:
		if (words[i] == word1) {//***********�˴��޸��ˣ���ͬ��word,�Ƚ��ַ������ڵ�ַ�����ַ���ֵ
			// if found, check if it's followed by word2:
			if (words[(i + 1) % wordcount] == word2) {//***********�˴��޸��ˣ���ͬ��word
				// yes, we found (word1, word2)
				count++;
			}
		}
    }
    return count;
}


// pick_nth -- find word after the nth pair
//
// this works like countpairs(), but it stops
// after finding n words and returns the next
// word
//
//�ж��word0word1��ϣ������ȡ���е�ĳһ�������word2
//����word2
char *pick_nth(char *word1, char *word2, int n)
{
    int count = 0;
    int i;
    for (i = 0; i < wordcount; i++) {
		if (words[i] == word1) {//***********�˴��޸��ˣ���ͬ��word,�Ƚ��ַ������ڵ�ַ�����ַ���ֵ
			if (words[(i + 1) % wordcount] == word2) {//***********�˴��޸��ˣ���ͬ��word,�Ƚ��ַ������ڵ�ַ�����ַ���ֵ
				count++;
				if (count == n)
					return words[(i + 2) % wordcount];
			}
		}
    }
    fatal("pick_nth did not find nth tuple");
	return NULL;	// this avoids a compiler warning, but
					// is never executed
}    


/* generate -- generate from trigram model */
/**/
//generate��countpairs��pick_nth�ظ��Ƚϣ���δ�Ż�
//�ܷ����ҵ�pairsʱ��¼����pairs��ַ�����飬�Ӷ������������
void generate(int howmany, char *word1, char *word2)
{
    int count;
    char sep;	/* word separator */
    printf("%s %s", word1, word2);
    for (count = 2; count < howmany; count++) {
		/* first see how many pairs there are: */
		int n = countpairs(word1, word2);
		char *newword;
		if (n == 0) fatal("no pairs found");
		/* now pick a random number from 1 to n: */
		n = (rand() % n) + 1;
		/* find nth word: */
		newword = pick_nth(word1, word2, n);
		/* shift */
		//׼����һ�����
		word1 = word2;
		word2 = newword;
		/* break the line every 10 words */
		if (count % 10 == 0) sep = '\n';
		else sep = ' ';
		/* and add periods before capitalized words */
		if (isupper(word2[0])) printf(".");
		printf("%c%s", sep, word2);
    }
    printf(".\n");
}


void main()
{
	int c=1,b=2,a=3,d=5;
	a = a+b+c;
	a += b+c;
    if(a=b)
		c = 0;
	// seed the random number generator:
	clock_t start = clock();
	srand((unsigned) time(NULL));
    opentext("F:\\Courses\\Operating System\\Week7\\Lab10\\Trigram program\\life.txt");

	//�����ֵ�
    readwords();
	//�ֵ䴴����ɣ��ر��ֵ�
	fclose(inp);
	//���¾��ӣ��������ǰ2��
    generate(10000, words[wordcount/2],
	     words[wordcount/2 + 1]);
	clock_t finish = clock();
	double duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("%lf",duration);
	getchar();	// this prevents the output window from
			// closing until the user has looked at it*/
}

