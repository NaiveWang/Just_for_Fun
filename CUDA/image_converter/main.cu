#include <stdio.h>
//#include "bmp_loader.h"
//#include "converter.h"
//#include <unistd.h>
#include "bmp_lib.h"
#include <sys/time.h>
#include <stdlib.h>
#define LINEAR_R 0.2126
#define LINEAR_G 0.7152
#define LINEAR_B 0.0722

bmpa* loadimage_rgb(char* file_name)
{
  FILE* fp=NULL;
  bmpa* a = (bmpa*)malloc(sizeof(bmpa));

  //open file
  fp=fopen(file_name,"rb");
  //read header
  fread(a->header,sizeof(unsigned char),54,fp);
  //get height and width
  a->w=*(int*)(a->header+18);
  a->h=*(int*)(a->header+22);
  //allocate
  a->type = BMP_RGB;
  a->array = malloc(sizeof(unsigned char)*3*a->w*a->h);
  //read content
  fread(a->array,sizeof(unsigned char),3*a->w*a->h,fp);
  //close file
  fclose(fp);
  //return pointer
  return a;
}
void free_image(bmpa* a)
{
  free(a->array);
  free(a);
}
void saveimage_grey(bmpa* a,char* file_name)
{
  FILE *fp=NULL;
  fp = fopen(file_name,"wb");
  fwrite(a->header,sizeof(char),54,fp);
  fwrite(a->array,sizeof(char)*3,a->w*a->h,fp);
  //fwrite((int*)EOF,sizeof(int),1,fp);
  fclose(fp);
}

__global__ void gpu_thread_greyscaler(unsigned char** base)
{
  int counter=8000*8000;
  while(counter--)
  {
    *(unsigned char*)(base + 3 * counter) =
    *(unsigned char*)(base + 3 * counter + 1) =
    *(unsigned char*)(base + 3 * counter + 2) =
    (unsigned char)(
      (*(unsigned char*)(base + 3 * counter)) * LINEAR_R +
      (*(unsigned char*)(base + 3 * counter + 1)) * LINEAR_G +
      (*(unsigned char*)(base + 3 * counter + 2)) * LINEAR_B);
  }
  /*
  int i=threadIdx.x;
  *(unsigned char*)(base+i*3) =
  *(unsigned char*)(base+i*3 + 1) =
  *(unsigned char*)(base+i*3 + 2) =
  (unsigned char)(
    (*(unsigned char*)(base+i*3)) * LINEAR_R +
    (*(unsigned char*)(base+i*3 + 1)) * LINEAR_G +
    (*(unsigned char*)(base+i*3 + 2)) * LINEAR_B);*/
}

int convert_gpu(bmpa* a)
{
  unsigned char* dev=NULL;
  long stat;
  //printf("N : %d",sizeof(char)*a->w*a->h*3);
  stat = cudaMalloc(&dev,sizeof(char)*a->w*a->h*3);
  if(stat==cudaSuccess)
  {
    stat = cudaMemcpy(dev,a->array,sizeof(char)*a->w*a->h*3,cudaMemcpyHostToDevice);
    printf("W : %ld\n",stat);
    //computing section
    gpu_thread_greyscaler<<<1,1>>>(&dev);
    stat = cudaMemcpy(a->array,dev,sizeof(char)*a->w*a->h*3,cudaMemcpyDeviceToHost);
    //printf("W : %ld\n",stat);
    cudaFree(dev);
    return 0;
  }
  else
  {
    printf("E : %ld\n",stat);
    return 1;
  }

}
double get_time()
{
  static struct timeval t;

  gettimeofday(&t,NULL);
  return t.tv_sec*1000.0 + t.tv_usec/1000.0;
}

void convert_cpu(bmpa* a)
{
  int counter = a->w * a->h;
  while(counter--)
  {
    *(unsigned char*)(a->array + 3 * counter) =
    *(unsigned char*)(a->array + 3 * counter + 1) =
    *(unsigned char*)(a->array + 3 * counter + 2) =
    (unsigned char)(
      (*(unsigned char*)(a->array + 3 * counter)) * LINEAR_R +
      (*(unsigned char*)(a->array + 3 * counter + 1)) * LINEAR_G +
      (*(unsigned char*)(a->array + 3 * counter + 2)) * LINEAR_B);
  }
}
int main(int argc, char *argv[])
{
  bmpa *bp=NULL;
  double t;
  switch(argv[1][0])
  {
    case 'g':
      printf("Loading file...");
      t=get_time();
      bp=loadimage_rgb("image.bmp");
      t=get_time()-t;
      printf("Time Elapsed:%lfms\n",t);

      printf("Computing using GPU...");
      t=get_time();
      convert_gpu(bp);
      t=get_time()-t;
      printf("Time Elapsed:%lfms\n",t);

      //printf("<>%d<>%d<>\n",bp->w,bp->h);

      printf("Saving file...");
      t=get_time();
      saveimage_grey(bp,"grey.bmp");
      t=get_time()-t;
      printf("Time Elapsed:%lfms\n",t);
      free_image(bp);
      return 0;
    case 'c':
      printf("Loading file...");
      t=get_time();
      bp=loadimage_rgb("image.bmp");
      t=get_time()-t;
      printf("Time Elapsed:%lfms\n",t);

      printf("Computing using CPU...");
      t=get_time();
      convert_cpu(bp);
      t=get_time()-t;
      printf("Time Elapsed:%lfms\n",t);

      //printf("<>%d<>%d<>\n",bp->w,bp->h);

      printf("Saving file...");
      t=get_time();
      saveimage_grey(bp,"grey.bmp");
      t=get_time()-t;
      printf("Time Elapsed:%lfms\n",t);
      free_image(bp);
      return 0;
    default:
      return -1;
  }
  //return 0;
}
