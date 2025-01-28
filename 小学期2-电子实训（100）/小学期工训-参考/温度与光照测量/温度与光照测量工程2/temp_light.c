/**********************
STC-B_DEMO.c for 温度光照测量工程
型号:STC15F2K60S2 主频:11.0592MHz
************************/
#include <STC15F2K60S2.H>
#define ulint unsigned long
#define uint  unsigned int
#define uchar unsigned char

/*---------宏定义---------*/
#define cstDigBegin   0         // 数码管显示位选起始,用户可修改
#define cstDigEnd     20        // 数码管显示位选终止位。8为发光二极管,大于8 可用于调节显示量度

#define cstDig0       ucDigtmp0 //数码管各位上显示内容数组序号,用户可修改
#define cstDig1       ucDigtmp1 //11代表段选无显示  
#define cstDig2       ucDigtmp2
#define cstDig3       ucDigtmp3
#define cstDig4       ucDigtmp4
#define cstDig5       ucDigtmp5
#define cstDig6       ucDigtmp6
#define cstDig7       ucDigtmp7
#define cstDig8       ucDigtmp8 //流水灯

#define cstClockXmsMaxNum 40 //Xms时钟
#define cstSampleNum 4000  //取多次值求平均值减小误差

/*---------函数声明---------*/
void InitADC();        //初始化ADC切换
void InitAdcTherm();   //初始化温度ADC
void InitAdcPhoto();  //初始化光ADC
void ADC_Process();    //ADC中断服务处理
void Date_ThermToDigit();  //分别取出温度的百位、十位、个位
void Date_PhotoToDigit();  //分别取出光照的百位、十位、个位

void Init();                  //Initial
void T10us_Process();         //Function for 10us
void T100us_Process();        //Function for 100us
void T1ms_Process();          //Function for 1ms
void T10ms_Process();         //Function for 10ms
void T100ms_Process();        //Function for 100ms
void TXms_Process();          //Function for Xms,用户可修改

void Seg7LedDisplay( uchar s, uchar e );  //显示单个数码管或流水灯
void Seg7LedUpdate();                //将显示的数据更新

/*---------变量定义---------*/
//定时器计数时间标志
bit btT10usFlag = 0;      //时基10uS
bit btT100usFlag = 0;     //50个＝5ms单相通电时间
bit btT1msFlag = 0;       //数码管扫描频率节拍
bit btT10msFlag = 0;      //按键消抖节拍
bit btT100msFlag = 0;     //数码管显示数据更新
bit btTXmsFlag = 0;       //4ms温度光照采样切换模式

//定时器内部专用时间计数
uchar ucT10usCnt = 0;    //时基10uS
uchar ucT100usCnt = 0;   //原代码里设想的是5ms 单相通电时间
uchar ucT1msCnt = 0;
uchar ucT10msCnt = 0;
uchar ucT100msCnt = 0;

uchar ucClockXms = 0;     //Xms(本例是计40*100us)
uchar ucLedTmp = 0x00;    //流水灯显示值

uchar ucDigtmp0 = 0;
uchar ucDigtmp1 = 0;
uchar ucDigtmp2 = 0;
uchar ucDigtmp3 = 0;
uchar ucDigtmp4 = 0;
uchar ucDigtmp5 = 0;
uchar ucDigtmp6 = 0;
uchar ucDigtmp7 = 0;
uchar ucDigtmp8 = 0;

uint uiSampleNum = 0;
uint uiState = 1;                      //状态位，区分光和温度

uint uiPhoto = 0;                     //执行光的次数
uint uiTherm = 0;                     //执行温度的次数
ulint ulAdSumPhoto = 0;               //光AD值得总和
ulint ulAdSumTherm = 0;              //温度AD值的总和

uint uiThermTmp;
int intThermLookUp = 0;              //温度值
uint uiThermAbs;                    //温度绝对值
uint uiPhotoTmp = 0;                 //光

//设置用于显示温度的三个变量
uint uiThermDig100 = 0;     //百位
uint uiThermDig10 = 0;      //十位
uint uiThermDig1 = 0;       //个位

//设置用于显示光的三个变量
uint uiPhotoDig100 = 0;    //百位
uint uiPhotoDig10 = 0;     //十位
uint uiPhotoDig1 = 0;      //个位

//数码管上显示0-F
char arrSegSelect[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                       0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
                      };
