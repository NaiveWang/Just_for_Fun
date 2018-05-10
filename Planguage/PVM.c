#include "PVM.h"
void VMReadFile(char *file)
{
  int c0;
  //get file
  VMpe=parseFile(file);
  //checkStructure(VMpe);
  //initialize the code list
  c0=VMpe->processorTemplateNum;
  listCode = malloc(sizeof(void*) * c0);
  //getchar();
  while(c0--)
  {
    *(listCode+c0)=(VMpe->processorTemplates + c0)->code;
  }//getchar();
  //initialaze the mutex list
  c0=VMpe->mutexNum;
  listMutex=malloc(sizeof(mutex) * c0);
  while(c0--)
  {
    (listMutex + c0)->lock = NULL;
    (listMutex + c0)->size = *(VMpe->mutexSizeList + c0);
    (listMutex + c0)->content = malloc((listMutex + c0)->size);
  }

  //initialize the instance list
  //allocate the space
  listInstanceSize = VMpe->processorInstanceNUM;
  listInstance = malloc(sizeof(PBase) * listInstanceSize);
  printf("%d\n",listInstanceSize);//getchar();
  for(c0=0;c0<listInstanceSize;c0++)
  {
    //allocate data section.
    ///listInstance[c0].data = malloc(VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].dataSize);
    //assign value
    listInstance[c0].code = VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].code;
    listInstance[c0].pc = VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].code;//getchar();
    listInstance[c0].PID = &listInstance[c0];
    listInstance[c0].status = VMpe->processorInstances[c0].initStatus;
    listInstance[c0].eflag = 0;
    //allocate data space!
    listInstance[c0].data=malloc(
      VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size+
      VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stackSize+
      VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].globalSize+
      256*sizeof(void*));
    {
      void* *ap = listInstance[c0].data;
      //PRINTADDR(listInstance[c0].data);
      //PRINTADDR(ap);
      //PRINTADDR(ap[0]);
      //data r
      ap[0] = listInstance[c0].data;
      //ap+=sizeof(void*);
      //PRINTADDR(ap[0]);
      //PRINTADDR(*(long*)listInstance[c0].data);
      //stack0 base pointer
      ap[1] = listInstance[c0].data + 256 * 8;
      //ap++;
      //stack0 pointer
      ap[2] = listInstance[c0].data + 256 * 8;
      //ap++;
      //stack base pointer
      ap[3] = listInstance[c0].data + 256 * 8 + VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size;
      //ap++;
      //stack pointer
      ap[4] = listInstance[c0].data + 256 * 8 + VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size;
      //ap++;
      //global base pointer
      ap[5] = listInstance[c0].data + 256 * 8 +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stackSize;
      //ap++;
      //constant/string base pointer.
      //ap++;
    }
    {
      int c1;
      void* *dataBase = listInstance[c0].data;//global data base is at [5]
      //printf("\t%d\n",VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initNumGlobal);
      for(c1=0;c1<VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initNumGlobal;c1++)
      {
        //printf(")%d()%d(\n",VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].offset,VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].length);
        //printf("X%ldX\n",*(long*)VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].data);
        memmove(
          (char*)dataBase[5]+VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].offset,
          VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].data,
          VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].length);
        //read global data
      }
      for(c1=0;c1<VMpe->processorInstances[c0].initNum;c1++)
      {
        memmove(
          (char*)dataBase[5]+VMpe->processorInstances[c0].initData[c1].offset,
          VMpe->processorInstances[c0].initData[c1].data,
          VMpe->processorInstances[c0].initData[c1].length);
        //read global data
      }
    }
  }
  //Connections
  for(c0=0;c0<VMpe->connectionMappingNum;c0++)
  {
    //find the address anyway
    void* addr;
    switch(VMpe->connectionMapping[c0].nodeDType)
    {
      case TYP_INST:
        addr = *(void**)(listInstance[VMpe->connectionMapping[c0].nodeDNo].data + 5 * sizeof(void*));
        break;
      case TYP_MUTEX:
        addr = (listMutex[VMpe->connectionMapping[c0].nodeDNo].content);
        break;
      default:
        printf("In connection %d : unknown reference type ID:%d\n",c0,VMpe->connectionMapping[c0].nodeDType);
        return;
    }//now we have got the address
    //put it on to the right instance
    *(void**)(listInstance[VMpe->connectionMapping[c0].nodeSNo].data + VMpe->connectionMapping[c0].nodeSPort * sizeof(void*))=addr;
  }
}
void debugVM(PBase *p,int howManyStack0Elem)
{
  long* stack0p;
  printf("VM Debug Start\t");
  printf("ProcessorID:%lu ",(unsigned long)p);
  printf("Next Instruction P:%lx No:%hu\n",(long)p->pc,*(unsigned short*)p->pc);
  printf("Current Status:%x ",p->status);
  printf("Current Flag:%x\n",p->eflag);
  printf("datapointer : %lx \n",(long)(p->data));
  //printf("self0pointer:%lx \n",*(long*)(p->data));
  //PRINTADDR(*(long*)p->data);
  //printf("Stack0pointer : %lx \n",*(long*)(p->data + POINTER_STACK0));
  stack0p=(long*)*(long*)(p->data + POINTER_STACK0);
  printf("stack0TopValue :%lx:%lx:%ld/%lx/%ld\n",*(long*)(p->data+8),(long)stack0p,*(stack0p-1),*(stack0p-1),*(stack0p-1));
  printf("##%ld\n", *(long*)(p->data+40));
  /*while(howManyStack0Elem--)
  {
    printf("stack0:%lx\n",*stack0p);
    stack0p--;
  }*/
  printf("VM Debug End\n");
}
void *execDebug(void* no)
{
  int error=0;
  int ino = *(int*)no;
  while(!error)
  {//loop for each loadded processor
    //execute one thread
    printf("@%d\n",listInstance[ino].status);
    while(!listInstance[ino].status)//trap not invoked^^^^^^^^^^^
    {
      //printf("Trying one step...\n");
      debugVM(&listInstance[ino],4);
      executionOneStep(&listInstance[ino]);
      //printf("Ended.\n");
      //debugVM(&listInstance[ino],4);
      getchar();
      //scanf("\n");
    }
    ino+=NUM_E_THREAD;
    if(ino==listInstanceSize) ino = *(int*)no;
  }
}
void VMStartUp()
{
  int r=0;
  pthread_create(&executionThread[0],NULL,execDebug,&r);
  pthread_join(executionThread[0],NULL);
}
