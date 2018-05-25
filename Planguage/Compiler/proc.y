%{
void yyerror (char const *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include "symbol.h"
#include "y.tab.h"
#include "codegen.h"
//#define SIZE_NAME 128
extern char* yytext;
extern int currentScope;
void typeCheck(int,int);
%}
%union {int type;long dec;char name[128];double real;}
%token PROCESSOR
%token IF ELSE WHILE FOR
%token CONTINUE BREAK
%token _REBOOT RETURN _HALT _SUSPEND
%token INT
%token REAL
%token CHAR
%token STRING
%token STATIC VOID
%token EQUAL DIFF GRTEQU LESEQU RAND ROR
%token CONSTANT_REAL
%token CONSTANT_CHAR
%token CONSTANT_STRING
%token CONSTANT_HEX
%token CONSTANT_OCT
%token SHL SHR SAR INC DEC
%token ASSAR ASSHL ASSHR ASADD ASSUB ASDIV ASMOD ASMUL ASAND ASOR ASEOR

%token <dec>CONSTANT_INT
%token <name>ID

%type <type>expression assignment_expression primary_expression postfix_expression
%type <type>unary_expression cast_expression
%type <type>multiplicative_expression additive_expression shift_expression relational_expression
%type <type>equality_expression
%type <type>and_expression exclusive_or_expression inclusive_or_expression
%type <type>logical_or_expression logical_and_expression
%start translation_unit
%%
primary_expression
	: ID {$$=0;}
	| CONSTANT_INT {$$=TYP_INT;}
	| CONSTANT_REAL {$$=TYP_REAL;}
	| CONSTANT_CHAR {$$=TYP_CHAR;}
	| STRING {$$=TYP_STRING;}
	| '(' expression ')' {$$=$2;}
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression INC
	| postfix_expression DEC
	;


unary_expression
	: postfix_expression
	| INC unary_expression
	| DEC unary_expression
	| unary_operator cast_expression
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_specifier ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
		{typeCheck($1,$3);}
	| multiplicative_expression '/' cast_expression
	 	{typeCheck($1,$3);}
	| multiplicative_expression '%' cast_expression
		{typeCheck($1,$3);}
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	 	{typeCheck($1,$3);}
	| additive_expression '-' multiplicative_expression
	 	{typeCheck($1,$3);}
	;

shift_expression
	: additive_expression
	| shift_expression SHL additive_expression
		{typeCheck($1,$3);}
	| shift_expression SHR additive_expression
		{typeCheck($1,$3);}
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
		{typeCheck($1,$3);}
	| relational_expression '>' shift_expression
		{typeCheck($1,$3);}
	| relational_expression LESEQU shift_expression
		{typeCheck($1,$3);}
	| relational_expression GRTEQU shift_expression
		{typeCheck($1,$3);}
	;

equality_expression
	: relational_expression
	| equality_expression EQUAL relational_expression
		{typeCheck($1,$3);}
	| equality_expression DIFF relational_expression
		{typeCheck($1,$3);}
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
		{typeCheck($1,$3);}
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
		{typeCheck($1,$3);}
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
		{typeCheck($1,$3);}
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression RAND inclusive_or_expression
		{typeCheck($1,$3);}
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression ROR logical_and_expression
		{typeCheck($1,$3);}
	;

assignment_expression
	: logical_or_expression
	| unary_expression assignment_operator assignment_expression
		{typeCheck($1,$3);}
	;

assignment_operator
	: '='
	| ASMUL
	| ASDIV
	| ASMOD
	| ASADD
	| ASSUB
	| ASSHL
	| ASSHR
	| ASAND
	| ASEOR
	| ASOR
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;
declaration_specifiers
	: STATIC
	| STATIC declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	;
init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: direct_declarator
	| direct_declarator '=' assignment_expression
	;


type_specifier
	: VOID
	| CHAR
	| REAL
	| INT
	;


direct_declarator
	: ID //{//printf("$$$%d$$$",currentScope);}
	| direct_declarator '[' assignment_expression ']'
	| direct_declarator '[' ']'
	;

statement
  :
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
  | control_statement
	;
control_statement
  : _HALT  ';' {gen2(_HALT);}
  | _REBOOT ';' {gen2(_REBOOT);}
	| _SUSPEND ';' {gen2(_SUSPEND);}
  ;

compound_statement
	: '{' {currentScope++;} block_item_list '}' {currentScope--;}
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	| statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: processor_declaration
	| translation_unit processor_declaration
	;

processor_declaration
	: PROCESSOR ID '(' CONSTANT_INT ',' CONSTANT_INT ',' CONSTANT_INT ')'
		{genPHeader($2,$4,$6,$8);}
		compound_statement
	;

%%
#include <stdio.h>

//extern char yytext[];
extern int column;

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
void typeCheck(int l,int r)
{
	printf("type checking failure : \n");
	yyerror(yytext);
	exit(-1);
}
