/**********************
文件名称：多功能
说明：进行音乐播放的例程,按下key1键后开始播放音乐
***********************/

/**********************
基于STC15F2K60S2系列单片机C语言编程实现
使用如下头文件，不用另外再包含"REG51.H"
***********************/
#include <STC15F2K60S2.h>
#include "oled.h"
#include "bmp.h"
#include "stdlib.h"
#define uint unsigned int
#define uchar unsigned char
sbit beep = P3 ^ 4; //蜂鸣器
sbit key1 = P3 ^ 2; //按键1
sbit key2 = P3 ^ 3; //按键2
sbit key3 = P1 ^ 7; //按键3
u8 line = 0, line_music = 0, music = 0, flag_music = 0, flag_photo = 0, line_game = 0, ji = 0, flag1 = 0, level = 1, cxk = 0, cxk_line = 0;
uchar timeh, timel, gequ = 0, shuma, caidan2 = 0, yinyue2 = 0, zhaopian2 = 0, shipin2 = 0, youxi2 = 0; //定义定时器的重装值
uint jindu = 0, score = 0, score1 = 0;
bit flag, color = 0, game = 0, start_game = 0, end_game = 0; //播放标志位

unsigned char weixuan[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};      //位选码
unsigned char caidan[] = {0x00, 0x00, 0x37, 0x07, 0x7b, 0x37, 0x3e, 0x00};       // MENU
unsigned char yinyue[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f}; // MUSIC
unsigned char zhaopian[] = {0x00, 0x73, 0x76, 0x3f, 0x07, 0x01, 0x3f, 0x00};     // PHOTO
unsigned char shipin1[] = {0x00, 0x00, 0x3e, 0x06, 0x5e, 0x7b, 0x3f, 0x00};      // video
unsigned char youxi1[] = {0x00, 0x00, 0x3d, 0x7b, 0x37, 0x07, 0x7b, 0x00};       // game
unsigned char huanyin[] = {0xbe, 0x0e, 0x7b, 0x38, 0x39, 0x3f, 0x4f, 0x7b};      // welcome

uchar code arrLed[] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff}; // LED 值
uchar code music1[] =                                                         //音乐代码，歌曲为孤勇者，格式为: 音符, 节拍, 音符, 节拍,
    {
        0x16, 0x08, 0x17, 0x08,
        0x21, 0x08, 0x22, 0x08,
        0x17, 0x08, 0x21, 0x08,
        0x21, 0x10, 0x21, 0x08,
        0x17, 0x08, 0x21, 0x08,
        0x22, 0x08, 0x17, 0x08,
};
uchar code music2[] = //歌曲为稻香
    {
        0x21, 0x06,
        0x21, 0x06,
        0x16, 0x06,
        0x21, 0x0C,
        0x16, 0x06,
        0x21, 0x06};
uchar code music3[] = //歌曲为晴天
    {
        0x25,
        0x10,
        0x25,
};
uchar code music4[] = //演员
    {
        0x15, 0x0C,
        0x24, 0x0C,
        0x23, 0x0C,
        0x23, 0x14,
};
uchar code quzi[] = //此数组数据为各个音符在定时器中的重装值，第一列是高位，第二列是低位	//时间
    {
        0xf8, 0x8c, //低八度，低1
        0xf9, 0x5b,
        0xfa, 0x15, //低3
        0xfa, 0x67,
        0xfb, 0x04, //低5
        0xfb, 0x90,
        0xfc, 0x0c, //低7
        0xfc, 0x44, //中央C调
        0xfc, 0xac, //中2
        0xfd, 0x09,
        0xfd, 0x34, //中4
        0xfd, 0x82,
        0xfd, 0xc8, //中6
        0xfe, 0x06,
        0xfe, 0x22, //高八度，高1
        0xfe, 0x56,
        0xfe, 0x6e, //高3
        0xfe, 0x9a,
        0xfe, 0xc1, //高5
        0xfe, 0xe4,
        0xff, 0x03 //高7
};

