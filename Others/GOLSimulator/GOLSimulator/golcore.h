#ifndef GOLCORE_H
#define GOLCORE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Using Double Cache To Accelerate Iteration **/
class GOLCore
{
public:
#define CACHES 64
    char conf_color;
    int conf_boundary;
    int conf_log;
    int conf_stall;
    int conf_grid;

    GOLCore(int, int);
    GOLCore(char*);//read save from files.
    ~GOLCore();
    unsigned char* GOLSeek(int, int);
    unsigned char* GOLSeekNext(int, int);
    void GOLClear();

    int GOLEnvCounter(int, int);
    void GOLNextFrame();
    void SaveGame(char*);
    void LoadGame(char*);
    void NewGame(int,int);
    void RanGame(int,int);
    void logInit();
    void logRecord();
    void logSave();

    char CacheMark;
    char mark_stall;

    unsigned char *map[CACHES];
    int size_x,size_y;
    int alive[CACHES];
private:
    void GOLDeleteMap();
    void GOLAssignMap();
    int steps;

    FILE *logfp;
    FILE *save;
};

#endif // GOLCORE_H
