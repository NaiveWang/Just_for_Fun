#include <stdio.h>
int main(void)
{
  double f;
  while(scanf("%le",&f)!=EOF)
    printf("%lf\n",f);
  return 0;
}
