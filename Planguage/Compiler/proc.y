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
%start transition_unit
%%
primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;
postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
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
	| '(' type_specifier')' cast_expression
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
	| shift_expression SAR additive_expression
	;
relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression GRTEQU shift_expression
	| relational_expression LESEQU shift_expression
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
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;
assignment_operator
	: '='
	| ASMUL
	| ASDIV
	| ASMOD
	| ASADD
	| ASSUB
	| ASSHR
	| ASSAR
	| ASSHL
	| ASAND
	| ASEOR
	| ASOR
	;
expression
	: assignment_expression
	;
constant_expression
	: conditional_expression
	;
	
	
	
	
transition_unit
  : processor_declaration
  | transition_unit processor_declaration
  ;
processor_declaration
  : PROCESSOR '(' CONSTANT_INT ',' CONSTANT_INT ',' CONSTANT_INT ')' compound_statement
  ;
compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list statement_list '}'
	;
statement_list
	: statement
	| statement_list statement
	;
declaration_list
	: declaration
	| declaration_list declaration
	;
declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;
declaration_specifiers
	: STATIC declaration_specifiers
	| type_specifier declaration_specifiers
	;
type_specifier
	: VOID
	| CHAR
	| INT
	| REAL
	;
init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;
init_declarator
	: declarator
	| declarator '=' initializer
	;
declarator
	: pointer direct_declarator
	| direct_declarator
	;
direct_declarator
	: IDENTIFIER
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	;
pointer
	: '*'
	| '*' pointer
	;
initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;
initializer_list
	: initializer
	| initializer_list ',' initializer
	;
	

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	| processor_statement
	;
declaration_list
	: declaration
	| declaration_list declaration
	;
statement_list
	: statement
	| statement_list statement
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
processor_statement
	: HALT;
	| REBOOT
	;
jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;
%%
#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
