#include "demo.h"
int main(void)
{
  int a=1000;
  int b=1234;
  int c;

  c = sum(a,b);
  swap(&a,&c);
  return 0;
}
