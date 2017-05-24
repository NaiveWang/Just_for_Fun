#include <stdio.h>
#include "production.h"
#include "scan_toolkit.h"
/**
 * SLR parser.
 * we can also call it "Simple LR parser",
 */
#define STACK 4096

typedef enum type_of_element
{
    REDUCE=0,SHIFT,ACC
}e_type;
/**
 * About the parsing table:
 * I'm using addresses to represent states,
 * CLOSURE's addresses, cause they'r unique.
 */
/** Type Statement Section **/
typedef struct items_of_closure
{
    char *left;
    char *right;
    char *stage;
    struct items_of_closure *next;
}items;
typedef struct list_of_items
{
    items *val;
    struct list_of_items *next;
}iteml;
typedef struct element_of_parsing_table
{
    e_type etp;
    void *c_state;//current state
    void *data;
    /* it depends on what "etp" is.
     * SHIFT: next action state.
     * REDUCE: production's address.
     * ACC: parse success, terminate it!
     */
    struct element_of_parsing_table *next;
}element;
typedef struct head_of_parsing_table
{
    char *val;
    element *elem;
    struct head_of_parsing_table *next;
}ptable;
/** Global Variables Section **/
char* symbol[STACK];
char **psb;
void* states[STACK];
void **pst;
ptable *ACTION;
ptable *GOTO;
term *TERMINAL;
/** Function Section **/
/* utility functions */
void getTerminal()
{
    ;
}

/* Our Lead Functions */
void init_SLR()
{
    psb=symbol;
    pst=states+1;
    //*states=ADDRESS_OF_INITIAL_STATE
    for(;;)
    {
        ///Í¨ÉÌ¿íÒÂ¡£
    }
}
void SLR()
{
    ;
}
/* Main Function */
int main(void)
{
    return 0;
}
