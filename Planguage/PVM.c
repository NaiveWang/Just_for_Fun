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
}
