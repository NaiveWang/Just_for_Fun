#ifndef GOLCORE_H
#define GOLCORE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Using Double Cache To Accelerate Iteration **/
typedef struct GOLmodule
{
    int x,y;
    char *data;
}module;

class GOLCore
{
public:
#define CACHES 256
//#define FILE_SAVE 0x00
//#define FILE_MODULE 0x01
#define MOD_LIST_SIZE 16
    char conf_color;
    int conf_boundary;
    int conf_log;
    int conf_stall;
    int conf_grid;
    module Module[MOD_LIST_SIZE];

    GOLCore(int, int);
    GOLCore(char*);//read save from files.
    ~GOLCore();
    unsigned char* GOLSeek(int, int);
    unsigned char* GOLSeekNext(int, int);
    unsigned char* GOLSeekPrev(int, int);
    void GOLClear();

    int GOLEnvCounter(int, int);
    void GOLNextFrame();
    void SaveGame(char*);
    void LoadGame(char*);
    void LoadMod(char*);
    void SaveMod(char*);
    void NewGame(int,int);
    void RanGame(int,int,int);
    void logInit();
    void logRecord();
    void logSave();

    void moduleClear();

    unsigned char CacheMark;
    char mark_stall;

    unsigned char *map[CACHES];
    int size_x,size_y;
    int alive[CACHES];
    int mod_current;
    int mod_counter;
private:
    void GOLDeleteMap();
    void GOLAssignMap();
    int steps;

    FILE *logfp;
    FILE *save;
};

#endif // GOLCORE_H
