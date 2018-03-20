/**
 * This file contains data structures and basic function mappings of one thread of the virtual machine.
 * Note: This file does not contains any configuration and user perferences, and these data must be obtained
 * by the initializer, which means some information should be hold before the running steps.
 **/
 #include <stdlib.h>
 /** Data structure defination section **/
typedef struct pCore_RegisterList
{
  char flag;//ZF, SF & execution status.
  void *pc;//program counter.
  void *sp0;
  void *sp;

  /**void *stack0;//fast stack.
  void *stack;//stack.
  void *data_global;
  void *data_const;**/
  void *data;
  void *code;

  char *Cp,C;
  int *Ip,I;
  long *Lp,L;
  double *Rp,R;
  //These data is for the Safe Mode.
  void *rangeL_stack0,*rangeH_stack0;
  void *rangeL_stack,*rangeH_stack;
  void *rangeL_data_global,*rangeH_data_global;
  void *rangeL_data_const,*rangeH_data_const;
  void *rangeL_code,*rangeH_code;
}pCore;
/** Auxiliary Function **/
inline void* getAddr(void* base, int offset)
{
  return base+offset;
}
/** Instruction Set Section **/
*void *HALT(pCore *p)
//6:1byte for decoding,5 bit for the data's addr
{
  //return a value.
}
void *CALL(pCore *p)
//5:1bit for decoding, 4bit for pc's addr
{
  //push the superior's pc into stack.
  p->Ip = p->sp;
  p->sp+=4;
  *(p->Ip) = p->pc;
  //put the target handle into pc.
  p->pc = (int)*(p->pc+1) + code;

}
void *RETN(pCore *p)
//1:1bit for decoding
{
  //set the program counter back
  /// guarantee the stack pointer is the right one.
  p->Ip = p->sp;
  p->sp- = 4;
  p->pc = *(p->Ip) + 1;
}
void *JUMP(pCore *p)
//6:1bit for decoding, 1bit for mask, 4bit for position.
{
  p->Cp = p->pc+1;
  if(p->flag & *(p->Cp))
  {
    p->Ip = *(p->pc+2);
  }
  else
  {
    pc+=6;
  }
}
void *JMPN(pCore *p)
//6:1bit for decoding, 1bit for mask, 4bit for position.
{
  p->Cp = p->pc+1;
  if(!(p->flag & *(p->Cp)))
  {
    p->Ip = *(p->pc+2);
  }
  else
  {
    p->pc+=6;
  }
}
void *RAND(pCore *p);
void *ALLO(pCore *p)
//9:1bit for decoding, 4bit for size, 4bit for addr
{
  p->Ip = p->pc+1;
  (int)*(pc+5)+data = malloc(*(p->Ip));
  p->pc+=9;
}
void *RELZ(pCore *p)
//5:1bit decode, 4bit addr
{
  free((int)*(p->pc+1));
  p->pc+=5;
}
void MOV1(pCore *p)
//9:1bit decode, 4bit addr->4bit addr
{
  p->C = *(char*)(p->pc+1);
  p->Cp = p->pc+5;
  *(p->Cp) = p->C;
  p->pc+=9;
}
*void MOV4(void *pc);
//9:1bit decode, 4bit addr->4bit addr
{
  p->I = *(int*)(p->pc+1);
  p->Ip = p->pc+5;
  *(p->Ip) = p->I;
  p->pc+=9;
}
*void MOV8(void *pc);
//9:1bit decode, 4bit addr->4bit addr
{
  p->L = *(long*)(p->pc+1);
  p->Lp = p->pc+5;
  *(p->Lp) = p->L;
  p->pc+=9;
}
*void MOVb(void *pc);

*void SWAP1(void *pc);
*void SWAP4(void *pc);
*void SWAP8(void *pc);

