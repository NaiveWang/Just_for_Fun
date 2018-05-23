#include <stdio.h>
#include "proc.h"
#include "symbol.h"
extern int yylex();
extern int yylineno;
extern char* yytext;
int main(void)
{
  int ntoken;
  do{
    //
    ntoken = yylex();
    printf("%d\n",(int)ntoken);
  }while(ntoken);
  return 0;
}
