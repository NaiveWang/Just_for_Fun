#ifndef PASSENBLER_H
#define PASSENBLER_H
#include <stdio.h>
#include "PCore.h"
#include "PFile.h"
FILE *input,*output;
int PTNum,PINum,MNum,ConnNum;
int main(int argv,char** argc)
{
  if(argv!=3)
  {
    printf("Error : lack of input file or output file.\n");
    return -1;
  }
  //argc+1: input file, text.
  //argc+2: output file, binary.
  return 0;
}
#endif
