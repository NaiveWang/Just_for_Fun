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
void MOV1A(PBase *p);
void MOV1(PBase *p);
void MOV8A(PBase *p);//2decode
void MOV8(PBase *p);//2decode+(1+4)addr*2=12
void MOVBA(PBase *p);//2decode:stack0//8addr1,8addr2,4size
void PUSH0A(PBase *p);//2decode+(1+4)addr=7, put the value into BASE_STACK0
void PUSH0I8(PBase *p);//2decode+8data=10
void PUSH0I1(PBase *p);
void PUSH08(PBase *p);//2decode+(1+4)addr=7
void PUSH01(PBase *p);
void POP08(PBase *p);//2decode+(1+4)addr=7
void POP01(PBase *p);

void PUSH1(PBase *p);
void POP1(PBase *p);
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
void OPADDB(PBase *p);
void OPADDI(PBase *p);//2decode=2
void OPADDR(PBase *p);

void OPSUBB(PBase *p);
void OPSUBI(PBase *p);
void OPSUBR(PBase *p);

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

void OPNOTB(PBase *p);
void OPNOTI(PBase *p);//2decode=2

void OPANDB(PBase *p);
void OPANDI(PBase *p);

void OPORB(PBase *p);
void OPORI(PBase *p);

void OPXORB(PBase *p);
void OPXORI(PBase *p);

void OPTSTB(PBase *p);
void OPTSTI(PBase *p);//2decode=2

void OPINCB(PBase *p);
void OPINCI(PBase *p);

void OPDECB(PBase *p);
void OPDECI(PBase *p);

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