//温度值对应表
int code arrThermLUT[] = {239, 197, 175, 160, 150, 142, 135, 129, 124, 120, 116, 113, 109, 107, 104, 101,
                          99, 97, 95, 93, 91, 90, 88, 86, 85, 84, 82, 81, 80, 78, 77, 76,
                          75, 74, 73, 72, 71, 70, 69, 68, 67, 67, 66, 65, 64, 63, 63, 62,
                          61, 61, 60, 59, 58, 58, 57, 57, 56, 55, 55, 54, 54, 53, 52, 52,
                          51, 51, 50, 50, 49, 49, 48, 48, 47, 47, 46, 46, 45, 45, 44, 44,
                          43, 43, 42, 42, 41, 41, 41, 40, 40, 39, 39, 38, 38, 38, 37, 37,
                          36, 36, 36, 35, 35, 34, 34, 34, 33, 33, 32, 32, 32, 31, 31, 31,
                          30, 30, 29, 29, 29, 28, 28, 28, 27, 27, 27, 26, 26, 26, 25, 25,
                          24, 24, 24, 23, 23, 23, 22, 22, 22, 21, 21, 21, 20, 20, 20, 19,
                          19, 19, 18, 18, 18, 17, 17, 16, 16, 16, 15, 15, 15, 14, 14, 14,
                          13, 13, 13, 12, 12, 12, 11, 11, 11, 10, 10, 9, 9, 9, 8, 8, 8, 7,
                          7, 7, 6, 6, 5, 5, 54, 4, 3, 3, 3, 2, 2, 1, 1, 1, 0, 0, -1, -1, -1,
                          -2, -2, -3, -3, -4, -4, -5, -5, -6, -6, -7, -7, -8, -8, -9, -9,
                          -10, -10, -11, -11, -12, -13, -13, -14, -14, -15, -16, -16, -17,
                          -18, -19, -19, -20, -21, -22, -23, -24, -25, -26, -27, -28, -29,
                          -30, -32, -33, -35, -36, -38, -40, -43, -46, -50, -55, -63, 361
                         };

/*---------主函数---------*/
void main()
{
    Init();
    ucLedTmp = 0x00;            //流水灯显示值
    while( 1 )
    {
        if( btT10usFlag )
        {
            btT10usFlag = 0;  T10us_Process();
        }
        if( btT100usFlag )
        {
            btT100usFlag = 0;  T100us_Process();
        }
        if( btT1msFlag )
        {
            btT1msFlag = 0;   T1ms_Process();
        }
        if( btT10msFlag )
        {
            btT10msFlag = 0;  T10ms_Process();
        }
        if( btT100msFlag )
        {
            btT100msFlag = 0;  T100ms_Process();
        }
        if( btTXmsFlag  )    //Xms标志位有效代表4ms到了
        {
            btTXmsFlag = 0;   TXms_Process();
        }
    }
}

/*---------T0定时器中断服务处理函数--------*/
void T0_Process() interrupt 1
{
    btT10usFlag = 1;
    ucT10usCnt++;
    if( ucT10usCnt == 10 )
    {
        ucT10usCnt = 0;  btT100usFlag = 1;  ucT100usCnt++;
    }
    if( ucT100usCnt == 10 )
    {
        ucT100usCnt = 0;  btT1msFlag = 1;  ucT1msCnt++;
    }
    if( ucT1msCnt == 10 )
    {
        ucT1msCnt = 0;   btT10msFlag = 1;  ucT10msCnt++;
    }
    if( ucT10msCnt == 10 )
    {
        ucT10msCnt = 0;  btT100msFlag = 1;
    }
}
/*---------初始化函数--------*/
void Init()
{
    //Hardware Init
    P0M1 = 0x00;                 //设置P0为推挽模式，点亮数码管
    P0M0 = 0xff;
    P2M1 = 0x00;
    P2M0 = 0x08;                 //将P2^3设置为推挽模式，其余为准双向口模式

    //Interrupt Init
    /*10微秒@11.0592MHz 16可重载  定时器0     不修改
      ISP软件生成，原来是1ms在11.592MHz 12T模式 */
    AUXR |= 0x80;   //定时器时钟1T模式
    TMOD &= 0xF0;   //设置定时器模式
    TL0 = 0x91;     //设置定时初值
    TH0 = 0xFF;     //设置定时初值
    EA = 1;         //打开总的中断
    ET0 = 1;        //开启定时器中断
    TF0 = 0;        //清除TF0标志
    TR0 = 1;        //启动定时器
}

/*---------各时钟节拍处理函数--------*/
void T10us_Process()
{
}
void T100us_Process()
{
    ucClockXms++;
    if ( ucClockXms == ( cstClockXmsMaxNum ) )
    {
        ucClockXms = 0;  btTXmsFlag = 1;
    }
}
void T1ms_Process()             //1ms适用数码管扫描服务
{
    Seg7LedDisplay( cstDigBegin, cstDigEnd );
}
void T10ms_Process()           //10ms适用按键扫描服务
{
}
void TXms_Process()             //Xms服务,可修改
{
    InitADC();
}
void T100ms_Process()          //100ms适用数据显示更新
{
    Seg7LedUpdate();
}

