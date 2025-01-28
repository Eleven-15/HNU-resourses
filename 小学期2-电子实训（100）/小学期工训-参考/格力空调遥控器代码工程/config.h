/************************
 *定义常用的宏，配置板子
 ************************/
#ifndef CONFIG_H
#define CONFIG_H
#include "STC15F2K60S2.H"
#define IR_OUT P35
#define TIMER01MSTH0   0xfc    //1ms定时器初值TH
#define TIMER01MSTL0   0x66	  //1ms定时器初值TL
#define TIMER113USTH1		0xF4    //13us定时器初值(定时器1在12T模式下8位自动装载)
#define TIMER113USTL1   0xF4    //
#define TIMER1600USNUM  46//600us时间，定时器1产生的中断次数
#define TIMER11600USNUM	123//1600us时间，定时器1产生的中断次数
#define TIMER14500USNUM	346//4500us时间，定时器1产生的中断次数
#define TIMER19000USNUM 692//9000us时间，定时器1产生的中断次数
#define TIMER120000USNUM  1538//20000us的时间，定时器1产生的中断次数
#define DIGTUBENUM    8			//数码管个数，板子上有8个数码管，定义为8
#define DIGGROUPNUM	  8		   	//数码管的组数
#define KEYNUM    8				//定义按键个数，这里有3个按键+导航按键5中情况，共8种
#define KEYSENSITY 100			//按键灵敏度
#endif