#include "PCoreIR.h"
void MOVIA(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rbx),%rax");
  asm("movq 8(%rbx),%rax");
  asm("subq $16,%rbx");
  asm("movq %%rbx,%0":"=r"(p->data+POINTER_STACK0));
  pc+=2;
}
void MOVI(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->pc));

  asm("xorq %rdx,%rdx");
  asm("movw 2(%rbx),%dl");

  asm("xorq %rbp,%rbp");
  asm("movl 3(%rbx),%ebp");
  asm("add %0,%%rbp"::"r"(p->data));

  asm("movq (%rbp,%rdx,8),%rax");

  asm("xorq %rdx,%rdx");
  asm("movw 7(%rbx),%dl");

  asm("xorq %rbp,%rbp");
  asm("movl 8(%rbx),%ebp");
  asm("add %0,%%rbp"::"r"(p->data));

  asm("movq %rax,(%rbp,%rdx,8)");
  pc+=10;
}
