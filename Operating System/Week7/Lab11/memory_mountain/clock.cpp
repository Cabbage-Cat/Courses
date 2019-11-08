#include <windows.h>
#include <time.h>
#include "clock.h"

#include "tsc.h"


tsc_t begin, end;
tsc_t res;

//int res;
double result;
void start_counter()
{
	begin= tsc_get(); 
//Part1 = litmp.QuadPart;
}

/*
double get_counter()
{
	
	end = tsc_get();
	res = (int)(end - begin);
	result = (double) res;
	return result;
}
*/
double get_counter()
{
	signed __int64 temp;

	end = tsc_get();
	temp = end - begin;
	result = (double) temp;
	return result;
}

double ovhd()
{
  /* Do it twice to eliminate cache effects */
  int i;
  double result;
  for (i = 0; i < 2; i++) {
    start_counter();
    result = get_counter();
  }
  return result;
}

double mhz()
{
	double rate;
	start_counter();
	Sleep(2);
	rate = get_counter() /(1e6*2);
	return rate;
}