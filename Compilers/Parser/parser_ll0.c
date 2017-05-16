#include <stdio.h>
#include "production.h"
#include "scan_toolkit.h"
#define p(x) printf("%s",x)
char *phase;
void Error(int n)
{
    switch(n)
    {
        case 0:p("unknown error");break;
        case 1:p("code ended\n");break;
    }
}
void LL0parser(char *start)
{
    right *r = IsNon(start);
    if(r==NULL)
    {
        phase = nextPhase();
        if(phase==NULL){Error(0);return;}
        if(IsID(start)&&IsID(phase))//terminal identifier
        {
            //fit
        }
        else if(IsIm(start)&&IsIm(start))//terminal immediate
        {
            //fit
        }
        else if(~strcmp(phase,start))//terminal
        {
            //fit
        }
        else
        {
            Error(0);
            return;
        }
    }
    else
    {
        term *t;
        while(r)
        {
            t=r->val;
            while(t)
            {
                LL0parser(t->val);
                t=t->next;
            }
            r=r->next;
        }
    }
}
int main(void)
{
    OpenLex("stmt.out");
    LL0parser("STMS");
    CloseLex();
    Pinit("LL0.formal");
    return 0;
}