void display4()
{
    OLED_ShowCHinese(0, 5, 23);  //
    OLED_ShowCHinese(16, 5, 24); //
    OLED_ShowCHinese(32, 5, 25); //
    OLED_ShowCHinese(48, 5, 26); //正在播放
    OLED_ShowChar(64, 5, '-', 16);
}
void vedio()
{
    while (1)
    {
        OLED_DrawBMP1(32, 0, 64, 64, cxk1_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk2_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk3_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk4_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk5_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk6_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk7_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk8_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk9_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk10_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk11_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk12_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk13_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk14_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk15_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk16_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk17_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk18_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk19_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk20_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk21_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk22_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk23_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk24_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk25_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk26_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk27_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk28_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk29_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk30_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk31_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk32_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk33_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk34_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk35_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk36_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk37_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk38_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk39_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk40_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk41_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk42_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk43_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk44_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk45_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
        OLED_DrawBMP1(32, 0, 64, 64, cxk46_64x64);
        if (key3 == 0)
            break;
        delay_ms(30);
    }
}
/**********************
函数名称：void delay(unsigned int xms)
功能描述：延时
入口参数：xms：输入需要延时的毫秒值
出口参数：无
备注：

***********************/
void delay(unsigned int xms)
{
    uint i, j;
    for (i = xms; i > 0; i--)
        for (j = 124; j > 0; j--)
            ;
}
/**********************
函数名称：uchar quyin(uchar tem)
功能描述：在quzi数组中，找到music数组定义的简谱音符的重装值，并返回其在quzi数组中的位置
入口参数：tem：music数组中定义的简谱音符
出口参数：返回的是tem音符在quzi数组中的位置值
备注：

***********************/
uchar quyin(uchar tem)
{
    uchar qudiao, jp, weizhi; //定义曲调，音符和位置
    qudiao = tem / 16;        //高4位是曲调值
    jp = tem % 16;            //低4位是音符
    if (qudiao == 1)          //当曲调值为1时，即是低八度，低八度在quzi数组中基址为0
        qudiao = 0;
    else if (qudiao == 2) //当曲调值为2时，即是中八度，中八度在quzi数组中基址为14
        qudiao = 14;
    else if (qudiao == 3) //当曲调值为3时，即是高八度，高八度在quzi数组中，基址为28
        qudiao = 28;
    weizhi = qudiao + (jp - 1) * 2; //通过基址加上音符作为偏移量，即可定位此音符在quzi数组中的位置
    return weizhi;                  //返回这一个位置值
}
/**********************
函数名称：void playmusic()
功能描述：播放音乐
入口参数：无
出口参数：无
备注：

***********************/
void playmusic()
{
    uchar p, m, tem; // m为节拍
    music = 1;
    OLED_Clear();
    flag = 1;
    while (key1 == 1 && key3 == 1)
    {
        while (flag == 1) //若播放的标志位为1则播放音乐
        {
            if (gequ == 0) //歌曲选择位为0，则播放孤勇者
            {
                p = music1[jindu];
                if (p == 0x00) //如果碰到结束符,延时1秒,回到开始再来一遍
                {
                    jindu = 0;
                    delay(1000);
                    break;
                }
                else if (p == 0xff) //若碰到休止符,延时100ms,继续取下一音符
                {
                    jindu = jindu + 1;
                    delay(100);
                    TR0 = 0;
                    break;
                }
                else //正常情况下取音符和节拍
                {
                    tem = quyin(music1[jindu]); //取出当前音符在quzi数组中的位置值
                    timeh = quzi[tem];          //把音符相应的计时器重装载值赋予timeh和timel
                    timel = quzi[tem + 1];
                    jindu++;
                    TH0 = timeh; //把timeh和timel赋予计时器
                    TL0 = timel;
                    m = music1[jindu]; //取得节拍
                    jindu++;
                }
                TR0 = 1;        //开定时器1
                delay(m * 180); //等待节拍完成, 通过P3^4口输出音频
                TR0 = 0;        //关定时器1
                beep = 0;       //使beep端口置0，起保护蜂鸣器作用
            }
            else if (gequ == 1) //歌曲选择位为1，则播放稻香
            {
                p = music2[jindu];
                if (p == 0x00) //如果碰到结束符,延时1秒,回到开始再来一遍
                {
                    jindu = 0;
                    delay(1000);
                    break;
                }
                else if (p == 0xff) //若碰到休止符,延时100ms,继续取下一音符
                {
                    jindu = jindu + 1;
                    delay(100);
                    TR0 = 0;
                    break;
                }
                else //正常情况下取音符和节拍
                {
                    tem = quyin(music2[jindu]); //取出当前音符在quzi数组中的位置值
                    timeh = quzi[tem];          //把音符相应的计时器重装载值赋予timeh和timel
                    timel = quzi[tem + 1];
                    jindu++;
                    TH0 = timeh; //把timeh和timel赋予计时器
                    TL0 = timel;
                    m = music2[jindu]; //取得节拍
                    jindu++;
                }
                TR0 = 1;        //开定时器1
                delay(m * 300); //等待节拍完成, 通过P3^4口输出音频
                TR0 = 0;        //关定时器1
                beep = 0;       //使beep端口置0，起保护蜂鸣器作用
            }
            else if (gequ == 2) //歌曲选择位为2，则播放晴天
            {
                p = music3[jindu];
                if (p == 0x00) //如果碰到结束符,延时1秒,回到开始再来一遍
                {
                    jindu = 0;
                    delay(1000);
                    break;
                }
                else if (p == 0xff) //若碰到休止符,延时100ms,继续取下一音符
                {
                    jindu = jindu + 1;
                    delay(100);
                    TR0 = 0;
                    break;
                }
                else //正常情况下取音符和节拍
                {
                    tem = quyin(music3[jindu]); //取出当前音符在quzi数组中的位置值
                    timeh = quzi[tem];          //把音符相应的计时器重装载值赋予timeh和timel
                    timel = quzi[tem + 1];
                    jindu++;
                    TH0 = timeh; //把timeh和timel赋予计时器
                    TL0 = timel;
                    m = music3[jindu]; //取得节拍
                    jindu++;
                }
                TR0 = 1;        //开定时器1
                delay(m * 200); //等待节拍完成, 通过P3^4口输出音频
                TR0 = 0;        //关定时器1
                beep = 0;       //使beep端口置0，起保护蜂鸣器作用
            }
            else if (gequ == 3) //歌曲选择位为3，则播放演员
            {
                p = music4[jindu];
                if (p == 0x00) //如果碰到结束符,延时1秒,回到开始再来一遍
                {
                    jindu = 0;
                    delay(1000);
                    break;
                }
                else if (p == 0xff) //若碰到休止符,延时100ms,继续取下一音符
                {
                    jindu = jindu + 1;
                    delay(100);
                    TR0 = 0;
                    break;
                }
                else //正常情况下取音符和节拍
                {
                    tem = quyin(music4[jindu]); //取出当前音符在quzi数组中的位置值
                    timeh = quzi[tem];          //把音符相应的计时器重装载值赋予timeh和timel
                    timel = quzi[tem + 1];
                    jindu++;
                    TH0 = timeh; //把timeh和timel赋予计时器
                    TL0 = timel;
                    m = music4[jindu]; //取得节拍
                    jindu++;
                }
                TR0 = 1;        //开定时器1
                delay(m * 200); //等待节拍完成, 通过P3^4口输出音频
                TR0 = 0;        //关定时器1
                beep = 0;       //使beep端口置0，起保护蜂鸣器作用
            }
        }
        if (flag != 1) //播放标志位不为1时，暂停播放音乐
        {
            while (flag != 1)
                ;
        }
    }
}
/**********************
函数名称：void init_sys()
功能描述：系统初始化，功能是配置IO口
入口参数：无
出口参数：无
备注：

***********************/
void init_sys()
{
    P0M0 = 0xff; //设置推挽模式
    P0M1 = 0x00;
    P2M0 = 0x08;
    P2M1 = 0x00;
    P3M0 = 0x10;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
}
void clear_line()
{
    OLED_ShowCHinese(0, 6, 16);
    OLED_ShowCHinese(16, 6, 16);
    OLED_ShowCHinese(32, 6, 16);
    OLED_ShowCHinese(48, 6, 16);
    OLED_ShowCHinese(64, 6, 16);
    OLED_ShowCHinese(80, 6, 16);
    OLED_ShowCHinese(96, 6, 16);
    OLED_ShowCHinese(112, 6, 16);
}
/**********************
函数名称：void init()
功能描述：定时器和外部中断的初始化
入口参数：无
出口参数：无
备注：

***********************/
void init()
{
    TMOD = 0x01; //设置定时器0，定时方式1，16位手动重装模式
    TH0 = 0xD8;  //设置定时初值
    TL0 = 0xEF;
    TH1 = (65536 - 1000) / 256; //ÉèÖÃ¶¨Ê±Æ÷1³õÖµ
    TL1 = (65536 - 1000) % 256;
    IE = 0x87; // 1000 0111  EA=1,EX0=1,ET0=1,EX1=0;
    EA = 1;    //´ò¿ª×ÜÖÐ¶Ï
    ET0 = 1;   //´ò¿ª¶¨Ê±Æ÷0ÖÐ¶Ï
    ET1 = 1;   //´ò¿ª¶¨Ê±Æ÷1ÖÐ¶Ï
    TR1 = 1;   //Æô¶¯¶¨Ê±Æ÷1
    EX0 = 1;   //Æô¶¯Íâ²¿ÖÐ¶Ï0
    IP = 0x02; // 0000 0010  PT0=1;   定时器0优先级高
    TR0 = 0;   //定时器0开始运行
    beep = 0;  //使beep端口置0，起保护蜂鸣器作用
}

void TEST_MainPage(void)
{
    OLED_Clear();
    if (gequ == 0)
    {
        clear_line();
        display4();
        OLED_ShowCHinese(74, 5, 11);  //
        OLED_ShowCHinese(92, 5, 12);  //
        OLED_ShowCHinese(110, 5, 13); //孤勇者
        OLED_DrawBMP1(0, 0, 128, 32, BMP1);
    }
    else if (gequ == 1)
    {
        clear_line();
        display4();
        OLED_ShowCHinese(82, 5, 17);  //
        OLED_ShowCHinese(110, 5, 18); //稻香
        OLED_DrawBMP1(0, 0, 128, 32, BMP1);
    }
    else if (gequ == 2)
    {
        clear_line();
        display4();
        OLED_ShowCHinese(82, 5, 19);  //
        OLED_ShowCHinese(110, 5, 20); //晴天
        OLED_DrawBMP1(0, 0, 128, 32, BMP1);
    }
    else if (gequ == 3)
    {
        clear_line();
        display4();
        OLED_ShowCHinese(82, 5, 36);  //
        OLED_ShowCHinese(110, 5, 37); //演员
        OLED_DrawBMP1(0, 0, 128, 32, BMP1);
    }
    delay_ms(300);
}

void gunndong()
{
    OLED_Clear();
    OLED_WR_Byte(0x2E, OLED_CMD); //关闭滚动
    OLED_WR_Byte(0x27, OLED_CMD); //水平向左或者右滚动 26/27
    OLED_WR_Byte(0x00, OLED_CMD); //虚拟字节
    OLED_WR_Byte(0x00, OLED_CMD); //起始页 0
    OLED_WR_Byte(0x07, OLED_CMD); //滚动时间间隔
    OLED_WR_Byte(0x07, OLED_CMD); //终止页 7
    OLED_WR_Byte(0x00, OLED_CMD); //虚拟字节
    OLED_WR_Byte(0xFF, OLED_CMD); //虚拟字节
    TEST_MainPage();
    OLED_WR_Byte(0x2F, OLED_CMD); //开启滚动
}
void touzi1()
{
    OLED_DrawBMP1(50, 0, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p4);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p3);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p6);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p2);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p5);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p4);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p6);
    delay_ms(70);
    OLED_DrawBMP1(50, 0, 25, 25, p3);
    delay_ms(70);
}
void touzi2()
{
    OLED_DrawBMP1(25, 4, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p4);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p3);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p6);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p2);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p5);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p4);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p6);
    delay_ms(70);
    OLED_DrawBMP1(25, 4, 25, 25, p3);
    delay_ms(70);
}
void touzi3()
{
    OLED_DrawBMP1(75, 4, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p4);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p3);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p6);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p2);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p5);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p4);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p1);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p6);
    delay_ms(70);
    OLED_DrawBMP1(75, 4, 25, 25, p3);
    delay_ms(70);
}
void tz_show1(unsigned int n)
{
    if (n == 1)
        OLED_DrawBMP1(50, 0, 25, 25, p1);
    if (n == 2)
        OLED_DrawBMP1(50, 0, 25, 25, p2);
    if (n == 3)
        OLED_DrawBMP1(50, 0, 25, 25, p3);
    if (n == 4)
        OLED_DrawBMP1(50, 0, 25, 25, p4);
    if (n == 5)
        OLED_DrawBMP1(50, 0, 25, 25, p5);
    if (n == 6)
        OLED_DrawBMP1(50, 0, 25, 25, p6);
}
void tz_show2(unsigned int n)
{
    if (n == 1)
        OLED_DrawBMP1(25, 4, 25, 25, p1);
    if (n == 2)
        OLED_DrawBMP1(25, 4, 25, 25, p2);
    if (n == 3)
        OLED_DrawBMP1(25, 4, 25, 25, p3);
    if (n == 4)
        OLED_DrawBMP1(25, 4, 25, 25, p4);
    if (n == 5)
        OLED_DrawBMP1(25, 4, 25, 25, p5);
    if (n == 6)
        OLED_DrawBMP1(25, 4, 25, 25, p6);
}
void tz_show3(unsigned int n)
{
    if (n == 1)
        OLED_DrawBMP1(75, 4, 25, 25, p1);
    if (n == 2)
        OLED_DrawBMP1(75, 4, 25, 25, p2);
    if (n == 3)
        OLED_DrawBMP1(75, 4, 25, 25, p3);
    if (n == 4)
        OLED_DrawBMP1(75, 4, 25, 25, p4);
    if (n == 5)
        OLED_DrawBMP1(75, 4, 25, 25, p5);
    if (n == 6)
        OLED_DrawBMP1(75, 4, 25, 25, p6);
}
void main()
{
    u32 tz1, tz2, tz3, ii;
    OLED_Init();
    OLED_Clear();
    init_sys(); //系统初始化
    init();
    P0 = 0x00;
    key1 = 1; //两个按键设为输入状态，检测中断
    key2 = 1;
    flag = 0; //播放标志位清零
    caidan2 = 0;
    yinyue2 = 0;
    zhaopian2 = 0;
    shipin2 = 0;
    youxi2 = 0;
    shuma = 0;
    music = 0;
    while (1)
    {
        OLED_DrawBMP(0, 0, 128, 6, BMP0);
        OLED_ShowString(0, 6, "HUNAN UNIVERSITY", 16);
        if (key1 == 0)
        {
            caidan2 = 1;
            OLED_Clear();
            while (1)
            {

                while (1)
                {
                    if (line == 0)
                    {
                        OLED_DrawBMP(0, 0, 128, 8, music_bmp);
                    }
                    else if (line == 1)
                    {
                        OLED_DrawBMP(0, 0, 128, 8, photo);
                    }
                    else if (line == 2)
                    {
                        OLED_DrawBMP(0, 0, 128, 8, shipin);
                    }
                    else if (line == 3)
                    {
                        OLED_DrawBMP(0, 0, 128, 8, youxi);
                    }
                    if (key1 == 0)
                    {
                        delay_ms(25);
                        if (key1 == 0)
                        {
                            if (line == 3)
                            {
                                line = 0;
                            }
                            else
                            {
                                line = line + 1;
                            }
                        }
                    }
                    if (key3 == 0)
                    {
                        OLED_Clear();
                        break;
                    }
                    if (key2 == 0)
                    {
                        if (line == 0) //音乐
                        {
                            OLED_Clear();
                            yinyue2 = 1;
                            gunndong();
                            playmusic();
                            music = 0;
                            P0 = 0x00;
                            OLED_Clear();
                            yinyue2 = 0;
                            break;
                        }
                        else if (line == 2) //视频
                        {
                            OLED_Clear();
                            shipin2 = 1;
                            vedio();
                            shipin2 = 0;
                        }
                        else if (line == 1) //图片
                        {
                            OLED_Clear();
                            zhaopian2 = 1;
                            while (1)
                            {
                                OLED_ColorTurn(color);
                                if (key1 == 0)
                                {
                                    OLED_Clear();
                                    flag_photo++;
                                    if (flag_photo == 3)
                                    {
                                        flag_photo = 0;
                                    }
                                }
                                if (key2 == 0)
                                {
                                    color = ~color;
                                }
                                if (key3 == 0)
                                {
                                    zhaopian2 = 0;
                                    break;
                                }
                                if (flag_photo == 0)
                                {
                                    OLED_DrawBMP(0, 2, 128, 8, BMP2);
                                }
                                else if (flag_photo == 1)
                                {
                                    OLED_DrawBMP(0, 0, 128, 8, BMP3);
                                }
                                else
                                    OLED_DrawBMP(0, 0, 128, 8, BMP4);
                            }
                        }
                        else if (line == 3) //游戏
                        {
                            OLED_Clear();
                            youxi2 = 1;
                            while (1)
                            {
                                OLED_ShowCHinese(0, 2, 9);
                                OLED_ShowCHinese(0, 5, 10);
                                OLED_ShowNum(48, 2, 1, 1, 16);
                                OLED_ShowChar(56, 2, '.', 16);
                                OLED_ShowCHinese(64, 2, 43);
                                OLED_ShowCHinese(80, 2, 44);
                                OLED_ShowCHinese(96, 2, 45);
                                OLED_ShowNum(48, 5, 2, 1, 16);
                                OLED_ShowChar(56, 5, '.', 16);
                                OLED_ShowCHinese(64, 5, 46);
                                OLED_ShowCHinese(80, 5, 47);
                                OLED_ShowCHinese(96, 5, 48);
                                OLED_ShowCHinese(112, 5, 49);

                                if (key1 == 0)
                                {
                                    delay_ms(50);
                                    if (key1 == 0)
                                    {
                                        if (line_game == 0)
                                        {
                                            line_game = 1;
                                        }
                                        else if (line_game == 1)
                                        {
                                            line_game = 0;
                                        }
                                    }
                                }
                                if (line_game == 0)
                                {
                                    OLED_ShowCHinese(30, 2, 16);
                                    OLED_ShowCHinese(30, 5, 15);
                                }
                                else if (line_game == 1)
                                {
                                    OLED_ShowCHinese(30, 5, 16);
                                    OLED_ShowCHinese(30, 2, 15);
                                }
                                if (key3 == 0)
                                {
                                    youxi2 = 0;
                                    break;
                                }
                                if (key2 == 0)
                                {
                                    if (line_game == 1)
                                    {
                                        OLED_Clear();
                                        game = 0;
                                        start_game == 0;
                                        end_game = 0;
                                        OLED_ShowCHinese(6, 2, 31);
                                        while (1)
                                        {
                                            OLED_ShowCHinese(0, 0, 29);
                                            OLED_ShowCHinese(16, 0, 30);
                                            OLED_ShowNum(32, 0, 1, 1, 16);//玩家1
                                            OLED_ShowCHinese(85, 0, 29);
                                            OLED_ShowCHinese(101, 0, 30);
                                            OLED_ShowNum(117, 0, 2, 1, 16);//玩家2
                                            OLED_DrawBMP1(50, 0, 25, 25, p2);
                                            OLED_DrawBMP1(25, 4, 25, 25, p3);
                                            OLED_DrawBMP1(75, 4, 25, 25, p4);//三张骰子图
                                            if (key3 == 0 && game == 0)
                                            {
                                                delay_ms(50);
                                                if (key3 == 0 && game == 0)
                                                {
                                                    OLED_ShowCHinese(6, 2, 32);
                                                    OLED_ShowCHinese(105, 2, 31);
                                                    game = 1;
                                                }
                                            }
                                            if (key2 == 0 && game == 0)
                                            {
                                                delay_ms(50);
                                                if (key2 == 0 && game == 0)
                                                {
                                                    OLED_ShowCHinese(6, 2, 33);
                                                    OLED_ShowCHinese(105, 2, 31);
                                                    game = 1;
                                                }
                                            }
                                            if (key3 == 0 && game == 1)
                                            {
                                                delay_ms(100);
                                                if (key3 == 0 && game == 1)
                                                {
                                                    OLED_ShowCHinese(105, 2, 32);
                                                    start_game = 1;
                                                }
                                            }
                                            if (key2 == 0 && game == 1)
                                            {
                                                delay_ms(100);
                                                if (key2 == 0 && game == 1)
                                                {
                                                    OLED_ShowCHinese(105, 2, 33);
                                                    start_game = 1;
                                                }
                                            }
                                            if (start_game == 1 && end_game == 0)
                                            {
                                                score = 0;
                                                OLED_ShowNum(55, 4, score, 2, 16);//显示点数
                                                tz1 = (rand() % (6 - 1 + 1)) + 1;
                                                tz2 = (rand() % (6 - 1 + 1)) + 1;
                                                tz3 = (rand() % (6 - 1 + 1)) + 1;
                                                OLED_ShowNum(55, 4, score, 2, 16);
                                                touzi1();
                                                tz_show1(tz1);
                                                score += tz1;
                                                OLED_ShowNum(55, 4, score, 2, 16);
                                                score += tz2;
                                                touzi2();
                                                tz_show2(tz2);
                                                OLED_ShowNum(55, 4, score, 2, 16);
                                                score += tz3;
                                                touzi3();
                                                tz_show3(tz3);
                                                OLED_ShowNum(55, 4, score, 2, 16);
                                                if (11 <= score && score <= 18)
                                                {
                                                    OLED_ShowCHinese(55, 6, 32);//显示大
                                                }
                                                else
                                                {
                                                    OLED_ShowCHinese(55, 6, 33);//显示小
                                                }
                                                start_game = ~start_game;
                                                delay_ms(3000);
                                                end_game = 1;
                                            }
                                            if (end_game == 1)
                                            {
                                                youxi2 = 0;
                                                OLED_Clear();
                                                break;
                                            }
                                        }
                                    }
                                    else if (line_game == 0)
                                    {
                                        OLED_Clear();
                                        while (1)
                                        {
                                            OLED_ShowCHinese(0, 0, 81);
                                            OLED_ShowCHinese(0, 2, 82);
                                            OLED_ShowCHinese(0, 4, 83);
                                            OLED_ShowCHinese(0, 6, 84);
                                            OLED_ShowCHinese(80, 0, 85);
                                            OLED_ShowCHinese(100, 0, 86);
                                            OLED_ShowCHinese(80, 2, 87);
                                            OLED_ShowCHinese(100, 2, 88);
                                            OLED_ShowCHinese(80, 4, 89);
                                            OLED_ShowCHinese(100, 4, 90);
                                            OLED_ShowCHinese(80, 6, 91);
                                            OLED_ShowCHinese(100, 6, 92);
                                            if (cxk_line == 0)
                                            {
                                                OLED_ShowCHinese(60, 6, 16);
                                                OLED_ShowCHinese(60, 0, 15);
                                            }
                                            else if (cxk_line == 1)
                                            {
                                                OLED_ShowCHinese(60, 0, 16);
                                                OLED_ShowCHinese(60, 2, 15);
                                            }
                                            else if (cxk_line == 2)
                                            {
                                                OLED_ShowCHinese(60, 2, 16);
                                                OLED_ShowCHinese(60, 4, 15);
                                            }
                                            else if (cxk_line == 3)
                                            {
                                                OLED_ShowCHinese(60, 4, 16);
                                                OLED_ShowCHinese(60, 6, 15);
                                            }
                                            if (key1 == 0)
                                            {
                                                delay_ms(50);
                                                if (key1 == 0)
                                                {
                                                    cxk_line++;
                                                    if (cxk_line == 4)
                                                    {
                                                        cxk_line = 0;
                                                    }
                                                }
                                            }
                                            if (key3 == 0)
                                            {
                                                OLED_Clear();
                                                break;
                                            }
                                            if (key2 == 0)
                                            {
                                                OLED_Clear();
                                                flag1 = 0;
                                                score = 0;
                                                ji = 0;
                                                OLED_DrawBMP1(0, 2, 32, 32, pp3);
                                                while (1)
                                                {
                                                    OLED_ShowCHinese(20, 0, 46);
                                                    OLED_ShowCHinese(40, 0, 47);
                                                    OLED_ShowCHinese(60, 0, 48);
                                                    OLED_ShowCHinese(80, 0, 49);
                                                    OLED_ShowNum(85, 6, score1, 2, 16);
                                                    for (ii = 0; ii < 10; ii++)
                                                    {
                                                        if (cxk_line == 0)
                                                        {
                                                            level = 0;
                                                        }
                                                        else if (cxk_line == 1)
                                                        {
                                                            level = 3;
                                                        }
                                                        else if (cxk_line == 2)
                                                        {
                                                            level = 6;
                                                        }
                                                        else if (cxk_line == 3)
                                                        {
                                                            cxk_line = (rand() % (6 - 1 + 1)) + 1;
                                                        }
                                                        OLED_ShowCHinese(45, 6, 52);
                                                        OLED_ShowCHinese(61, 6, 53);
                                                        OLED_ShowChar(77, 6, ':', 16);
                                                        for (ji = 112; ji >= 16; ji -= 16)
                                                        {
                                                            OLED_DrawBMP1(ji, 3, 16, 16, pp1);
                                                            OLED_DrawBMP1(ji + 16, 3, 16, 16, pp2);
                                                            delay_ms(200 - level * 20);

                                                            OLED_DrawBMP1(0, 2, 32, 32, pp3);
                                                            if (key2 == 0)
                                                            {
                                                                delay_ms(10);
                                                                if (key2 == 0)
                                                                {
                                                                    OLED_DrawBMP1(0, 2, 32, 32, pp5);
                                                                    if (16 <= ji && ji <= 32)
                                                                    {
                                                                        score1++;
                                                                    }
                                                                    delay_ms(10);
                                                                    OLED_DrawBMP1(0, 2, 32, 32, pp3);
                                                                }
                                                            }
                                                        }
                                                        OLED_ShowNum(85, 6, score1, 2, 16);
                                                    }
                                                    if (score1 >= 8)
                                                    {
                                                        OLED_ShowNum(60, 3, 3, 1, 16);
                                                        delay_ms(500);
                                                        OLED_ShowNum(60, 3, 2, 1, 16);
                                                        delay_ms(500);
                                                        OLED_ShowNum(60, 3, 1, 1, 16);
                                                        delay_ms(500);
                                                        OLED_ShowCHinese(60, 3, 16);
                                                        score1 = 0;
                                                        cxk_line=0;
                                                        OLED_Clear();
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        OLED_ShowCHinese(40, 4, 38);
                                                        OLED_ShowCHinese(60, 4, 39);
                                                        OLED_ShowCHinese(80, 4, 40);
                                                        delay_ms(500);
                                                        delay_ms(500);
                                                        delay_ms(500);
                                                        score1=0;
                                                        cxk_line=0;
                                                        OLED_Clear();
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                caidan2 = 0;
                break;
            }
            OLED_WR_Byte(0x2E, OLED_CMD); //关闭滚动
        }
        if (key3 == 0)
        {
            OLED_Clear();
            while (1)
            {
                if (cxk == 0)
                {
                    OLED_ShowCHinese(8, 1, 55);
                    OLED_ShowCHinese(24, 1, 56);
                    OLED_ShowCHinese(40, 1, 57);
                    OLED_ShowCHinese(56, 1, 58);
                    OLED_ShowCHinese(72, 1, 59);
                    OLED_ShowCHinese(86, 1, 60);
                    OLED_ShowCHinese(102, 1, 61);
                    OLED_ShowCHinese(8, 5, 62);
                    OLED_ShowCHinese(24, 5, 63);
                    OLED_ShowCHinese(40, 5, 64);
                    OLED_ShowCHinese(56, 5, 65);
                    OLED_ShowCHinese(72, 5, 66);
                    OLED_ShowCHinese(86, 5, 67);
                    OLED_ShowCHinese(102, 5, 68);
                }
                else if (cxk == 1)
                {
                    OLED_ShowCHinese(8, 1, 69);
                    OLED_ShowCHinese(24, 1, 70);
                    OLED_ShowCHinese(40, 1, 71);
                    OLED_ShowCHinese(56, 1, 72);
                    OLED_ShowCHinese(72, 1, 73);
                    OLED_ShowCHinese(86, 1, 74);
                    OLED_ShowCHinese(102, 1, 75);
                    OLED_ShowCHinese(8, 5, 76);
                    OLED_ShowCHinese(24, 5, 77);
                    OLED_ShowCHinese(40, 5, 16);
                    OLED_ShowCHinese(56, 5, 16);
                    OLED_ShowString(44, 5, "RAP", 16);
                    OLED_ShowCHinese(72, 5, 78);
                    OLED_ShowCHinese(86, 5, 79);
                    OLED_ShowCHinese(102, 5, 80);
                }
                if (key1 == 0)
                {
                    delay_ms(25);
                    if (key1 == 0)
                    {
                        cxk++;
                        if (cxk == 2)
                        {
                            cxk = 0;
                        }
                    }
                }
                if (key2 == 0)
                {
                    OLED_Clear();
                    break;
                }
            }
        }
    }
}
/**********************
函数名称：void tim1() interrupt 1
功能描述：定时器0中断处理，重新装值，并把beep值取反，产生方波
入口参数：无
出口参数：无
备注：

***********************/
void tim1() interrupt 1 //计时器控制频率
{
    TH0 = timeh; //赋初值
    TL0 = timel;
    beep = ~beep; //中断使得beep翻转产生方波
}
/**********************
函数名称：void ex1() interrupt 0
功能描述：按下按键1的外部中断，对标志位取反，功能是暂停和播放音乐
入口参数：无
出口参数：无
备注：

***********************/
void ex1() interrupt 0
{
    if (key3 == 0)
    {
        delay_ms(50);
        if (key3 == 0)
        {
            while (!key3)
                ;
            flag = ~flag;
        }
    }
}
/**********************
函数名称：void ex2() interrupt 2
功能描述：按下按键2的外部中断，作用为切换歌曲
入口参数：无
出口参数：无
备注：

***********************/
void ex2() interrupt 2
{
    delay(5);
    if (key2 == 0 && music == 1) //按键key2按下，切换歌曲
    {
        jindu = 0; //歌曲的进度清零，从头开始演唱
        gequ++;    //下一曲
        flag_music = 0;
        if (gequ == 4) //到达最后一首调到第一首
            gequ = 0;
        gunndong();
    }
}

void timer1() interrupt 3
{
    shuma++;
    if (shuma == 8)
    {
        shuma = 0;
    }
    P0 = 0;
    P2 = weixuan[shuma];
    switch (shuma)
    {
    case 0:
        P0 = huanyin[0];
        break;
    case 1:
        P0 = huanyin[1];
        break;
    case 2:
        P0 = huanyin[2];
        break;
    case 3:
        P0 = huanyin[3];
        break;
    case 4:
        P0 = huanyin[4];
        break;
    case 5:
        P0 = huanyin[5];
        break;
    case 6:
        P0 = huanyin[6];
        break;
    case 7:
        P0 = huanyin[7];
        break;
    default:
        P0 = huanyin[7];
        break;
    }
    if (caidan2 == 1)
    {
        switch (shuma)
        {
        case 2:
            P0 = caidan[2];
            break;
        case 3:
            P0 = caidan[3];
            break;
        case 4:
            P0 = caidan[4];
            break;
        case 5:
            P0 = caidan[5];
            break;
        case 6:
            P0 = caidan[6];
            break;
        default:
            P0 = caidan[0];
            break;
        }
    }
    if (yinyue2 == 1)
    {
        switch (shuma)
        {
        case 0:
            P0 = yinyue[jindu & 8];
            break;
        case 1:
            P0 = yinyue[(jindu + 1) % 8];
            break;
        case 2:
            P0 = yinyue[(jindu + 2) % 8];
            break;
        case 3:
            P0 = yinyue[(jindu + 3) % 8];
            break;
        case 4:
            P0 = yinyue[(jindu + 4) % 8];
            break;
        case 5:
            P0 = yinyue[(jindu + 5) % 8];
            break;
        case 6:
            P0 = yinyue[(jindu + 6) % 8];
            break;
        case 7:
            P0 = yinyue[(jindu + 7) % 8];
            break;
        default:
            P0 = yinyue[(jindu + 8) % 8];
            break;
        }
    }
    if (zhaopian2 == 1)
    {
        switch (shuma)
        {
        case 1:
            P0 = zhaopian[1];
            break;
        case 2:
            P0 = zhaopian[2];
            break;
        case 3:
            P0 = zhaopian[3];
            break;
        case 4:
            P0 = zhaopian[4];
            break;
        case 5:
            P0 = zhaopian[5];
            break;
        case 6:
            P0 = zhaopian[6];
            break;
        default:
            P0 = zhaopian[7];
            break;
        }
    }
    if (shipin2 == 1)
    {
        switch (shuma)
        {
        case 2:
            P0 = shipin1[2];
            break;
        case 3:
            P0 = shipin1[3];
            break;
        case 4:
            P0 = shipin1[4];
            break;
        case 5:
            P0 = shipin1[5];
            break;
        case 6:
            P0 = shipin1[6];
            break;
        default:
            P0 = shipin1[7];
            break;
        }
    }
    if (youxi2 == 1)
    {
        switch (shuma)
        {
        case 2:
            P0 = youxi1[2];
            break;
        case 3:
            P0 = youxi1[3];
            break;
        case 4:
            P0 = youxi1[4];
            break;
        case 5:
            P0 = youxi1[5];
            break;
        case 6:
            P0 = youxi1[6];
            break;
        default:
            P0 = shipin1[7];
            break;
        }
    }
}