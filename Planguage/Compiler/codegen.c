#include "codegen.h"
void initGen(char *s)
{
  //open file
  genOut = fopen(s,"w");
}
void finishGen()
{
  fflush(genOut);
  fclose(genOut);
}
void gen2 (int codeTyp)
{
  switch(codeTyp)
  {
    case _HALT:
      fprintf(genOut,"HALT");
      break;
    case _SUSPEND:
      fprintf(genOut,"SUSPEND");
      break;
    case _REBOOT:
      fprintf(genOut,"REBOOT");
      break;
  }
  fprintf(genOut,"\n");
}
void genPHeader(char* s,int st0,int st,int gl)
{
  //generate the processor header of the file
  fprintf(genOut,".processor %s %d %d %d\n",s,st0,st,gl);
}
