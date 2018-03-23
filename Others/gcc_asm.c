
#include<stdio.h>

void main() {

   int a = 3, b = 30, c;

   asm("movl %0, %%eax"::"a"(a));
   asm("movl %%eax,%0":"=r"(c));

   printf("%d\n",c);
}
