D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P     ([Pp][+-]?{D}+)
FS		(f|F|l|L)
IS    ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))
%{
#include "p.h"

%}
%%
"="                       {count();return TOKEN_ASSIGN;}
";"                       {count();return TOKEN_SEMI;}
"processor"               {count();return TOKEN_PROCESSOR;}
"int"                     {count();return TOKEN_INT;}
"real"                    {count();return TOKEN_REAL;}
"reboot"                  {count();return TOKEN_REBOOT;}
"halt"                    {count();return TOKEN_HALT;}
{L}({L}|{D})*		          {count();return TOKEN_ID; }
0[xX]{H}+{IS}?						{ count(); return(CONSTANT); }
0[0-7]*{IS}?							{ count(); return(CONSTANT); }
[1-9]{D}*{IS}?						{ count(); return(CONSTANT); }

{D}+{E}{FS}?							{ count(); return(CONSTANT); }
{D}*"."{D}+{E}?{FS}?			{ count(); return(CONSTANT); }
{D}+"."{D}*{E}?{FS}?			{ count(); return(CONSTANT); }
0[xX]{H}+{P}{FS}?					{ count(); return(CONSTANT); }
0[xX]{H}*"."{H}+{P}{FS}?  { count(); return(CONSTANT); }
0[xX]{H}+"."{H}*{P}{FS}?  { count(); return(CONSTANT); }

[ \t\v\n\f]								{count();}
%%
int yywrap(void)
{
	return 1;
}
void comment(void)
{
	char c, prev = 0;

	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	printf("unterminated comment");
}


int column = 0;

void count(void)
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}
