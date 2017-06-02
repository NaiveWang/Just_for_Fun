/*
 * Post map:
 * Relay Signal---P20
 * Infrared: P1 0-3
 */

#include <reg51.h>
#define MASK 0x0F
sbit relay=P0^0;
sbit a=P2^0;
unsigned char tag;
//bit ex;
void delay(int a)
{
    while(a--);
}
void main(void)
{
    // Insert code
    relay=0;
    tag=0xFF;
    P3=0xFF;
    while(1)
    {
        if(tag && (~P3&0xF0))
        {
            relay=1;
            delay(10000);
            relay=0;
            tag=~tag;
        }
        else if(~tag && !(~P3&0xF0))
        {
            relay=1;
            delay(10000);
            relay=0;
            tag=~tag;
        }
        delay(4000);
    }
}
