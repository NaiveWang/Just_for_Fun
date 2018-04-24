#include "PCoreIR.h"
void *MOV8A(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rbx),%rax");
  asm("movq 8(%rbx),%rax");
  asm("subq $16,%rbx");
  asm("movq %%rbx,%0":"=r"(p->data+POINTER_STACK0));
  pc+=2;
}
void *MOV8(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->pc));

  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");

  asm("xorq %rbp,%rbp");
  asm("movl 3(%rbx),%ebp");
  asm("add %0,%%rbp"::"r"(p->data));

  asm("movq (%rbp,%rdx,8),%rax");

  asm("xorq %rdx,%rdx");
  asm("movb 7(%rbx),%dl");

  asm("xorq %rbp,%rbp");
  asm("movl 8(%rbx),%ebp");
  asm("add %0,%%rbp"::"r"(p->data));

  asm("movq %rax,(%rbp,%rdx,8)");
  p->pc+=12;
}
void *PUSH0A(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data));
  asm("xorq %rbx,%rbx");
  asm("movl %0,%%ebx"::"r"(p->pc+3));
  asm("addq %rbx,%rdx");
  asm("xorq %eax,%eax");
  asm("movb %0,%%al"::"r"(p->pc+2));
  asm("leaq (%rdx,%rax,8),%rax");
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  asm("movq %rax,(%rbx)");
  asm("addq $8,%rbx");
  asm("movq %%rbx,%0":"r"(p->data+POINTER_STACK0));

  p->pc+=7;
}
void *PUSH0II(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK0));
  asm("movq %0,%%rax"::"r"(p->pc+2));
  asm("movq (%rax),%rax");
  asm("movq %rax,(%rbx)");
  asm("addq $8,%rbx");
  asm("movq %%rbx,%0":"=r"(p->data + POINTER_STACK0));
  p->pc+=10;
}
void *PUSH08(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  //asm("leaq %0,%%rcx"::"r"(p->data));
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),edx");
  asm("addq %0,%%rdx"::"r"(p->data));
  asm("xorq %rax,%rax");
  asm("movb 2(rbx),al");
  asm("movq (%rdx,%rax,8),%rax");

  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK0));
  asm("movq %rax,(%rbx)");
  asm("addq $8,%rbx");
  asm("movq %%rbx,%0":"=r"(p->data + POINTER_STACK0));
  p->pc+=7;
}
void *POP08(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK0));
  asm("subq 8,%rbx");
  asm("movq (%rbx),%rax");

  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),edx");
  asm("addq %0,%%rdx"::"r"(p->data));
  asm("xorq %rcx,%rcx");
  asm("movb 2(rbx),cl");
  asm("movq %rax,(%rdx,%rcx,8)");
  p->pc+=7;
}
void *PUSH8(PBase *p)//2decode+(1+4)addr=7
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  //asm("leaq %0,%%rcx"::"r"(p->data));
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),edx");
  asm("addq %0,%%rdx"::"r"(p->data));
  asm("xorq %rax,%rax");
  asm("movb 2(rbx),al");
  asm("movq (%rdx,%rax,8),%rax");

  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK));
  asm("movq %rax,(%rbx)");
  asm("addq $8,%rbx");
  asm("movq %%rbx,%0":"=r"(p->data + POINTER_STACK));
}
void *POP8(PBase *p)//2decode+(1+4)addr=7
{
  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK));
  asm("subq 8,%rbx");
  asm("movq (%rbx),%rax");

  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),edx");
  asm("addq %0,%%rdx"::"r"(p->data));
  asm("xorq %rcx,%rcx");
  asm("movb 2(rbx),cl");
  asm("movq %rax,(%rdx,%rcx,8)");
  p->pc+=7;
}
void *CALL(PBase *p)
{
  //get stack pointer
  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK));
  //get pc,pc is now in %rax
  asm("movq %0,%%rax"::"r"(p->pc));
  //get new pc to %rcx
  asm("movq 2(%rax),%rcx");
  //change pc to new start point with current instruction lenth
  asm("addq $10,%rax");
  //push pc value
  asm("movq %rax,(%rbx)");
  //add pc with code base, now %rbx is free
  asm("addq %0,%%rcx"::"r"(p->code));
  //put rcx(new pc to pc's addr)
  asm("movq %%rcx,%0":"=r"(p->pc));
  //end
}
void *RETN(PBase *p)
{
  //get recovery pc from stack
  //get stack pointer
  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK));
  //operate the stack
  asm("subq $8,%%rbx");
  //get the value
  asm("movq (%rbx),%rax");
  //old pc in %rax, put it to his home
  asm("movq %%rax,%0":"=r"(p->pc));
  //end, notice:no need to influence pc with its length.
}
void *JUMP(PBase *p)
{
  //get the offset
  //get pc
  asm("movq %0,%%rbx"::"r"(p->pc));
  //get offset
  asm("movq 2(%rbx),%rax");
  //offset in the %rax, add it to the pc
  asm("addq %rax,%rbx");
  //put it back to pc's house
  asm("movq %%rbx,%0":"=r"(p->pc));
}
void *JMPC(PBase *p)
{
  //get flag
  asm("movl %0,%%eax"::"r"(p->eflag));
  //get mask
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("movl 2(%rbx),%ecx");
  //and flag
  asm("andl %ecx,%eax");
  //zf:
  asm("jz nojump");
  //jump, get val
  asm("movq 6(%rbx),%rax");
  asm("addq %rax,%rbx");//add offset
  asm("movq %%rbx,%0":"=r"(p->pc));
  return;
  asm("nojump:");
  pc+=14;
  //get pc
}
void *OPADDI(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("addq %rax,-4(%rbx)");
  asm("lahf");
  asm("movb %ah,%al");
  asm("movl %%eax,%0":"=r"(p->eflag));
}
