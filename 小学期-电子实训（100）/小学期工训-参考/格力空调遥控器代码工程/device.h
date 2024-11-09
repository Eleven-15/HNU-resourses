/***********************
 *改头文件定义关键件部
 *件的结构体
 ************************/
#ifndef DEVICE_H
#include "ctype.h"
#include "config.h"
#define DEVICE_H
//描述50us定时器等待列表的结构体
//每隔50us会使该列表的tflags数组元素都置1
extern uint8 Timer01msFlag0;
extern uint8 Timer01msFlag1;
extern uint8 IRFLAG;
extern uint16 timer0Num;
void Timer0Init();
void Timer1Init();
//描述按键部件，包括普通按键，导航按键		  
struct  keyfunc{
	uint8  up[KEYNUM];		   	  //按键松开的次数
	uint8  down[KEYNUM];		  //按键按下的次数
	uint8  state[KEYNUM];		  //按键所处的状态，0是松开，1是按下
	uint8  sensitivity;			  //按键灵敏度，越小越灵敏，但抖动现象也越明显
};
void  keyInit();
void  keyScan();
void digScan();
#endif