/*---------数码管与发光二极管显示函数--------*/
void Seg7LedDisplay( uchar s, uchar  e )
{
    unsigned char arrSegSelect[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x40, 0x00}; //  数码管显示译码表
    /* 序号:   0    1    2    3     4    5    6      7     8     9     10   11          */
    /* 显示:   0    1    2    3     4    5    6      7     8     9     -   (无)      */
    static  int  i;
	P0 = 0x00;
    P2 = ( P2 & 0xf0 ) | i;
    switch( i )
    {
        case 0:
            P0 = arrSegSelect[cstDig0];   break;
        case 1:
            P0 = arrSegSelect[cstDig1];   break;
        case 2:
            P0 = arrSegSelect[cstDig2];   break;
        case 3:
            P0 = arrSegSelect[cstDig3];   break;
        case 4:
            P0 = arrSegSelect[cstDig4];   break;
        case 5:
            P0 = arrSegSelect[cstDig5];   break;
        case 6:
            P0 = arrSegSelect[cstDig6];   break;
        case 7:
            P0 = arrSegSelect[cstDig7];   break;
        case 8:
            P0 = cstDig8;   break;
        default:
            P0 = 0x00;     break;
    }
    if( ++i > e ) i = s;
}

/*---------数码管及流水灯上的显示数据更新函数--------*/
void Seg7LedUpdate()
{
    if ( intThermLookUp < 0 )
        ucDigtmp0 = 10;
    else
        ucDigtmp0 = uiThermDig100; //数码管各位上显示内容数组序号,用户可修改
    ucDigtmp1 = uiThermDig10;      //11代表段选无显示
    ucDigtmp2 = uiThermDig1;
    ucDigtmp3 = 11;
    ucDigtmp4 = 11;
    ucDigtmp5 = uiPhotoDig100;
    ucDigtmp6 = uiPhotoDig10;
    ucDigtmp7 = uiPhotoDig1;
    ucDigtmp8 = ucLedTmp;       //流水灯
}

/*---------初始化ADC函数--------*/
void InitADC()
{
    if( uiState == 1 )
    {
        InitAdcPhoto();        //初始化光
    }
    else
    {
        InitAdcTherm();         //初始化温度
    }
    uiState = -uiState;
}
void InitAdcTherm()             //初始化温度ADC
{
    P1ASF = 0xff;               //将P1口作为模拟功能A/D使用
    ADC_RES = 0;               //寄存器ADC_RES和ADC_RESL保存A/D转化结果
    ADC_RESL = 0;              //初始赋值0
    ADC_CONTR = 0x8b;         //选择P1^3作为A/D输入使用
    CLK_DIV = 0x20;             //ADRJ=1存放10位ADC结果
}
void InitAdcPhoto()              //初始化光ADC
{
    P1ASF = 0xff;
    ADC_RES = 0;
    ADC_RESL = 0;
    ADC_CONTR = 0x8c;           //CHS=100选择P1^4作为A/D输入使用
    CLK_DIV = 0x20;
    EADC = 1;
}

/*---------ADC中断子函数--------*/
void ADC_Process() interrupt 5 using 1
{
    uiSampleNum++;
    EA = 0;                          //关闭中断    
    if( uiSampleNum > cstSampleNum )  //取多次值求平均值减小误差
    {
        if( uiState == 1 )              //此时uiState=1执行温度部分
        {
            uiThermTmp = ( ulAdSumTherm + uiTherm / 2 ) / uiTherm; //四舍五入
            intThermLookUp = arrThermLUT[uiThermTmp - 1]; //查找表中AD的温度值
            ulAdSumTherm = 0;
            uiTherm = 0;
            uiSampleNum = 0;
            Date_ThermToDigit();
        }
        if( uiState == -1 )             //此时uiState=-1执行光部分
        {
            uiPhotoTmp = ( ulAdSumPhoto + uiPhoto / 2 ) / uiPhoto;  //四舍五入
            ulAdSumPhoto = 0;
            uiPhoto = 0;
            uiSampleNum = 0;
            Date_PhotoToDigit();
        }
    }

    if( uiState == 1 )
    {
        //对应温度的数据处理
        uiTherm++;
        uiThermTmp = ( ADC_RES * 256 + ADC_RESL ) / 4; //10位AD值转换为8位AD值
        ulAdSumTherm += uiThermTmp;              //AD值的和
    }
    if( uiState == -1 )
    {
        //处理光部分的数据
        uiPhoto++;
        ulAdSumPhoto += ADC_RES * 256 + ADC_RESL; // AD值的和
    }
    ADC_CONTR &= ~0X10;                  //转换完成后，ADC_FLAG清零
    ADC_CONTR |= 0X08;                   //转换完成后，ADC_START赋1
    EA = 1;
    EADC = 1; //打开中断
}

/*---------数据转换子函数--------*/
//分别取出温度和光照的百位、十位、个位
void Date_ThermToDigit()
{
    if( intThermLookUp < 0 )
        uiThermAbs = -intThermLookUp;
    else
        uiThermAbs = intThermLookUp;
    uiThermDig100 = uiThermAbs % 1000 / 100;
    uiThermDig10 = uiThermAbs % 100 / 10;
    uiThermDig1 = uiThermAbs % 10;
}
void Date_PhotoToDigit()
{
    uiPhotoDig100 = uiPhotoTmp % 1000 / 100;
    uiPhotoDig10 = uiPhotoTmp % 100 / 10;
    uiPhotoDig1 = uiPhotoTmp % 10;
}