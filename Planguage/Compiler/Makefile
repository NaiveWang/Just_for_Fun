compiler:
	lex proc.l
	yacc -d proc.y
	gcc main.c compiler.c symbol.c y.tab.c lex.yy.c -o lexer
