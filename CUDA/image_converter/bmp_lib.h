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

#endif
