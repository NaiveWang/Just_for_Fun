/**
 * This header file contains rules of
 * remapping the execution file
 * into organized form, which is in the memory.
 **/
#ifndef PFILE_H
#define PFILE_H
#include <stdio.h>
#include <stdlib.h>
#define MIN_STACK0 2<<8
#define MIN_STACK 2<<10
#define CLEAR_ALL 0x00
#define CODE_RESERVED 0xff
#define TYP_MUTEX 0x00
#define TYP_INST 0xff
 typedef struct initializingDataStructuresListElement
 {
   int offset;
   int length;
   void *data;
 }initD;
 typedef struct processorTemplateTableElement
 {
   int codeLength;
   void *code;
   int stack0Size;
   int stackSize;
   int globalSize;
   int dataSize;
   int initNumGlobal;
   initD* initDataGlobal;
 }processorT;
 typedef struct processorInstanceTableElement
 {
   int processorReferenceNo;
   int initNum;
   initD* initData;
 }processorI;
 typedef struct connectionMappingTable
 {
   //char nodeSType;
   //bug fixed:mutex cannot reference other entity
   int nodeSNo;
   int nodeSPort;
   //assign destination to source
   char nodeDType;
   int nodeDNo;
 }connections;
 typedef struct ExeReorganizedStructure
 {
   int processorTemplateNum;
   processorT* processorTemplates;

   int mutexNum;
   int *mutexSizeList;

   int processorInstanceNUM;
   processorI* processorInstances;

   int connectionMappingNum;
   connections* connectionMapping;
 }PExe;
/** utility functions **/
PExe* parseFile(char *fileS);
void clearFile(PExe *pe,char flag);
void makeExeFile(char *fileS, PExe *pe);
#endif
