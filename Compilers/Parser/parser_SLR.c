#include <stdio.h>
#include "production.h"
#include "scan_toolkit.h"
/**
 * SLR parser.
 * we can also call it "Simple LR parser",
 */
#define STACK 4096
#define paddr(X) printf("%X\n",X)

typedef enum type_of_element
{
    REDUCE=0,SHIFT,ACC
}e_type;
typedef enum tag_of_augmented_production
{
    EXIST,EX_TB,EMPTY,NOP,MODIFIED
}a_tag;
/**
 * About the parsing table:
 * I'm using addresses to represent states,
 * CLOSURE's addresses, cause they'r unique.
 */
/** Type Statements Section **/
typedef struct augmented_production_set
{
    a_tag tag,tag0;
    pds *left;
    right *riht;
    term *stage;
    struct augmented_production_set *next;
}a_pdtn;
typedef struct chain_for_trans_table
{
    a_pdtn *item;
    struct chain_for_trans_table *GOTO;
    struct chain_for_trans_table *next;
}t_table;
typedef struct chain_for_trans_tables
{
    t_table *val;
    char *via;
    struct chain_for_trans_tables *next;
}t_list;
/** Global Variables Section **/
char* symbol[STACK];
char **psb;
void* states[STACK];
void **pst;
term *TERMINAL;
a_pdtn *aP;
a_tag tc;//transition closure tag.
t_list *DFAL;
/** Functions Section **/
/* Debug Functions */
void showTERMINAL()
{
    term *t=TERMINAL;
    printf("TERMINALS:\n");
    while(t)
    {
        printf("%s ",t->val);
        t=t->next;
    }
    printf("\n");
}
void showAproduction()
{
    a_pdtn *a=aP;
    while(a)
    {
        term *t=a->riht->val;
        if(a->tag==EXIST) printf("E::");
        printf("%s->",a->left->left);
        while(t)
        {
            if(t==a->stage) printf(".");
            printf("%s",t->val);
            t=t->next;
        }
        if(t==a->stage) printf(".");
        printf("\n");
        a=a->next;
    }
}
void showClosure(t_table *tt)
{
    while(tt)
    {
        term *t=tt->item->riht->val;
        printf("%s->",tt->item->left->left);
        while(t)
        {
            if(t==tt->item->stage) printf(".");
            printf("%s",t->val);
            t=t->next;
        }
        if(t==tt->item->stage) printf(".");
        printf("  %X\n",tt->GOTO);
        tt=tt->next;
    }
    printf("+++++++++++++\n");
}
/* utility functions */
void getTerminal()
{//Checked.
    TERMINAL=NULL;
    pds *p=P;
    right *r;
    term *t;
    while(p)
    {
        r=p->val;
        while(r)
        {
            t=r->val;
            while(t)
            {
                if(!IsNon(t->val))
                {//attempt adding nonterminal
                    term *tm=TERMINAL;
                    while(tm)
                    {
                        if(!strcmp(tm->val,t->val)) break;
                        tm=tm->next;
                    }
                    if(!tm)
                    {
                        tm=malloc(sizeof(term));
                        strcpy(tm->val,t->val);
                        tm->next=TERMINAL;
                        TERMINAL=tm;
                    }
                }
                t=t->next;
            }
            r=r->next;
        }
        p=p->next;
    }
}
void initAugProduction()
{//before getting the proper production.
    pds *p=P;
    aP=NULL;
    a_pdtn *temp;
    while(p)
    {
        right *r=p->val;
        while(r)
        {
            term *t=r->val;
            temp=malloc(sizeof(a_pdtn));
            temp->left=p;
            temp->riht=r;
            temp->stage=t;
            temp->next=aP;
            aP=temp;
            while(t)
            {//add each item to augmented production set.
                t=t->next;
                temp=malloc(sizeof(a_pdtn));
                temp->left=p;
                temp->riht=r;
                temp->stage=t;
                temp->next=aP;
                aP=temp;
            }
            r=r->next;
        }
        p=p->next;
    }
}
void setTagEmpty()
{
    a_pdtn *a=aP;
    while(a)
    {
        a->tag=EMPTY;
        a=a->next;
    }
}
void setTag0Empty()
{
    a_pdtn *a=aP;
    while(a)
    {
        a->tag0=EMPTY;
        a=a->next;
    }
}
a_pdtn* findAP(pds *p,term *t)
{
    a_pdtn *a=aP;
    while(a)
    {
        if(a->left==p && a->stage==t) return a;
        a=a->next;
    }
    return NULL;
}
void addToClosure(a_pdtn *a,t_table **t)
{
    t_table *tt=malloc(sizeof(t_table));
    tt->GOTO=NULL;
    tt->item=a;
    tt->next=*t;
    *t=tt;
}
void spawnCLOSURE(t_table **t)
{
    tc=NOP;
    t_table *tt=*t,*temp;
    pds *p;
    a_pdtn *a;
    setTagEmpty();
    while(tt)
    {//set initialized elements' tag
        tt->item->tag=EXIST;
        tt=tt->next;
    }
    //getting ready for add element into this closure.
    for(;;)
    {
        //scan each element.
        tt=*t;//printf("exist\n");
        while(tt)
        {//scan the production one time.
            //get the trans item.
            if(tt->item->stage)
            {
                p=IsNonP(tt->item->stage->val);
                if(p)
                {
                    a=aP;
                    while(a)
                    {//scan the augmented production set.
                        if(a->left==p && a->riht->val==a->stage && a->tag==EMPTY)
                        {//add new element to the closure.
                            a->tag=EXIST;
                            temp=malloc(sizeof(t_table));
                            temp->item=a;
                            temp->GOTO=NULL;
                            temp->next=*t;
                            *t=temp;
                            tc=MODIFIED;
                        }
                        a=a->next;
                    }
                }
            }
            tt=tt->next;
        }
        //if nothing added closure gotten.
        if(tc==MODIFIED)
        {
            tc=NOP;
            continue;
        }
        else break;
    }
}
void freeList(t_list *t)
{
    t_table *tt;
    while(t->val)
    {
        tt=t->val;
        t->val=t->val->next;
        free(tt);
    }
    free(t);
}
char tableCmp(t_table *a,t_table *b)
{//1 represents equal.
    a_pdtn *ap=aP;
    setTagEmpty();
    while(a)
    {
        a->item->tag=EXIST;
        a=a->next;
    }
    while(b)
    {
        if(b->item->tag==EMPTY) return 0;
        b->item->tag=EMPTY;
        b=b->next;
    }
    while(ap)
    {
        if(ap->tag==EXIST) return 0;
        ap=ap->next;
    }
    return 1;//equal.
}
t_table* ListCmp(t_list *t)
{//using tag, cause no collusion with "getCLOSURE()"
    //setTagEmpty();
    //if it's equal, return the equivalent closure's address.
    t_list *lt=DFAL;
    while(lt)
    {
        //if some closures equal, return equal.
        if(tableCmp(t->val,lt->val)) return lt->val;
        lt=lt->next;
    }
    return NULL;//not equal.
}
void assignGOTO(t_list *l,t_table *gto)
{
    t_table *tt=l->val;
    while(tt)
    {
        if(tt->item->tag0==EX_TB)
        {
            tt->item->tag0=EXIST;
            //printf("assigned %x\n",gto);
            tt->GOTO=gto;
        }
        tt=tt->next;
    }
}
/* Our Lead Functions */
void init_SLR()
{
    //1.set the first closure.
    a_pdtn *a;
    t_list *scan,*newp;
    initAugProduction();
    showAproduction();
    a=aP;
    //showAproduction();
    DFAL=malloc(sizeof(t_list));
    DFAL->next=NULL;
    DFAL->via=NULL;
    DFAL->val=malloc(sizeof(t_table));
    //printf("%X\n",a);
    while(a->next) a=a->next;
    DFAL->val->item=a;
    DFAL->val->GOTO=NULL;
    DFAL->val->next=NULL;
    spawnCLOSURE(&(DFAL->val));
    scan=DFAL;
    newp=DFAL;

    while(scan)
    {//make new closures here.
        //paddr(scan);
        showClosure(scan->val);
        printf("CURR\n");
        t_table *t=scan->val;//paddr(t);paddr(DFAL->val);
        //t_table *tgoto;
        setTag0Empty();
        //scan the whole closure if there's a new goto.
        while(t)
        {//pointer t's traversal
            if(t->item->tag0==EMPTY && t->item->stage!=NULL)
            {
                //if the current item is new,
                //allocate a new closure with current goto term.
                t_list *ttl=malloc(sizeof(t_list));
                t_table *ttl0;
                t_table *ttt=t->next;
                ttl->val=NULL;
                addToClosure(findAP(t->item->left,t->item->stage->next),&ttl->val);
                t->item->tag0=EX_TB;
                while(ttt)
                {
                    if(ttt->item->tag0==EMPTY && !strcmp(t->item->stage->val,ttt->item->stage->val))
                    {//finding the same GOTO function.
                        addToClosure(findAP(ttt->item->left,ttt->item->stage->next),&ttl->val);
                        ttt->item->tag0=EX_TB;
                    }
                    ttt=ttt->next;
                }
                //spawning CLOSURE.
                spawnCLOSURE(&ttl->val);
                showClosure(ttl->val);
                //checking the spawned CLOSURE.
                ttl0=ListCmp(ttl);
                //paddr(ttl0);
                if(ttl0==NULL)
                {//if it's unique.
                    //add the closure to tail.
                    ttl0=ttl->val;
                    ttl->next=NULL;
                    newp->next=ttl;
                    ttl->via=t->item->stage->val;
                    newp=newp->next;
                }
                else
                {
                    freeList(ttl);
                }
                //assign the goto to proper item
                assignGOTO(scan,ttl0);
            }
            t=t->next;
        }
        //paddr(scan->val);
        scan=scan->next;
    }
    //the first closure is done.
}
void SLR()
{
    ;
}
/* Main Functions */
t_table *test;
int main(void)
{
    Pinit("SLR.formal");
    getTerminal();
    showTERMINAL();
    init_SLR();
    //showAproduction();
    //OpenLex("stmt.out");
    Pclose();
    return 0;
}