void *LOAD1(pCore *p)
//9:1bit for decoding, 4bit is the address, 4bit is the segment address.
{
  p->Cp = *(p->pc + 1);
  p->C = *(p->Cp);
  p->Cp = getAddr(p->data, (int)*(p->pc + 5));
  *(p->Cp) = p->C;
}
void *LOAD4(pCore *p)
//9:1bit for decoding, 4bit is the address, 4bit is the segment address.
{
  p->Ip = *(p->pc + 1);
  p->I = *(p->Ip);
  p->Ip = getAddr(p->data, (int)*(p->pc + 5));
  *(p->Ip) = p->I;
}
void *LOAD8(pCore *p)
//9:1bit for decoding, 4bit is the address, 4bit is the segment address.
{
  p->Lp = *(p->pc + 1);
  p->L = *(p->Lp);
  p->Lp = getAddr(p->data, (int)*(p->pc + 5));
  *(p->Lp) = p->L;
}
void *STOR1(pCore *p)
//9:1bit for decoding, 4bit is the address, 4bit is the segment address.
{
  p->Cp = getAddr(p->data, (int)*(p->pc + 5));
  p->C = *p->Cp;
  p->Cp = *(P->pc + 1);
  *(p->Cp) = p->Cp;
}
void *STOR4(pCore *p)
//9:1bit for decoding, 4bit is the address, 4bit is the segment address.
{
  p->Ip = getAddr(p->data, (int)*(p->pc + 5));
  p->I = *p->Ip;
  p->Ip = *(P->pc + 1);
  *(p->Ip) = p->Ip;
}
void *STOR8(pCore *p)
//9:1bit for decoding, 4bit is the address, 4bit is the segment address.
{
  p->Lp = getAddr(p->data, (int)*(p->pc + 5));
  p->L = *p->Lp;
  p->Lp = *(P->pc + 1);
  *(p->Lp) = p->Lp;
}
*void PUSH1(void *pc);
*void PUSH4(void *pc);
*void PUSH8(void *pc);
*void PUSHb(void *pc);

*void POP1(void *pc);
*void POP4(void *pc);
*void POP8(void *pc);
*void POPb(void *pc);

*void PUSH01(void *pc);
*void PUSH04(void *pc);
*void PUSH08(void *pc);

*void PUSH01i(void *pc);
*void PUSH04i(void *pc);
*void PUSH08i(void *pc);

*void POP01(void *pc);
*void POP04(void *pc);
*void POP08(void *pc);

*void IMM1(void *pc);
*void IMM4(void *pc);
*void IMM8(void *pc);

*void ADD1(void *pc);
*void ADD4(void *pc);
*void ADD8(void *pc);
*void ADDf(void *pc);

*void SUB1(void *pc);
*void SUB4(void *pc);
*void SUB8(void *pc);
*void SUBf(void *pc);

*void NEG1(void *pc);
*void NEG4(void *pc);
*void NEG8(void *pc);
*void NEGf(void *pc);

*void CMP1(void *pc);
*void CMP4(void *pc);
*void CMP8(void *pc);
*void CMPf(void *pc);

*void MUL1(void *pc);
*void MUL4(void *pc);
*void MUL8(void *pc);
*void NULf(void *pc);

*void DIV1(void *pc);
*void DIV4(void *pc);
*void DIV8(void *pc);
*void DIVf(void *pc);

*void AND1(void *pc);
*void AND4(void *pc);
*void AND8(void *pc);

*void OR1(void *pc);
*void OR4(void *pc);
*void OR8(void *pc);

*void XOR1(void *pc);
*void XOR4(void *pc);
*void XOR8(void *pc);

*void INV1(void *pc);
*void INV4(void *pc);
*void INV8(void *pc);

*void TST1(void *pc);
*void TST4(void *pc);
*void TST8(void *pc);

*void SHL1(void *pc);
*void SHL4(void *pc);
*void SHL8(void *pc);

*void SHR1(void *pc);
*void SHR4(void *pc);
*void SHR8(void *pc);

*void ROL1(void *pc);
*void ROL4(void *pc);
*void ROL8(void *pc);

*void ROR1(void *pc);
*void ROR4(void *pc);
*void ROR8(void *pc);
 /** Decoding function **/
 /** Running function(one thread) **/
