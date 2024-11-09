/**********************
mySeg7Shift 八位数码管滚动显示
型号:STC15F2K60S2 主频:11.0592MHz
************************/
#include "STC15F2K60S2.H"
#define uint unsigned int
#define uchar unsigned char

/*---------引脚别名定义---------*/
sbit sbtSel0 = P2 ^ 0; //
sbit sbtSel1 = P2 ^ 1; //
sbit sbtSel2 = P2 ^ 2; //位选的三个引脚控制位

/*---------变量定义---------*/
uchar ucDig1Tmp;
uchar ucDig2Tmp;
uchar ucDig3Tmp;
uchar ucDig4Tmp;
uchar ucDig5Tmp;
uchar ucDig6Tmp;
uchar ucDig7Tmp;
uchar ucDig8Tmp;//show_wi(i=1,2,3,4,……,8)分别是对应左到右的各个数码管上的显示的数字
uchar ucSeg7State;
uchar ucCount;
uchar arrSegSelect[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x40, 0x00}; //段选，显示0-f
uchar arrDigSelect[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}; //位选,选择是0-7中的一个数码管

/*---------初始化函数---------*/
void Init()
{
    P2M0 = 0xff;
    P2M1 = 0x00;
    P0M0 = 0xff;
    P0M1 = 0x00; //P0，P2都设置为推挽输出

    ucSeg7State = 0;
    ucCount = 0;

    ucDig1Tmp = 0; //最开始数码管从左到右显示0-7
    ucDig2Tmp = 1;
    ucDig3Tmp = 2;
    ucDig4Tmp = 3;
    ucDig5Tmp = 4;
    ucDig6Tmp = 5;
    ucDig7Tmp = 6;
    ucDig8Tmp = 7;

    TMOD = 0x01;             //定时器0，方式1
    ET0 = 1;                  //开启定时器中断
    TH0 = ( 65535 - 1000 ) / 256; //定时器0的高八位设置
    TL0 = ( 65535 - 1000 ) % 256; //定时器0的低八位设置，这里总体就是设置定时器0的初始值是1ms
    TR0 = 1;                 //启动定时器
    EA = 1;                  //打开总的中断
}

/*---------定时器T0中断服务函数---------*/
void T0_Process() interrupt 1     //把数码管的显示提到中断里面来了
{
    TH0 = ( 65535 - 1000 ) / 256; //重新装载定时器0的初始值，为了下一次定时器溢出准备
    TL0 = ( 65535 - 1000 ) % 256;
    ucSeg7State++;         //这变量两个作用：具有下面分频作用，和扫描过程中显示第ucSeg7State个数码管的作用
    if( ucSeg7State == 8 )    //进行分频，每中断八次才让ucCount的值加一次
    {
        ucSeg7State = 0;
        ucCount++;
    }
    if( ucCount == 100 )     //考虑到扫描频率很高这里再次分频，ucCount加到100才执行
    {
        ucCount = 0;
        ucDig1Tmp++;     //让从左到右各个数码管上的数字都加一
        ucDig2Tmp++;
        ucDig3Tmp++;
        ucDig4Tmp++;
        ucDig5Tmp++;
        ucDig6Tmp++;
        ucDig7Tmp++;
        ucDig8Tmp++;
    }
    P0 = 0;                       //让数码管显示更加好，不受上一次P0赋的值的影响
    P2 = arrDigSelect[ucSeg7State];   //位选，选第ucSeg7State个数码管
    switch( ucSeg7State )           //每次中断显示一个数码管来显示
    {
        case 0:
            P0 = arrSegSelect[ucDig1Tmp % 10];
            break;//从左到右，第一个数码管显示
        case 1:
            P0 = arrSegSelect[ucDig2Tmp % 10];
            break;//从左到右，第二个数码管显示
        case 2:
            P0 = arrSegSelect[ucDig3Tmp % 10];
            break;//从左到右，第三个数码管显示
        case 3:
            P0 = arrSegSelect[ucDig4Tmp % 10];
            break;//从左到右，第四个数码管显示
        case 4:
            P0 = arrSegSelect[ucDig5Tmp % 10];
            break;//从左到右，第五个数码管显示
        case 5:
            P0 = arrSegSelect[ucDig6Tmp % 10];
            break;//从左到右，第六个数码管显示
        case 6:
            P0 = arrSegSelect[ucDig7Tmp % 10];
            break;//从左到右，第七个数码管显示
        default:
            P0 = arrSegSelect[ucDig8Tmp % 10];
            break;//从左到右，第八个数码管显示
    }
}

/*---------主函数---------*/
void main()
{
    Init(); //初始化
    while( 1 )
    {
    }
}
