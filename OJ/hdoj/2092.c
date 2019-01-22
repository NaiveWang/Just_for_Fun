#include <stdio.h>
#include <math.h>

int m,n;

double val;

int main(void)
{
  while(scanf("%d%d",&m,&n)!=EOF&&(n|m))
  {
    m = m*m - (n<<2);
    //printf("%lf*",sqrt(m));
    if(m<0||fmod(sqrt(m),1))
      printf("No\n");
    else
      printf("Yes\n");
  }
  return 0;
}
