/********************
 *�жϷ�������ʵ���˶�ʱ��0��
 *�жϺʹ����ж�
 *********************/
#include "device.h"
/********************
 *��ʱ��0�ж�
 *********************/
void int_timer0(void) interrupt 1 {
  Timer01msFlag0=1;
	Timer01msFlag1=1;
	TH0=TIMER01MSTH0;
	TL0=TIMER01MSTL0;
}
/********************
 *��ʱ��1�ж�
 *********************/
void int_timer1(void) interrupt 3{
	timer0Num++;
	if(IRFLAG)
		IR_OUT=~IR_OUT;
	else
		IR_OUT=0;
}
