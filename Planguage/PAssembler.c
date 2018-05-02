#include "PAssembler.h"
void ReadLine()
{
    fscanf(input,"%s\n",inputBuffer);
}
void countIdentifier()
{
    char bufferC=0;
    while(bufferC!=EOF)
    {
        fscanf(input,"%c",&bufferC);
        if(bufferC==IDENTIFIER)
        {
            fscanf(input,"%c",inputBuffer);
            switch(*inputBuffer)
            {
                case'p':
                    fscanf(input,"%8c",inputBuffer+1);
                    if(strncmp(inputBuffer,I_PROCESSOR,9)) pe.processorTemplateNum++;
                    break;
                case'm':
                    fscanf(input,"%4c",inputBuffer+1);
                    if(strncmp(inputBuffer,I_PROCESSOR,5)) pe.mutexNum++;
                    break;
                case'i':
                    fscanf(input,"%7c",inputBuffer+1);
                    if(strncmp(inputBuffer,I_PROCESSOR,8)) pe.processorInstanceNUM++;
                    break;
                case'c':
                    fscanf(input,"%9c",inputBuffer+1);
                    if(strncmp(inputBuffer,I_PROCESSOR,10)) pe.connectionMappingNum++;
                    break;
            }
        }
    }
}
int ifIdentifierOverdefined(char *List,char *target,int boundary)
{//assume they have the \0 end sign
    while(boundary--)
    {
        if(strcmp(List,target))
        {
            List+=NAME_BUFFER_SIZE;
            continue;
        }
        return -1;
    }
    return 0;
}
int matchIdentifier(char *List,char *target,int boundary)
{
    int bkboundary;
    for(bkboundary=0;bkboundary<boundary;bkboundary++)
    {
        if(strcmp(List,target))
        {
            List+=NAME_BUFFER_SIZE;
            continue;
        }
        return bkboundary;
    }
    return -1;
}
