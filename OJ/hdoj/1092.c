#include <stdio.h>
int c;
int sum;
int tmp;

int main(void)
{
  while(1)
  {
    scanf("%d",&c);
    if(c)
    {
      sum=0;
      while(c--)
      {
        scanf("%d",&tmp);
        sum+=tmp;
      }
      printf("%d\n",sum);
    }
    else
      break;
  }
  return 0;
}
