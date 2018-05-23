%{
void yyerror (char *s);
//int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include "proc.h"
%}


%token PROCESSOR
%token IF ELSE WHILE FOR
%token CONTINUE BREAK
%token REBOOT RETURN HALT
%token INT REAL CHAR STATIC
%token EQUAL DIFF GRTEQU LESEQU RAND ROR
%token ID CONSTANT_INT CONSTANT_REAL CONSTANT_CHAR CONSTANT_STRING
%token SHL SHR SAR INC DEC
%token ASSAR ASSHL ASSHR ASADD ASSUB ASDIV ASMOD ASMUL ASAND ASOR ASEOR
%%
transition_unit
  : processor_declaration
  | transition_unit processor_declaration
  ;
processor_declaration
  : PROCESSOR '(' CONSTANT_INT ',' CONSTANT_INT ',' CONSTANT_INT ')' compound_statement
%%
#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
