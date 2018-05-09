/**
 * Here is the instruction set & mapping
 **/
#ifndef PCOREIR_H
#define PCOREIR_H
#include "PCoreBase.h"
#include <string.h>
#include <stdio.h>
//instructions
//template: void <NAME>(PBase)
/** key word define **/
typedef struct compileData
{
  int length;
  char key[28];
}IR;
/**Processor Control**/

void HALT(PBase *p);//2
void SUSPEND(PBase *p);//2
void REBOOT(PBase *p);//2
/** Data transfer **/
void MOV1A(PBase *p);//2
void MOV1(PBase *p);//2+5*2=12
void MOV8A(PBase *p);//2decode
void MOV8(PBase *p);//2decode+(1+4)addr*2=12
void MOVBA(PBase *p);//2decode:stack0//8addr1,8addr2,4size
void PUSH0A(PBase *p);//2decode+(1+4)addr=7, put the value into BASE_STACK0
void PUSH0I8(PBase *p);//2decode+8data=10
void PUSH0I1(PBase *p);//3
void PUSH08(PBase *p);//2decode+(1+4)addr=7
void PUSH01(PBase *p);//7
void POP08(PBase *p);//2decode+(1+4)addr=7
void POP01(PBase *p);//7

void PUSH1(PBase *p);//7
void POP1(PBase *p);//7
void PUSH8(PBase *p);//2decode+(1+4)addr=7
void POP8(PBase *p);//2decode+(1+4)addr=7
/** Type Conventions**/
void CBI(PBase *p);
void CIB(PBase *p);
void CRI(PBase *p);
void CIR(PBase *p);
void CBR(PBase *p);
void CRB(PBase *p);
/** Memory Allocation **/
void ALLO(PBase *p);
void FREE(PBase *p);
/** Control **/
void CALL(PBase *p);//2decode+8offset=10,push pc
void RETN(PBase *p);//2decode=2:recover pc
void JUMP(PBase *p);//2decode+8offset=10
void JMPC(PBase *p);//2decode+4mask+8offset=14
/** Operation **/
void OPADDB(PBase *p);//2
void OPADDI(PBase *p);//2decode=2
void OPADDR(PBase *p);//2

void OPSUBB(PBase *p);//2
void OPSUBI(PBase *p);//2
void OPSUBR(PBase *p);//2

void OPMULB(PBase *p);
void OPNULI(PBase *p);
void OPMULR(PBase *p);

void OPIMULB(PBase *p);
void OPIMULI(PBase *p);
void OPIMULR(PBase *p);

void OPDIVB(PBase *p);
void OPDIVI(PBase *p);//2decode=2
void OPDIVR(PBase *p);

void OPIDIVB(PBase *p);
void OPIDIVI(PBase *p);
void OPIDIVR(PBase *p);

void OPCMPB(PBase *p);
void OPCMPI(PBase *p);//2decode=2
void OPCMPR(PBase *p);

void OPNOTB(PBase *p);//2
void OPNOTI(PBase *p);//2decode=2

void OPANDB(PBase *p);//2
void OPANDI(PBase *p);//2

void OPORB(PBase *p);//2
void OPORI(PBase *p);//2

void OPXORB(PBase *p);//2
void OPXORI(PBase *p);//2

void OPTSTB(PBase *p);//2
void OPTSTI(PBase *p);//2decode=2

void OPINCB(PBase *p);//2
void OPINCI(PBase *p);//2

void OPDECB(PBase *p);//2
void OPDECI(PBase *p);//2

void OPSHLB(PBase *p);
void OPSHLI(PBase *p);

void OPSHRB(PBase *p);
void OPSHRI(PBase *p);

void OPSARB(PBase *p);
void OPSARI(PBase *p);
int instructionParser(int *r0, char* code);
void executionOneStep(PBase *p);
//mapping
//void instructions()
#endif
