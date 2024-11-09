/**********************
myVib 振动传感器
型号:STC15F2K60S2 主频:11.0592MHz
************************/
#include <STC15F2K60S2.h>
#include <intrins.h>      //_nop_();
#define uchar unsigned char

uchar code arrLed[] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff}; //Led值
/*---------引脚别名定义---------*/
sbit sbtVib = P2 ^ 4;     //振动传感器
sbit sbtLedSel = P2 ^ 3;  //数码管与LED灯切换引脚

/*---------延时函数---------*/
void Delay40ms()        //延时40ms@11.0592MHz
{
    unsigned char i, j, k;
    _nop_();
    _nop_();
    i = 2;
    j = 175;
    k = 75;
    do
    {
        do
        {
            while ( --k );
        }
        while ( --j );
    }
    while ( --i );
}

/*---------初始化函数---------*/
void Init()
{
    P0M0 = 0xff;
    P0M1 = 0x00;
    P2M0 = 0x08;    //P2.3口推挽输出
    P2M1 = 0x00;
    sbtLedSel = 1;
}

/*---------主函数---------*/
void main()
{
    uchar i = 0;
    Init();
    sbtVib = 1;
    P0 = 0x00;                  //初始LED灯为灭
    while( 1 )
    {
        if( sbtVib == 0 )      //若检测到低电平说明振动发生，点亮LED
        {
            i = 0;
            while( i < 9 )
            {
                P0 = arrLed[i];
                Delay40ms();    //延时
                i++;
            }
        }
        else
            P0 = 0x00;
    }
}
