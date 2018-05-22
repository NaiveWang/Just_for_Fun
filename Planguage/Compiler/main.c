#include <stdio.h>
#include "p.h"
extern int yylex();
extern int yylineno;
extern char* yytext;
int main(void)
{
  int ntoken;
  do{
    //
    ntoken = yylex();
    printf("|%c|",(int)ntoken);
  }while(ntoken);
  return 0;
}
