D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P     ([Pp][+-]?{D}+)
FS		(f|F|l|L)
IS    ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))
%{
#include "proc.h"

%}
%%
"processor"               {count();return PROCESSOR;}

"int"                     {count();return INT;}
"real"                    {count();return REAL;}
"char"          	        {count();return HALT;}

"reboot"                  {count();return REBOOT;}
"halt"                    {count();return HALT;}
"return"          	      {count();return HALT;}

"if"          	          {count();return IF;}
"else"          	        {count();return ELSE;}
"while"          	        {count();return WHILE;}
"for"          	      	  {count();return FOR;}
"continue"          	    {count();return CONTINUE;}
"break"          	        {count();return BREAK;}
"static"    							{count();return STATIC;}

{L}({L}|{D})*		          {count();return ID; }

0[xX]{H}+{IS}?						{ count(); return(CONSTANT_INT); }
0[0-7]*{IS}?							{ count(); return(CONSTANT_INT); }
[1-9]{D}*{IS}?						{ count(); return(CONSTANT_INT); }

{D}+{E}{FS}?							{ count(); return(CONSTANT_INT); }
{D}*"."{D}+{E}?{FS}?			{ count(); return(CONSTANT_REAL); }
{D}+"."{D}*{E}?{FS}?			{ count(); return(CONSTANT_REAL); }
0[xX]{H}+{P}{FS}?					{ count(); return(CONSTANT_REAL); }
0[xX]{H}*"."{H}+{P}{FS}?  { count(); return(CONSTANT_REAL); }
0[xX]{H}+"."{H}*{P}{FS}?  { count(); return(CONSTANT_REAL); }
">>>="			{ count(); return(ASSAR); }
">>="			{ count(); return(ASSHR); }
"<<="			{ count(); return(ASSHL); }
"+="			{ count(); return(ASADD); }
"-="			{ count(); return(ASSUB); }
"*="			{ count(); return(ASMUL); }
"/="			{ count(); return(ASDIV); }
"%="			{ count(); return(ASMOD); }
"&="			{ count(); return(ASAND); }
"^="			{ count(); return(ASEOR); }
"|="			{ count(); return(ASOR); }
">>>"			{ count(); return(SAR); }
">>"			{ count(); return(SHR); }
"<<"			{ count(); return(SHL); }
"++"			{ count(); return(INC); }
"--"			{ count(); return(DEC); }
"&&"			{ count(); return(RAND); }
"||"			{ count(); return(ROR); }
"<="			{ count(); return(LESEQU); }
">="			{ count(); return(GRTEQU); }
"=="			{ count(); return(EQUAL); }
"!="			{ count(); return(DIFF); }

";"			{ count(); return(';'); }
"{"		{ count(); return('{'); }
"}"		{ count(); return('}'); }
","			{ count(); return(','); }
":"			{ count(); return(':'); }
"="			{ count(); return('='); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
"["		{ count(); return('['); }
"]"		{ count(); return(']'); }
"."			{ count(); return('.'); }
"&"			{ count(); return('&'); }
"!"			{ count(); return('!'); }
"~"			{ count(); return('~'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }
"%"			{ count(); return('%'); }
"<"			{ count(); return('<'); }
">"			{ count(); return('>'); }
"^"			{ count(); return('^'); }
"|"			{ count(); return('|'); }
[ \t\v\n\f]								{count();}
.
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
