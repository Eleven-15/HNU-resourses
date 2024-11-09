#include "STC15F2K60S2.h"
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int
//数码管段选信号 从0到9
uchar code duanxuan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//数码管位选信号 显示在第4到7位
uchar code weixuan[4]={0x04,0x05,0x06,0x07};

sbit led_sel=P2^3;//74HC138 的一个使能位
sbit key1=P3^2;//按键k1
sbit key2=P3^3;//按键k2

uint number;//显示在数码管上的值
uint flag;//位选的位置
int count1,count2,count3,count4;//用于消抖计数
bit status_P,status_P2;//记录按键前一状态
void Init()
{
/**************************
将P0设置成推挽输出 P2的低四位设置成推挽输出 P3不需要设置成推挽输出
**************************/
	P0M0=0XFF;
	P0M1=0X00;
	P2M0=0X0F;
	P2M1=0X00;
	
	led_sel=0;
	P0=0;
	number=5000;//初始化number=5000
	count1=0;
	count2=0;
	count3=0;
	count4=0;
	
	
	status_P=0;
	status_P2=0;
	flag=0;
	
	TMOD=0X00;
	EA=1;
	ET0=1;
	TH0=(65536-200)/256;
	TL0=(65536-200)%256;
	TR0=1;
}

void InterruptTimer0()interrupt 1
{
	switch(flag)
	{
		case 0:P0=0;P2=weixuan[flag];P0=duanxuan[number/1000];break;
		case 1:P0=0;P2=weixuan[flag];P0=duanxuan[(number/100)%10];break;
		case 2:P0=0;P2=weixuan[flag];P0=duanxuan[(number%100)/10];break;
		case 3:P0=0;P2=weixuan[flag];P0=duanxuan[(number%100)%10];break;
	}
	flag++;
	
	count1++;
	if(key1==0)
	{
		count2++;
	}
		
	
	count3++;
	if(key2==0)
	{
		count4++;
	}
}

void main()
{
	Init();
	while(1)
	{
		if(flag==4)//修正位选位置  可放在中断程序外 放在中断外 效果更好
			flag=0;
		
		if(count1==30)//消抖大概6ms 总共统计次数 30次
		{
			if(count2>=20)// 如果低电平的有效次数为 2/3 以上
			{
				if(status_P==1)
				{
					status_P=0;
					number++;
				}
			}
			else
				status_P=1;
			count1=0;
			count2=0;
		}
		
		
		if(count3==30)//消抖大概6ms 总共统计次数 60次
		{
			if(count4>=20)// 如果低电平的有效次数为 2/3 以上
			{
				if(status_P2==1)
				{
					status_P2=0;
					number--;
				}
			}
			else
				status_P2=1;
			count3=0;
			count4=0;
		}
	}
}