/**********************
        三按键测试
型号:STC15F2K60S2 主频:11.0592MHz
************************/
#include <STC15F2K60S2.H>

/*---------引脚别名定义---------*/
sbit sbtKey1 = P3 ^ 2;
sbit sbtKey2 = P3 ^ 3;
sbit sbtKey3 = P1 ^ 7;
sbit sbtLedSel = P2 ^ 3;

/*---------初始化函数---------*/
void Init()
{
    //推挽输出
    P0M0 = 0XFF;
    P0M1 = 0X00;
    P2M0 = 0X08;
    P2M1 = 0X00;
    sbtLedSel = 1;          //选择让LED灯发光,可以不设置，默认为1
    P0 = 0;                 //初始化P0，让LED灯全部熄灭
}

/*---------主函数---------*/
void main()
{
    Init();
    while( 1 )
    {
        if( sbtKey1 == 0 )  //检测按键1是否被按下
            P0 |= 0x01;     //按下则L0发光
        else
            P0 &= ~0x01;    //否则L0熄灭

        if( sbtKey2 == 0 )  //检测按键2是否被按下
            P0 |= 0x02;     //按下则L1发光
        else
            P0 &= ~0x02;    //否则L1熄灭

        if( sbtKey3 == 0 )  //检测按键3是否被按下
            P0 |= 0x04;     //按下则L2发光
        else
            P0 &= ~0x04;    //否则L2熄灭
    }
}
