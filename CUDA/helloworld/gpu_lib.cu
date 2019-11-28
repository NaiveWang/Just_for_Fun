#include "gpu_lib.cuh"
__global__ void add(unsigned char* a,unsigned char* b,unsigned char* c,int n)
{
  int i=blockDim.x * blockIdx.x + threadIdx.x;
  if(i<n)
    c[i] = a[i]*0.7f + b[i]*0.3f;
}
extern "C" void func(unsigned char* a,unsigned char *b,unsigned char *c)
{
  unsigned char* dev_c=NULL;
  unsigned char* dev_a=NULL;
  unsigned char* dev_b=NULL;

  long status  = 0;
  cudaMalloc(&dev_a,sizeof(unsigned char)*10);
  cudaMalloc(&dev_b,sizeof(unsigned char)*10);
  status = cudaMalloc(&dev_c,sizeof(unsigned char)*10);
  //printf("%ld<<\n",status);
  if(status == cudaSuccess)
  {
    cudaMemcpy(dev_a,a,sizeof(unsigned char)*10,cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b,b,sizeof(unsigned char)*10,cudaMemcpyHostToDevice);

    add<<<10/256+1,256>>>(dev_a,dev_b,dev_c,10);

    cudaMemcpy(c,dev_c,sizeof(unsigned char)*10,cudaMemcpyDeviceToHost);



    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
  }
}
