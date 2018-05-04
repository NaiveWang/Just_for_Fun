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
                    //printf("##%s\n",inputBuffer);
                    if(!strncmp(inputBuffer,I_PROCESSOR,9)) pe->processorTemplateNum++;
                    break;
                case'm':
                    fscanf(input,"%4s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_MUTEX,5)) pe->mutexNum++;
                    break;
                case'i':
                    fscanf(input,"%7s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_INSTANCE,8)) pe->processorInstanceNUM++;
                    break;
                case'c':
                    fscanf(input,"%9s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_CONNECTION,10)) pe->connectionMappingNum++;
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
    if(inputBuffer[inputBufferPointer]=='\n')
    {
      parseLine++;
      continue;//skip empty lines
    }
    //convert \n to NULL
    a0=inputBufferPointer;
    while(inputBuffer[a0]^'\n') a0++;
    inputBuffer[a0]=0;
    parseLine++;
    return 0;
  }
  return -1;
}
char* nameSeek(char* s, int n)
{
  return s + n*NAME_BUFFER_SIZE;
}
int strCopy(char *s,char *d)
{
  static int a0;
  a0=0;
  while((*s != '\n')&&(*s != ' ')&&(*s != '\t'))
  {
    //printf("%d/",a0);
    *d = *s;
    d++;
    s++;
    a0++;
  }
  *d=0;
  return a0;
}
int ifIdentifierOverdefined(char *List,int n)
{//search if exist one match, return -1;
  //strCopy(target,identifierBuffer);
  while(n--)
  {
    if(!strcmp(identifierBuffer,nameSeek(List,n))) return -1;
  }
  return 0;
}
int matchIdentifier(char *List,char *target,int n)
{
  strCopy(target,identifierBuffer);
  while(n--)
  {
    if(!strcmp(identifierBuffer,nameSeek(List,n))) return n;
  }
  errno=3;
  return -1;
}
int addIdentifier(char* t,char *List,int *n)
{

  strcpy(nameSeek(List,*n),t);
  (*n)++;
}
void skipWhitespace()
{
  while(inputBuffer[inputBufferPointer]==' '||inputBuffer[inputBufferPointer]=='\t') inputBufferPointer++;
}
void parseStart()
{
  if(inputBuffer[inputBufferPointer]==IDENTIFIER)
  {//identifier get successful
    inputBufferPointer++;
    if(!strncmp(inputBuffer+inputBufferPointer,I_PROCESSOR,9))
    {//into processor
      inputBufferPointer+=9;
      parsingStatus=PS_IN_PROCESSOR;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_MUTEX,5))
    {
      inputBufferPointer+=5;
      parsingStatus=PS_MUTEX_SECTION;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_INSTANCE,8))
    {
      inputBufferPointer+=8;
      parsingStatus=PS_INSTANCE_SECTION;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_CONNECTION,10))
    {
      inputBufferPointer+=10;
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
  //skip whitespace
  static int a0;
  skipWhitespace();
  //printf("##%s\n",inputBuffer+inputBufferPointer);
  //check name
  a0=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //printf("#%dFetching Mutex :%s:",a0,identifierBuffer);
  if(ifIdentifierOverdefined(mNameList,mListNum)
  ||ifIdentifierOverdefined(iNameList,iListNum))
  {
    errno=4;
    return;
  }
  //addname & skip name
  //printf("$%s$\n",identifierBuffer);
  addIdentifier(identifierBuffer,mNameList,&mListNum);
  //printf("&%d\n",mListNum);
  //skip whitespace
  inputBufferPointer+=a0;
  skipWhitespace();
  //get size
  //printf("%s",inputBuffer+inputBufferPointer);
  sscanf(inputBuffer+inputBufferPointer,"%d",&a0);
  //printf("$%d$\n",a0);
  //assign the file structure(record)
  pe->mutexSizeList[mListNum-1]=a0;
  parsingStatus=PS_START;
  readLine();
}
void parseConnection()
{
  static int a0;
  //find the source name
  skipWhitespace();
  //check if it exist, error return
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  a0=matchIdentifier(iNameList,identifierBuffer,iListNum);
  if(a0==-1)
  {//error return
    errno=5;
    return;
  }
  pe->connectionMapping[cListNum].nodeSNo=a0;
  //get the port number
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  sscanf(identifierBuffer,"%d",&a0);
  pe->connectionMapping[cListNum].nodeSPort=a0;
  //get the destination
  skipWhitespace();
  strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  a0=matchIdentifier(iNameList,identifierBuffer,iListNum);
  if(a0==-1)
  {
    a0=matchIdentifier(mNameList,identifierBuffer,mListNum);
    if(a0==-1)
    {
      errno=6;
      return;
    }
    pe->connectionMapping[cListNum].nodeDType=TYP_MUTEX;
  }
  else pe->connectionMapping[cListNum].nodeDType=TYP_INST;
  pe->connectionMapping[cListNum].nodeDNo=a0;
  //list pointer+1;
  cListNum++;
  //read next line
  readLine();
  //modify the status to start
  parsingStatus=PS_START;
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
    case 4:printf("identifier conflict, name override");break;
    case 5:printf("undefined instance name");break;
    case 6:printf("undefined destination entity name");break;
    case -1:return;//file end
  }
  printf(".\n");
}
void _debugShowNameList(char *list,int n)
{
  printf("$DEBUG$%d\n",n);
  while(n--)
  {
    printf("$DEBUG$%s\n",list + n * NAME_BUFFER_SIZE);
  }
}
