#ifndef CODEGEN_H
#define CODEGEN_H
#include <stdio.h>
#include "symbol.h"
#include "y.tab.h"
#include "../PCoreIR.h"
/* external */
extern IR pir[];
/* global parameter */
FILE *genOut;
/* functions */
void initGen(char*);
void finishGen();
void gen2(int);
void gen12(int,int,int,int,int);
void gen10(int,long);
void gen7(int,int,int);
void gen3(int,char);
void gen14(int,int,long);
void genMark(int);
#endif
