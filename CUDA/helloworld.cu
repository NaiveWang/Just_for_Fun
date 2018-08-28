/* This C file will be compiled by nvcc */
#include "stdio.h"


unsigned char a[10]={2,3,4,5,6,7,8,9,10,1};
unsigned char b[10]={1,2,3,4,5,6,7,8,9,10};
__global__ void add(unsigned char* a,unsigned char* b,unsigned char* c,int n)
{
  int i=blockDim.x * blockIdx.x + threadIdx.x;
  if(i<n)
    c[i] = a[i]*0.7f + b[i]*0.3f;
}

int main()
{
  unsigned char* dev_c=NULL;
  unsigned char* dev_a=NULL;
  unsigned char* dev_b=NULL;
  unsigned char c[10];

  int counter;

  long status  = 0;
  cudaMalloc(&dev_a,sizeof(unsigned char)*10);
  cudaMalloc(&dev_b,sizeof(unsigned char)*10);
  status = cudaMalloc(&dev_c,sizeof(unsigned char)*10);
  printf("%ld<<\n",status);
  if(status == cudaSuccess)
  {
    cudaMemcpy(dev_a,a,sizeof(unsigned char)*10,cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b,b,sizeof(unsigned char)*10,cudaMemcpyHostToDevice);

    add<<<10/256+1,256>>>(dev_a,dev_b,dev_c,10);

    cudaMemcpy(c,dev_c,sizeof(unsigned char)*10,cudaMemcpyDeviceToHost);

    for(counter=0;counter<10;counter++)
    {
      printf("%d ",c[counter]);
    }
    printf("\n");

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
  }
  else
  {
    printf("%ld>Allocating failed\n",(long)dev_c);
  }
  return 0;
}
