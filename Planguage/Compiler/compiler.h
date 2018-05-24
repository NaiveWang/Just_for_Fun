#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
//#include "symbol.h"
#include "proc.h"
/* external reference section */
extern int yylex();
extern int yyparse();
extern int yylineno;
extern char* yytext;

extern void symbolInit();
/* global argument section */
/* function section */
int lexNextToken();
#endif
