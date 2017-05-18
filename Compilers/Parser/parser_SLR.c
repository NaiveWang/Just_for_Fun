#include <stdio.h>
#include "production.h"
#include "scan_toolkit.h"
#define STACK 4096
/** Global Variables Section **/
char stack[STACK][PLEN];
int s_top;
void push(char *s)
{
    strcpy(stack[s_top],s);
    s_top++;
}
char* pop()
{
    if(s_top) s_top--;
    else return NULL;
    return stack[s_top];
}
void SLR()
{
    ;
}
int main(void)
{
    return 0;
}
