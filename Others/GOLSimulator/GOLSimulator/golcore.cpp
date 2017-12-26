#include "golcore.h"

GOLCore::GOLCore(int x,int y)
{

    map1=(unsigned int*)malloc(x*y*sizeof(int));
    map2=(unsigned int*)malloc(x*y*sizeof(int));
    size_x = x;
    size_y = y;
    for(int i = x*y;i--;)
    {
        *(map1 + i) = 0;
        //*map2 + i = 0;//this step is not necessary.
    }
    CacheMark = 0;
}

GOLCore::~GOLCore()
{
    free(map1);
    free(map2);
}
unsigned int* GOLCore::GOLSeek(int x, int y)
{
    switch(this->CacheMark)
    {
    case 0:return this->map1 + x*size_x + y;//break;
    default:return this->map2 + x*size_x + y;
    }
    return NULL;
}
void GOLCore::GOLNextFrame()
{
    static unsigned int *t0,*t1;

    //assign the right caches
    switch(CacheMark)
    {
    case 0:t0=this->map1;t1=this->map2;break;
    default:t0=this->map2;t1=this->map1;
    }
    CacheMark=~CacheMark;
}
