#include <stdio.h>
#include <stdlib.h>
#define LINUX
//#define REGS 256
#define FLAGS 2
#define STACK 262144
#define INSTRUCTION 45
/** This segment is the memory of VM**/
//char reg[REGS];
typedef struct InstructionDecodingTable
{
  char instruction[4];
  int dataLength;
  void *(*i)();
}idt;
typedef struct InstructionLinkList
{
  void *(*instruction)();
  int *data;
  struct InstructionLinkList *prior,*next;
}inode;

long reg;
int insdata[4];

char stack[STACK];
char flag[FLAGS];
int pc,sp;

/** INSTRUCTION SET **/
void *MOVC()
{
}
void *MOVI()
{
}
void *MOVL()
{
}
void *JUMP()
{
}
void *JMPF()
{
}
void *JMPN()
{
}
void *HALT()
{
}
void *ADDC()
{
}
void *ADDI()
{
}
void *ADDL()
{
}
void *SUBC()
{
}
void *SUBI()
{
}
void *SUBL()
{
}
void *MULC()
{
}
void *MULI()
{
}
void *MULL()
{
}
void *DIVC()
{
}
void *DIVI()
{
}
void *DIVL()
{
}
void *_CMP()
{
}
void *NEGC()
{
}
void *NEGI()
{
}
void *NEGL()
{
}
void *NOTC()
{
}
void *NOTI()
{
}
void *NOTL()
{
}
void *EORC()
{
}
void *EORI()
{
}
void *EORL()
{
}
void *ANDC()
{
}
void *ANDI()
{
}
void *ANDL()
{
}
void *_ORC()
{
}
void *_ORI()
{
}
void *_ORL()
{
}
void *TSTC()
{
}
void *TSTI()
{
}
void *TSTL()
{
}
void *RAND()
{
}
void *CALL()
{
}
void *RETN()
{
}
void *PUTC()
{
}
void *GETC()
{
}
void *PUTI()
{
}
void *GETI()
{
}
idt ins[INSTRUCTION]={  {"MOVC",2,MOVC},{"MOVI",2,MOVI},{"MOVL",2,MOVL},{"JUMP",2,JUMP},{"JMPF",2,JMPF},{"JMPN",2,JMPN},{"HALT",1,HALT},
                        {"ADDC",3,ADDC},{"ADDI",3,ADDI},{"ADDL",3,ADDL},{"SUBC",3,SUBC},{"SUBI",3,SUBI},{"SUBL",3,SUBL},{"MULC",3,MULC},
                        {"MULI",3,MULI},{"MULL",3,MULL},{"DIVC",3,DIVC},{"DIVI",3,DIVI},{"DIVL",3,DIVL},{"_CMP",2,_CMP},{"NEGC",2,NEGC},
                        {"NEGI",2,NEGI},{"NEGL",2,NEGL},{"NOTC",2,NOTC},{"NOTI",2,NOTI},{"NOTL",2,NOTL},{"EORC",3,EORC},{"EORI",3,EORI},
                        {"EORL",3,EORL},{"ANDC",3,ANDC},{"ANDI",3,ANDI},{"ANDL",3,ANDL},{"_ORC",3,_ORC},{"_ORI",3,_ORI},{"_ORL",3,_ORL},
                        {"TSTC",1,TSTC},{"TSTI",1,TSTI},{"TSTL",1,TSTL},{"RAND",1,RAND},{"CALL",3,CALL},{"RETN",3,RETN},{"PUTC",1,PUTC},
                        {"PUTI",1,PUTI},{"GETC",1,GETC},{"GETI",1,GETI}};

int decoder(char* s)
{
  int i=INSTRUCTION;
  while(i--)
  {
    if(ins[i].instruction[0]==s[0] && ins[i].instruction[1]==s[1] && ins[i].instruction[2]==s[2] && ins[i].instruction[3]==s[3])
      return i;
  }
}
void readBin(char *s)
{
  FILE *fp;
  fp=fopen(s,"rb");
}

void VMstart()
{
  //reset pointer.
  pc=sp=0;
}

int main(int argc,char **argv)
{
  return 0;
}
