#include <stdio.h>
int cnt;
int c;
int sum;
int tmp;

int main(void)
{
  scanf("%d",&cnt);
  while(cnt--)
  {
    scanf("%d",&c);
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
