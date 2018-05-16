#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void handler()
{
  //handler section, handle the signal
  printf("FBI Warning.\n");
  exit(12);
}
int main(void)
{
  signal(SIGSEGV,handler);
  int *a=NULL;
  *a=1000000;
  return 0;
}
