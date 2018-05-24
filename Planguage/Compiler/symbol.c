#include "symbol.h"
void symbolInit()
{
  //set the cursor to zero
  identifiersCursor=0;
  constantsCursor=0;
}
id* addID(char* s)
{
  //compare the identifier name first
  static int a0;
  for(a0=0;a0<identifiersCursor;a0++)
  {
    //check each list member with target string
    if(!strcmp(s,identifiers[a0].name))
    {
      //same name
      //return the address
      return identifiers+a0;
    }
    //nothing matched
    //check if stack oveflow
    if(a0==SIZE_IDLIST)
    {
      return NULL;
    }
    //all checked, copy the string
    strcpy(identifiers[a0].name,s);
    identifiers[a0].type = TYP_META;
    identifiersCursor++;
    return identifiers+a0-1;
  }
}
constant* addConst(int typ,char* str)
{
  //switch it!
  //check if the list is overflow
  static long i;
  static double r;
  static char c;
  //static char *s;
  static int a0;
  if(constantsCursor==SIZE_CONSTLIST)
    return NULL;
  //parse the item
  //correct ----------assign the type
  //constants[constantsCursor]
  switch(typ)
  {
    case CONSTANT_REAL:
      //
      sscanf(str,"%le",&r);
      for(a0=0;a0<constantsCursor;a0++)
      {
        //check
        if(constants[a0].type==TYP_REAL &&
          *(double*)constants[a0].content==r)
        {
          //match
          return constants+a0;
        }
      }
      //rookie
      constants[constantsCursor].type = TYP_REAL;
      constants[constantsCursor].content = malloc(sizeof(double));
      *(double*)constants[constantsCursor].content = r;
      constantsCursor++;
      return constants+constantsCursor-1;
      break;
    case CONSTANT_INT:
      //
      sscanf(str,"%ld",&i);
      for(a0=0;a0<constantsCursor;a0++)
      {
        //check
        if(constants[a0].type==TYP_INT &&
          *(long*)constants[a0].content==r)
        {
          //match
          return constants+a0;
        }
      }
      //rookie
      constants[constantsCursor].type = TYP_INT;
      constants[constantsCursor].content = malloc(sizeof(long));
      *(long*)constants[constantsCursor].content = i;
      constantsCursor++;
      return constants+constantsCursor-1;
      break;

      case CONSTANT_HEX:
        //
        sscanf(str,"%lx",&i);
        for(a0=0;a0<constantsCursor;a0++)
        {
          //check
          if(constants[a0].type==TYP_INT &&
            *(long*)constants[a0].content==r)
          {
            //match
            return constants+a0;
          }
        }
        //rookie
        constants[constantsCursor].type = TYP_INT;
        constants[constantsCursor].content = malloc(sizeof(long));
        *(long*)constants[constantsCursor].content = i;
        constantsCursor++;
        return constants+constantsCursor-1;
        break;

      case CONSTANT_OCT:
          //
          sscanf(str,"%lo",&i);
          for(a0=0;a0<constantsCursor;a0++)
          {
            //check
            if(constants[a0].type==TYP_INT &&
              *(long*)constants[a0].content==r)
            {
              //match
              return constants+a0;
            }
          }
          //rookie
          constants[constantsCursor].type = TYP_INT;
          constants[constantsCursor].content = malloc(sizeof(long));
          *(long*)constants[constantsCursor].content = i;
          constantsCursor++;
          return constants+constantsCursor-1;
          break;

    case TYP_CHAR:
      //
      sscanf(str,"%c",&c);
      for(a0=0;a0<constantsCursor;a0++)
      {
        //check
        if(constants[a0].type==TYP_CHAR &&
          *(char*)constants[a0].content==c)
        {
          //match
          return constants+a0;
        }
      }
      //rookie
      constants[constantsCursor].type = TYP_CHAR;
      constants[constantsCursor].content = malloc(sizeof(char));
      *(char*)constants[constantsCursor].content = c;
      constantsCursor++;
      return constants+constantsCursor-1;
      break;
    case CONSTANT_STRING:
      //copy it directly
      constants[constantsCursor].content = malloc(strlen(str)+1);
      strcpy((char*)constants[constantsCursor].content,str);
      constants[constantsCursor].type = TYP_STRING;
      constantsCursor++;
      return constants+constantsCursor-1;
      break;
    default:
      return NULL;
  }
}
