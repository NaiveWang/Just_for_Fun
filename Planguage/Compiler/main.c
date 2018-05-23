#include <stdio.h>
#include "compiler.h"
int main(void)
{
  int ntoken;
  do{
    //
    ntoken = lexNextToken();
    //printf("%d\n",(int)ntoken);
  }while(ntoken);
  return 0;
}
