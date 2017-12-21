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
int *insdata;

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
void changeFlagR(double *target)
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
  pc++;
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
  pc++;
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
  pc++;
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
void *CALL()
{
  segd[sizeofsegd+sp].data=malloc(5);
  char *temp0=segd[sizeofsegd+sp].data;
  int *temp1=segd[sizeofsegd+sp].data + 1;
  *temp0=flag;
  *temp1=pc;
  sp++;
  pc=segi[pc].data[0];
}
void *RETN()
{
  sp--;
  flag=(char)segd[sizeofsegd+sp].data;
  pc=(int)(segd[sizeof+sp].data + 1) + 1;
  free(segd[sizeofsegd+sp].data);
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
//value/destination//
void *ALOC()
{
  char *s = insdata;
  char *t = addrFetcher(insdata+1,insdata+2);
  *t = *s;
  pc++;
}
void *ALOI()
{
  int *s = insdata;
  int *t = addrFetcher(insdata+1,insdata+2);
  *t = *s;
  pc++;
}
void *ALOL()
{
  long *s = insdata;
  long *t = addrFetcher(insdata+2,insdata+3);
  *t = *s;
  pc++;
}
void *ALOR()
{
  double *s = insdata;
  double *t = addrFetcher(insdata+2,insdata+3);
  *t = *s;
  pc++;
}
//type,Source1,2/destination/
void *ARBC()
{
  char *s1=addrFetcher(insdata+1,insdata+2);
  char *s2=addrFetcher(insdata+3,insdata+4);
  char *d=addrFetcher(insdata+5,insdata+6);
  switch(insdata[0])
  {
    case 0x0:*d = *s1 + *s2;break;
    case 0x1:*d = *s1 - *s2;break;
    case 0x2:*d = *s1 * *s2;break;
    case 0x3:*d = *s1 / *s2;break;
    case 0x4:*d = *s1 % *s2;break;
    case 0x5:*d = *s1 << *s2;break;
    case 0x6:*d = *s1 >> *s2;break;
    case 0x7:*d = *s1 & *s2;break;
    case 0x8:*d = *s1 | *s2;break;
    case 0x9:*d = *s1 ^ *s2;break;
  }
  changeFlagC(d);
  pc++;
}
void *ARBI()
{
  int *s1=addrFetcher(insdata+1,insdata+2);
  int *s2=addrFetcher(insdata+3,insdata+4);
  int *d=addrFetcher(insdata+5,insdata+6);
  switch(insdata[0])
  {
    case 0x0:*d = *s1 + *s2;break;
    case 0x1:*d = *s1 - *s2;break;
    case 0x2:*d = *s1 * *s2;break;
    case 0x3:*d = *s1 / *s2;break;
    case 0x4:*d = *s1 % *s2;break;
    case 0x5:*d = *s1 << *s2;break;
    case 0x6:*d = *s1 >> *s2;break;
    case 0x7:*d = *s1 & *s2;break;
    case 0x8:*d = *s1 | *s2;break;
    case 0x9:*d = *s1 ^ *s2;break;
  }
  changeFlagI(d);
  pc++;
}
void *ARBL()
{
  long *s1=addrFetcher(insdata+1,insdata+2);
  long *s2=addrFetcher(insdata+3,insdata+4);
  long *d=addrFetcher(insdata+5,insdata+6);
  switch(insdata[0])
  {
    case 0x0:*d = *s1 + *s2;break;
    case 0x1:*d = *s1 - *s2;break;
    case 0x2:*d = *s1 * *s2;break;
    case 0x3:*d = *s1 / *s2;break;
    case 0x4:*d = *s1 % *s2;break;
    case 0x5:*d = *s1 << *s2;break;
    case 0x6:*d = *s1 >> *s2;break;
    case 0x7:*d = *s1 & *s2;break;
    case 0x8:*d = *s1 | *s2;break;
    case 0x9:*d = *s1 ^ *s2;break;
  }
  changeFlagL(d);
  pc++;
}
void *ARBR()
{
  double *s1=addrFetcher(insdata+1,insdata+2);
  double *s2=addrFetcher(insdata+3,insdata+4);
  double *d=addrFetcher(insdata+5,insdata+6);
  switch(insdata[0])
  {
    case 0x0:*d = *s1 + *s2;break;
    case 0x1:*d = *s1 - *s2;break;
    case 0x2:*d = *s1 * *s2;break;
    case 0x3:*d = *s1 / *s2;break;
  }
  changeFlagR(d);
  pc++;
}
void *ARUC()
{
  char *s=addrFetcher(insdata+1,insdata+2);
  char *d=addrFetcher(insdata+3,insdata+4);
  switch(insdata[0])
  {
    case 0x0:*d = ~ *s; break;
    case 0x1:*d = - *s; break;
  }
  changeFlagC(d);
  pc++;
}
void *ARUI()
{
  int *s=addrFetcher(insdata+1,insdata+2);
  int *d=addrFetcher(insdata+3,insdata+4);
  switch(insdata[0])
  {
    case 0x0:*d = ~ *s; break;
    case 0x1:*d = - *s; break;
  }
  changeFlagI(d);
  pc++;
}
void *ARUL()
{
  long *s=addrFetcher(insdata+1,insdata+2);
  long *d=addrFetcher(insdata+3,insdata+4);
  switch(insdata[0])
  {
    case 0x0:*d = ~ *s; break;
    case 0x1:*d = - *s; break;
  }
  changeFlagL(d);
  pc++;
}
void *NEGR()
{
  double *s=addrFetcher(insdata+1,insdata+2);
  double *d=addrFetcher(insdata+3,insdata+4);
  /**switch(insdata[0])
  {
    case 0x0:*d = ~ *s; break;
    //case 0x1:*d = - *s; break;
  }*/
  *d = - *s;
  changeFlagR(d);
  pc++;
}
void *PUSH()
{
  segd[sp+sizeofsegd].size=insdata[0];
  segd[sp+sizeofsegd].length=insdata[1];
  segd[sp+sizeofsegd].data=malloc(insdata[0]*insdata[1]);
  sp++;
  pc++;
}
void *POP()
{
  sp--;
  free(segd[sp+sizeofsegd].data);
  pc++;
}
idt ins[INSTRUCTION]={  {"MOVC",4,MOVC},{"MOVI",4,MOVI},{"MOVL",4,MOVL},
                        {"JUMP",1,JUMP},{"JMPF",2,JMPF},{"JMPN",2,JMPN},
                        {"HALT",1,HALT},
                        {"CALL",3,CALL},{"RETN",3,RETN},
                        {"PUTC",1,PUTC},{"PUTI",1,PUTI},{"GETC",1,GETC},{"GETI",1,GETI},
                        {"ALOC",2,ALOC},{"ALOI",2,ALOI},{"ALOL",3,ALOL},{"ALOR",3,ALOR},//allocation
                        {"ARBC",7,ARBC},{"ARBI",7,ARBI},{"ARBL",7,ARBL},{"ARBR",7,ARBR},//arithmatic binary
                        {"ARUC",2,ARUC},{"ARUI",2,ARUI},{"ARUL",2,ARUL},{"NEGR",2,NEGR}//arithmatic unary
                        };
int decoder(int* s)
{
  int i=INSTRUCTION;
  int *p;
  while(i--)
  {
    p=ins[i].instruction;
    if(*s == *p)
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
  static void *(*instruction)()=NULL;
  while(instruction != HALT || JMPF || JMPN)
  {
    instruction=segi[pc].instruction;
    insdata=segi[pc].data;
    *instruction;
  }
}
void VMstart()
{
  //reset pointer.
  pc=sp=0;
  while(segi[pc].instruction != HALT)
  {
    RunABlock();
  }
}

int main(void)
{
  //readBin(*argv);
  //VMstart();
  return 0;
}
