/**********************
myBeep 蜂鸣器测试
型号:STC15F2K60S2 主频:11.0592MHz
************************/
#include <STC15F2K60S2.H>
#define uint  unsigned int
#define uchar unsigned char

/*---------引脚别名定义---------*/
sbit sbtBeep = P3 ^ 4;                  //蜂鸣器引脚
sbit sbtKey1 = P3 ^ 2;                  //按键1引脚
sbit  a = P3^5;

/*---------变量定义---------*/
bit btBeepFlag;                        //控制蜂鸣器开关的标志位

/*---------初始化函数--------*/
void init()
{
    P3M1 = 0x00;
    P3M0 = 0x10;                  //设置P3^4为推挽模式

    TMOD = 0x00;                  //设置定时器0，工作方式0，16位自动重装定时器
    TH0 = 0xff;                   //设定定时器0的初值
    TL0 = 0x03;
    EA = 1;                       //打开总中断
    ET0 = 1;                      //打开定时器0中断允许位
    TR0 = 1;

    btBeepFlag = 0;                //标志位置1
    P0 = 0x00;                    //关闭P0端口
    sbtBeep = 0;                  //蜂鸣器引脚置0，以保护蜂鸣器	
	  a = 0;	  
}

/*---------延时子函数--------*/
void delay( uint xms )
{
    uchar i;
    for( ; xms > 0; xms-- )
        for( i = 114; i > 0; i-- )
        {
            ;
        }
}

/*---------主函数--------*/
void main()
{
    init();
    while( 1 )
    {
        if( sbtKey1 == 0 )
        {
            delay( 10 );                     //延时消抖
            if( sbtKey1 == 0 )
            {
                while( !sbtKey1 );
                btBeepFlag = ~btBeepFlag;    //蜂鸣器开关标志位翻转
            }
        }
    }
}

/*---------T0定时器中断服务处理函数--------*/
void T0_Process() interrupt 1
{
    if( btBeepFlag )
    {
        sbtBeep = ~sbtBeep;            //产生方波使得蜂鸣器发声
    }
    else
    {
        sbtBeep = 0;                  //停止发声，并将sbtBeep端口置于低电平
    }
}
