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
#include "y.tab.h"
//#include "proc.h"
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
    int scope;
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

int currentScope;
/* buffer */
/*#define STRING_BUFFER_SIZE 1024
long bufferI;
double bufferF;
char bufferC;
char bufferS[STRING_BUFFER_SIZE];*/
/* function references */
/* function section */
void symbolInit();
id* addID(char*);
id* findID(char*);
constant* addConst(int,char*);
#endif
