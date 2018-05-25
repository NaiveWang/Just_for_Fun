%{
void yyerror (char const *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include "symbol.h"
#include "y.tab.h"
#include "codegen.h"
extern char* yytext;
extern int currentScope;
%}
%union {int dec;char* name;}
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
%token <name>ID
%token <dec>CONSTANT_INT
%token CONSTANT_REAL
%token CONSTANT_CHAR
%token CONSTANT_STRING
%token CONSTANT_HEX
%token CONSTANT_OCT
%token SHL SHR SAR INC DEC
%token ASSAR ASSHL ASSHR ASADD ASSUB ASDIV ASMOD ASMUL ASAND ASOR ASEOR
%start translation_unit
%%
primary_expression
	: ID
	| CONSTANT_INT
	| CONSTANT_REAL
	| CONSTANT_CHAR
	| STRING
	| '(' expression ')'
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
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression SHL additive_expression
	| shift_expression SHR additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LESEQU shift_expression
	| relational_expression GRTEQU shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQUAL relational_expression
	| equality_expression DIFF relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression RAND inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression ROR logical_and_expression
	;

assignment_expression
	: logical_or_expression
	| unary_expression assignment_operator assignment_expression
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
	: ID {printf("$$$%d$$$",currentScope);}
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
	: PROCESSOR ID '(' CONSTANT_INT ',' CONSTANT_INT ',' CONSTANT_INT ')' {
		genPHeader($2,$4,$6,$8);
	} compound_statement
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
