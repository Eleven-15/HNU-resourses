#include "device.h"
#include "intrins.h"
/********************
 *定时器0部件实现
 ********************/
uint8 Timer01msFlag0=0;
uint8 Timer01msFlag1=0;
void Timer0Init(void)		//1??@11.0592MHz
{
	AUXR &= 0x7F;		//?????12T??
	TMOD &= 0xF0;		//???????
	TMOD |= 0x01;		//???????
	IE |=0x02;
	TL0 = TIMER01MSTL0;		//??????
	TH0 = TIMER01MSTH0;		//??????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
}

/********************
 *定时器1部件实现
 ********************/
uint8 IRFLAG=0;
uint16 timer0Num=0;
void Timer1Init(void)		//1??@11.0592MHz
{
	AUXR &= 0xBF;		//?????12T??
	TMOD &= 0x0F;		//???????
	TMOD |= 0x20;
	IE |=0x08;
	IP |=0x08;
	TF1 = 0;		//??TF1??
	TR1=0;
}

/********************
 *数码管部件实现
 ********************/
uint8 digitalTubeData[DIGTUBENUM]={0};
uint8 digindex=0;				   //当前显示的数码管位置	
pdata uint8 digtalduan[18]={0x3f,0x06,0x5b,0x4f,
						0x66,0x6d,0x7d,0x07,
						0x7f,0x6f,0x77,0x7c,
						0x39,0x5e,0x79,0x71,
						0x40,0x00};
	  
/********************
 *数码管动态扫描函数
 ********************/
void  digScan(){
	if(Timer01msFlag0==1){	 //根据1ms定时器列表判断是否进行扫描
		P0=0;								 //清零P0消除残影
		P2&=0xf8;
		P2|=digindex;						 //点亮当前位
		P0=digtalduan[digitalTubeData[digindex]]; //输出对应位置上的值
		Timer01msFlag0=0;						   //清零1ms定时器列表的标志位
		digindex=(digindex+1)%DIGTUBENUM;					   //切换到下一个 位置
	}
}
/********************
 *按键部件实现
 ********************/
xdata struct keyfunc  keygroup={0};
void  keyInit(){
	keygroup.sensitivity=KEYSENSITY;
	P1ASF=0x80;							   //初始化导航按键的一些参数
	ADC_RES=0;
	ADC_CONTR=0X8F;
	CLK_DIV=0X00;
}
/********************
 *按键扫描实现
 ********************/
void  keyScan(){
	uint8 i,adcResult;
	if(Timer01msFlag1==1){		
		Timer01msFlag1=0;//1ms到了？
		if(P3&0x04)								  //判断当前按键的状态，松开up加1，按下down加1
			keygroup.up[0]++;
		else 
			keygroup.down[0]++;
		if(P3&0x08)
			keygroup.up[1]++;
		else 
			keygroup.down[1]++;
		keygroup.up[2]++;
		keygroup.up[3]++;
		keygroup.up[4]++;
		keygroup.up[5]++;
		keygroup.up[6]++;
		keygroup.up[7]++;
		if(ADC_CONTR&0x10){						//数模转换完成，则重新进行转换
			  ADC_CONTR&=~0x10;
			  ADC_CONTR|=0x08;
			  adcResult=ADC_RES>>5;
		}
		switch(adcResult){						//跟数模转换获得的值判断按下的是哪个按键
			case 0:	keygroup.up[2]--;keygroup.down[2]++;break;
			case 1:	keygroup.up[3]--;keygroup.down[3]++;break;
			case 2:	keygroup.up[4]--;keygroup.down[4]++;break;
			case 3:	keygroup.up[5]--;keygroup.down[5]++;break;
			case 4:	keygroup.up[6]--;keygroup.down[6]++;break;
			case 5:	keygroup.up[7]--;keygroup.down[7]++;break;
		}
	}
	else return;
	//统计的次数达到sensitivity，则对按键的状态进行更新
	if(keygroup.up[0]+keygroup.down[0]==keygroup.sensitivity){
		for(i=0;i<KEYNUM;i++){	   //判断该周期内按键处于松开还是按下状态
			keygroup.state[i]=keygroup.up[i]>keygroup.down[i]?0:1;
			keygroup.up[i]=0;
			keygroup.down[i]=0;
		}
	}
}
