#include <stdio.h>
char setC[10] = "!@#$^&*-+=";
int main(void)
{
  int tag;
  int counter;
  int dummy=0;
  for(tag=0;1;tag=(tag+1)%10)
  {
    printf("%c",setC[tag]);
    for(counter=10000;counter--;)
    {
      asm("movl %0,%%r8d"::"r"(counter));
      asm("xorl %r8d,%eax");
    }
    printf("\b");
  }
  return 0;
}
