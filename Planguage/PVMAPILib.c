#include "PVMAPILib.h"
void basicIO_Buffer(PBase* p)
{
  ;
}
void basicIO_File(PBase* p)
{
  ;
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
