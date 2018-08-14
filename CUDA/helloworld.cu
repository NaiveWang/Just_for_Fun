/* This C file will be compiled by nvcc */
#include <stdio.h>
__global__ void add(int a,int b,int *c)
{
  *c = a+b;
}
int main()
{
  int a,b,c;
  int *dev_c;

  a=10;
  b=100;

  cudaMalloc(&dev_c,sizeof(int));

  add<<<1,1>>>(a,b,dev_c);

  cudaMemcpy(&c,dev_c,sizeof(int),cudaMemcpyDeviceToHost);

  printf(">>>%d\n",c);

  cudaFree(dev_c);
  return 0;
}
