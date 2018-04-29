#include <stdio.h>
#include "PVM.h"
int main(int argv,char **argc)
{
  printf("%s\n",*(argc+1));

  return 0;
}
