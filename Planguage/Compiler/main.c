#include <stdio.h>
#include "compiler.h"
int main(void)
{
  symbolInit();
  yyparse();
  return 0;
}
