#include "golcore.h"

#include <QDebug>
#include <time.h>

void GOLCore::GOLDeleteMap()
{
    for(int i=CACHES;i--;)
    {
        free(map[i]);
    }
}
void GOLCore::GOLAssignMap()
{
    for(int i=CACHES;i--;)
    {
        map[i] = (unsigned char*) malloc(size_x*size_y);
    }
}
void GOLCore::GOLClear()
{
    CacheMark=0;
    memset(GOLSeek(0,0),0,this->size_x*this->size_y);
}
GOLCore::GOLCore(int x,int y)
{

    //map1=(unsigned char*)malloc(x*y*sizeof(char));
    size_x = x;
    size_y = y;
    GOLAssignMap();
    GOLClear();
    conf_color=0;
    //initialize the random seed
    srand((unsigned)time(NULL));
}
GOLCore::GOLCore(char* fp)
{
    int x,y;
    save = fopen(fp,"rb");
    fread(&x,sizeof(int),1,save);
    fread(&y,sizeof(int),1,save);
    GOLCore(x,y);
    fread(this->map[0],sizeof(char),x*y,save);
    fclose(save);
}

GOLCore::~GOLCore()
{
    GOLDeleteMap();
}
unsigned char* GOLCore::GOLSeek(int x, int y)
{
    return map[(int)CacheMark] + x*size_x + y;
}
unsigned char* GOLCore::GOLSeekNext(int x, int y)
{
    return map[(CacheMark+1)%CACHES] + x*size_x + y;
}
int GOLCore::GOLEnvCounter(int x, int y)
{
    static int c;
    c=0;
    /**if(conf_boundary)
    {
        ;
    }
    else
    {**/
        if(*GOLSeek((x+size_x+1)%size_x,(y+size_y+1)%size_y)) c++;
        if(*GOLSeek((x+size_x+1)%size_x,y)) c++;
        if(*GOLSeek((x+size_x+1)%size_x,(y+size_y-1)%size_y)) c++;

        if(*GOLSeek((x+size_x-1)%size_x,(y+size_y+1)%size_y)) c++;
        if(*GOLSeek((x+size_x-1)%size_x,y)) c++;
        if(*GOLSeek((x+size_x-1)%size_x,(y+size_y-1)%size_y)) c++;

        if(*GOLSeek(x,(y+size_y+1)%size_y)) c++;
        if(*GOLSeek(x,(y+size_y-1)%size_y)) c++;
    //}
    //qDebug()<<x<<"@"<<y<<"@"<<c;
    return c;
}
void GOLCore::GOLNextFrame()
{
    static int x,y;
    this->alive[(CacheMark+1)%CACHES]=0;
    for(x=size_x;x--;)for(y=size_y;y--;)
    {
        if(GOLEnvCounter(x,y) < 2 || GOLEnvCounter(x,y) > 3) *GOLSeekNext(x,y)=0;//died of underpopularity or crowdy.
        else if(GOLEnvCounter(x,y) == 3)
            switch(*GOLSeek(x,y))
            {
            case 0 :*GOLSeekNext(x,y) = 255; break;//repoduction
            case 1 :*GOLSeekNext(x,y) = 1;   break;
            default:*GOLSeekNext(x,y) = *GOLSeek(x,y)-1;
            }

        else if(*GOLSeek(x,y)>1) *GOLSeekNext(x,y)=*GOLSeek(x,y)-1;
        if(*GOLSeekNext(x,y)) this->alive[(CacheMark+1)%CACHES]++;
    }
    CacheMark = (CacheMark+1)%CACHES;
    //qDebug()<<(int)CacheMark;
}
void GOLCore::SaveGame(char *fp)
{
    save = fopen(fp,"wb");
    fwrite(&size_x,sizeof(int),1,save);
    fwrite(&size_y,sizeof(int),1,save);
    fwrite(map[(int)CacheMark],sizeof(char),this->size_x * this->size_y,save);
    fclose(save);
}
void GOLCore::LoadGame(char *s)
{
    GOLDeleteMap();
    save = fopen(s,"rb");
    fread(&this->size_x,sizeof(int),1,save);
    fread(&this->size_y,sizeof(int),1,save);
    GOLAssignMap();
    CacheMark=0;
    fread(map[0],sizeof(char),this->size_x * this->size_y,save);
    fclose(save);
}

void GOLCore::NewGame(int x,int y)
{
    GOLDeleteMap();
    this->size_x=x;
    this->size_y=y;
    GOLAssignMap();
    GOLClear();
}

void GOLCore::RanGame(int x,int y)
{
    GOLDeleteMap();
    this->size_x=x;
    this->size_y=y;
    GOLAssignMap();
    CacheMark=0;
    for(int i=size_x*size_y;i--;)
    {
        *(map[0]+i)=rand()&1;
    }
}

