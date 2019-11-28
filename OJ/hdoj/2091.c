#include <stdio.h>
char x;
int scale;
int c,c0;
char tag=0;


int main(void)
{
  while(1)
  {
    scanf("%c",&x);
    if(x=='@') break;
    if(tag) printf("\n");
    scanf("%d",&scale);
    for(c=scale-1;c--;)
    {
      printf(" ");
    }
    printf("%c\n",x);
    if(scale>1)
    {
      for(c=scale-2;c--;)
      {
        for(c0=c+1;c0--;) printf(" ");
        printf("%c",x);
        for(c0=2*(scale-2-c)-1;c0--;) printf(" ");
        printf("%c\n",x);
      }
      for(c=scale*2-1;c--;)
      {
        printf("%c",x);
      }
      printf("\n");
    }
    tag=1;
    getchar();
  }
  return 0;
}
