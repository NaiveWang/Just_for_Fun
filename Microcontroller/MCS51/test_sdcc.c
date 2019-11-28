#include "8051.h"

#define uint unsigned int
#define uchar unsigned char
uchar tab[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void Delay(uint xms)
{
        uint i,j;
        for(i=xms;i>0;i--)
        for(j=110;j>0;j--);
}

void main()
{
        uchar i;
        while(1)
        {
                for(i=0;i<8;i++)
                {
                        P1 = tab[i];
                        Delay(100);
                }
        }
}
