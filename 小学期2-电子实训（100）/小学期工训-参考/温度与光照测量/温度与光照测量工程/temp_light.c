#include "STC15F2K60S2.H"

sbit SEL0=P2^0;			//定义引脚
sbit SEL1=P2^1;
sbit SEL2=P2^2;
sbit SEL3=P2^3;

#define uint unsigned int
#define ulint unsigned long

uint time=0;				//延时
uint flag=1;				//标志位，区分光和温度

uint l=0;						//执行光的次数
uint t=0;						//执行温度的次数
ulint suml=0;				//光AD值得总和
ulint sumt=0;				//温度AD值的总和

uint date_temp;
int temp=0;					//温度值
uint abs_temp;			//温度绝对值
uint light=0;				//光

//设置用于显示温度的三个变量
uint temp_bai=0;		//百位
uint temp_shi=0;		//十位
uint temp_ge =0;		//个位

//设置用于显示光的三个变量
uint light_bai=0;		//百位
uint light_shi=0;		//十位
uint light_ge =0;		//个位

//数码管上显示0-F
char segtable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
								 0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//温度值对应表
int code tempdata[]={239,197,175,160,150,142,135,129,124,120,116,113,109,107,104,101, 
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
										  7, 7, 6, 6,5, 5, 54,4, 3, 3,3, 2, 2, 1, 1, 1, 0, 0, -1, -1, -1, 
										  -2, -2, -3, -3, -4, -4, -5, -5, -6, -6, -7, -7, -8, -8, -9, -9, 
										  -10, -10, -11, -11, -12, -13, -13, -14, -14, -15, -16, -16, -17, 
										  -18, -19, -19, -20, -21, -22, -23, -24, -25, -26, -27, -28, -29, 
										  -30, -32, -33, -35, -36, -38, -40, -43, -46, -50, -55, -63, 361};
void Delay(int n);     //延时函数
void weixuan(char i);  //数码管位的选择
void SEG_Display();    //显示温度，光度
void InitADC_temp();   //初始化温度ADC
void InitADC_light();  //初始化光ADC
void date_processtemp();
void date_processlight();

void Delay(int n)			//延时函数
{
	int x;
	while(n--)
	{
		x=60;
		while(x--);
	}
}

void weixuan(char i)	//数码管位的选择
{
	SEL2=i/4;
	SEL1=i%4/2;
	SEL0=i%2;
}
void SEG_Display()   //显示温度，光度
{
  //用于设置温度的位数
	if(temp<0)
	{
		P0=0;
		weixuan(0);				//若温度为负，则首位显示‘-‘
		P0=0x40;
		Delay(10);
	}
	else
	{
		P0=0;
		weixuan(0);
		P0=segtable[temp_bai];
		Delay(10);
	}
	
	P0=0;
	weixuan(1);
	P0=segtable[temp_shi];
	Delay(10);
	
	P0=0;
	weixuan(2);
	P0=segtable[temp_ge];
	Delay(10);

	//用于设置光的位数
	P0=0;
	weixuan(5);
	P0=segtable[light_bai];
	Delay(10);
	
	P0=0;
	weixuan(6);
	P0=segtable[light_shi];
	Delay(10);
	
	P0=0;
	weixuan(7);
	P0=segtable[light_ge];
	Delay(10);
}

void T_L()
{
	P0M1=0x00;						//设置P0为推挽模式，点亮数码管
	P0M0=0xff;
	P2M1=0x00;
	P2M0=0x08;						//将P2^3设置为推挽模式，其余为准双向口模式
	SEL3=0;								//熄灭LED灯
	
	IE=0xa8;							//EA=1打开总中断，EADC=1允许A/D转化中断，ET1=1允许T1中断	
	TMOD=0x10;						//使用定时器1，16位不可重装载模式，TH1、TL1全用
	TH1=(65535-40000)/256;//高8位赋初值，定时40000周期
	TL1=(65535-40000)%256;//低8位赋初值
	TR1=1;								//启动定时器1
	
	while(1)
	{
		SEG_Display();
	}
}

void InitADC_temp()			//初始化温度ADC
{
	P1ASF=0xff;						//将P1口作为模拟功能A/D使用
	ADC_RES=0;						//寄存器ADC_RES和ADC_RESL保存A/D转化结果
	ADC_RESL=0;						//初始赋值0
	ADC_CONTR=0x8b;				//ADC_POWER=1打开A/D转换器电源;ADC_START=1启动模拟转换器ADC;CHS=011选择P1^3作为A/D输入使用
	CLK_DIV=0x20;					//ADRJ=1：ADC_RES[1:0]存放高2位ADC结果，ADC_RESL[7:0]存放低8位ADC结果
}
void InitADC_light()		//初始化光ADC
{
	P1ASF=0xff;
	ADC_RES=0;
	ADC_RESL=0;
	ADC_CONTR=0x8c;				//CHS=100选择P1^4作为A/D输入使用
	CLK_DIV=0x20;
}

//分别取出温度和光照的百位、十位、个位
void date_processtemp()
{
	if(temp<0)
		abs_temp=-temp;
	else
		abs_temp=temp;
	temp_bai=abs_temp%1000/100;
	temp_shi=abs_temp%100/10;
	temp_ge =abs_temp%10;
}
void date_processlight()
{
	light_bai=light%1000/100;
	light_shi=light%100/10;
	light_ge =light%10;
}

void Timer1_Routine() interrupt 3	//3为定时器1中断编号
{
	IE=0x00;							//关闭总中断
	TR1=0;								//定时器1停止
	TH1=(65535-40000)/256;//重新赋值
	TL1=(65535-40000)%256;

	if(flag==1)
	{
		InitADC_light();		//初始化光
	}
	else
	{
		InitADC_temp();			//初始化温度
	}
	flag=-flag;

	IE=0xa8;							//打开总中断
	TR1=1;								//启动定时器1
}

//AD中断
void adc_isr() interrupt 5 using 1
{
  time++;
	IE=0x00;							//关闭中断
	
	if(time>2000)      //取多次值求平均值减小误差
	{
		if(flag==1)										//此时flag=1执行温度部分
		{	
			date_temp=(sumt+t/2)/t;			//四舍五入
			temp=tempdata[date_temp-1]; //查找对应的AD的温度值
			sumt=0;
			t=0;
			time=0;
			date_processtemp();	
		}

		if(flag==-1)									//此时flag=-1执行光部分
		{
			light=(suml+l/2)/l;					//四舍五入
			suml=0;
			l=0;
			time=0;
	   	date_processlight();
		}    
	}

	if(flag==1)
	{
		//对应温度的数据处理
		t++;
		date_temp=(ADC_RES*256+ADC_RESL)/4;//由10位AD值转换为8位AD值
		sumt+=date_temp;						//求t次AD值的和

	}
	if(flag==-1)
	{
		//处理光部分的数据
		l++;
		suml+=ADC_RES*256+ADC_RESL;//求l次AD值的和
	}

	ADC_CONTR&=~0X10;  					 //转换完成后，ADC_FLAG清零
	ADC_CONTR|=0X08;	 					 //转换完成后，ADC_START赋1
	IE=0xa8;					 					 //打开中断
}

void main()
{
	T_L();
}