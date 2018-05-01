#ifndef PVM_H
#define PVM_H
/**
 * This is the header of Process VM
 * it describes the organization of the main body.
 * structures and utility functions.
 **/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "PCore.h"
#include "PFile.h"
#include "PVMAPILib.h"
#define NUM_E_THREAD 1
/** MACRO Section **/
//the number of execution threads, it mainly depends on the hardware
//#define TN_EXE 3//my computer has 8 logical core, extended by the technology known as intel's hyper threading.
typedef struct MutexStructure
{
  void* lock;//can be used to the id of threads
  unsigned long size;
  void* content;
}mutex;
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
//thread pool
pthread_t APIHandlerT;
pthread_t errorHandlerT;
pthread_t triggerHandlerT;
pthread_t executionThread[NUM_E_THREAD];
//Statistic Data
/** Functions **/
void VMReadFile(char *file);
void debugVM(PBase *p,int howManyStack0Elem);
void *execDebug(void* no);
void *execNormal();
void VMStartUp();
#endif
