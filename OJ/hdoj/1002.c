#include <stdio.h>
#include <string.h>
int count;
char buff[3][1003];


int main(void)
{
  int c0=1;
  int c1,c2,c3;
  char pos,sum;

  scanf("%d",&count);
  while(c0<=count)
  {
    scanf("%s %s",buff[0],buff[1]);
    /**printf("%s$%s",buff[0],buff[1]);
    //process the two values*/
    c1=strlen(buff[0])-1;
    c2=strlen(buff[1])-1;
    pos=0;
    c3=0;

    for(;c1>=0&&c2>=0;c1--,c2--)
    {
      sum = (buff[0][c1]&0x0f) + (buff[1][c2]&0x0f) + pos;
      /**printf("##%d",sum);*/
      if(sum>=10)
      {
        sum = sum - 10;
        pos=1;
      }
      else pos=0;
      buff[2][c3]=sum|0x30;
      c3++;
    }
    if(c1>=0)
    {
      for(;c1>=0;c1--)
      {
        sum = (buff[0][c1]&0x0f) + pos;
        if(sum>=10)
        {
          sum = sum - 10;
          pos=1;
        }
        else pos=0;
        buff[2][c3]=sum|0x30;
        c3++;
      }
    }
    else if(c2>=0)
    {
      for(;c2>=0;c2--)
      {
        sum = (buff[1][c2]&0x0f) + pos;
        if(sum>=10)
        {
          sum = sum - 10;
          pos=1;
        }
        else pos=0;
        buff[2][c3]=sum|0x30;
        c3++;
      }
    }
    if(pos)
    {
      buff[2][c3]='1';
      c3++;
    }
    /**print the vals*/
    buff[2][c3]=0;
    printf("Case %d:\n",c0);
    printf("%s + %s = ",buff[0],buff[1]);
    for(c1=strlen(buff[2]);c1;c1--)
    {
      printf("%c",buff[2][c1-1]);
    }
    c0++;
    printf("\n");
    if(c0<=count)
      printf("\n");
  }
  return 0;
}
