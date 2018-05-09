#include "PCoreIR.h"
void MOV8A(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $16,%rbx");

  asm("movq (%rbx),%rax");
  asm("movq (%rax),%rcx");
  asm("movq 8(%rbx),%rax");
  asm("movq %rcx,(%rax)");

  //asm("leaq %0,%%rax"::"r")
  asm("movq %rbx,(%rdx)");
asm("movq %%rdx,%0":"=r"(p->debugBuffer));printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=2;
}
void MOV8(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");

  asm("movq (%rax),%rax");// value stored at rax
//asm("movq %%rax,%0":"=r"(p->debugBuffer));printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  asm("xorq %rdx,%rdx");
  asm("movb 7(%rbx),%dl");

  //asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 8(%rbx),%edx");
  asm("addq %rdx,%rcx");
//asm("movq %%rax,%0":"=r"(p->debugBuffer));
  asm("movq %rax,(%rcx)");
  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=12;
}
void MOVBA(PBase *p)
{
  asm("leaq (%0),%%rdx"::"r"(p->data + POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $24,%rbx");
  asm("movq %rbx,(%rdx)");
  asm("movq 16(%rbx),%rcx");
  asm("movq 8(%rbx),%rax");
  asm("movq (%rbx),%rbx");
  asm("movq %rcx,%rdx");
  asm("andq $0x000000000000000f,%rdx");
  asm("shrq $4,%rcx");

  asm("loop1:");
  asm("jz loop2");
  asm("movdqu (%rax),%xmm0");
  asm("movdqu %xmm0,(%rbx)");
  asm("addq $16,%rax");
  asm("addq $16,%rbx");
  asm("decq %rcx");
  asm("jmp loop1");
  asm("loop2:");

  //asm("loop1:")
  asm("jz loopend");
  asm("movb (%rax),%ch");
  asm("movb %ch,(%rbx)");
  asm("incq %rax");
  asm("incq %rbx");
  asm("decq %rdx");
  asm("jmp loop2");
  asm("loopend:");
  p->pc+=2;
}
void PUSH0A(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");//address calculation finshed:rax
  //asm("movq (%rax),%rax");// value stored at rax
  asm("movq 16(%rcx),%rdx");
  asm("movq %rax,(%rdx)");
  asm("addq $8,16(%rcx)");
  //asm("movq %%rdx,%0":"=r"(p->debugBuffer));
  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=7;
}
void PUSH0I8(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));//getchar();
  asm("movq (%rdx),%rbx");
  //asm("movq %%rbx,%0":"=r"(p->debugBuffer));printf("!%ld!%lx\n",p->debugBuffer,p->debugBuffer);
  asm("movq %0,%%rax"::"r"(p->pc+2));

  asm("movq (%rax),%rax");


  asm("movq %rax,(%rbx)");//getchar();

  asm("addq $8,%rbx");
  asm("movq %rbx,(%rdx)");
  //

  p->pc+=10;
}
void PUSH08(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");//address calculation finshed:rax
  asm("movq (%rax),%rax");// value stored at rax
  asm("movq 16(%rcx),%rdx");
  asm("movq %rax,(%rdx)");
  asm("addq $8,16(%rcx)");
  p->pc+=7;
}
void POP08(PBase *p)
{
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq 16(%rcx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("pushq %rax");
  asm("movq %rbx,16(%rcx)");
  //value:rax base:rcx
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 3(%rbx),%edx");
  asm("popq %rax");
  asm("movq %rax,(%rdx,%rcx)");
  //asm("movq %%rax,%0":"=r"(p->debugBuffer));printf("!%ld!%lx\n",p->debugBuffer,p->debugBuffer);
  p->pc+=7;
}
void PUSH8(PBase *p)//2decode+(1+4)addr=7
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");//address calculation finshed:rax
  asm("movq (%rax),%rax");// value stored at rax
  asm("movq 32(%rcx),%rdx");
  asm("movq %rax,(%rdx)");
  asm("addq $8,16(%rcx)");
  p->pc+=7;
}
void POP8(PBase *p)//2decode+(1+4)addr=7
{
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq 32(%rcx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("pushq %rax");
  asm("movq %rbx,16(%rcx)");
  //value:rax base:rcx
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 3(%rbx),%edx");
  asm("popq %rax");
  asm("movq %rax,(%rdx,%rcx)");
  p->pc+=7;
}
void CALL(PBase *p)
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
void RETN(PBase *p)
{
  //get recovery pc from stack
  //get stack pointer
  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK));
  //operate the stack
  asm("subq $8,%rbx");
  //get the value
  asm("movq (%rbx),%rax");
  //old pc in %rax, put it to his home
  asm("movq %%rax,%0":"=r"(p->pc));
  //end, notice:no need to influence pc with its length.
}
void JUMP(PBase *p)
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
void JMPC(PBase *p)
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
  //return;
  asm("jmp jump");
  asm("nojump:");
  p->pc+=14;
  asm("jump:");
  //get pc
}
void OPADDI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");

  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");

  asm("addq %rax,-8(%rbx)");
  asm("lahf");//asm("movq %%rbx,%0":"=r"(p->debugBuffer));

  asm("movq %rbx,(%rdx)");
  //asm("movb %ah,%al");
  asm("movl %%eax,%0":"=r"(p->eflag));
  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=2;
}
void OPDIVI(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  //asm("subq $8,%rbx");
  asm("movq (%rbx),%rbx");
  asm("movq -8(%rbx),%rcx");
  asm("movq -16(%rbx),%rax");
  asm("cqo");
  asm("idivq %rcx");
  asm("movq %rdx,-8(%rbx)");//quotient
  asm("movq %rax,-16(%rbx)");//reminder
  //asm("movq %%rax,%0":"=r"(p->debugBuffer));
  asm("lahf");
  //asm("movb %ah,%al");
  asm("movl %%eax,%0":"=r"(p->eflag));

  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=2;
}
void OPCMPI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $16,%rbx");
  asm("movq %rbx,(%rdx)");
  asm("movq 8(%rbx),%rax");
  asm("cmpq (%rbx),%rax");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPNOTI(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rbx),%rbx");
  asm("notq -8(%rbx)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPTSTI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $16,%rbx");
  asm("movq %rbx,(%rdx)");
  asm("movq 8(%rbx),%rax");
  asm("test (%rbx),%rax");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}

