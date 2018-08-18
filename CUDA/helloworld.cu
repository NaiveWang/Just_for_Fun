/* This C file will be compiled by nvcc */
#include "stdio.h"


__global__ void add(float a,float b,float* c)
{
  *c = a + b;
}

int main()
{
  float a,b,c;
  float *dev_c=NULL;
  long status  = 0;

  a=1.2f;
  b=5.1f;

  status = cudaMalloc(&dev_c,sizeof(float));
  printf("%ld<<\n",status);
  if(status == cudaSuccess)
  {
    add<<<1,1>>>(a,b,dev_c);

    cudaMemcpy(&c,dev_c,sizeof(float),cudaMemcpyDeviceToHost);

    printf(">>>%f\n",c);

    cudaFree(dev_c);
  }
  else
  {
    printf("%ld>Allocating failed\n",(void*)dev_c);
  }
  return 0;
}
