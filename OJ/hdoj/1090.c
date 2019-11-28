#include <stdio.h>
int a,b;
int c;


int main(void)
{
  scanf("%d",&c);
  while(c--)
  {
    scanf("%d %d",&a,&b);
    printf("%d\n",a+b);
  }
  return 0;
}
