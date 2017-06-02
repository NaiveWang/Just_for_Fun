/*
 */

#include <reg51.h>
sbit servo=P2^0;
unsigned int target=25;percent=0;
void IntT0() interrupt 1 using 0
{
    //TH0=(65536-98)/256;
    //TL0=(65536-98)%256;
    percent++;
    if(percent==200)
    {
        percent = 0;
        servo = 1;
    }
    else if(percent == target)
    {
        servo = 0;
    }
}
void main(void)
{

    // Insert code
    TH0=256-100;
    EA=1;
    ET0=1;
    TMOD=0x02;
    TR0=1;
    while(1)
    {
        //target%=100;
        //target++;
        ;
    }

}
