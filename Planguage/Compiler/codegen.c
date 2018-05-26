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
void gen2OP(char* ins,int type)
{
  //
  fprintf(genOut, "OP%s", ins);
  switch(type)
  {
    case TYP_INT :
      fprintf(genOut, "I\n");
      break;
    case TYP_REAL:
      fprintf(genOut, "R\n");
      break;
    case TYP_CHAR:
      fprintf(genOut, "B\n");
      break;
  }
}
void gen2OP_0(char* s)
{
  fprintf(genOut, "OP%s", s);
}
void gen2OP_1(int t)
{
  switch(t)
  {
    case TYP_INT :
      fprintf(genOut, "I\n" );
      break;
    case TYP_REAL:
      fprintf(genOut, "R\n" );
    case TYP_CHAR:
      fprintf(genOut, "B\n" );
      break;
  }
}
void genPHeader(char* s,int st0,int st,int gl)
{
  //generate the processor header of the file
  fprintf(genOut,".processor %s %d %d %d\n",s,st0,st,gl);
}
void gen(char* s)
{
  fprintf(genOut,"%s\n",s);
}
void genImmI(char* s,long v)
{
  fprintf(genOut, "%s %ld\n", s, v);
}
void genImmR(char* s,double v)
{
  fprintf(genOut, "%s %le\n", s, v);
}
void genImmC(char* s,char v)
{
  fprintf(genOut, "%s %c\n", s, v);
}
