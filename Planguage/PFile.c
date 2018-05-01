#include "PFile.h"
PExe* parseFile(char *fileS)
{
  int count;
  FILE *fp=fopen(fileS,"rb");
  PExe *pe=malloc(sizeof(PExe));
  fread(&pe->processorTemplateNum,sizeof(int),1,fp);//get number of P
  pe->processorTemplates=malloc(sizeof(processorT)*pe->processorTemplateNum);//allocate accomdation
  for(count=0;count < pe->processorTemplateNum;count++)
  {//processor template
    processorT *ppt=pe->processorTemplates+count;
    fread(&ppt->codeLength,sizeof(int),1,fp);//get Code length
    ppt->code = malloc(ppt->codeLength);//allocate space first
    fread(ppt->code,1,ppt->codeLength,fp);//get code section
    fread(&ppt->stack0Size,sizeof(int),1,fp);//get size of stack0
    fread(&ppt->stackSize,sizeof(int),1,fp);//get size of stack
    fread(&ppt->globalSize,sizeof(int),1,fp);
    fread(&ppt->initNumGlobal,sizeof(int),1,fp);//get the list size
    ppt->initDataGlobal = malloc(sizeof(initD) * ppt->initNumGlobal);//allocate space
    {
      int count1 = ppt->initNumGlobal;
      while(count1--)
      {//read the initializing data into the memory, need to allocate space.
        fread(&(ppt->initDataGlobal + count1)->offset,sizeof(int),1,fp);
        fread(&(ppt->initDataGlobal + count1)->length,sizeof(int),1,fp);
        (ppt->initDataGlobal + count1)->data = malloc((ppt->initDataGlobal + count1)->length);
        fread((ppt->initDataGlobal + count1)->data,1,(ppt->initDataGlobal + count1)->length,fp);
        //bingo
      }
    }
  }
  //template finished
  fread(&pe->mutexNum,sizeof(int),1,fp);//get number of mutex
  pe->mutexSizeList=malloc(sizeof(int) * pe->mutexNum);//allocate
  fread(pe->mutexSizeList,sizeof(int),pe->mutexNum,fp);//get data directly.
  //mutex finished
  fread(&pe->processorInstanceNUM,sizeof(int),1,fp);
  //allocate first!!
  pe->processorInstances=malloc(sizeof(processorI) * pe->processorInstanceNUM);
  for(count=0;count<pe->processorInstanceNUM;count--)
  {//get instancelist
    processorI *ppi=pe->processorInstances+count;
    fread(&ppi->processorReferenceNo,sizeof(int),1,fp);//number
    fread(&ppi->initNum,sizeof(int),1,fp);//get the list size
    ppi->initData = malloc(sizeof(initD) * ppi->initNum);//allocate space
    {
      int count1 = ppi->initNum;
      while(count1--)
      {//read the initializing data into the memory, need to allocate space.
        fread(&(ppi->initData + count1)->offset,sizeof(int),1,fp);
        fread(&(ppi->initData + count1)->length,sizeof(int),1,fp);
        (ppi->initData + count1)->data = malloc((ppi->initData + count1)->length);
        fread((ppi->initData + count1)->data,1,(ppi->initData + count1)->length,fp);
        //bingo
      }
    }
  }
  //instances finished
  fread(&pe->connectionMappingNum,sizeof(int),1,fp);
  pe->connectionMapping = malloc(sizeof(connections) * pe->connectionMappingNum);
  fread(pe->connectionMapping,sizeof(connections),pe->connectionMappingNum,fp);
  //finished
  fclose(fp);
  return pe;
}
void clearFile(PExe *pe)
{
  ;
}
