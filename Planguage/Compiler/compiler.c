#include "compiler.h"
int lexNextToken()
{
  static int a0;
  a0=yylex();
  if(a0==CONSTANT_INT||
    a0==CONSTANT_HEX||
    a0==CONSTANT_OCT||
    a0==CONSTANT_REAL||
    a0==CONSTANT_CHAR||
    a0==CONSTANT_STRING||
  )
    printf("\n$%s$\n",yytext);
}
