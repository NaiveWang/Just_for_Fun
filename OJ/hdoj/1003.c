#include <stdio.h>
/**
 * HDOJ 1003 Max Sum
 */
#define T 21

char *input="2\n5 6 -1 5 4 -7\n7 0 6 -1 1 -6 7 -5";

int a,_a;
int n,_n;

int array[T];


int main(void)
{
  scanf("%d",&a);
  for(_a=0;_a<a;_a++)
  {
    scanf("%d",&n);
    for(_n=0;_n<n;_n++)
    {
      scanf("%d",array+_n);
    }
    /** input section ended **/
  }
  return 0;
}
