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
/** MACRO Section **/
//the number of execution threads, it mainly depends on the hardware
#define TN_EXE 3//my computer has 8 logical core, extended by the technology known as intel's hyper threading.
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
//Statistic Data
/** Functions **/
void VMInitializer();
#endif
