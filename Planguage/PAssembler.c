#include "PAssembler.h"
void countIdentifier()
{
    char bufferC=0;
    while((bufferC=(char)fgetc(input))!=EOF)
    {
        //fscanf(input,"%c",&bufferC);
        //if(bufferC=='\n') fscanf(input,"\n");
        //if(bufferC==EOF) break;
        //bufferC=(char)fgetc(input);
        //printf("%c",bufferC);
        if(bufferC==IDENTIFIER)
        {
            inputBuffer[0]=(char)fgetc(input);
            //printf("#%c\n",bufferC);
            switch(*inputBuffer)
            {
                case'p':
                    fscanf(input,"%8s",inputBuffer+1);
                    printf("##%s\n",inputBuffer);
                    if(!strncmp(inputBuffer,I_PROCESSOR,9)) pe.processorTemplateNum++;
                    break;
                case'm':
                    fscanf(input,"%4s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_MUTEX,5)) pe.mutexNum++;
                    break;
                case'i':
                    fscanf(input,"%7s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_INSTANCE,8)) pe.processorInstanceNUM++;
                    break;
                case'c':
                    fscanf(input,"%9s",inputBuffer+1);
                    if(!strncmp(inputBuffer,I_CONNECTION,10)) pe.connectionMappingNum++;
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
