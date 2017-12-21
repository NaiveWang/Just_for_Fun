#include <stdio.h>
#include <stdlib.h>
/** Assembler **/
int main(char *arg0,char *arg1)
{
  FILE fp0=fopen(arg0,"r");
  FILE fp1=fopen(arg1,"w");
  //fp0 = fp1
  fclose(fp0);
  fclose(fp1);
  return 0;
}
