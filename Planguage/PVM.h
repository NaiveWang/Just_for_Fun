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
#define INITIAL_PERFORMANCE_VAL 32
#define INITIAL_DELAY_VAL 2
#define MAX_PERFORMANCE_VAL 32000
#define MAX_DELAY_VAL 500;
#define PRINTADDR(x) printf("ADDR:%lx\n",(long)(x))
#define SEEK_TABLE(x,y,a) ((x)+(y)*(a))
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
#define MTX_HDL_TYP_WAIT 0
#define MTX_HDL_TYP_TEST 1
#define MTX_HDL_TYP_LEAVE 2
#define TRIGGER 3
typedef struct mutexHandlerWaitingQueue
{
  PBase *pid;
  int opTyp;
  mutex *mTarget;
}MHQ;
typedef struct triggerListElement
{
  int number;
  int *list;
}tgr;
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
pthread_mutex_t rtLock;
pthread_mutex_t qLock;
int queueH,queueT;
MHQ waitingQueue[M_WAITING_LIST_SIZE];
//thread pool
pthread_t haltT;
pthread_t constraintHandler;
pthread_t runtimeT;
pthread_t executionThread[NUM_E_THREAD];
IME executionGroup[NUM_E_THREAD];
//global variables
tgr *triggerList;
/** Error Handle Val **/
int errno;
//Statistic Data
/** utility functions **/
/** mutex **/
void mutexTinit();
void *runtimeHandler();
/** Functions **/
void VMReadFile(char *file);
void debugVM(PBase *p,int howManyStack0Elem);
void *execDebug(void* no);
void *execNormal();
void dispatcher();
void VMStartUp();
void *VMHalt();
#endif
