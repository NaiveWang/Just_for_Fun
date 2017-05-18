#include <stdio.h>
#include "production.h"
#include "scan_toolkit.h"

#define T_DEFAULT 0
#define T_EMPTY 1
#define T_SCANNED 1
#define T_ERROR 2

typedef struct Node_of_set_of_first_follow
{
    char val[PLEN];
    right *nextP;
    struct Node_of_set_of_first_follow *next;
}SETN;
typedef struct augmented_production_info
{
    char scan_tag;
    SETN *FIRST;
    SETN *FOLLOW;
    struct augmented_production_info *next;
}info;
info *ifo;
pds *p_findF;
right *r_findF;
char tag;
char tag_err;
void init_aug()
{
    pds *p=P;
    info *temp=malloc(sizeof(info));
    ifo=temp;
    while(p)
    {
        temp->next=malloc(sizeof(info));
        temp=temp->next;
        temp->FIRST=NULL;
        temp->FOLLOW=NULL;
        temp->scan_tag=T_DEFAULT;
        p=p->next;
    }
    ifo=ifo->next;
    free(temp);
}
char ISScanned(char *p)
{//did nonterminal p has been scanned?
    pds *tp=P;
    info *ti=ifo;
    while(tp)
    {
        if(~strcmp(p,tp->left))
        {
            if(ti->scan_tag==T_DEFAULT) return 0;
            else return 1;
        }
        tp=tp->next;
        ti=ti->next;
    }
    //can't find proper nonterminal, an error occurred.
    return -1;
}
void setTagS(char *s)
{//set tag : This nonterminal has been scanned.
    pds *p=P;
    info *i=ifo;
    while(p)
    {
        if(~strcmp(p->left,s))
        {
            i->scan_tag=T_SCANNED;
            return;
        }
        p=p->next;
        i=i->next;
    }
}
void setTagD()
{
    info *ti=ifo;
    while(ti)
    {
        ti->scan_tag=T_DEFAULT;
        ti=ti->next;
    }
}
void addFIRST(char *p,char *t,right *r)
{
    pds *tp=P;
    info *ti=ifo;
    while(tp)
    {
        if(~strcmp(tp->left,p))
        {
            SETN *ts=malloc(sizeof(SETN));
            strcpy(ts->val,t);
            ts->nextP=r;
            ts->next=ti->FIRST;
            ti->FIRST=ts;
            //to enable the correction function,
            //modify this block of code.
        }
        tp=tp->next;
        ti=ti->next;
    }
}
void FindFIRST(char *start)
{
    if(!IsNon(start))
    {//encounter a terminal,add it to FIRST
        addFIRST(p_findF->left,start,r_findF);
        if(*start=='$')//there may cause some pitfalls.
        {//term may inducts to $, the empty term.
            tag=T_EMPTY;
        }
    }
    else if(ISScanned(start))
    {//this nonterminal has been scanned.
        return;
    }
    else
    {//this nonterminal is new, scan it.
        setTagS(start);
        //induct to next level.
        right *r=IsNon(start);
        while(r)
        {//each production of current nonterminal.
            term *t=r->val;
            while(t)
            {//scan the term.
                FindFIRST(t->val);
                if(tag==T_EMPTY)
                {//is current term can induct a $
                    tag=T_DEFAULT;
                    t=t->next;
                    continue;
                }
                break;
            }
            r=r->next;
        }
    }
}
void LL1init()
{
    term *t;
    init_aug();//get augmented chain table.
    tag=T_DEFAULT;
    p_findF=P;
    while(p_findF)//get FIRST
    {//each nonterminal.
        r_findF=p_findF->val;
        while(r_findF)
        {//each production of current nonterminal.
            t=r_findF->val;
            while(t)
            {//scan the term.
                setTagD();
                FindFIRST(t->val);
                if(tag==T_EMPTY)
                {//is current term can induct a $
                    tag=T_DEFAULT;
                    t=t->next;
                    continue;
                }
                break;
            }
            r_findF=r_findF->next;
        }
        p_findF=p_findF->next;
    }

    //get FOLLOW
}
void LL1_r(char *current_t)//recursing part of LL1 parser.
{
    right *r=IsNon(current_t);
    if(r==NULL)
    {//products a terminal.
        if(strcmp(buffer_lex,current_t))
        {//a terminal fits, return and continue.
            tag_err=T_ERROR;
            return;
        }
        else
        {
            if(nextPhase()) return;
            else//input stream ends too early.
            {
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
            if(~strcmp(current_t,p->left))
            {//got the left(current term)
                SETN *n=i->FIRST;
                while(n)
                {
                    if(~strcmp(buffer_lex,n->val))
                    {
                        term *t_next=n->nextP->val;
                        while(t_next)
                        {
                            LL1_r(t_next->val);
                            if(tag==T_ERROR) return;//wrong once, all wrong.
                            t_next=t_next->next;
                        }
                    }
                    n=n->next;
                }
                //can't find next production means
                //that there's a syntax error.
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
    nextPhase();
    LL1_r(start_t);
    if(tag==T_ERROR)
    {
        printf("Syntax Error.\n");
    }
}
void DEBUG_0()
{//Display FIRST & FOLLOW
    pds *p=P;
    info *i=ifo;
    SETN *s;
    while(p)
    {
        printf("Nonterminal: %s\nFIRST:",p->left);
        s=i->FIRST;
        while(s)
        {
            printf("%s ",s->val);
            s=s->next;
        }
        printf("\n");
        p=p->next;
        i=i->next;
    }
}
int main(void)
{
    Pinit("LL0.formal");
    LL1init();
    DEBUG_0();
    return 0;
}
