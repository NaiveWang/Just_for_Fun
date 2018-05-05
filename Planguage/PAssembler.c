#include "PAssembler.h"
void countIdentifier()
{
    while(!readLine())
    {

      if(*(inputBuffer+inputBufferPointer) == IDENTIFIER)
      {
        inputBufferPointer++;
        //printf("%s\n",inputBuffer+inputBufferPointer);
        //printf("%ld\n",strlen(I_PROCESSOR));
        if(!strncmp(inputBuffer+inputBufferPointer,I_PROCESSOR,strlen(I_PROCESSOR))) pe->processorTemplateNum++;
        else if(!strncmp(inputBuffer+inputBufferPointer,I_MUTEX,strlen(I_MUTEX))) pe->mutexNum++;
        else if(!strncmp(inputBuffer+inputBufferPointer,I_INSTANCE,strlen(I_INSTANCE))) pe->processorInstanceNUM++;
        else if(!strncmp(inputBuffer+inputBufferPointer,I_CONNECTION,strlen(I_CONNECTION))) pe->connectionMappingNum++;
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
    if(inputBuffer[inputBufferPointer]=='\n'||inputBuffer[inputBufferPointer]==';')
    {
      parseLine++;
      continue;//skip empty lines
    }
    //convert \n to NULL
    a0=inputBufferPointer;
    while(inputBuffer[a0]^'\n'&&inputBuffer[a0]^';') a0++;
    inputBuffer[a0]=0;
    parseLine++;
    printf("#%s#\n",inputBuffer+inputBufferPointer);
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
  while((*s != '\n')&&(*s != ' ')&&(*s != '\t')&&(*s != ';')&&(*s != ','))
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
void skipIdentifier()
{
  while(inputBuffer[inputBufferPointer]!=' '&&inputBuffer[inputBufferPointer]!='\t') inputBufferPointer++;
}
void parseStart()
{
  if(inputBuffer[inputBufferPointer]==IDENTIFIER)
  {//identifier get successful
    inputBufferPointer++;
    if(!strncmp(inputBuffer+inputBufferPointer,I_PROCESSOR,strlen(I_PROCESSOR)))
    {//into processor
      inputBufferPointer+=strlen(I_PROCESSOR);
      parsingStatus=PS_IN_PROCESSOR;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_MUTEX,strlen(I_MUTEX)))
    {
      inputBufferPointer+=strlen(I_MUTEX);
      parsingStatus=PS_MUTEX_SECTION;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_INSTANCE,strlen(I_INSTANCE)))
    {
      inputBufferPointer+=strlen(I_INSTANCE);
      parsingStatus=PS_INSTANCE_SECTION;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_CONNECTION,strlen(I_CONNECTION)))
    {
      inputBufferPointer+=strlen(I_CONNECTION);
      parsingStatus=PS_CONNECTIONS;
    }
    else errno=2;
  }
  else errno=1;
}
int countI()
{
  static unsigned int a0,a1;
  a1=0;
  for(a0=0;inputBuffer[inputBufferPointer+a0]!='\n'&&inputBuffer[inputBufferPointer+a0]!=';';a0++)
  {
    if(inputBuffer[inputBufferPointer+a0]==',') a1++;
  }
  return a1+1;
}
int countC()
{
  //
  static int a0,a1;
  //get the first '"'
  skipWhitespace();
  a0=0;
  a1=0;
  if(inputBuffer[inputBufferPointer+a1]=='"')
  {//right, go on
     //if match '\', +2, else +1
     a1++;
     while(inputBuffer[inputBufferPointer+a1]=='"')
     {
         if(inputBuffer[inputBufferPointer+a1]=='\\') a1+=2;
         else a1++;
         a0++;
     }
     return a0;
  }
  else
  {
      errno=13;
      return 0;
  }
}
void parseString(void* base)
{
    static int a0;
    //skip the first closure sign
    ///make sure U have skipped the whitespace already.
    inputBufferPointer++;
    a0=0;
    //loop, parse and copy to base+n
    while(inputBuffer[inputBufferPointer]!='"')
    {//meet to to end
        //parse the character
        if(inputBuffer[inputBufferPointer]=='\\')
        {
            static char c0;
            inputBufferPointer++;
            //get a slash
            switch(inputBuffer[inputBufferPointer])
            {
                case '0':
                    c0='\0';
                    break;
                case 'n':
                    c0='\n';
                    break;
                case 't':
                    c0='\t';
                    break;
                default:
                    c0=inputBuffer[inputBufferPointer];
            }
            *(char*)(base+a0)=c0;
        }
        else
        {
            *(char*)(base+a0)=inputBuffer[inputBufferPointer];
            //normal step
        }
        inputBufferPointer++;
        a0++;
        //move pointer
    }
    inputBufferPointer++;
}
void parseProcessor()
{
  static int a0;
  //get processor name
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //check if overrided:error return
  if(ifIdentifierOverdefined(pNameList,pListNum))
  {
    errno = 4;
    return;
  }
  //not override, push table to 新时代
  addIdentifier(identifierBuffer,pNameList,&pListNum);
  //get stack0 int
  skipWhitespace();
  sscanf(inputBuffer+inputBufferPointer,"%d",&a0);
  pe->processorTemplates[pListNum-1].stack0Size=a0;
  //get stack int
  skipWhitespace();
  sscanf(inputBuffer+inputBufferPointer,"%d",&a0);
  pe->processorTemplates[pListNum-1].stackSize=a0;
  //get data size
  skipWhitespace();
  sscanf(inputBuffer+inputBufferPointer,"%d",&a0);
  pe->processorTemplates[pListNum-1].globalSize=a0;
  //set some pointer to NULL at first
  pe->processorTemplates[pListNum-1].initDataGlobal=NULL;
  //next line
  if(readLine())
  {
    errno=8;
    return;
  }
  //skipWhitespace();
  //look up for segment
  //printf("#%s#\n",inputBuffer+inputBufferPointer);
  if(!strncmp(inputBuffer+inputBufferPointer,I_DATA_SECTION,strlen(I_DATA_SECTION)))
  {//data segment
    parsingStatus=PS_DATA_SECTION_GLOBAL;
  }
  else if(!strncmp(inputBuffer+inputBufferPointer,I_CODE_SECTION,strlen(I_CODE_SECTION)))
  {//code segment
    parsingStatus=PS_CODESECTION;
  }
  else
  {//cannot find proper segment
        //printf("$$");
    errno=8;
    return;
  }
}
void parseProcessorCode()
{
    static long fb;
    static int a0,a1;
  ///1.calculate length of code section.
  //backup file pointer
  fb=ftell(input);
  //loop:count length of each instruction until meet the . identifier
  //initialize the date first
  a0=0;
  while(!readLine())
  {
      if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
      //find the instruction
      strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
      printf("&%s&\n",identifierBuffer);
      instructionParser(&a1,identifierBuffer);
      printf("&%s&%d&\n",identifierBuffer,a1);
      if(!a1)
      {//error handler: unknown instructions
          errno=14;
          return;
      }
      //count the number
      a0+=a1;
  }
  ///2.allocate the space of code section.
  if(!a0)
  {//zero instructions
      errno=12;//error
      return;
  }
  //allocate code space
  pe->processorTemplates[pListNum].codeLength=a0;
  pe->processorTemplates[pListNum].code = malloc(a0);
  ///3.recover file pointer, start parsing step
  //recover file pointer
  fseek(input,fb,SEEK_SET);
  //loop, parse instructions
  a1=0;//code section offset;
  while(!readLine())
  {
      static char c0;
      static int a2,a3;
      static unsigned short id;
      if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
      //switch the instructions;
      strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
      id=instructionParser(&a0,identifierBuffer);
      skipIdentifier();
      *(unsigned short*)(pe->processorTemplates[pListNum].code+a1)=id;
      switch(a0)
      {//the content parsing step
          case 2://no operand
              break;
          case 12://2 groups of base:offset
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d:%d",&a2,&a3);
            c0=(char)a2;
            *(char*)(pe->processorTemplates[pListNum].code+a1+2)=c0;
            *(int*)(pe->processorTemplates[pListNum].code+a1+3)=a3;
            skipIdentifier();
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d:%d",&a2,&a3);
            c0=(char)a2;
            *(char*)(pe->processorTemplates[pListNum].code+a1+7)=c0;
            *(int*)(pe->processorTemplates[pListNum].code+a1+8)=a3;
            break;//todo
          case 7://1 group of base:offset
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d:%d",&a2,&a3);
            c0=(char)a2;
            *(char*)(pe->processorTemplates[pListNum].code+a1+2)=c0;
            *(int*)(pe->processorTemplates[pListNum].code+a1+3)=a3;
            break;//todo
          case 10://8byte instant number
            skipWhitespace();
            switch(inputBuffer[inputBufferPointer])
            {
              case 'I':
                inputBufferPointer++;
                skipWhitespace();
                sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorTemplates[pListNum].code+a1+2));
                break;
              case 'R':
                inputBufferPointer++;
                skipWhitespace();
                sscanf(inputBuffer+inputBufferPointer,"%lf",(double*)(pe->processorTemplates[pListNum].code+a1+2));
                break;
              default:
                errno=15;
                return;
            }
            //sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorTemplates[pListNum].code+a1+2));
            break;
          case 6://4byte, find with system call number
            break;//todo
          case 3://1 byte instant
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%c",(char*)(pe->processorTemplates[pListNum].code+a1+2));
            break;
          case 14://4 byte mask instant, 8 byte offset
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d",(int*)(pe->processorTemplates[pListNum].code+a1+2));
            skipIdentifier();
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorTemplates[pListNum].code+a1+6));
            break;//todo
      }
      //move pointer forward
      a1+=a0;
  }
  //set next status
  parsingStatus=PS_START;
  //end;
}
void parseProcessorData()
{
  static int a0,a1,a2;
  static long fBackup,ofst;
  //backup the file offset
  fBackup = ftell(input);
  //count data element size
  pe->processorTemplates[pListNum-1].initNumGlobal=0;
  for(;;)
  {
    //read line, count element, handle error.
    if(readLine())
    {
      errno=8;
      return;
    }
    //get the key word,  switch : I/C
    if(inputBuffer[inputBufferPointer]=='I'||inputBuffer[inputBufferPointer]=='C')
      pe->processorTemplates[pListNum-1].initNumGlobal++;
    //look up next state, handle error.
    else if(!strncmp(inputBuffer+inputBufferPointer,I_CODE_SECTION,strlen(I_CODE_SECTION)))
    {
      //ps
      parsingStatus = PS_CODESECTION;
      //end count;
      break;
    }
  }
  //return to start
  fseek(input,fBackup,SEEK_SET);
  //zero element error handle
  if(! pe->processorTemplates[pListNum-1].initNumGlobal)
  {
    errno=9;
    return;
  }
  //allocate spece
  pe->processorTemplates[pListNum-1].initDataGlobal = malloc(sizeof(initD) * pe->processorTemplates[pListNum-1].initNumGlobal);
  //set offset
  ofst=0;
  a0=0;
  for(;;)
  {//get line
    readLine();

    //check the stop sign
    if(inputBuffer[inputBufferPointer]==IDENTIFIER)
    {
      //ps
      parsingStatus = PS_CODESECTION;
      //end count;
      break;
    }
    //parser type
    switch(inputBuffer[inputBufferPointer])
    {
      case 'O':
        //set offset
        //skip space
        inputBufferPointer++;
        skipWhitespace();
        sscanf(inputBuffer+inputBufferPointer,"%ld",&ofst);
        break;
      case 'S':
        //skip n space
        inputBufferPointer++;
        skipWhitespace();
        sscanf(inputBuffer+inputBufferPointer,"%d",&a1);
        ofst+=a1;
        break;
      case 'I':
        //parse integer
        //write offset first
        pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
        //get the size
        //check if exist fixed sign
        inputBufferPointer++;
        skipWhitespace();
        if(inputBuffer[inputBufferPointer]=='F')
        {//get size by fixed identifier
          inputBufferPointer++;
          skipWhitespace();
          //get the value
          inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
          a1=sscanf(identifierBuffer,"%d",&a1);
          //caculate the size
          a1=a1<<3;
          //write size
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].length = a1;
          if(!a1)
          {
            errno=10;
            return;
          }
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].data = malloc(a1);
          //collect elem
          skipWhitespace();
          //collect dot
          a1=countI();
          a2=0;
          while(a1--)
          {
            //copy the num into buffer
            inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            //write content, offset using a2
            sscanf(identifierBuffer,"%ld",(long*)(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2));
            a2+=8;
            inputBufferPointer++;
          }
          //finished
        }
        else
        {//without fixed identifier
          //count the size by looking up
          a1=countI();
          if(!a1)
          {
            errno=10;
            return;
          }
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].length = a1;
          //read content
          a2=0;
          while(a1--)
          {
            //copy the num into buffer
            inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            //write content, offset using a2
            sscanf(identifierBuffer,"%ld",(long*)(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2));
            a2+=8;
            inputBufferPointer++;
          }
        }
        //a0++
        a0++;
        break;

        case 'R':
          //parse integer
          //write offset first
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
          //get the size
          //check if exist fixed sign
          inputBufferPointer++;
          skipWhitespace();
          if(inputBuffer[inputBufferPointer]=='F')
          {//get size by fixed identifier
            inputBufferPointer++;
            skipWhitespace();
            //get the value
            inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            a1=sscanf(identifierBuffer,"%d",&a1);
            //caculate the size
            a1=a1<<3;
            //write size
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].length = a1;
            if(!a1)
            {
              errno=10;
              return;
            }
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].data = malloc(a1);
            //collect elem
            skipWhitespace();
            //collect dot
            a1=countI();
            a2=0;
            while(a1--)
            {
              //copy the num into buffer
              inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
              //write content, offset using a2
              sscanf(identifierBuffer,"%lf",(double*)(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2));
              a2+=8;
              inputBufferPointer++;
            }
            //finished
          }
          else
          {//without fixed identifier
            //count the size by looking up
            a1=countI();
            if(!a1)
            {
              errno=10;
              return;
            }
            pe->processorInstances[iListNum-1].initData[a0].length = a1;
            //read content
            a2=0;
            while(a1--)
            {
              //copy the num into buffer
              inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
              //write content, offset using a2
              sscanf(identifierBuffer,"%ld",(long*)(pe->processorInstances[iListNum-1].initData[a0].data + a2));
              a2+=8;
              inputBufferPointer++;
            }
          }
          //a0++
          a0++;
          break;

      case 'C':
        //parse char/string
        //write offset first
        pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
        inputBufferPointer++;
        skipWhitespace();
        //check macro identifier L
        if(inputBuffer[inputBufferPointer]=='L')
        {
            static int l;
            //length defined
            //get length
            inputBufferPointer++;
            skipWhitespace();
            inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            sscanf(identifierBuffer,"%d",&l);
            //get next step
            //check macro identifier F
            skipWhitespace();
            if(inputBuffer[inputBufferPointer]=='F')
            {
                static int f;
                inputBufferPointer++;
                //fixed size
                skipWhitespace();
                //get the fixed
                inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
                sscanf(identifierBuffer,"%d",&f);
                skipWhitespace();
                //put length
                pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=l*f;
                //allocate
                pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(f*l);
                //write string
                for(a2=0;a2<a1;a2++)
                {
                    parseString(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data+a2*l);
                    skipWhitespace();
                    inputBufferPointer++;
                    skipWhitespace();
                    a2++;
                }
            }
            else
            {//fixed length.
                inputBufferPointer++;
                skipWhitespace();
                a1=countI();
                pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=a1*l;
                //allocate space,
                pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(a1*l);
                //copy n times, LOOP
                for(a2=0;a2<a1;a2++)
                {
                    parseString(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data+a2*l);
                    skipWhitespace();
                    inputBufferPointer++;
                    skipWhitespace();
                    a2++;
                }
            }
        }
        else
        {
            inputBufferPointer++;
            skipWhitespace();
            ///sole string or character
            //collect the length of this string
            a1=countC();
            //write the value of length
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=a1;
            //allocate it
            if(!a1)
            {
                errno=10;
                return;
            }
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(a1);
            //copy it!
            parseString(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data);
            //#end
        }
        break;
      default:
        errno=11;
        return;
    }
    //parse F identifier, branch
  }
  //loop, get the data
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
  if(readLine())
  {
    errno=-1;
    return;
  }
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
  if(readLine())
  {
    errno=-1;
    return;
  }
  //modify the status to start
  parsingStatus=PS_START;
}
void parseInstance()
{
  static int a0;
  //get instance name,
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //check the name
  if(ifIdentifierOverdefined(mNameList,mListNum)
  ||ifIdentifierOverdefined(iNameList,iListNum))
  {
    errno=4;
    return;
  }
  //sign up at pe struct
  addIdentifier(identifierBuffer,iNameList,&iListNum);
  //get reference name
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //check if it is true
  a0=matchIdentifier(pNameList,identifierBuffer,pListNum);
  //if its true, assign to proper place, not error return.
  if(a0 == -1)
  {
    errno = 7;
    return;
  }
  pe->processorInstances[iListNum-1].processorReferenceNo = a0;
  pe->processorInstances[iListNum-1].initData=NULL;
  //next line
  if(readLine())
  {
    errno=-1;
    return;
  }
  //branch: .data / return to start
  if(!strncmp(inputBuffer+inputBufferPointer,I_DATA_SECTION,strlen(I_DATA_SECTION)))
  {
    parsingStatus=PS_DATA_SECTION;
    if(readLine())
    {
      errno=-1;
      return;
    }
  }

  else parsingStatus=PS_START;
}
void parseInstanceData()
{
  static int a0,a1,a2;
  static long fBackup,ofst;
  //backup the file offset
  fBackup = ftell(input);
  //count data element size
  pe->processorInstances[iListNum-1].initNum=0;
  for(;;)
  {
    //read line, count element, handle error.
    if(readLine())
    {
      break;
    }
    //get the key word,  switch : I/C
    if(inputBuffer[inputBufferPointer]=='I'||inputBuffer[inputBufferPointer]=='C')
      pe->processorInstances[iListNum-1].initNum++;
    //look up next state, handle error.
    else if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
  }
  //return to start
  fseek(input,fBackup,SEEK_SET);
  //zero element error handle
  if(! pe->processorInstances[iListNum-1].initNum)
  {
    errno=9;
    return;
  }
  //allocate spece
  pe->processorInstances[iListNum-1].initData = malloc(sizeof(initD) * pe->processorInstances[iListNum-1].initNum);
  //set offset
  ofst=0;
  a0=0;
  for(;;)
  {//get line
    readLine();

    //check the stop sign
    if(inputBuffer[inputBufferPointer]==IDENTIFIER)
    {
      //
      parsingStatus = PS_START;
      //end count;
      break;
    }
    //parser type
    switch(inputBuffer[inputBufferPointer])
    {
      case 'O':
        //set offset
        //skip space
        inputBufferPointer++;
        skipWhitespace();
        sscanf(inputBuffer+inputBufferPointer,"%ld",&ofst);
        break;
      case 'S':
        //skip n space
        inputBufferPointer++;
        skipWhitespace();
        sscanf(inputBuffer+inputBufferPointer,"%d",&a1);
        ofst+=a1;
        break;
      case 'I':
        //parse integer
        //write offset first
        pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
        //get the size
        //check if exist fixed sign
        inputBufferPointer++;
        skipWhitespace();
        if(inputBuffer[inputBufferPointer]=='F')
        {//get size by fixed identifier
          inputBufferPointer++;
          skipWhitespace();
          //get the value
          inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
          a1=sscanf(identifierBuffer,"%d",&a1);
          //caculate the size
          a1=a1<<3;
          //write size
          pe->processorInstances[iListNum-1].initData[a0].length = a1;
          if(!a1)
          {
            errno=10;
            return;
          }
          pe->processorInstances[iListNum-1].initData[a0].data = malloc(a1);
          //collect elem
          skipWhitespace();
          //collect dot
          a1=countI();
          a2=0;
          while(a1--)
          {
            //copy the num into buffer
            inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            //write content, offset using a2
            sscanf(identifierBuffer,"%ld",(long*)(pe->processorInstances[iListNum-1].initData[a0].data + a2));
            a2+=8;
            inputBufferPointer++;
          }
          //finished
        }
        else
        {//without fixed identifier
          //count the size by looking up
          a1=countI();
          if(!a1)
          {
            errno=10;
            return;
          }
          pe->processorInstances[iListNum-1].initData[a0].length = a1;
          //read content
          a2=0;
          while(a1--)
          {
            //copy the num into buffer
            inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            //write content, offset using a2
            sscanf(identifierBuffer,"%ld",(long*)(pe->processorInstances[iListNum-1].initData[a0].data + a2));
            a2+=8;
            inputBufferPointer++;
          }
        }
        //a0++
        a0++;
        break;

        case 'R':
          //parse integer
          //write offset first
          pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
          //get the size
          //check if exist fixed sign
          inputBufferPointer++;
          skipWhitespace();
          if(inputBuffer[inputBufferPointer]=='F')
          {//get size by fixed identifier
            inputBufferPointer++;
            skipWhitespace();
            //get the value
            inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            a1=sscanf(identifierBuffer,"%d",&a1);
            //caculate the size
            a1=a1<<3;
            //write size
            pe->processorInstances[iListNum-1].initData[a0].length = a1;
            if(!a1)
            {
              errno=10;
              return;
            }
            pe->processorInstances[iListNum-1].initData[a0].data = malloc(a1);
            //collect elem
            skipWhitespace();
            //collect dot
            a1=countI();
            a2=0;
            while(a1--)
            {
              //copy the num into buffer
              inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
              //write content, offset using a2
              sscanf(identifierBuffer,"%lf",(double*)(pe->processorInstances[iListNum-1].initData[a0].data + a2));
              a2+=8;
              inputBufferPointer++;
            }
            //finished
          }
          else
          {//without fixed identifier
            //count the size by looking up
            a1=countI();
            if(!a1)
            {
              errno=10;
              return;
            }
            pe->processorInstances[iListNum-1].initData[a0].length = a1;
            //read content
            a2=0;
            while(a1--)
            {
              //copy the num into buffer
              inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
              //write content, offset using a2
              sscanf(identifierBuffer,"%ld",(long*)(pe->processorInstances[iListNum-1].initData[a0].data + a2));
              a2+=8;
              inputBufferPointer++;
            }
          }
          //a0++
          a0++;
          break;

      case 'C':
        //parse char/string
        //write offset first
        pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
        inputBufferPointer++;
        skipWhitespace();
        //check macro identifier L
        if(inputBuffer[inputBufferPointer]=='L')
        {
            static int l;
            //length defined
            //get length
            inputBufferPointer++;
            skipWhitespace();
            inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            sscanf(identifierBuffer,"%d",&l);
            //get next step
            //check macro identifier F
            skipWhitespace();
            if(inputBuffer[inputBufferPointer]=='F')
            {
                static int f;
                inputBufferPointer++;
                //fixed size
                skipWhitespace();
                //get the fixed
                inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
                sscanf(identifierBuffer,"%d",&f);
                skipWhitespace();
                //put length
                pe->processorInstances[iListNum-1].initData[a0].length=l*f;
                //allocate
                pe->processorInstances[iListNum-1].initData[a0].data=malloc(f*l);
                //write string
                for(a2=0;a2<a1;a2++)
                {
                    parseString(pe->processorInstances[iListNum-1].initData[a0].data+a2*l);
                    skipWhitespace();
                    inputBufferPointer++;
                    skipWhitespace();
                    a2++;
                }
            }
            else
            {//fixed length.
                inputBufferPointer++;
                skipWhitespace();
                a1=countI();
                pe->processorInstances[iListNum-1].initData[a0].length=a1*l;
                //allocate space,
                pe->processorInstances[iListNum-1].initData[a0].data=malloc(a1*l);
                //copy n times, LOOP
                for(a2=0;a2<a1;a2++)
                {
                    parseString(pe->processorInstances[iListNum-1].initData[a0].data+a2*l);
                    skipWhitespace();
                    inputBufferPointer++;
                    skipWhitespace();
                    a2++;
                }
            }
        }
        else
        {
            inputBufferPointer++;
            skipWhitespace();
            ///sole string or character
            //collect the length of this string
            a1=countC();
            //write the value of length
            pe->processorInstances[pListNum-1].initData[a0].length=a1;
            //allocate it
            if(!a1)
            {
                errno=10;
                return;
            }
            pe->processorInstances[iListNum-1].initData[a0].data=malloc(a1);
            //copy it!
            parseString(pe->processorInstances[iListNum-1].initData[a0].data);
            //#end
        }
        break;
      default:
        errno=11;
        return;
    }
    //parse F identifier, branch
  }
  //loop, get the data
}
void errorHandler()
{
  if(~errno) printf("Error at line %d,code:%d : ",parseLine,errno);
  switch(errno)
  {
    case 0:printf("No error found");break;
    case 1:printf("expecting a dot(.) identifier");break;
    case 2:printf("Typo or bad announcement");break;
    case 3:printf("identifier undefined");break;
    case 4:printf("identifier conflict, name override");break;
    case 5:printf("undefined instance name");break;
    case 6:printf("undefined destination entity name");break;
    case 7:printf("undefined template name");break;
    case 8:printf("processor template lacking necessary segment(.code)");break;
    case 9:printf("empty data section");break;
    case 10:printf("empty data element");break;
    case 11:printf("unknown key word");break;
    case 12:printf("empty code section");break;
    case 13:printf("syntax error : expect a string closure");break;
    case 14:printf("unknown instructions");break;
    case 15:printf("syntax error : expect a I or R, not others");break;
    case -1:return;//file end
  }
  printf(".\n");
}
void _debugShowNameList(char *list,int n)
{
  printf("#DEBUG STRAT#%d\n",n);
  while(n--)
  {
    printf("%s\n",list + n * NAME_BUFFER_SIZE);
  }
  printf("#DEBUG ENDED#%d\n",n);
}
