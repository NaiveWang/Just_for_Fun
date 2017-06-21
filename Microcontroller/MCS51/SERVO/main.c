/*
 */

#include <reg51.h>
sbit servo=P2^0;
sbit LED=P2^1;
unsigned int target=25;percent=0;
void IntT0() interrupt 1 using 0
{
    //TH0=(65536-98)/256;
    //TL0=(65536-98)%256;
    percent++;
    if(percent == target)
    {
        servo = 0;
    }

    if(percent==200)
    {
        percent = 0;
        servo = 1;
    }

}
/*void IntT1() interrupt 1 using 1
{
    target++;
    target=target%25;
}**/
void delay(unsigned int d)
{
    static unsigned int a;

    while(d--) a=a*a*d;
}
void main(void)
{

    // Insert code
    TH0=256-100;
    TL1=0;
    TH1=0;
    EA=1;
    ET0=1;
    //ET1=1;
    TMOD=0x02;
    TR0=1;
    //TR1=1;
    while(1)
    {
        //target%=100;
        //target++;
        delay(60000);delay(60000);delay(60000);
        //target=15;
        target=5;
        LED=0;
        delay(60000);delay(60000);delay(60000);
        //target=25;
        target=25;
        LED=1;
    }

}
