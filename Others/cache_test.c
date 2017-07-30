/** This program is about to make out cache size of CPU **/
/** Linux GCC Only **/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(void)
{
  register clock_t start,stop,t;
  register char r=0xFF;
  register char *cache;
  register int size = 1;
  register int c0=0x00002000,c1,c2;
  while(size ^ 0x00001000)
  {
    c2=c0;
    t=0;
    while(c2--)
    {
      *cache=0xFF;
      c1 = size<<10;
      cache = malloc(c1);
      //if(cache == NULL) exit(-1);
      start = clock();

      while(c1--)
      {
        c1[cache]++;
      }
      stop = clock();
      free(cache);
      t+=stop-start;
    }
    printf("%ld---%dkb\n",t,size);
    size = size<<1;
    c0 = c0>>1;
  }
  return 0;
}
