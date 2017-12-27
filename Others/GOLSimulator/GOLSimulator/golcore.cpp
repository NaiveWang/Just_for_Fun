#include "golcore.h"

GOLCore::GOLCore(int x,int y)
{

    //map1=(unsigned char*)malloc(x*y*sizeof(char));
    for(int i=CACHES;i--;)
    {
        map[i]=(unsigned char*)malloc(x*y*sizeof(char));
    }
    size_x = x;
    size_y = y;
    for(int i = x*y;i--;)
    {
        *(map[0] + i ) = 0;
    }
    CacheMark = 0;
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
    for(int i=CACHES;i--;)
    {
        free(map[i]);
    }
}
unsigned char* GOLCore::GOLSeek(int x, int y)
{
    return map[(int )CacheMark] + x*size_x + y;
}
unsigned char* GOLCore::GOLSeekNext(int x, int y)
{
    return map[(CacheMark+1)%256] + x*size_x + y;
}
int GOLCore::GOLEnvCounter(int x, int y)
{
    static int c;
    c=0;
    if(conf & CONF_INF)
    {
        for(x=size_x;x--;)for(y=size_y;y--;)
        {
            if(GOLSeek((x+size_x+1)%size_x,(y+size_y+1)%size_y)) c++;
            if(GOLSeek((x+size_x+1)%size_x,y)) c++;
            if(GOLSeek((x+size_x+1)%size_x,(y+size_y-1)%size_y)) c++;

            if(GOLSeek((x+size_x-1)%size_x,(y+size_y+1)%size_y)) c++;
            if(GOLSeek((x+size_x-1)%size_x,y)) c++;
            if(GOLSeek((x+size_x-1)%size_x,(y+size_y-1)%size_y)) c++;

            if(GOLSeek(x,(y+size_y+1)%size_y)) c++;
            if(GOLSeek(x,(y+size_y-1)%size_y)) c++;
        }
    }
    else
    {
        for(x=size_x;x--;)for(y=size_y;y--;)
        {
            ;//if(x<0)
        }
    }
    return c;
}
void GOLCore::GOLNextFrame()
{
    static int x,y;
    this->alive=0;
    for(x=size_x;x--;)for(y=size_y;y--;)
    {
        if(GOLEnvCounter(x,y) < 2 || GOLEnvCounter(x,y) > 3) *GOLSeekNext(x,y)=0;//died of underpopularity or crowdy.
        else if(GOLEnvCounter(x,y) == 3) *GOLSeekNext(x,y)=255;//repoduction
        else if(*GOLSeek(x,y)>1) *GOLSeekNext(x,y)=*GOLSeek(x,y)-1;
        if(GOLSeekNext(x,y)) this->alive++;
    }
}
void GOLCore::SaveGame(char *fp)
{
    save = fopen(fp,"wb");
    fwrite(map[(int)CacheMark],sizeof(char),this->size_x * this->size_y,save);
    fclose(save);
}
