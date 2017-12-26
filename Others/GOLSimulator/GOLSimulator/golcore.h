#ifndef GOLCORE_H
#define GOLCORE_H
#include <stdlib.h>
/** Using Double Cache To Accelerate Iteration **/
class GOLCore
{
public:
    int conf;

    GOLCore(int, int);
    ~GOLCore();
    unsigned int* GOLSeek(int, int);
    void GOLNextFrame();

private:
    char CacheMark;
    unsigned int *map1,*map2;
    int size_x,size_y;
};

#endif // GOLCORE_H
