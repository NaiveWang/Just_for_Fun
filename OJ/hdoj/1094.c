#include <stdio.h>
int c;
int sum;
int tmp;

int main(void)
{
  while(scanf("%d",&c)!=EOF)
  {
    sum=0;
    while(c--)
    {
      scanf("%d",&tmp);
      sum+=tmp;
    }
    printf("%d\n",sum);
  }
  return 0;
}
