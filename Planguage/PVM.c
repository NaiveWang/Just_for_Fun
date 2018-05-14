#include "PVM.h"
void *mutexT()
{
  for(;;)
  {
    //wait for the handler lock
    pthread_mutex_lock(&MtxHdllock);
    //wait the mutex of queue
    pthread_mutex_lock(&qLock);
    //do the job
    while(queueH-queueT)
    {
      //some thing on queue handle one node of it
      //branch, get the resource or wait?
      switch(waitingQueue[queueT].opType)
      {
        case MTX_HDL_TYP_WAIT://wait procedure
          //look up the mutex lock
          if(waitingQueue[queueT].mTarget->lock)
          {
            //non-zero, wait
            //put the instance info into the tail
            if(waitingQueue[queueT].mTarget->waitList)
            {
              waitL *wlp = waitingQueue[queueT].mTarget->waitList;
              //there are some node here
              //find tail
              while(wlp->next) wlp = wlp->next;
              wlp->next = malloc(sizeof(waitL));
              wlp = wlp->next;
              wlp->next = NULL;
              wlp->pid = waitingQueue[queueT].pid;
            }
            else
            {
              //there are no node, just initlize it.
              waitingQueue[queueT].mTarget->waitList = malloc(sizeof(waitL));
              //assign the value
              waitingQueue[queueT].mTarget->waitList->next=NULL;
              waitingQueue[queueT].mTarget->waitList->pid = waitingQueue[queueT].pid;
            }
            //leave the status to wait(nop)
          }
          else
          {
            //zero, take the bun!
            //set the lock
            waitingQueue[queueT].mTarget->lock = waitingQueue[queueT].pid;
            //set the status to running
            waitingQueue[queueT].pid->status = PROCESSOR_STATUS_RUNNING;
          }
          break;
        case MTX_HDL_TYP_TEST:
          //test, always set running at least
          //set what ? flag!!!!!!
          //branch, if the mutex is vacant
          if(waitingQueue[queueT].mTarget->lock)
          {
            //locked, set flag to 0
            waitingQueue[queueT].pid->eflag = 0;
          }
          else
          {
            //bingo
            //set the lock
            waitingQueue[queueT].mTarget->lock = waitingQueue[queueT].pid;
            //set flag to -1
            waitingQueue[queueT].pid->eflag = -1;
          }
          //always set the status to runnning
          waitingQueue[queueT].pid->status = PROCESSOR_STATUS_RUNNING;
          break;
        case MTX_HDL_TYP_LEAVE:
          //set the lock to zero
          waitingQueue[queueT].mTarget->lock = NULL;
          //set the current instance to running status
          waitingQueue[queueT].pid->status = PROCESSOR_STATUS_RUNNING;
          //if there is any thing on waiting list, get it with lock
          if(waitingQueue[queueT].mTarget->waitList)
          {
            waitL *wlp;
            //something, give it to it
            wlp = waitingQueue[queueT].mTarget->waitList;
            waitingQueue[queueT].mTarget->lock = wlp->pid;
            wlp->pid->status = PROCESSOR_STATUS_RUNNING;
            waitingQueue[queueT].mTarget->waitList = waitingQueue[queueT].mTarget->waitList->next;
            free(wlp);
          }
          break;
        default : ;//error halt;
      }
      //delete one of the node
      queueT++;
      queueT %= M_WAITING_LIST_SIZE;
    }
    //unlock mutex
    pthread_mutex_unlock(&qLock);
    //ground self
    pthread_mutex_lock(&MtxHdllock);
  }
}
void mutexTinit()
{
  //init the queue
  queueH=queueT=0;
  //set lock?
  pthread_mutex_init(&qLock,NULL);
  pthread_mutex_init(&MtxHdllock,NULL);
  //lock the handler lock
  pthread_mutex_lock(&MtxHdllock);
  //create the thread
  pthread_create(&mutexHandler,NULL,mutexT,NULL);
}
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
    (listMutex + c0)->waitList = NULL;
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
    //initialize the constrtaint
    //1.allocate a map
    constraintMap = malloc(VMpe->processorInstanceNUM * VMpe->processorInstanceNUM);
    //set the block to zero
    memset(constraintMap,0,VMpe->processorInstanceNUM * VMpe->processorInstanceNUM);
    for(c0=0;c0<VMpe->constraintNum;c0++)
    {
      static int c1;
      for(c1=0;c1<VMpe->constraintList[c0].nodeSNum;c1++)
      {
        //heris the descent one
        constraintMap[SEEK_TABLE(VMpe->constraintList[c0].nodeSNoList[c1],VMpe->constraintList[c0].nodeDNo,VMpe->processorInstanceNUM)] = 1;
      }
    }
    //well done
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
  //constraint
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
void *execNormal(void *initPointer)
{
  /**
   * here is the execution function, it belongs to different thread
   * and the execution list cones to a circular link list
   */
  //values on the stack whlie running
  int performance=INITIAL_PERFORMANCE_VAL;//how much step run on each instance
  int delay;//this attrbute means sleep how many ms for each circle scan
  IME *instanceMountingList;
  int a0;//a1;

  //initialize the list pointer
  instanceMountingList = (IME*)initPointer;
  for(;;)
  {//the execution step
    //check the info of performance
    //branch:idle or active
    if(performance)
    {
      //active section
      //execute current instance, switch
      a0=performance;//resource counter
      while(a0)
      {
        //loop enabled block
        switch(instanceMountingList->list->instance->status)
        {
          case PROCESSOR_STATUS_RUNNING:
            //running
            executionOneStep(instanceMountingList->list->instance);
            a0--;
            break;
          case PROCESSOR_STATUS_SYS:
            //system call
            a0--;
            break;
          case PROCESSOR_STATUS_HALT:
            //halt the VM
            //maybe here we need to modify some global variables.
            break;
          case PROCESSOR_STATUS_SUSPENDED:
            //instance was suspended
            //call the suspended handler
            break;
          case PROCESSOR_STATUS_REBOOT:
            //instance is waiting for restart
            break;
          case PROCESSOR_STATUS_MWAIT:
            //call the mutex handler
            break;
          case PROCESSOR_STATUS_MTEST:
            //call the mutex handler
            break;
          case PROCESSOR_STATUS_MLEAVE:
            //call the mutex handler
            break;
          default:;//error/unknown status
        }
      }
      //instanceMountingList->list = instanceMountingList->list->next;
    }
    else
    {
      /*idle section*/
      //loop : check the the list if exist one that is runnnig
      instanceMountingList->start = instanceMountingList->list;
      for(;;)
      {
        instanceMountingList->list = instanceMountingList->list->next;
        //check the instance status
        if(!instanceMountingList->list->instance->status)
        {
          //running instance detected
          performance = INITIAL_PERFORMANCE_VAL;
          break;
        }
        if(instanceMountingList->start - instanceMountingList->list)
          continue;//not to the end
        else
        {
          //the end, all instances are suspended
          //set the sleep time longer
          delay += INITIAL_DELAY_VAL;
          break;
        }
      }
    }
  }
}
void VMStartUp()
{
  int r=0;
  pthread_create(&executionThread[0],NULL,execDebug,&r);
  pthread_join(executionThread[0],NULL);
}
