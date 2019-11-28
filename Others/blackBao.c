#include <stdio.h>
#include <string.h>

#ifndef ChiZaoYaoWan
#define ChiZaoYaoWan

#define TRUE 0x00
#define FALSE 0xFF

#define QingFengBuShiZi

#ifdef QingFengBuShiZi
#define Nong "衣"
#else
#define Nong "农"
#endif

void IsQingHuaBoShi(char *s)
{
  if(strcmp(s,"农"))
    printf("Yes, he is.\n");
  else
    printf("This is impossible.\n");
}

int main(void)
{
  printf("清关易道,通商宽%s\n",Nong);
  printf("是不是清华博士?\n");
  IsQingHuaBoShi(Nong);
  return 0;
}

#endif
