#ifndef PASSENBLER_H
#define PASSENBLER_H
#include <stdio.h>
#include <string.h>
#include "PCore.h"
#include "PFile.h"

#define IDENTIFIER '.'
#define BUFFER_SIZE 1024
#define NAME_BUFFER_SIZE 128
#define I_PROCESSOR "processor"
#define I_MUTEX "mutex"
#define I_INSTANCE "instance"
#define I_CONNECTION "connection"
/** Global Variables **/
char inputBuffer[BUFFER_SIZE];
FILE *input,*output;
PExe pe;
//element list
char *pNameList;
char *iNameList;
char *mNameList;
char *cNameList;
/**Utility Function Section**/
void ReadLine();
void countIdentifier();
int ifIdentifierOverdefined(char *List,char *target);
int matchIdentifier(char *List,char *target);
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
  countIdentifier();
  fseek(input,0,SEEK_SET);
  //allocate the space,
  pNameList=malloc(NAME_BUFFER_SIZE * pe.processorTemplateNum);
  iNameList=malloc(NAME_BUFFER_SIZE * pe.mutexNum);
  mNameList=malloc(NAME_BUFFER_SIZE * pe.processorInstanceNUM);
  cNameList=malloc(NAME_BUFFER_SIZE * pe.connectionMappingNum);
  //parse processor.
  return 0;
}
#endif
