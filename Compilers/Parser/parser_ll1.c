#include <stdio.h>
//#define LL1
#include "production.h"
#include "FOLLOW.h"
#include "scan_toolkit.h"
#include "timer.h"
/**
 * LL(1) parser
 * without production checking.
 * if U choose an input production set,
 * U'll get a wrong LL(1) parser.
 */
void LL1_r(char *current_t)//recursing part of LL1 parser.
{
    right *r=IsNon(current_t);
    //printf("%s>>>%s\n",buffer_lex,current_t);
    if(r==NULL)
    {//products a terminal.
        //printf("%s is a terminal.\n",current_t);
        if(*current_t=='$')
        {//if the terminal is an epsilon.
            return;
        }
        else if(strcmp(buffer_lex,current_t))
        {//a terminal fits, return and continue.
            tag_err=T_ERROR;
            printf("###Not Equal.\n");
            expected=current_t;
            //printf("%s\n",expected);
            return;
        }
        else
        {
            //printf("Equal.\n");
            if(nextPhase()) return;
            else//input stream ends too early.
            {
                printf("###Stream ends.\n");
                tag_err=T_ERROR;
                return;
            }
        }
    }
    else
    {//get a nonterminal,recurs.
        //differ form LL0 parsing, in this block
        //no need to scan whole production tree
        //just find next production via current phrase in input buffer.
        pds *p=P;
        info *i=ifo;
        while(p)
        {//find next production precisely
            if(!strcmp(current_t,p->left))
            {//got the left(current term)
                SETN *n=i->FIRST;
                while(n)
                {
                    if(!strcmp(buffer_lex,n->val))
                    {
                        term *t_next=n->nextP->val;
                        while(t_next)
                        {
                            LL1_r(t_next->val);
                            if(tag==T_ERROR) return;//wrong once, all wrong.
                            t_next=t_next->next;
                        }
                        return;
                    }
                    n=n->next;
                }
                //can't find next production means
                //that there's a syntax error.
                printf("###No production matched.\n");
                tag_err=T_ERROR;
                return;
            }
            p=p->next;
            i=i->next;
        }
        //return;
    }
}
void LL1_parser(char *start_t)
{
    initScanner();
    timerStart();
    //Sleep(1000);
    expected=NULL;
    LL1_r(start_t);


    if(tag_err==T_ERROR)
    {
        //printf("***%s\n",buffer_lex);
        printf("Syntax Error.\n");
        printf("%X\n",expected);
        if(expected)
        {
            printf("The parser may expect : %s\n",expected);
        }
    }
    else if(nextPhase())
    {
        printf("Syntax Error.\n");
        printf("Input Stream Remains.\n");
    }
    else
    {
        printf("Syntax Checking Passed, Congratulations!\n");
        printf("cost %ld milliseconds.\n",timerEnd());
    }
}
int main(void)
{
    Pinit("LL0.formal");
    OpenLex("stmt.out");
    timerStart();
    LL1init();
    printf("Building LL1 Parsing table : %ld ms.\n",timerEnd());
    DEBUG_0();
    LL1_parser("BLOCK");
    Pclose();
    return 0;
}
