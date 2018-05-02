#include "PVMAPILib.h"
void basicIO_Buffer(PBase* p)
{
  switch(*(((int*)&p->APICallID)+1))
  {
    case 0 :printf("%ld ",*(long*)p->APICallAddr);break;//print 8 i
    case 1 :printf("%c ",*(char*)p->APICallAddr);break;//print c c
    case 2 :printf("%s",(char*)p->APICallAddr);break;//print string
    case 3 :scanf("%ld",(long*)p->APICallAddr);break;//scan 8 i
    case 4 :scanf("%c",(char*)p->APICallAddr);break;//scan c c
    default:printf("API Error:no such calling identifier in basicIO_Buffer");
  }
}
void basicIO_File(PBase* p)
{
  static FILE *fp;
  switch(*(((int*)&p->APICallID)+1))
  {
    default:printf("API Error:no such calling identifier in basicIO_File");
  }
}
void *APIHandler(void* vp)
{
  static PBase* p;
  p = (PBase*)vp;
  switch(*(int*)&p->APICallID)
  {
    case 0:basicIO_Buffer(p);break;
    case 1:basicIO_File(p);break;
    default:printf("Error:unknown calling ID\n");
  }
}
