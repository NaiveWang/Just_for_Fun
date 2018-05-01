#include "PVM.h"
void VMReadFile(char *file)
{
  int c0;
  //get file
  VMpe=parseFile(file);
  //initialize the code list
  c0=VMpe->processorTemplateNum;
  listCode = malloc(sizeof(void*) * c0);
  while(c0--)
  {
    *(listCode+c0)=(VMpe->processorTemplates + c0)->code;
  }
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
  for(c0=0;c0<listInstanceSize;c0++)
  {
    //allocate data section.
    listInstance[c0].data = malloc(VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].dataSize);
    //assign value
    listInstance[c0].code = VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].code;
    listInstance[c0].pc = VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].code;
    listInstance[c0].PID = &listInstance[c0];
    listInstance[c0].status = 0;
    listInstance[c0].eflag = 0;
    {
      void* *ap = listInstance[c0].data;
      //data r
      *ap = listInstance[c0].data;
      ap++;
      //stack0 base pointer
      *ap = listInstance[c0].data + 256 * 8;
      ap++;
      //stack0 pointer
      *ap = listInstance[c0].data + 256 * 8;
      ap++;
      //stack base pointer
      *ap = listInstance[c0].data + 256 * 8 + VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size;
      ap++;
      //stack pointer
      *ap = listInstance[c0].data + 256 * 8 + VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size;
      ap++;
      //global base pointer
      *ap = listInstance[c0].data + 256 * 8 +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stackSize;
      ap++;
      //constant/string base pointer.
      *ap = listInstance[c0].data + 256 * 8 +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stackSize +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].globalSize;
      ap++;
    }
    {
      int c1,c2;
      for(c1=0;c1<VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initNumGlobal;c1++)
      {
        initD* d = &VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1];
        for(c2=0;c2<d->length;c2++)
        {
          *(char*)(listInstance[c0].data + c2) = *(char*)(d->data + c2);
        }
      }
      for(c1=0;c1<VMpe->processorInstances[c0].initNum;c1++)
      {
        initD* d = &VMpe->processorInstances[c0].initData[c1];
        for(c2=0;c2<d->length;c2++)
        {
          *(char*)(listInstance[c0].data + c2) = *(char*)(d->data + c2);
        }
      }
    }
  }
}
void debugVM(PBase *p,int howManyStack0Elem)
{
  long* stack0p;
  printf("VM Debug Start\n");
  printf("ProcessorID:%lud",(unsigned long)p);
  printf("Next Instruction No:%hu\n",*(unsigned short*)p->pc);
  printf("Current Status:%x",p->status);
  printf("Current Flag:%x",p->eflag);
  stack0p=(long*)*(long*)(p->data + 16);
  while(howManyStack0Elem--)
  {
    printf("stack0:%lx\n",*stack0p);
    stack0p--;
  }
  printf("VM Debug End\n");
}
void *execDebug(void* no)
{
  int error=0;
  int ino = *(int*)no;
  while(!error)
  {//loop for each loadded processor
    //execute one thread
    while(listInstance[ino].status)//trap not invoked^^^^^^^^^^^
    {
      printf("Trying one step...\n");
      executionOneStep(&listInstance[ino]);
      printf("Ended.\n");
      scanf("\n");
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
