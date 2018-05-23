#ifndef SYMBOL_H
#define SYMBOL_H
/**
  * this file contains the fucking
  *
  *
  **/
/* type define & macro */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "proc.h"
#define LENGTH_ID 32
#define SIZE_IDLIST 4096
#define SIZE_CONSTLIST 4096
#define TYP_META 0
#define TYP_PTR 'P'
#define TYP_CHAR 'C'
#define TYP_INT 'I'
#define TYP_REAL 'R'
#define TYP_STRING 'S'
typedef struct identifierList
{
    char type;
    char name[LENGTH_ID];
}id;
typedef struct constantList
{
    char type;
    void *content;
}constant;
/* global data section */
id identifiers[SIZE_IDLIST];
int identifiersCursor;
constant constants[SIZE_CONSTLIST];

int constantsCursor;
/* function references */
/* function section */
void symbolInit();
id* addID(char* s);
constant* addConst(char typ,char* s);
#endif
