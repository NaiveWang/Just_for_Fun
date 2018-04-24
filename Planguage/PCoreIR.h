#include "PCoreBase.h"
/**
 * Here is the instruction set & mapping
 **/
#ifndef PCOREIR_H
#define PCOREIR_H
//instructions
//template: void *<NAME>(PBase)
/** Data transfer **/
void *MOV8A(PBase *p);//2decode
void *MOV8(PBase *p);//2decode+(1+4)addr*2=12
void *PUSH0A(PBase *p);//2decode+(1+4)addr=7, put the value into BASE_STACK0
void *PUSH0I8(PBase *p);//2decode+8data=10
void *PUSH08(PBase *p);//2decode+(1+4)addr=7
void *POP08(PBase *p);//2decode+(1+4)addr=7
void *PUSH8(PBase *p);//2decode+(1+4)addr=7
void *POP8(PBase *p);//2decode+(1+4)addr=7
/** Control **/
void *CALL(PBase *p);//2decode+8offset=10,push pc
void *RETN(PBase *p);//2decode=2:recover pc
void *JUMP(PBase *p);//2decode+8offset=10
void *JMPC(PBase *p);//2decode+4mask+8offset=14
/** Operation **/
void *OPADDI(PBase *p);//2decode=2
void *OPSUBI(PBase *p);//2decode=2
void *OPMULI(PBase *p);//2decode=2
void *OPDIVI(PBase *p);//2decode=2
//mapping
//void instructions()
#endif
