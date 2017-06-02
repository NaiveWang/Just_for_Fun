#include <stdio.h>
#include "production.h"
#include "scan_toolkit.h"
#define STACK 4096
char stack[STACK][PLEN];
int s_top;
void push(char *s)
{
    strcpy(stack[s_top],s);
    s_top++;
}
char* pop()
{
    if(s_top) s_top--;
    else return NULL;
    return stack[s_top];
}
short match(term *t)
{
    if(t->next)
    {
        short i = match(t->next);
        if(i)
        {
            printf("%s===%s\n",stack[s_top-i],t->val);
            if(strcmp(stack[s_top-i],t->val)) return 0;
            return i+1;
        }
        else return 0;
    }
    else
    {
        //printf("%s===%s\n",stack[s_top-1],t->val);
        if(strcmp(stack[s_top-1],t->val)) return 0;
        return 2;
    }
}
pds* findp()
{
    pds *p=P;
    while(p)
    {
        right *r=p->val;
        while(r)
        {
            short i = match(r->val);
            if(i)
            {
                printf("%d\n",i);
                s_top-=(i-1);

                return p;
            }
            r=r->next;
        }
        p=p->next;
    }
    return NULL;
}
void sr(char *start)
{
    //push(nextPhase());
    while(nextPhase())
    {
        push(buffer_lex);
        printf("push:%s\n",buffer_lex);
        for(;;)
        {
            pds *p = findp();
            if(p)
            {
                printf("%s\n",p->left);
                push(p->left);
            }
            else break;

        }
    }
    printf("%s %d\n",*stack,s_top);
    if(~strcmp(start,*stack) && s_top==1) printf("No syntax error.\n");
    else printf("Something Wrong Here.\n");
}
int main(void)
{
    Pinit("sr.formal");
    OpenLex("SLR.out");
    s_top=0;
    //printf("%s\n",findp()->left);
    sr("E");
    CloseLex();
    return 0;
}
