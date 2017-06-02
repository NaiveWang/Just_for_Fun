#include <stdio.h>
#include "production.h"
#include "scan_toolkit.h"
#define p(x) printf("%s\n",x)
#define PRODUCTION_SKIP 2
#define DEFAULT 0
#define ERROR 1//occurred

//char *phase;
int tag;
void Error(int n)
{
    switch(n)
    {
        case 0:p("Unknown error  ");break;
        case 1:p("Code ended\n");break;
        case 2:p("Syntax Error\n");break;
        default:p("You Bloody Bastard.\n");break;
    }
}
void LL0parser(char *start)
{
    right *r = IsNon(start);
    p(start);
    if(r==NULL)
    {//it's a terminal.

        if(IsE(start))return;//if it's a empty term:return.
        if(bc_move(0)==NULL)
        {
            tag = PRODUCTION_SKIP;
            return;
        }
        if(IsID(start)&&IsID(bc_move(0)))
        {//if it's an identifier:get next term and return.
            bc_move(1);
            p("matched");
            return;
        }
        if(IsIm(start)&&IsIm(bc_move(0)))
        {//if it's am immediate:get next term and return.
            bc_move(1);
            p("matched");
            return;
        }
        if(!strcmp(start,bc_move(0)))
        {//if it matches the current term:get next term and return.
            bc_move(1);
            p("matched");
            return;
        }
        //the term does not match:if input stream ends,error1;
        //if it's just does not match,return and set tag to PRODUCTION_SKIP

        tag = PRODUCTION_SKIP;
        return;
    }
    else
    {//it's a non terminal.
        p("--->");
        while(r)
        {//choose one of the nonterminal's production set.
            term *t=r->val;
            short i=0;
            while(t)
            {//scan the terms,and recurs the function.
                LL0parser(t->val);
                if(tag==ERROR) return;//process with the tag val:
                if(tag==PRODUCTION_SKIP)
                {//PRODUCTION_SKIP:set tag to DEFAULT
                    bc_move(-i);
                    //tag=DEFAULT;
                    break;
                }
                i++;
                t=t->next;
            }
            if(tag==PRODUCTION_SKIP)
            {//if the nonterminal does not match, test another production;
                tag=DEFAULT;
                r=r->next;
                continue;
            }
            else
            {//if matches, return to prior level immediately.
                tag=DEFAULT;
                return;
            }

            //INPUT_ENDS:just return.
        }
        //if searched all but no match,error occurred.
        tag=PRODUCTION_SKIP;
        return;
    }
}
int main(void)
{
    Pinit("LL0.formal");
    OpenLex("ll0.out");
    usingChain();
    CloseLex();
    tag=DEFAULT;
    //Pchecker();
    LL0parser("E");
    if(bc_move(0)!=NULL) Error(2);
    freeChain();

    return 0;
}