void (*InstructionSet[])(PBase *p) = {
  MOV8A,MOV8,MOVBA,
  PUSH0A,PUSH0I8,PUSH08,POP08,
  PUSH8,POP8,
  CALL,RETN,JUMP,JMPC,
  OPADDI,
  OPDIVI,
  OPCMPI,
  OPNOTI,
  OPTSTI};
const int pir_n=18;
IR pir[]={
  {2,"MOV8A"},{12,"MOV8"},{2,"MOVBA"},
  {7,"PUSH0A"},{10,"PUSH0I8"},{7,"PUSH08"},{7,"POP08"},
  {7,"PUSH8"},{7,"POP8"},
  {10,"CALL"},{2,"RETN"},{10,"JUMP"},{14,"JMPC"},
  {2,"OPADDI"},
  {2,"OPDIVI"},
  {2,"OPCMPI"},
  {2,"OPNOTI"},
  {2,"OPTSTI"}};

int instructionParser(int *r0, char *code)
{
    static int a0;
    for(a0=0;a0<pir_n;a0++)
    {
        //printf("^%s^\n",);
        if(strcmp(code,pir[a0].key)) continue;
        //printf("FOUND ONE!!!!!!!!!!!!!!\n");
        *r0=pir[a0].length;
        return a0;
    }
    *r0=0;
    return -1;
}
void executionOneStep(PBase *p)
{
  unsigned short codeNo;
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("movw (%%rbx),%0":"=r"(codeNo));
  //printf("^%d^\n",codeNo);
  //getchar();
  InstructionSet[codeNo](p);
  //getchar();
}
