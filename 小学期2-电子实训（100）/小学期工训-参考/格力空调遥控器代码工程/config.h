/************************
 *���峣�õĺ꣬���ð���
 ************************/
#ifndef CONFIG_H
#define CONFIG_H
#include "STC15F2K60S2.H"
#define IR_OUT P35
#define TIMER01MSTH0   0xfc    //1ms��ʱ����ֵTH
#define TIMER01MSTL0   0x66	  //1ms��ʱ����ֵTL
#define TIMER113USTH1		0xF4    //13us��ʱ����ֵ(��ʱ��1��12Tģʽ��8λ�Զ�װ��)
#define TIMER113USTL1   0xF4    //
#define TIMER1600USNUM  46//600usʱ�䣬��ʱ��1�������жϴ���
#define TIMER11600USNUM	123//1600usʱ�䣬��ʱ��1�������жϴ���
#define TIMER14500USNUM	346//4500usʱ�䣬��ʱ��1�������жϴ���
#define TIMER19000USNUM 692//9000usʱ�䣬��ʱ��1�������жϴ���
#define TIMER120000USNUM  1538//20000us��ʱ�䣬��ʱ��1�������жϴ���
#define DIGTUBENUM    8			//����ܸ�������������8������ܣ�����Ϊ8
#define DIGGROUPNUM	  8		   	//����ܵ�����
#define KEYNUM    8				//���尴��������������3������+��������5���������8��
#define KEYSENSITY 100			//����������
#endif