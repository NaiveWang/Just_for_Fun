#ifndef SYMBOL_H
#define SYMBOL_H
/**
  * this file contains the fucking
  *
  *
  **/
/* type define & macro */
#define LENGTH_ID 32
#define TYP_CHAR 'C'
#define TYP_INT 'I'
#define TYP_REAL 'R'
#define TYP_STRING 'S'
typedef struct identifierList
{
    char type;
    char name[LENGTH_ID];
}id
typedef struct constantList
{
    char type;
    void *content;
}constant;
/* function section */
#endif
