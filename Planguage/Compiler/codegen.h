#ifndef CODEGEN_H
#define CODEGEN_H
#include <stdio.h>
#include "symbol.h"
#include "y.tab.h"
#include "../PCoreIR.h"
/* external */
//extern IR pir[];

/* global parameter */
int globalSegOfst;
int stackSegOfst;

FILE *genOut;
/* functions */
void initGen(char*);
void finishGen();
void gen2(int);
void gen2OP(char*,int);
void gen2OP_0(char*);
void gen2OP_1(int);
void genImmI(char*,long);
void genImmR(char*,double);
void genImmC(char*,char);
void genMark(int);
void genPHeader(char*,int,int,int);
void gen(char*);
#endif
