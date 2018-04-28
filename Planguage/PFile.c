PExe* parseFile(char *fileS)
{
  int count;
  FILE *fp=fopen(fileS,"rb");
  PExe *pe=malloc(sizeof(PExe));
  fread(&pe->processorTemplateNum,sizeof(int),1,fp);
  pe->processorTemplates=malloc(sizeof(processorT)*pe->processorTemplateNum);
  for(count=pe->processorTemplateNum;pe--;)
  {//processor template
    processorT *ppt=p->processorTemplates+count;
    fread(&ppt->codeLength,sizeof(int),1,fp);
    fread(ppt->code,1,ppt->codeLength,fp);
    fread(&ppt->dataSize,sizeof(int),1,fp);
    
  }
  fclose(fp);
}
