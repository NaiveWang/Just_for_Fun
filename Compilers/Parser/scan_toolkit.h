#ifndef SCAN_TOOLKIT_H
#define SCAN_TOOLKIT_H
#include <stdio.h>
#define LEXBUF 512
#define PLEN 16
typedef struct node_of_phrase
{
    char val[PLEN];
    struct node_of_phrase *prev;
    struct node_of_phrase *next;
}pnode;
FILE *source;
pnode *buffer_chain,*origin;
char buffer_lex[LEXBUF];

void OpenLex(char *so)
{
    source = fopen(so,"r");
}
void CloseLex()
{
    fclose(source);
}
char* initScanner()
{
    fscanf(source,"%s",buffer_lex);
    return buffer_lex;
}
char* nextPhase()
{
    if(buffer_lex[0]&&fscanf(source,"%s",buffer_lex)!=EOF)
    {
        //printf("%s",buffer_lex);
        return buffer_lex;
    }
    else
    {
        buffer_lex[0]=0;
        return NULL;
    }
}
void usingChain()
{
    pnode *p;
    buffer_chain = malloc(sizeof(pnode));
    p=buffer_chain;
    while(nextPhase())
    {
        p->next=malloc(sizeof(pnode));
        p->next->prev=p;
        p=p->next;
        strcpy(p->val,buffer_lex);
        p->next=NULL;
    }
    p=buffer_chain;
    buffer_chain=p->next;
    free(p);
    buffer_chain->prev=NULL;
    origin=buffer_chain;
}
void freeChain()
{
    pnode *p=origin;
    while(origin)
    {
        p=origin;
        origin=origin->next;
        free(p);
    }
}
char* bc_move(int i)
{
    if(i>=0)
    {
        while(i--)
        {
            buffer_chain=buffer_chain->next;
        }
    }
    else
    {
        while(i++)
        {
            buffer_chain=buffer_chain->prev;
        }
    }
    return buffer_chain->val;
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
char IsE(char *s)
{
	if(*s == '$') return 1;
	return 0;
}
#endif
