/**
 * This file contains data structures and basic function mappings of one thread of the virtual machine.
 * Note: This file does not contains any configuration and user perferences, and these data must be obtained
 * by the initializer, which means some information should be hold before the running steps.
 **/
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
  void *data[64];
  void *code;
  //These data is for the Safe Mode.
  void *rangeL_stack0,*rangeH_stack0;
  void *rangeL_stack,*rangeH_stack;
  void *rangeL_data_global,*rangeH_data_global;
  void *rangeL_data_const,*rangeH_data_const;
  void *rangeL_code,*rangeH_code;
}pCore;
 /** Instruction Set Section **/
*void HALT(pCore *p)
//6:1byte for decoding,5 bit for the data's addr
{
  //return a value.
}
*void CALL(pCore *p)
//5:1bit for decoding, 4bit for pc's addr
{
  
  //push the superior's pc into stack.
  //put the target handle into pc.
}
*void RETN(void *p);
*void JUMP(void *p);
*void JMPN(void *p);

*void RAND(void *p);
*void ALLO(void *p);
*void RELZ(void *p);

*void MOV1(void *pc);
*void MOV4(void *pc);
*void MOV8(void *pc);
*void MOVb(void *pc);

*void SWAP1(void *pc);
*void SWAP4(void *pc);
*void SWAP8(void *pc);

*void LEA(void *pc);

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
