/**********************
    :八位数码管+流水灯
型号:STC15F2K60S2 主频:11.0592MHz
************************/
#include <STC15F2K60S2.h>
#define uint unsigned int
#define uchar unsigned char

uchar arrSeg7Select[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f}; //显示0-8
uchar arrDigitSelect[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};   //数码管0-7

/*---------引脚别名定义---------*/
sbit sbtLedSel = P2 ^ 3;  //数码管与LED灯切换引脚

/*---------变量定义---------*/
uchar uiLed = 0x01;        //LED灯值寄存
uint  uiLedCnt = 0;        //LED灯累计计数器
uchar i = 0;               //数码管扫描显示循环

/*---------初始化函数---------*/
void Init()
{
    P0M1 = 0x00;
    P0M0 = 0xff;
    P2M1 = 0x00;
    P2M0 = 0x08;
    sbtLedSel = 0;  //先选择数码管亮
}

/*---------延时函数---------*/
//下为生成1ms的延时函数，通过传入参数n，函数可以延时n毫秒
void delay_ms( uint n )
{
    while( n )
    {
        uchar i, j;
        i = 11;
        j = 190;
        do
        {
            while ( --j );
        }
        while ( --i );
        n--;
    }
}

/*---------主函数---------*/
void main()
{
    Init();
    while( 1 )
    {
        sbtLedSel = 0;
        for( i = 0; i < 8; i++ )
        {
            P0 = 0;
            P2 = arrDigitSelect[i];     //选择数码管的位数
            P0 = arrSeg7Select[i + 1];  //显示对应的数值
            delay_ms( 1 );
        }
        uiLedCnt++;
        sbtLedSel = 1;
        P0 = uiLed;                     //LED显示
        delay_ms( 1 );                  //延时200ms
        if( uiLedCnt == 50 )
        {
            if( uiLed == 0x80 )        //value等于0x80时，重新赋初值0x01
                uiLed = 0x01;
            else
                uiLed = uiLed << 1;    //value值逐一左移
            uiLedCnt = 0;
        }
    }
}
