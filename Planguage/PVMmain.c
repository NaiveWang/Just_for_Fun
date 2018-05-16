#include <stdio.h>
#include "PVM.h"
int main(int argv,char **argc)
{
  signal(SIGSEGV,handlerSegFault);
  if(argv==1)
  {
    printf("PVM Warning: No input file.\n");
    return -1;
  }
  printf("Reading %s\n",*(argc+1));
  VMReadFile(*(argc+1));
  //checkStructure(VMpe);
  clearFile(VMpe,CODE_RESERVED);
  printf("execution file loaded.\n");
  dispatcher();
  VMStartUp();
  return 0;
}
