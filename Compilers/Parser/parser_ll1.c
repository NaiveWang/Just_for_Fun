#include <stdio.h>
#include "production.h"
#include "scan_toolkit.h"
#include "timer.h"

#define T_DEFAULT 0
#define T_EMPTY 1
#define T_SCANNED 1
#define T_ERROR 2
#define MODIFIED 1
#define COMPLETE 0

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
char *expected;
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
    temp=ifo;
    ifo=ifo->next;
    free(temp);
}
char ISScanned(char *p)
{//did nonterminal p has been scanned?
    pds *tp=P;
    info *ti=ifo;
    while(tp)
    {
        if(!strcmp(p,tp->left))
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
        if(!strcmp(p->left,s))
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
        if(!strcmp(tp->left,p))
        {
            //printf(">>>ADD %s TO %s\n",tp->left,p);
            SETN *ts=malloc(sizeof(SETN));
            strcpy(ts->val,t);
            ts->nextP=r;
            ts->next=ti->FIRST;
            ti->FIRST=ts;
            //to enable the correction function,
            //modify this block of code.
            return;
        }
        tp=tp->next;
        ti=ti->next;
    }
}
SETN* getFIRST(char *s)
{
    pds *p=P;
    info *i=ifo;
    while(p)
    {
        if(!strcmp(s,p->left))
        {
            return i->FIRST;
        }
        p=p->next;
        i=i->next;
    }
    return NULL;
}
SETN* getFOLLOW(char *s)
{
    pds *p=P;
    info *i=ifo;
    while(p)
    {
        if(!strcmp(s,p->left))
        {
            return i->FOLLOW;
        }
        p=p->next;
        i=i->next;
    }
    return NULL;
}
void addFOLLOW(char *p,char *t)
{
    pds *tp=P;
    info *ti=ifo;
    while(tp)
    {
        if(!strcmp(tp->left,p))
        {
            if(ti->FOLLOW)
            {//if the set is not empty.
                SETN *fow=ti->FOLLOW;
                if(!strcmp(t,fow->val)) return;
                while(fow->next)
                {
                    //if some element's equal,return.
                    if(!strcmp(t,fow->next->val)) return;
                    fow=fow->next;
                }
                fow->next=malloc(sizeof(SETN));
                tag=MODIFIED;
                fow=fow->next;
                fow->next=NULL;
                strcpy(fow->val,t);
            }
            else
            {//the set is empty
                ti->FOLLOW=malloc(sizeof(SETN));
                tag=MODIFIED;
                ti->FOLLOW->next=NULL;
                strcpy(ti->FOLLOW->val,t);
            }
            return;
        }
        tp=tp->next;
        ti=ti->next;
    }
}
void FindFIRST(char *start)
{
    if(!IsNon(start))
    {//encounter a terminal,add it to FIRST
        //printf("LEFT:%s ADD:%s\n",p_findF->left,start);

        if(*start=='$')//there may cause some pitfalls.
        {//term may inducts to $, the empty term.
            //printf("%s maybe a E\n",r_findF->val->val);
            tag=T_EMPTY;
            return;
        }
        addFIRST(p_findF->left,start,r_findF);
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
                    if(!t->next)
                    {//if it's a rightmost epsilon.
                        return;
                    }
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
void p3s()
{
    pds *p=P;
    info *i=ifo;
    SETN *s;
    while(p)
    {
        s=i->FIRST;
        while(s)
        {
            if(*(s->val)=='$')
            {
                break;
            }
            s=s->next;
        }
        if(s)i->scan_tag=1;
        else i->scan_tag=0;
        p=p->next;
        i=i->next;
    }
}
int IsTermMatch(term *t)
{

    if(IsNon(t->val))
    {//nonterminal
        static SETN *s;
        static pds *p;
        static info *i;
        s=getFOLLOW(p_findF->left);
        p=P;
        i=ifo;
        while(s)
        {
            addFOLLOW(t->val,s->val);
            s=s->next;
        }
        //can t derives epsilon??
        while(p)
        {//printf("+++");
            if(!strcmp(t->val,p->left))
            {
                return (int)i->scan_tag;
            }
            p=p->next;
            i=i->next;
        }
    }
    return 0;
}
int p3r(term *t)
{
    //printf("%s ",t->val);
    if(t->next)
    {
        if(p3r(t->next))
        {
            return IsTermMatch(t);
        }
        return 0;
    }
    else return IsTermMatch(t);
}
void LL1init()
{
    term *t;
    init_aug();//get augmented chain table.
    tag=T_DEFAULT;
    p_findF=P;
    info *i;
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
                {//is current term can induct a $ directly
                    tag=T_DEFAULT;
                    //add epsilon, if current term is a epsilon.
                    if(*t->val=='$') addFIRST(p_findF->left,t->val,r_findF);
                    t=t->next;//printf("%s\n",t->val);
                    continue;
                }
                break;
            }
            r_findF=r_findF->next;
        }
        //DEBUG_0();
        p_findF=p_findF->next;
    }
    //get FOLLOW
    ///Phase 1:add $ to start symbol;
    addFOLLOW(P->left,"$");
    ///Phase 2:for each production
    p_findF=P;
    while(p_findF)
    {
        r_findF=p_findF->val;
        while(r_findF)
        {//traversal of productions.
            t=r_findF->val;
            while(t->next)
            {//t,Xi;t->next,Xi+1
                if(IsNon(t->val))
                {
                    if(IsNon(t->next->val))
                    {//a nonterminal, add first set
                        SETN *first=getFIRST(t->next->val);
                        while(first)
                        {
                            addFOLLOW(t->val,first->val);
                            first=first->next;
                        }
                    }
                    else addFOLLOW(t->val,t->next->val);
                }
                t=t->next;
            }
            r_findF=r_findF->next;
        }
        p_findF=p_findF->next;

    }
    ///Phase 3:the most perplexing section.
    //set tag to make sure which nonterminal has epsilon.
    p3s();
    do{
        tag=COMPLETE;
        //let's do the fucking job.
        p_findF=P;
        while(p_findF)
        {
            r_findF=p_findF->val;
            while(r_findF)
            {//for each production.
                //printf("%s %s\n",p_findF->left,r_findF->val->val);
                p3r(r_findF->val);
                r_findF=r_findF->next;
            }
            p_findF=p_findF->next;
        }
    }while(tag==MODIFIED);
    //the final step.
    p_findF=P;
    i=ifo;
    while(p_findF)
    {//for each nonterminal A
        SETN *set;
        r_findF=p_findF->val;
        while(r_findF)
        {//each A->a
            set=i->FIRST;
            while(set)
            {
                if(r_findF==set->nextP && *(set->val)=='$')
                {//if there's a epsilon in FIRST(a)
                    //printf("%s\n",p_findF->left);//checked.
                    SETN *flw=i->FOLLOW;//FOLLOW(A)
                    while(flw)
                    {//for each b in FOLLOW(A)
                        //add to FIRST(A)
                        if(*(flw->val)!='$') addFIRST(p_findF->left,flw->val,set->nextP);
                        flw=flw->next;
                    }
                }
                set=set->next;
            }
            r_findF=r_findF->next;
        }
        p_findF=p_findF->next;
        i=i->next;
    }
}
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
void DEBUG_0()
{//Display FIRST & FOLLOW
    pds *p=P;
    info *i=ifo;
    SETN *s1,*s2;
    printf("\n>>>DEBUG SECTION 0 START<<<\n");
    while(p)
    {
        printf("NONTERMINAL: %s\n----FIRST:",p->left);
        s1=i->FIRST;
        s2=i->FOLLOW;
        while(s1)
        {
            printf("%s ",s1->val);
            s1=s1->next;
        }
        printf("\n----FOLLOW:");
        while(s2)
        {
            printf("%s ",s2->val);
            s2=s2->next;
        }
        printf("\n");
        p=p->next;
        i=i->next;
    }
    printf(">>>DEBUG SECTION 0 ENDS<<<\n\n");
}
int main(void)
{
    Pinit("LL0.formal");
    OpenLex("stmt.out");
    timerStart();
    LL1init();
    printf("Building LL1 Parsing table : %ld ms.\n",timerEnd());
    //DEBUG_0();
    LL1_parser("BLOCK");
    Pclose();
    return 0;
}
