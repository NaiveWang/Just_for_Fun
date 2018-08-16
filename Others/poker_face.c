#include <stdio.h>
#include <unistd.h>

int main(void)
{
  char mouth[2]={'\\','/'};
  char flag=0;
  //this is the Eye of the dummy poker face.
  printf(":/");

  while(1)
  {
    usleep(1000000);
    printf("\b%c",mouth[flag]);
    if(flag)
      flag=0;
    else
      flag=1;
  }


  return 0;
}
