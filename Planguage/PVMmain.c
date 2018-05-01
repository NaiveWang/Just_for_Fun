#include <stdio.h>
#include "PVM.h"
int main(int argv,char **argc)
{

  if(argv==1)
  {
    printf("PVM Warning: No input file.\n");
    return -1;
  }
  printf("Dispatching %s\n",*(argc+1));
  VMReadFile(*(argc+1));
  VMStartUp();
  return 0;
}
