#include <stdio.h>
#define LEXBUF 512
FILE *source;
char buffer_lex[LEXBUF];

void OpenLex(char *so)
{
    source = fopen(so,"r");
}
void CloseLex()
{
    fclose(source);
}
char* nextPhase()
{
    if(fscanf(source,"%s",buffer_lex)!=EOF)
    {
        //printf("%s",buffer_lex);
        return buffer_lex;
    }
    else return NULL;
}
char IsID(char *s)
{
    if(s[0]=='I' && s[1]=='D') return 1;
    return 0;
}
char IsIm(char *s)
{
    if(s[0]=='I' && s[1]=='M') return 1;
    return 0;
}
