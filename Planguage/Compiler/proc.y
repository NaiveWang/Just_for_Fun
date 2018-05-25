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
void typeErrNotFound();
void typeErrRedeclared();
void typeErrMismatch();
id* temp;
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
%type <type>type_specifier declaration_specifiers
%type <type>init_declarator init_declarator_list
%start translation_unit
%%
primary_expression
	: ID
		{
			temp=findID($1);
			if(temp)
			{
			$$=temp->type;
			}
			else
			{
			typeErrNotFound();
			}
		}
	| CONSTANT_INT {$$=TYP_INT;}
	| CONSTANT_REAL {$$=TYP_REAL;}
	| CONSTANT_CHAR {$$=TYP_CHAR;}
	| STRING {$$=TYP_STRING;}
	| '(' expression ')' {$$=$2;}
	;

postfix_expression
	: primary_expression
		{$$=$1;}
	| postfix_expression '[' expression ']'
		{$$=$1;}
	| postfix_expression INC
		{$$=$1;}
	| postfix_expression DEC
		{$$=$1;}
	;


unary_expression
	: postfix_expression
		{$$=$1;}
	| INC unary_expression
		{$$=$2;}
	| DEC unary_expression
		{$$=$2;}
	| unary_operator cast_expression
		{$$=$2;}
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
		{$$=$1;}
	| '(' type_specifier ')' cast_expression
		{$$=$2;}
	;

multiplicative_expression
	: cast_expression
		{$$=$1;}
	| multiplicative_expression '*' cast_expression
		{typeCheck($1,$3);$$=$1;}
	| multiplicative_expression '/' cast_expression
	 	{typeCheck($1,$3);$$=$1;}
	| multiplicative_expression '%' cast_expression
		{typeCheck($1,$3);$$=$1;}
	;

additive_expression
	: multiplicative_expression
		{$$=$1;}
	| additive_expression '+' multiplicative_expression
	 	{typeCheck($1,$3);$$=$1;}
	| additive_expression '-' multiplicative_expression
	 	{typeCheck($1,$3);$$=$1;}
	;

shift_expression
	: additive_expression
		{$$=$1;}
	| shift_expression SHL additive_expression
		{typeCheck($1,$3);$$=$1;}
	| shift_expression SHR additive_expression
		{typeCheck($1,$3);$$=$1;}
	;

relational_expression
	: shift_expression
		{$$=$1;}
	| relational_expression '<' shift_expression
		{typeCheck($1,$3);$$=$1;}
	| relational_expression '>' shift_expression
		{typeCheck($1,$3);$$=$1;}
	| relational_expression LESEQU shift_expression
		{typeCheck($1,$3);$$=$1;}
	| relational_expression GRTEQU shift_expression
		{typeCheck($1,$3);$$=$1;}
	;

equality_expression
	: relational_expression
		{$$=$1;}
	| equality_expression EQUAL relational_expression
		{typeCheck($1,$3);$$=$1;}
	| equality_expression DIFF relational_expression
		{typeCheck($1,$3);$$=$1;}
	;

and_expression
	: equality_expression
		{$$=$1;}
	| and_expression '&' equality_expression
		{typeCheck($1,$3);$$=$1;}
	;

exclusive_or_expression
	: and_expression
		{$$=$1;}
	| exclusive_or_expression '^' and_expression
		{typeCheck($1,$3);$$=$1;}
	;

inclusive_or_expression
	: exclusive_or_expression
		{$$=$1;}
	| inclusive_or_expression '|' exclusive_or_expression
		{typeCheck($1,$3);$$=$1;}
	;

logical_and_expression
	: inclusive_or_expression
		{$$=$1;}
	| logical_and_expression RAND inclusive_or_expression
		{typeCheck($1,$3);$$=$1;}
	;

logical_or_expression
	: logical_and_expression
		{$$=$1;}
	| logical_or_expression ROR logical_and_expression
		{typeCheck($1,$3);$$=$1;}
	;

assignment_expression
	: logical_or_expression
		{$$=$1;}
	| unary_expression assignment_operator assignment_expression
		{typeCheck($1,$3);$$=$1;}
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
	: declaration_specifiers init_declarator_list ';'
		{
		typeCheck($1,$2);
		setMetaType($1);
		}
	;
declaration_specifiers
	: STATIC type_specifier {$$=$2;}
	| type_specifier {$$=$1;}
	;
init_declarator_list
	: init_declarator
		{$$=$1;}
	| init_declarator_list ',' init_declarator
		{typeCheck($1,$3);$$=$1>$3?$1:$3;}
	;

init_declarator
	: direct_declarator {$$=TYP_META;}
	| direct_declarator '=' assignment_expression{$$=$3;}
	;


type_specifier
	: VOID {$$=TYP_META;}
	| CHAR {$$=TYP_CHAR;}
	| REAL {$$=TYP_REAL;}
	| INT {$$=TYP_INT;}
	;


direct_declarator
	: ID
		{
		temp=addID(TYP_META,$1);
		if(!temp)
			typeErrRedeclared();
		}
	| direct_declarator '[' assignment_expression ']'{if($3!=TYP_INT) typeErrMismatch();}
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
	: '{' {currentScope++;} block_item_list '}' {leaveScope();}
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
		{
		//check first
		temp = addID(TYP_PROC,$2);
		if(!temp)
			typeErrRedeclared();
		genPHeader($2,$4,$6,$8);
		}
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
printf("$%d#%d$",l,r);
if(l==TYP_META || r==TYP_META || l==r) return;
	printf("type checking failure:%d/%d/",l,r);
	yyerror(yytext);
	exit(-1);
}

void typeErrNotFound()
{
	printf("type error : cannot find declaration.");
	yyerror(yytext);
	exit(-1);
}
void typeErrRedeclared()
{
	printf("type error : identifier name override.");
	yyerror(yytext);
	exit(-1);
}
void typeErrMismatch()
{
	printf("type error : type mismatch.");
	yyerror(yytext);
	exit(-1);
}
