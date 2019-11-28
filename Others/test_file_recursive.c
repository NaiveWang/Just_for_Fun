#include <stdio.h>
char buffer[256];
void r(FILE *fp)
{
  FILE nfp=*fp;
  if(fgets(buffer,256,fp))
  {
    printf("%s",buffer);
    r(fp);
  }
  fgets(buffer,256,&nfp);
  printf("%s",buffer);
}
int main(void)
{
  FILE *fp=fopen("blackBao.c","r");
  r(fp);
  fclose(fp);
  return 0;
}
//fail, code abondanded
