#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "time.h"

#define streql(s1, s2) (strcmp(s1, s2) == 0)


FILE *inp;
//字典含的字符总个数，包括重复的词
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
//读入一个单词
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
    /* be careful if c is eof indication *///功能把一个字符退回到输入流中用法int ungetc
    if (c >= 0) ungetc(c, inp);
    return true;
}


// string_to_heap -- move a string to the heap
//***********此处修改了，不同于word
char *string_to_heap(char *s)
{
	//判断字典中是否已经有该单词，如果有，返回该单词字符串地址，否则分配空间新建字符串，返回新建地址
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
	//初始一个缓冲区，getword(word)将读到的一个单词存入该缓冲区
    char word[1024];
    while (getword(word)) {
		// then we figure out how much memory was
		// really needed, allocate that on the heap,
		// copy word to the heap memory, and save
		// a pointer in words array:
		//判断word是否是字典里没有的单词，如果没有则加入字典，并且字典单词总数+1，
		//如果有则不新创建，仅记录上次字符串地址，计数值+1
		//文章里所有单词都将加入字典，重复的不分配空间只使用第一次记录时所在的地址，比如"is"出现过，
		//则将原来"is"分配的地址在这里记录如字典，省去了分配空间的操作
		words[wordcount] = string_to_heap(word);//***********此处修改了，不同于word
		wordcount++;
    }
}



// countpairs -- how many pairs (word1, word2)
//
//判断是否有word0,word1组合连续出现在字典里，如果有计数值+1
int countpairs(char *word1, char *word2)
{
    int count = 0;
    int i;
    for (i = 0; i < wordcount; i++) {
		// find word1:
		if (words[i] == word1) {//***********此处修改了，不同于word,比较字符串所在地址而非字符串值
			// if found, check if it's followed by word2:
			if (words[(i + 1) % wordcount] == word2) {//***********此处修改了，不同于word
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
//有多个word0word1组合，随机读取其中的某一个后面的word2
//返回word2
char *pick_nth(char *word1, char *word2, int n)
{
    int count = 0;
    int i;
    for (i = 0; i < wordcount; i++) {
		if (words[i] == word1) {//***********此处修改了，不同于word,比较字符串所在地址而非字符串值
			if (words[(i + 1) % wordcount] == word2) {//***********此处修改了，不同于word,比较字符串所在地址而非字符串值
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
//generate中countpairs和pick_nth重复比较，尚未优化
//能否在找到pairs时记录所有pairs地址入数组，从而避免查找两次
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
		//准备下一次造句
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

	//创建字典
    readwords();
	//字典创建完成，关闭字典
	fclose(inp);
	//组新句子，传入句子前2词
    generate(10000, words[wordcount/2],
	     words[wordcount/2 + 1]);
	clock_t finish = clock();
	double duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("%lf",duration);
	getchar();	// this prevents the output window from
			// closing until the user has looked at it*/
}

