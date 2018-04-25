#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *t1()
{
  for(;;)
  {
    printf("-");
  }
}
void *t2()
{
  for(;;)
  {
    printf("|");
  }
}
int main(void)
{
  int a=100;
  pthread_t pt[2];
  pthread_create(pt,NULL,t1,NULL);
  pthread_create(pt+1,NULL,t2,NULL);
  printf("=\n");
  printf("+\n");
  while(a--)
  {
    printf("%d DOWN WITH BIG BROTHER\n",a);
  }
  pthread_join(pt[1],NULL);
  return 0;
}
