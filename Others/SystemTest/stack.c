#include <stdio.h>
#include <string.h>
int counter;
//this program will cause segmentation fault.
void crashStack()
{
    int a[256];//,b;
    //a=0;
    memset(a,0,1024);
    //b=0;
    counter++;
    /**if(counter&0xFF == 0)**/ printf("%d\n",counter);
    crashStack();
}
int main(void)
{
    counter = 0;
    crashStack();
    return 0;
}
