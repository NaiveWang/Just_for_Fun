#include "bmp_loader.h"
#include <stdlib.h>
#include <stdio.h>

bmpa* loadimage_rgb(char* file_name)
{
  FILE* fp=NULL;
  bmpa* a = malloc(sizeof(bmpa));

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
