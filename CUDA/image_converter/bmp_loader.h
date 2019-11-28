#ifndef BMP_LOADER_H
#define BMP_LOADER_H
#include "bmp_lib.h"
/**
  * This library will load a bmp file from current directory,
  * and return a
  */
bmpa* loadimage_rgb(char*);
void free_image(bmpa*);
void saveimage_grey(bmpa*,char*);

#endif
