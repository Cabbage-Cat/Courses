#include <stdio.h>
#include <string.h>
int partition(char* a,int l,int r){
  int pivot,i,j,t;
  pivot = a[l];
  i = l; j = r+1;

  while (1){
    do ++i;
    while (a[i] <= pivot && i <=r);
    do --j;
    while (a[j] > pivot);
    if (i>=j) break;
    t = a[i]; 
    a[l] = a[j];
    a[j] = t;
  }
  t = a[l];
  a[l] = a[j];
  a[j] = t;
  return j;
}

void sort(char a[],int l,int r){
  int j;
  if (l<r){
    j = partition(a,l,r);
    sort(a,l,j-1);
    sort(a,j+1,r);
  }
}

void main(int argc,char** argv){
  char* a = NULL;
  if (argc>1)
    a = argv[1];
  else 
    a = "Asuna is the best char!";
  printf("Unsorted: \"%s\"\n",a);
  sort(a,0,strlen(a)-1);
  printf("Sorted :   \"%s\"\n",a);
}
