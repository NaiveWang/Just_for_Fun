/***
 * This head file is devote to interpret the production file
 * and to pack it's function set to a module,
 * which can make things easier.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_LEN 64//length of nonterminal term
#define BUFF 1024
#define P(X) printf("DEBUG PASS:%c\n",X)
typedef struct term_chain_list
{
    char val[N_LEN];
    struct term_chain_list *next;
}term;
typedef struct production_rigntside_chain_list
{
    term *val;
    struct production_rigntside_chain_list *next;
}right;
typedef struct productions_chain_list
{
    char left[N_LEN];
    right *val;
    struct productions_chain_list *next;
}pds;
typedef struct symbol_table_chain_list
{
    char val[N_LEN];
    int attr;
    struct symbol_table_chain_list *next;
}s_table;
/* Global Arguments Declaring Section**/
char buffer_file[BUFF],*bf_ofst;
char buffer_term[N_LEN];
pds *P;
s_table *SBT;
void getTerm()
{
    static char *bt_ofst;
    while(*bf_ofst!='<') bf_ofst++;
    bf_ofst++;
    bt_ofst = buffer_term;
    while(*bf_ofst!='>')
    {
        *bt_ofst = *bf_ofst;
        bt_ofst++;
        bf_ofst++;
    }
    bf_ofst++;
    *bt_ofst = 0;
}

void Pinit(char *fn)
{
    FILE *fp = fopen(fn,"r");
    pds *o_P;
    o_P = malloc(sizeof(pds));
    P=o_P;
    //o_P->next=NULL;
    while(fgets(buffer_file,BUFF,fp))
    {
        right *o_r;
        bf_ofst = buffer_file;
        getTerm();
        //printf("%s\n",buffer_term);
        strcpy(o_P->left,buffer_term);
        o_P->val = malloc(sizeof(right));
        o_r = o_P->val;
        while(*bf_ofst!=10)
        {
            term *o_t;
            o_r->val=malloc(sizeof(term));
            o_t = o_r->val;
            o_r->next = NULL;
            for(;;)
            {
                getTerm();
                //printf("%s\n",buffer_term);
                strcpy(o_t->val,buffer_term);
                o_t->next=NULL;
                if(*bf_ofst=='|' || *bf_ofst==10) break;

                o_t->next = malloc(sizeof(term));
                o_t = o_t->next;
            }
            if(*bf_ofst==10) break;//P(*bf_ofst);
            o_r->next = malloc(sizeof(right));
            o_r = o_r->next;
        }
        //printf("%s\n",buffer_term);
        o_P->next = malloc(sizeof(pds));
        o_P = o_P->next;
        o_P->next = NULL;
    }
    o_P=P;
    while(o_P)
    {
        if(o_P->next->next==NULL)
        {
            free(o_P->next);
            o_P->next=NULL;
            break;
        }
        o_P = o_P->next;
    }
    fclose(fp);
    fp = fopen("reserved_symbol.txt","r");
    {
        s_table *sbt = malloc(sizeof(s_table));
        SBT = sbt;
        int attr;
        while(fscanf(fp,"%d %s\n",&attr,buffer_term)!=EOF)
        {
            sbt->next = malloc(sizeof(s_table));
            sbt = sbt->next;
            sbt->attr=attr;
            strcpy(sbt->val,buffer_term);
            //printf("%d %s\n",sbt->attr,sbt->val);
        }
        sbt->next=NULL;
        sbt=SBT;
        SBT=SBT->next;
        free(sbt);
    }
    fclose(fp);
}
right* IsNon(char *s)
{
    pds *p=P;
    while(p)
    {
        if(strcmp(s,p->left))
        {
            p=p->next;
            continue;
        }
        return p->val;
    }
    return 0;
}
void addID(char *s)
{
    s_table *p=malloc(sizeof(s_table));
    strcpy(p->val,s);
    p->attr=0;
    p->next = SBT;
    SBT = p;
}
