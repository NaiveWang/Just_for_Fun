#ifndef PASSENBLER_H
#define PASSENBLER_H
#include <stdio.h>
#include <string.h>
#include "PCore.h"
#include "PFile.h"

#define IDENTIFIER '.'
#define BUFFER_SIZE 1024
#define NAME_BUFFER_SIZE 128
//define identifier reserved key word
#define I_PROCESSOR "processor "
#define I_MUTEX "mutex "
#define I_INSTANCE "instance "
#define I_CONNECTION "connection "
//define parsing status
#define PS_IN_PROCESSOR 0
#define PS_DATA_SECTION_GLOBAL 1
#define PS_DATA_SECTION_TEMPLATE 2
#define PS_CODESECTION 3
#define PS_MUTEX_SECTION 4
#define PS_INSTANCE_SECTION 5
#define PS_CONNECTIONS 6
/** Global Variables **/
char inputBuffer[BUFFER_SIZE];
FILE *input,*output;
PExe pe;
int parsingStatus;
//element list
char *pNameList;
char *iNameList;
char *mNameList;
char *cNameList;
/**Utility Function Section**/
void countIdentifier();
int ifIdentifierOverdefined(char *List,char *target,int boundary);
int matchIdentifier(char *List,char *target,int boundary);
/** Assembler main body **/
int main(int argv,char** argc)
{
  if(argv!=3)
  {
    printf("Error : lack of input file or output file.\n");
    //system("pause");
    return -1;
  }
  //argc+1: input file, text.
  //argc+2: output file, binary.

  //read input file.
  pe.processorTemplateNum=0;
  pe.mutexNum=0;
  pe.processorInstanceNUM=0;
  pe.connectionMappingNum=0;
  input=fopen(*(argc+1),"r");
  if(input!=NULL) printf("reading file successful\n");
  else
  {
    printf("Error:File opening failure.\n");
    return -1;
  }
  printf("counting emelemts\n");
  countIdentifier();
  printf("Template(s):%d\n",pe.processorTemplateNum);
  printf("Mutex(es):%d\n",pe.mutexNum);
  printf("Instance(s):%d\n",pe.processorInstanceNUM);
  printf("Connection(s):%d\n",pe.connectionMappingNum);
  fseek(input,0,SEEK_SET);
  //allocate the space,
  if(pNameList) pNameList=malloc(NAME_BUFFER_SIZE * pe.processorTemplateNum);
  if(iNameList) iNameList=malloc(NAME_BUFFER_SIZE * pe.mutexNum);
  if(mNameList) mNameList=malloc(NAME_BUFFER_SIZE * pe.processorInstanceNUM);
  if(cNameList) cNameList=malloc(NAME_BUFFER_SIZE * pe.connectionMappingNum);
  //allocate the space for element
  if(pNameList) pe.processorTemplates = malloc(sizeof(processorT) * pe.processorTemplateNum);
  if(iNameList) pe.mutexSizeList = malloc(sizeof(int) * pe.mutexNum);
  if(mNameList) pe.processorInstances = malloc(sizeof(processorI) * pe.processorInstanceNUM);
  if(cNameList) pe.connectionMapping = malloc(sizeof(connections) * pe.connectionMappingNum);
  //parse processor, record name and others
  //while(fgets(inputBuffer,NAME_BUFFER_SIZE,input)!=NULL) printf("%s",inputBuffer);
  return 0;
}
#endif
