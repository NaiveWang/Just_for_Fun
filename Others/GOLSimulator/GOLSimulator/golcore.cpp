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
    conf_color=-1;
    conf_boundary=0;
    conf_log=0;
    conf_stall=0;
    conf_grid=0;
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
void GOLCore::logInit()
{
    logfp = fopen("log.csv","w");
    fprintf(logfp,"%d,%d\n",this->size_x,this->size_y);
    for(int x=0;x<this->size_x;x++)
    {
        for(int y=0;y<this->size_y;y++)
        {
            if(*(map[(int)CacheMark]+x*size_x+y)) fprintf(logfp,"x");
            else fprintf(logfp,"-");
            if(y< this->size_x-1) fprintf(logfp,",");
        }
        fprintf(logfp,"\n");
    }
    steps=0;
}
void GOLCore::logRecord()
{
    fprintf(logfp,"%d,%d\n",steps,alive[(int)CacheMark]);
    steps++;
}
void GOLCore::logSave()
{
    fclose(logfp);
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
    if(conf_boundary)
    {
        if(x==0)
        {
            if(y==0)
            {//corner
                if(*GOLSeek(x+1,y+1)) c++;
                if(*GOLSeek(x+1,y)) c++;
                //if(*GOLSeek(x+1,y-1)) c++;
                if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                //if(*GOLSeek(x,y-1)) c++;
                //if(*GOLSeek(x-1,y+1)) c++;
                //if(*GOLSeek(x-1,y)) c++;
                //if(*GOLSeek(x-1,y-1)) c++;
            }
            else if(y==size_y-1)
            {//corner
                //if(*GOLSeek(x+1,y+1)) c++;
                if(*GOLSeek(x+1,y)) c++;
                if(*GOLSeek(x+1,y-1)) c++;
                //if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                if(*GOLSeek(x,y-1)) c++;
                //if(*GOLSeek(x-1,y+1)) c++;
                //if(*GOLSeek(x-1,y)) c++;
                //if(*GOLSeek(x-1,y-1)) c++;
            }
            else
            {//edge
                if(*GOLSeek(x+1,y+1)) c++;
                if(*GOLSeek(x+1,y)) c++;
                if(*GOLSeek(x+1,y-1)) c++;
                if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                if(*GOLSeek(x,y-1)) c++;
                //if(*GOLSeek(x-1,y+1)) c++;
                //if(*GOLSeek(x-1,y)) c++;
                //if(*GOLSeek(x-1,y-1)) c++;
            }
        }
        else if(x==size_x-1)
        {
            if(y==0)
            {//corner
                //if(*GOLSeek(x+1,y+1)) c++;
                //if(*GOLSeek(x+1,y)) c++;
                //if(*GOLSeek(x+1,y-1)) c++;
                if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                //if(*GOLSeek(x,y-1)) c++;
                if(*GOLSeek(x-1,y+1)) c++;
                if(*GOLSeek(x-1,y)) c++;
                //if(*GOLSeek(x-1,y-1)) c++;
            }
            else if(y==size_y-1)
            {//corner
                //if(*GOLSeek(x+1,y+1)) c++;
                //if(*GOLSeek(x+1,y)) c++;
                //if(*GOLSeek(x+1,y-1)) c++;
                //if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                if(*GOLSeek(x,y-1)) c++;
                //if(*GOLSeek(x-1,y+1)) c++;
                if(*GOLSeek(x-1,y)) c++;
                if(*GOLSeek(x-1,y-1)) c++;
            }
            else
            {//edge
                //if(*GOLSeek(x+1,y+1)) c++;
                //if(*GOLSeek(x+1,y)) c++;
                //if(*GOLSeek(x+1,y-1)) c++;
                if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                if(*GOLSeek(x,y-1)) c++;
                if(*GOLSeek(x-1,y+1)) c++;
                if(*GOLSeek(x-1,y)) c++;
                if(*GOLSeek(x-1,y-1)) c++;
            }
        }
        else
        {
            if(y==0)
            {//edge
                if(*GOLSeek(x+1,y+1)) c++;
                if(*GOLSeek(x+1,y)) c++;
                //if(*GOLSeek(x+1,y-1)) c++;
                if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                //if(*GOLSeek(x,y-1)) c++;
                if(*GOLSeek(x-1,y+1)) c++;
                if(*GOLSeek(x-1,y)) c++;
                //if(*GOLSeek(x-1,y-1)) c++;
            }
            else if(y==size_y-1)
            {//edge
                //if(*GOLSeek(x+1,y+1)) c++;
                if(*GOLSeek(x+1,y)) c++;
                if(*GOLSeek(x+1,y-1)) c++;
                //if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                if(*GOLSeek(x,y-1)) c++;
                //if(*GOLSeek(x-1,y+1)) c++;
                if(*GOLSeek(x-1,y)) c++;
                if(*GOLSeek(x-1,y-1)) c++;
            }
            else
            {//inside
                if(*GOLSeek(x+1,y+1)) c++;
                if(*GOLSeek(x+1,y)) c++;
                if(*GOLSeek(x+1,y-1)) c++;
                if(*GOLSeek(x,y+1)) c++;
                //if(*GOLSeek(x,y)) c++;
                if(*GOLSeek(x,y-1)) c++;
                if(*GOLSeek(x-1,y+1)) c++;
                if(*GOLSeek(x-1,y)) c++;
                if(*GOLSeek(x-1,y-1)) c++;
            }
        }
    }
    else
    {
        if(*GOLSeek((x+size_x+1)%size_x,(y+size_y+1)%size_y)) c++;
        if(*GOLSeek((x+size_x+1)%size_x,y)) c++;
        if(*GOLSeek((x+size_x+1)%size_x,(y+size_y-1)%size_y)) c++;

        if(*GOLSeek((x+size_x-1)%size_x,(y+size_y+1)%size_y)) c++;
        if(*GOLSeek((x+size_x-1)%size_x,y)) c++;
        if(*GOLSeek((x+size_x-1)%size_x,(y+size_y-1)%size_y)) c++;

        if(*GOLSeek(x,(y+size_y+1)%size_y)) c++;
        if(*GOLSeek(x,(y+size_y-1)%size_y)) c++;
    }
    //qDebug()<<x<<"@"<<y<<"@"<<c;
    return c;
}
void GOLCore::GOLNextFrame()
{
    static int x,y;
    this->alive[(CacheMark+1)%CACHES]=0;
    //if(this->mark_stall) return;
    for(x=size_x;x--;)for(y=size_y;y--;)
    {
        //qDebug()<<GOLEnvCounter(x,y);
        if(GOLEnvCounter(x,y) < 2 || GOLEnvCounter(x,y) > 3)
        {
            *GOLSeekNext(x,y)=0;//died of underpopularity or crowdy.
            //qDebug()<<"Dead";
        }
        else if(GOLEnvCounter(x,y) == 3)
        {
            switch(*GOLSeek(x,y))
            {
            case 0 :*GOLSeekNext(x,y) = 255; break;//repoduction
            case 1 :*GOLSeekNext(x,y) = 1;   break;
            default:*GOLSeekNext(x,y) = *GOLSeek(x,y)-1;
            }
            //qDebug()<<"Born";
        }
        else//GOLEnvCounter(x,y) == 2
        {
            switch(*GOLSeek(x,y))
            {
            case 0 :*GOLSeekNext(x,y) = 0; break;//repoduction
            case 1 :*GOLSeekNext(x,y) = 1; break;
            default:*GOLSeekNext(x,y) = *GOLSeek(x,y)-1;
            }
            //*GOLSeekNext(x,y)=*GOLSeek(x,y)-1;
            //qDebug()<<"Keep";
        }
        if(*GOLSeekNext(x,y))
        {
            alive[(CacheMark+1)%CACHES]++;
        }

    }
    CacheMark = (CacheMark+1)%CACHES;
    if(conf_log) logRecord();
    if(conf_stall)//this block must be set to the end of the function.
    {
        for(x=this->size_x*this->size_y;x--;)
        {
            if(*(map[CacheMark]+x) ^ 255)//if this dot is the elder.
            {
                continue;
            }
            else
            {
                return;//so to speak.
            }
        }
        mark_stall=1;

    }
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
