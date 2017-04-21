/*
 * LED Type : Risym MAX7219
 * PORT MAP
 *------------------
 * P00 ---- DIN
 * P01 ---- CS
 * P02 ---- CLK
 *------------------
 * Clock:11.0592MHz
 **/

#include <reg52.h>
/**Macro Section**/
#define I_HOUR 20
#define I_MINT 53

#define DEVIDER 65536-43200//refer to Clock,11059200Hz to 200Hz
#define COUNTER 24
sbit CLK = P0^2;
sbit CS  = P0^1;
sbit DIN = P0^0;
/**Global Variables Declaring Section**/
unsigned char h,m,s;//hour,minutes,seconds.
int counter;
/*Here's the Digit Table**/
unsigned char d_map[10][8]={
{0x60,0x90,0x90,0x90,0x90,0x90,0x60,0x00},//0
{0x20,0x60,0x20,0x20,0x20,0x20,0x20,0x00},//1
{0x60,0x90,0x10,0x20,0x40,0x80,0xF0,0x00},//2
{0x60,0x90,0x10,0x20,0x10,0x90,0x60,0x00},//3
{0x80,0xA0,0xA0,0xF0,0x20,0x20,0x20,0x00},//4
{0xF0,0x80,0x80,0x60,0x10,0x90,0x60,0x00},//5
{0x60,0x90,0x80,0xE0,0x90,0x90,0x60,0x00},//6
{0xF0,0x10,0x20,0x40,0x40,0x40,0x40,0x00},//7
{0x60,0x90,0x90,0x60,0x90,0x90,0x60,0x00},//8
{0x60,0x90,0x90,0x70,0x10,0x90,0x60,0x00}};//9
/**Interrupt Functions**/
void timer() interrupt 1
{
    TH0=DEVIDER/256;
    TH1=DEVIDER%256;
    counter++;
}
/**LED Matrix Driver**/
void WriteB(unsigned char byte)
{
    static unsigned char i;
    //CS=0;
    for(i=8;i>=1;i--)
    {
        CLK=0;
        DIN=byte&0x80;
        byte=byte<<1;
        CLK=1;
    }
}
void WritehB(unsigned char byte)
{
    static unsigned char i;
    //CS=0;
    for(i=4;i>=1;i--)
    {
        CLK=0;
        DIN=byte&0x80;
        byte=byte<<1;
        CLK=1;
    }
}
void MInit()
{
    CS=0;
    WriteB(0x09);
    WriteB(0x00);
    WriteB(0x09);
    WriteB(0x00);
    WriteB(0x09);
    WriteB(0x00);
    WriteB(0x09);
    WriteB(0x00);
    CS=1;
    CS=0;
    WriteB(0x0a);
    WriteB(0x03);
    WriteB(0x0a);
    WriteB(0x03);
    WriteB(0x0a);
    WriteB(0x03);
    WriteB(0x0a);
    WriteB(0x03);
    CS=1;
    CS=0;
    WriteB(0x0b);
    WriteB(0x07);
    WriteB(0x0b);
    WriteB(0x07);
    WriteB(0x0b);
    WriteB(0x07);
    WriteB(0x0b);
    WriteB(0x07);
    CS=1;
    CS=0;
    WriteB(0x0c);
    WriteB(0x01);
    WriteB(0x0c);
    WriteB(0x01);
    WriteB(0x0c);
    WriteB(0x01);
    WriteB(0x0c);
    WriteB(0x01);
    CS=1;
    CS=0;
    WriteB(0x0f);
    WriteB(0x00);
    WriteB(0x0f);
    WriteB(0x00);
    WriteB(0x0f);
    WriteB(0x00);
    WriteB(0x0f);
    WriteB(0x00);
    CS=1;
}
void Disp()
{
    static unsigned char i;

    for(i=1;i<9;i++)
    {
        CS=0;
        WriteB(i);
        WritehB(d_map[h/10][i-1]);
        WritehB(d_map[h%10][i-1]);
        WriteB(i);
        WritehB(0x00);
        WritehB(d_map[m/10][i-1]);
        WriteB(i);
        WritehB(d_map[m%10][i-1]);
        WritehB(0x00);
        WriteB(i);
        WritehB(d_map[s/10][i-1]);
        WritehB(d_map[s%10][i-1]);
        CS=1;
    }
}

void main(void)
{
    /*Set Timer**/
    EA=1;
    ET0=1;
    TMOD=0x01;
    TH0=DEVIDER/256;
    TH1=DEVIDER%256;
    // Insert code
    /*Initializing**/
    MInit();
    h=I_HOUR;
    m=I_MINT;
    counter=0;
    TR0=1;
    Disp();
    /*Looping**/
    while(1)
    {
        if(counter==COUNTER)
        {
            counter=0;
            s++;
            if(s==59) m++;
            if(m==60) h++;
            s%=59;
            m%=60;
            Disp();
        }
    }
}
