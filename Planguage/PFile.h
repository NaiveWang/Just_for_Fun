/**
 * This header file contains rules of
 * remapping the execution file
 * into organized form, which is in the memory.
 **/
#ifndef PFILE_H
#define PFILE_H
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
   int dataSize;
   int initNumGlobal;
   initD* initDataGlobal;
   int initNumSpecialized;
   initD* initDataSpecialized;
 }processorT;
 typedef struct processorInstanceTableElement
 {
   int processorReferenceNo;
   void* initData;
 }processorI;
 typedef struct connectionMappingTable
 {
   char nodeSType;
   int nodeSNo;
   int nodeSPort;
   char nodeDType;
   int nodeTNo;
   int nodeDPort;
 }connections;
 typedef struct ExeReorganizedStructure
 {
   int processorTemplateNum;
   processorT* processorTemplates;

   int mutexNum;
   int* mutexSizeList;

   int processorInstanceNUM;
   processorI* processorInstances;

   int connectionMappingNum;
   connections* connectionMapping;
 }PExe;
/** utility functions **/
Pexe* parseFile(char *fileS);
void makeExeFile(char *fileS, char *sFileS);
#endif
