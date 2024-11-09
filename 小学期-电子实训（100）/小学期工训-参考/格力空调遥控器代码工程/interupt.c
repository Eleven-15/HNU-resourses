/********************
 *中断服务函数，实现了定时器0的
 *中断和串口中断
 *********************/
#include "device.h"
/********************
 *定时器0中断
 *********************/
void int_timer0(void) interrupt 1 {
  Timer01msFlag0=1;
	Timer01msFlag1=1;
	TH0=TIMER01MSTH0;
	TL0=TIMER01MSTL0;
}
/********************
 *定时器1中断
 *********************/
void int_timer1(void) interrupt 3{
	timer0Num++;
	if(IRFLAG)
		IR_OUT=~IR_OUT;
	else
		IR_OUT=0;
}
