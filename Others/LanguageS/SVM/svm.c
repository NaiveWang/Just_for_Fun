#include <stdio.h>
#include <stdlib.h>
#define LINUX
//#define REGS 256
#define MOMORY 262144
#define INSTRUCTION 45
/** This segment is the memory of VM**/
//char reg[REGS];
typedef struct InstructionDecodingTable
{
  char instruction[4];
  int dataLength;
  void *(*i)();
}idt;
typedef struct InstructionList
{
  void *(*instruction)();
  int *data;
}ielem;
typedef struct DataList
{
  int size,length;
  void *data;
}delem;
long reg;
int insdata[4];

char flag;//ZERO/SIGN/N/N/N/N/RRD/WRD
int pc,sp;

ielem *segi;
delem segd[MOMORY];
int sizeofsegi,sizeofsegd;

/** Aux **/
void* addrFetcher(int *x,int *y)
{//Because of the performance, this function do not have boundary check.
  return segd[*x].data + segd[*x].size * *y;
}
void changeFlagC(char *target)
{
  if(*target == 0) flag |= 0x01;
  if(*target < 0) flag |= 0x02;
}
void changeFlagI(int *target)
{
  if(*target == 0) flag |= 0x01;
  if(*target < 0) flag |= 0x02;
}
void changeFlagL(long *target)
{
  if(*target == 0) flag |= 0x01;
  if(*target < 0) flag |= 0x02;
}
void ReadReady()
{
  flag &= 0xFD;
}
void WriteReady()
{
  flag &= 0xF7;
}
/** INSTRUCTION SET **/
void *HALT()
{
  exit(*insdata);
}
void *MOVC()
{//source/destination
  if(segd[*insdata].size == segd[*(insdata+2)].size)
  {
    char *temp0 = addrFetcher(insdata+2,insdata+3);
    char *temp1 = addrFetcher(insdata,insdata+1);
    *temp0=*temp1;
  }
  else
  {
    *insdata=-1;
    *HALT();
  }
}
void *MOVI()
{//source/destination
  if(segd[*insdata].size == segd[*(insdata+2)].size)
  {
    int *temp0 = addrFetcher(insdata+2,insdata+3);
    int *temp1 = addrFetcher(insdata,insdata+1);
    *temp0=*temp1;
  }
  else
  {
    *insdata=-1;
    *HALT();
  }
}
void *MOVL()
{//source/destination
  if(segd[*insdata].size == segd[*(insdata+2)].size)
  {
    long *temp0 = addrFetcher(insdata+2,insdata+3);
    long *temp1 = addrFetcher(insdata,insdata+1);
    *temp0=*temp1;
  }
  else
  {
    *insdata=-1;
    *HALT();
  }
}
void *JUMP()
{
  pc+=*insdata;
}
void *JMPF()
{
  if(*(insdata+1)&flag) pc+=*insdata;
}
void *JMPN()
{
  if(*(insdata+1)^flag) pc+=*insdata;
}
void *ADDC()
{//source1/source2/destination
  if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
  {
    char *temp0 = addrFetcher(insdata+2,insdata+3);
    char *temp1 = addrFetcher(insdata,insdata+1);
    char *temp2 = addrFetcher(insdata+4,insdata+5);
    *temp2 = *temp0 + *temp1;
    changeFlagC(temp2);
  }
  else
  {
    *insdata=-1;
    *HALT();
  }
}
void *ADDI()
{//source1/source2/destination
  if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
  {
    int *temp0 = addrFetcher(insdata+2,insdata+3);
    int *temp1 = addrFetcher(insdata,insdata+1);
    int *temp2 = addrFetcher(insdata+4,insdata+5);
    *temp2 = *temp0 + *temp1;
    changeFlagL(temp2);
  }
  else
  {
    *insdata=-1;
    *HALT();
  }
}
void *ADDL()
{//source1/source2/destination
  if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
  {
    long *temp0 = addrFetcher(insdata+2,insdata+3);
    long *temp1 = addrFetcher(insdata,insdata+1);
    long *temp2 = addrFetcher(insdata+4,insdata+5);
    *temp2 = *temp0 + *temp1;
    changeFlagL(temp2);
  }
  else
  {
    *insdata=-1;
    *HALT();
  }
}
void *SUBC()
{//source1/source2/destination
    if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
    {
      char *temp0 = addrFetcher(insdata+2,insdata+3);
      char *temp1 = addrFetcher(insdata,insdata+1);
      char *temp2 = addrFetcher(insdata+4,insdata+5);
      *temp2 = *temp0 - *temp1;
      changeFlagC(temp2);
    }
    else
    {
      *insdata=-1;
      *HALT();
    }
}
void *SUBI()
{//source1/source2/destination
    if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
    {
      int *temp0 = addrFetcher(insdata+2,insdata+3);
      int *temp1 = addrFetcher(insdata,insdata+1);
      int *temp2 = addrFetcher(insdata+4,insdata+5);
      *temp2 = *temp0 - *temp1;
      changeFlagI(temp2);
    }
    else
    {
      *insdata=-1;
      *HALT();
    }
}
void *SUBL()
{//source1/source2/destination
    if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
    {
      long *temp0 = addrFetcher(insdata+2,insdata+3);
      long *temp1 = addrFetcher(insdata,insdata+1);
      long *temp2 = addrFetcher(insdata+4,insdata+5);
      *temp2 = *temp0 - *temp1;
      changeFlagL(temp2);
    }
    else
    {
      *insdata=-1;
      *HALT();
    }
}
void *MULC()
{
  //source1/source2/destination
      if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
      {
        char *temp0 = addrFetcher(insdata+2,insdata+3);
        char *temp1 = addrFetcher(insdata,insdata+1);
        char *temp2 = addrFetcher(insdata+4,insdata+5);
        *temp2 = *temp0 * *temp1;
        changeFlagC(temp2);
      }
      else
      {
        *insdata=-1;
        *HALT();
      }
}
void *MULI()
{//source1/source2/destination
    if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
    {
      int *temp0 = addrFetcher(insdata+2,insdata+3);
      int *temp1 = addrFetcher(insdata,insdata+1);
      int *temp2 = addrFetcher(insdata+4,insdata+5);
      *temp2 = *temp0 * *temp1;
      changeFlagI(temp2);
    }
    else
    {
      *insdata=-1;
      *HALT();
    }
}
void *MULL()
{//source1/source2/destination
    if(segd[*insdata].size == segd[*(insdata+2)].size == segd[*(insdata+4)].size)
    {
      long *temp0 = addrFetcher(insdata+2,insdata+3);
      long *temp1 = addrFetcher(insdata,insdata+1);
      long *temp2 = addrFetcher(insdata+4,insdata+5);
      *temp2 = *temp0 * *temp1;
      changeFlagL(temp2);
    }
    else
    {
      *insdata=-1;
      *HALT();
    }
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
idt ins[INSTRUCTION]={  {"MOVC",4,MOVC},{"MOVI",4,MOVI},{"MOVL",4,MOVL},{"JUMP",1,JUMP},{"JMPF",2,JMPF},{"JMPN",2,JMPN},{"HALT",1,HALT},
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
  int seeker;

  fp=fopen(s,"rb");
  //first is data section.
  //get the data size
  fread(&sizeofsegd,4,1,fp);

  //read the data repeatly.
  for(seeker=0;seeker<sizeofsegd;seeker++)
  {
    fread(&segd[seeker].size,4,1,fp);
    fread(&segd[seeker].length,4,1,fp);
    (segd+seeker)->data=malloc(segd[seeker].size * segd[seeker].length);
    fread((segd+seeker)->data,segd[seeker].size,segd[seeker].length,fp);
  }
  //have read the data segment.
  //now start reading the code.
  //and with predecoding step.
  fread(&sizeofsegi,4,1,fp);

  segi=calloc(sizeofsegi,sizeof(ielem));
  //the same as above.
  int code;
  for(seeker=0;seeker<sizeofsegi;seeker++)
  {
    fread(&code,4,1,fp);

    int temp = decoder(&code);

    segi[seeker].instruction=ins[temp].i;
    segi[seeker].data=malloc(ins[temp].dataLength*sizeof(int));
    //read the data of each instruction.
    fread(segi[seeker].data,4,ins[temp].dataLength,fp);
  }
}
void RunABlock()//run a block of code without branch
{
  ;
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
