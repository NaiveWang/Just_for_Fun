#include <stdio.h>
int a,b;

int main(void)
{
  while(1)
  {
    scanf("%d %d",&a,&b);
    if(a||b)
      printf("%d\n",a+b);
    else
      break;
  }
  return 0;
}
