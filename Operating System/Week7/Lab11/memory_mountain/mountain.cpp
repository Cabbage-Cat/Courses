/* mountain.c - Generate the memory mountain. */
/* $begin mountainmain */
#include <windows.h>
#include <iostream>
#include <fstream>
#include "fcyc2.h" /* K-best measurement timing routines */
#include "clock.h" /* routines to access the cycle counter */
using namespace std;

#define MINBYTES (1 << 10)  /* Working set size ranges from 1 KB */
#define MAXBYTES (1 << 24)  /* ... up to 128 MB */
#define MAXSTRIDE 16        /* Strides range from 1 to 32 */
#define STRIDESTRIDE 1     /* increment stride by this amount each time */
#define MAXELEMS MAXBYTES/sizeof(int) 

int mtdata[MAXELEMS];         /* The array we'll be traversing */

/* $end mountainmain */
void init_data(int *data, int n);
void test(int elems, int stride);
double run(int size, int stride, double Mhz);

/* $begin mountainmain */
int main()
{
	ofstream outClientFile("out.txt", ios::out);
	if(!outClientFile){
		cerr << "File could not be opened"<<endl;
		exit(1);
	}

    int size;        /* Working set size (in bytes) */
    int stride;      /* Stride (in array elements) */
    double Mhz;      /* Clock frequency */
	LARGE_INTEGER litmp; 
	
   
	QueryPerformanceFrequency(&litmp);          
//	Mhz = mhz();//(double)litmp.QuadPart; /* get the clock frequency */
	//Mhz = (double) litmp.QuadPart;
	Mhz = 2340;
/* $end mountainmain */
    /* Not shown in the text */
	outClientFile << "Clock frequency is approx" << Mhz << "\nMemory mountain (MB/sec)\n";

	outClientFile <<"\t";
    for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE)
	outClientFile << stride <<"\t";
    outClientFile <<"\n";

	 init_data(mtdata, MAXELEMS); /* Initialize each element in data to 1 */
 /* $begin mountainmain */
    for (size = MAXBYTES; size >= MINBYTES; size >>= 1) {
/* $end mountainmain */
	/* Not shown in the text */
	if (size > (1 << 20))
	    //printf("%dm\t", size / (1 << 20));
		outClientFile << (size /(1 <<20)) << "m\t";
	else
	   // printf("%dk\t", size / 1024");
		outClientFile << (size /1024) <<"k\t";

/* $begin mountainmain */
	for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE) {
	  //  printf("%.0f\t", run(size, stride, Mhz));
		outClientFile << (run(size, stride, Mhz)) << "\t";
	}
	//printf("\n");
	outClientFile << "\n";
    }
//	Sleep(50000);
    //exit(0);
	return 0;
}
/* $end mountainmain */

/* init_data - initializes the array */
void init_data(int *data, int n)
{
    int i;

    for (i = 0; i < n; i++)
	data[i] = 1;
}

/* $begin mountainfuns */
void test(int elems, int stride) /* The test function */
{
    int i, result = 0; 
    volatile int sink; 

    for (i = 0; i < elems; i += stride)
	result += mtdata[i];
    sink = result; /* So compiler doesn't optimize away the loop */
}

/* Run test(elems, stride) and return read throughput (MB/s) */
double run(int size, int stride, double Mhz)
{
    double cycles;
    int elems = size / sizeof(int); 

    test(elems, stride);                     /* warm up the cache */
    cycles = fcyc2(test, elems, stride, 1);  /* call test(elems,stride) */
    return ((size/stride)/(cycles/Mhz)); /* convert cycles to MB/s */
//	return ((Mhz)/cycles)/1000;
//	return cycles;
//	return (size/stride) /cycles;
}
/* $end mountainfuns */


