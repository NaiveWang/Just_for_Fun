#ifndef CONVERTER_H
#define CONVERTER_H
#include "bmp_lib.h"
#define LINEAR_R 0.2126
#define LINEAR_G 0.7152
#define LINEAR_B 0.0722
//void convert_cpu(bmpa*);
int convert_gpu(bmpa*);

#endif
