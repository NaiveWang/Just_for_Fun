/* This C file will be compiled by nvcc */
#include <stdio.h>
//#include "gpu_lib.cuh"

unsigned char a[10]={2,3,4,5,6,7,8,9,10,1};
unsigned char b[10]={1,2,3,4,5,6,7,8,9,10};

void func(unsigned char*,unsigned char*,unsigned char*);
int main()
{
  unsigned char c[10];
  int counter;

  func(a,b,c);
  for(counter=0;counter<10;counter++)
  {
    printf("%d ",c[counter]);
  }
  printf("\n");

  return 0;
}
