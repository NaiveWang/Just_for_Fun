#include "PAssembler.h"
void countIdentifier()
{
    char bufferC=0;
    while((bufferC=(char)fgetc(input))!=EOF)
    {
        //fscanf(input,"%c",&bufferC);
        //if(bufferC=='\n') fscanf(input,"\n");
        //if(bufferC==EOF) break;
        //bufferC=(char)fgetc(input);
        //printf("%c",bufferC);
        if(bufferC==IDENTIFIER)
        {
            inputBuffer[0]=(char)fgetc(input);
            //printf("#%c\n",bufferC);
            switch(*inputBuffer)
            {
                case'p':
                    fscanf(input,"%8s",inputBuffer+1);
                    printf("##%s\n",inputBuffer);
                    if(!strncmp(inputBuffer,I_PROCESSOR,9)) pe.processorTemplateNum++;
                    break;
                case'm':
                    fscanf(input,"%4s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_MUTEX,5)) pe.mutexNum++;
                    break;
                case'i':
                    fscanf(input,"%7s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_INSTANCE,8)) pe.processorInstanceNUM++;
                    break;
                case'c':
                    fscanf(input,"%9s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_CONNECTION,10)) pe.connectionMappingNum++;
                    break;
            }
        }
    }
}
int readLine()
{
  static int a0;
  while(fgets(inputBuffer,NAME_BUFFER_SIZE,input))
  {
    inputBufferPointer=0;
    while(inputBuffer[inputBufferPointer]==' '||inputBuffer[inputBufferPointer]=='\t') inputBufferPointer++;//skip whitespaces in one line
    if(inputBuffer[inputBufferPointer]=='\n') continue;//skip empty lines
    //convert \n to NULL
    a0=inputBufferPointer;
    while(inputBuffer[a0]^'\n') a0++;
    inputBuffer[a0]=0;
    return 0;
  }
  return -1;
}
char* nameSeek(char* s, int n)
{
  return s + n*NAME_BUFFER_SIZE + 1;
}
void strCopy(char *s,char *d)
{
  while(*s != '\n'||' '||'\t')
  {
    *d = *s;
    d++;
    s++;
  }
  *d=0;
}
int ifIdentifierOverdefined(char *List,char *target,int n)
{//search if exist one match, return -1;
  strCopy(target,identifierBuffer);
  while(n--)
  {
    if(strcmp(identifierBuffer,nameSeek(List,n))) return -1;
  }
  return 0;
}
int matchIdentifier(char *List,char *target,int n)
{
  strCopy(target,identifierBuffer);
  while(n--)
  {
    if(strcmp(identifierBuffer,nameSeek(List,n))) return n;
  }
  errno=3;
  return -1;
}
int addIdentifier(char* t,char *List,int *n)
{
  *n++;
  strCopy(t,nameSeek(List,*n));
}
char* skipWhitespace(char* s)
{
  while(*s==' '||'\t') s++;
  return s;
}
void parseStart()
{
  if(inputBuffer[0]==IDENTIFIER)
  {//identifier get successful
    if(!strncmp(inputBuffer,I_PROCESSOR,9))
    {//into processor
      parsingStatus=PS_MUTEX_SECTION;
    }
    else if(!strncmp(inputBuffer,I_MUTEX,5))
    {
      parsingStatus=PS_MUTEX_SECTION;
    }
    else if(!strncmp(inputBuffer,I_INSTANCE,8))
    {
      parsingStatus=PS_INSTANCE_SECTION;
    }
    else if(!strncmp(inputBuffer,I_CONNECTION,10))
    {
      parsingStatus=PS_CONNECTIONS;
    }
    else errno=2;
  }
  else errno=1;
}
void parseProcessor()
{
  ;
}
void parseProcessorCode()
{
  ;
}
void parseProcessorData()
{
  ;
}
void parseMutex()
{//find the nearest
  ;
}
void parseConnection()
{
  ;
}
void parseInstance()
{
  ;
}
void parseInstanceData()
{
  ;
}
void errorHandler()
{
  printf("Error at line %d : ",parseLine);
  switch(errno)
  {
    case 0:printf("No error found");break;
    case 1:printf("expecting a dot(.) identifier");break;
    case 2:printf("Typo or bad announcement");break;
    case 3:printf("identifier undefined");break;
  }
  printf(".\n");
}
