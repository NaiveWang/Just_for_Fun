#ifndef PVM_H
#define PVM_H
/**
 * This is the header of Process VM
 * it describes the organization of the main body.
 * structures and utility functions.
 **/
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "PCore.h"
#include "PFile.h"
#include "PVMAPILib.h"
#define NUM_E_THREAD 2
#define M_WAITING_LIST_SIZE 256
#define PRINTADDR(x) printf("ADDR:%lx\n",(long)(x));
/** MACRO Section **/
//the number of execution threads, it mainly depends on the hardware
//#define TN_EXE 3//my computer has 8 logical core, extended by the technology known as intel's hyper threading.
typedef struct instanceMountingLinkList
{
  PBase *instance;
  struct instanceMountingLinkList *next;
}IMLList;
typedef struct instanceMountingElement
{
  int INumber;
  IMLList *start;
  IMLList *list;
}IME;
typedef struct waitLinkList
{
  PBase *pid;
  struct waitLinkList *next;
}waitL;
typedef struct MutexStructure
{
  unsigned long size;
  void* lock;//can be used to the id of threads
  void* content;
  waitL *waitList;
}mutex;
typedef struct haltInformations
{
  PBase *pid;
  int val;
}hInfo;
typedef struct mutexHandlerWaitingQueue
{
  PBase *pid;
  int opType;
  mutex *mTarget;
}MHQ;
/** Global Section **/
//necassary sole data
PExe *VMpe;
//Lists & boundary
int listCodeSize;
void* *listCode;
int listMutexSize;
mutex *listMutex;
int listInstanceSize;
PBase *listInstance;
//halt
hInfo haltInfo;
//mutex handler global
int queueH,queueT;
MHQ waitingQueue[M_WAITING_LIST_SIZE];
//thread pool
pthread_t haltHandler;
pthread_t constraintHandler;
pthread_t mutexOperationHandler;
pthread_t executionThread[NUM_E_THREAD];
IME executionGroup[NUM_E_THREAD];
//global variables
char *constraintMap;
//Statistic Data
/** utility functions **/
char getConstraintNum(int i);
/** Functions **/
void VMReadFile(char *file);
void debugVM(PBase *p,int howManyStack0Elem);
void *execDebug(void* no);
void *execNormal();
void *awaker();
void *mutexHandler();
void VMStartUp();
#endif
