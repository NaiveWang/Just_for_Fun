#ifndef BMP_LIB_H
#define BMP_LIB_H
/**
  * This header file contains a protocal which is aim to manipulate an array which describes an image with RGB dimentions,
  * each dimention is stored using one byte.
  * note : this header contains control flow computes the pointers user needs, but it didn't contains memory allocating and releasing
  * steps.
  */
#define BMP_RGB 0x00
#define BMP_GREY 0x01
/* The data structure of a image, with grey mode and rgb mode */
typedef struct bit_map_cell_rgb
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
}bmpc_rgb;
typedef struct bit_map_cell_grey
{
  unsigned char scale;
}bmpc_grey;
typedef struct bit_map_array
{
  char type;
  int w;
  int h;
  char header[54];
  void* array;
}bmpa;
/* Utility functions, including cell locating, etc*/

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
void saveimage(bmpa* a,char* file_name)
{
  FILE *fp=NULL;
  fp = fopen(file_name,"wb");
  fwrite(a->header,sizeof(char),54,fp);
  fwrite(a->array,sizeof(char)*3,a->w*a->h,fp);
  //fwrite((int*)EOF,sizeof(int),1,fp);
  fclose(fp);
}

#endif
