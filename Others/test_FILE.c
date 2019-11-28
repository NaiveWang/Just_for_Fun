#include <stdio.h>
int main(void)
{
    FILE *fp = fopen("test.FILE.c","r");
    char s[128];
    while(~fscanf(fp,"<%3s>\n",s))
    {
        printf("%s\n",s);
    }
    return 0;
}
