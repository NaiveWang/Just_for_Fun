#include "PCompiler.h"
void openFile(char *s)
{
  //tokenlizer initializer
  //readfile
  input=fopen(s,"r");
  if(input==NULL)
  {
    errno=1;
  }
  else
  {
    //initialize the cursor and sole args
    tokenlizerStatus=TOKENLIZER_STATUS_CONTENT;
    instantListCursor=0;
    symbolTableCursor=0;
    lineBufferCursor=0;
    tokenBufferCursor=0;
    lineCursor=0;
    errno=0;
    readLine();
  }
}
char readLine()
{
  //read line into the line buffer
  //increase the line cursor
  if(fgets(lineBuffer,LENGTH_OF_LINE_BUFFER,input))
  {
    //success
    lineBufferCursor=0;
    lineCursor++;
    return -1;
  }
  else
  {
    fclose(input);
    return 0;
  }
}
void skipWhitespace()
{
  while(lineBuffer[lineBufferCursor]==' ' || lineBuffer[lineBufferCursor]=='\t') lineBufferCursor++;
}
symbol* addIdentifier()
{
  static int a0;
  //check the identifier in buffer
    //check if it has been declared
  for(a0=0;a0<symbolTableCursor;a0++)
  {
    //check
    if(strcmp(symbolTable[a0].name,tokenBuffer))
    {
      //not match, continue
      continue;
    }
    else
    {
      //match, return the current symbol addr
      return symbolTable+a0;
    }
  }
  //new identifier
  //check if it was valid
  //check first character
  if(
    (*tokenBuffer <= 'Z' && *tokenBuffer >= 'A')||
    (*tokenBuffer <= 'z' && *tokenBuffer >= 'a')||
    (*tokenBuffer == '_'))
  {
    //match, next step
    for(a0=1;tokenBuffer[a0];a0++)
    {
      //check each element
      if(
        (*tokenBuffer <= 'Z' && *tokenBuffer >= 'A')||
        (*tokenBuffer <= 'z' && *tokenBuffer >= 'a')||
        (*tokenBuffer <= '9' && *tokenBuffer >= '0')||
        (*tokenBuffer == '_'))
        continue;//matched
      else
        break;//not match
    }
  }
  else
  {
    //not match
    return NULL;
  }
  if(tokenBuffer[a0])
  {
    //not match
    return NULL;
  }
  else
  {
    //match, add element
    strcpy(symbolTable[symbolTableCursor].name,tokenBuffer);
    //return address
    symbolTableCursor++;
    return symbolTable+symbolTableCursor-1;
  }
}
instant* addInstant()
{
  static int a0,a1;
  static char bs[LENGTH_OF_TOKEN_BUFFER];
  static char bc;
  static long bi;
  static double br;
  //check type:
  switch(*tokenBuffer)
  {
    case '\'':
      //character
      if(sscanf(tokenBuffer+1,"%c",&bc)==1)
      {
        //success, char
        for(a0=0;a0<instantListCursor;a0++)
        {
          if(instantList[a0].type==TOKEN_INSTANT_CHAR &&
            *(char*)instantList[a0].content==bc)
            return instantList+a0;
        }
        //add new element
        instantList[instantListCursor].type==TOKEN_INSTANT_CHAR;
        instantList[instantListCursor].content=malloc(sizeof(char));
        *(char*)instantList[instantListCursor].content=bc;
        instantListCursor++;
        return instantList+instantListCursor-1;
      }
      else
      {
        //failure
        errno=2;
        return NULL;
      }
      break;
    case '"':
      //string
      //must be success
      strcpy(bs,tokenBuffer+1);
      //add string to list anyway
      instantList[instantListCursor].type = TOKEN_INSTANT_STRING;
      instantList[instantListCursor].content = malloc(strlen(tokenBuffer));
      strcpy((char*)instantList[instantListCursor].content,tokenBuffer+1);
      instantListCursor++;
      return instantList+instantListCursor-1;
      break;
    default:
      //number
      //check if it is real number
      for(a0=0;tokenBuffer[a0];a0++)
      {
        if(tokenBuffer[a0]=='.' || tokenBuffer[a0]|0x20 =='e') break;
      }
      if(tokenBuffer[a0])
      {
        //integer
        if(*tokenBuffer=='0')
        {
          //special number
          if(tokenBuffer[1]|0x20 =='x')
          {
            //hex, scan & check
            if(sscanf(tokenBuffer,"%lx",&bi)==1)
            {
              //success, int8
              for(a0=0;a0<instantListCursor;a0++)
              {
                if(instantList[a0].type==TOKEN_INSTANT_INT &&
                  *(long*)instantList[a0].content==bi)
                  return instantList+a0;
              }
              //add new element
              instantList[instantListCursor].type==TOKEN_INSTANT_INT;
              instantList[instantListCursor].content=malloc(sizeof(long));
              *(long*)instantList[instantListCursor].content=bi;
              instantListCursor++;
              return instantList+instantListCursor-1;
            }
            else
            {
              //failure
              errno=2;
              return NULL;
            }
          }
          else
          {
            //oct, scan & check
            if(sscanf(tokenBuffer,"%lo",&bi)==1)
            {
              //success , int8
              for(a0=0;a0<instantListCursor;a0++)
              {
                if(instantList[a0].type==TOKEN_INSTANT_INT &&
                  *(long*)instantList[a0].content==bi)
                  return instantList+a0;
              }
              //add new element
              instantList[instantListCursor].type==TOKEN_INSTANT_INT;
              instantList[instantListCursor].content=malloc(sizeof(long));
              *(long*)instantList[instantListCursor].content=bi;
              instantListCursor++;
              return instantList+instantListCursor-1;
            }
            else
            {
              //failure
              errno=2;
              return NULL;
            }
          }
        }
        else
        {
          //ordinary int
          if(sscanf(tokenBuffer,"%ld",&bi)==1)
          {
            //success , int8
            for(a0=0;a0<instantListCursor;a0++)
            {
              if(instantList[a0].type==TOKEN_INSTANT_INT &&
                *(long*)instantList[a0].content==bi)
                return instantList+a0;
            }
            //add new element
            instantList[instantListCursor].type==TOKEN_INSTANT_INT;
            instantList[instantListCursor].content=malloc(sizeof(long));
            *(long*)instantList[instantListCursor].content=bi;
            instantListCursor++;
            return instantList+instantListCursor-1;
          }
          else
          {
            //failure
            errno=2;
            return NULL;
          }
        }
      }
      else
      {
        //float
        if(sscanf(tokenBuffer,"%le",&br)==1)
        {
          //success, real
          for(a0=0;a0<instantListCursor;a0++)
          {
            if(instantList[a0].type==TOKEN_INSTANT_REAL &&
              *(double*)instantList[a0].content==br)
              return instantList+a0;
          }
          //add new element
          instantList[instantListCursor].type==TOKEN_INSTANT_REAL;
          instantList[instantListCursor].content=malloc(sizeof(double));
          *(double*)instantList[instantListCursor].content=br;
          instantListCursor++;
          return instantList+instantListCursor-1;
        }
        else
        {
          //failure
          errno=2;
          return NULL;
        }
      }
  }
}
token* getToken()
{
  //match next key word
  //skip whitespace of a line
  for(;;)
  {
    skipWhitespace();
    //check if is the end of the line or line comment
    while(!strncmp(lineBuffer+lineBufferCursor,COMMENT_SINGLELINE,strlen(COMMENT_SINGLELINE)) ||
        lineBuffer[lineBufferCursor]=='\n')
    {
      //skip line
      readLine();
      skipWhitespace();
    }
    //check if is the start comment
    if(!strncmp(lineBuffer+lineBufferCursor,COMMENT_START,strlen(COMMENT_START)))
    {
      //meet the comment start,
      lineBufferCursor+=strlen(COMMENT_START);
      //find the end of comment
      while(!strncmp(lineBuffer+lineBufferCursor,COMMENT_END,strlen(COMMENT_END)))
      {
        if(lineBuffer[lineBufferCursor]=='\n')
          readLine();
        else
          lineBufferCursor++;
      }
      lineBufferCursor+=strlen(COMMENT_END);
    }
    //loop, until met the read item
  }
}
void errorNotifier()
{
  //print error info via the error number
  printf("Error No.%d:",errno);
  switch(errno)
  {
    case 1 : printf("cannot open file");break;
    case 2 : printf("invalid token lexis at line %d",lineCursor);break;
    case 3 : printf("enviroment error : stackoverflow");break;
    default:printf("undefined errno");
  }
  printf(".\n");
}
