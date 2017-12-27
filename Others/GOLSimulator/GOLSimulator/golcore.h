#ifndef GOLCORE_H
#define GOLCORE_H
#include <stdlib.h>
#include <stdio.h>
/** Using Double Cache To Accelerate Iteration **/
class GOLCore
{
public:
#define CACHES 256
#define CONF_INF 0x00000001
#define CONF_LOG 0x00000002
    int conf;

    GOLCore(int, int);
    GOLCore(char*);//read save from files.
    ~GOLCore();
    unsigned char* GOLSeek(int, int);
    unsigned char* GOLSeekNext(int, int);
    int GOLEnvCounter(int, int);
    void GOLNextFrame();
    void SaveGame(char*);

private:
    char CacheMark;
    unsigned char *map[CACHES];
    int size_x,size_y;
    int alive;
    FILE *logfp;
    FILE *save;
};

#endif // GOLCORE_H
