/***********************
 *��ͷ�ļ�����ؼ�����
 *���Ľṹ��
 ************************/
#ifndef DEVICE_H
#include "ctype.h"
#include "config.h"
#define DEVICE_H
//����50us��ʱ���ȴ��б�Ľṹ��
//ÿ��50us��ʹ���б��tflags����Ԫ�ض���1
extern uint8 Timer01msFlag0;
extern uint8 Timer01msFlag1;
extern uint8 IRFLAG;
extern uint16 timer0Num;
void Timer0Init();
void Timer1Init();
//��������������������ͨ��������������		  
struct  keyfunc{
	uint8  up[KEYNUM];		   	  //�����ɿ��Ĵ���
	uint8  down[KEYNUM];		  //�������µĴ���
	uint8  state[KEYNUM];		  //����������״̬��0���ɿ���1�ǰ���
	uint8  sensitivity;			  //���������ȣ�ԽСԽ����������������ҲԽ����
};
void  keyInit();
void  keyScan();
void digScan();
#endif