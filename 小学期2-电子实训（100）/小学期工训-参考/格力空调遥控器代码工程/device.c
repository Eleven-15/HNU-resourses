#include "device.h"
#include "intrins.h"
/********************
 *��ʱ��0����ʵ��
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
 *��ʱ��1����ʵ��
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
 *����ܲ���ʵ��
 ********************/
uint8 digitalTubeData[DIGTUBENUM]={0};
uint8 digindex=0;				   //��ǰ��ʾ�������λ��	
pdata uint8 digtalduan[18]={0x3f,0x06,0x5b,0x4f,
						0x66,0x6d,0x7d,0x07,
						0x7f,0x6f,0x77,0x7c,
						0x39,0x5e,0x79,0x71,
						0x40,0x00};
	  
/********************
 *����ܶ�̬ɨ�躯��
 ********************/
void  digScan(){
	if(Timer01msFlag0==1){	 //����1ms��ʱ���б��ж��Ƿ����ɨ��
		P0=0;								 //����P0������Ӱ
		P2&=0xf8;
		P2|=digindex;						 //������ǰλ
		P0=digtalduan[digitalTubeData[digindex]]; //�����Ӧλ���ϵ�ֵ
		Timer01msFlag0=0;						   //����1ms��ʱ���б�ı�־λ
		digindex=(digindex+1)%DIGTUBENUM;					   //�л�����һ�� λ��
	}
}
/********************
 *��������ʵ��
 ********************/
xdata struct keyfunc  keygroup={0};
void  keyInit(){
	keygroup.sensitivity=KEYSENSITY;
	P1ASF=0x80;							   //��ʼ������������һЩ����
	ADC_RES=0;
	ADC_CONTR=0X8F;
	CLK_DIV=0X00;
}
/********************
 *����ɨ��ʵ��
 ********************/
void  keyScan(){
	uint8 i,adcResult;
	if(Timer01msFlag1==1){		
		Timer01msFlag1=0;//1ms���ˣ�
		if(P3&0x04)								  //�жϵ�ǰ������״̬���ɿ�up��1������down��1
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
		if(ADC_CONTR&0x10){						//��ģת����ɣ������½���ת��
			  ADC_CONTR&=~0x10;
			  ADC_CONTR|=0x08;
			  adcResult=ADC_RES>>5;
		}
		switch(adcResult){						//����ģת����õ�ֵ�жϰ��µ����ĸ�����
			case 0:	keygroup.up[2]--;keygroup.down[2]++;break;
			case 1:	keygroup.up[3]--;keygroup.down[3]++;break;
			case 2:	keygroup.up[4]--;keygroup.down[4]++;break;
			case 3:	keygroup.up[5]--;keygroup.down[5]++;break;
			case 4:	keygroup.up[6]--;keygroup.down[6]++;break;
			case 5:	keygroup.up[7]--;keygroup.down[7]++;break;
		}
	}
	else return;
	//ͳ�ƵĴ����ﵽsensitivity����԰�����״̬���и���
	if(keygroup.up[0]+keygroup.down[0]==keygroup.sensitivity){
		for(i=0;i<KEYNUM;i++){	   //�жϸ������ڰ��������ɿ����ǰ���״̬
			keygroup.state[i]=keygroup.up[i]>keygroup.down[i]?0:1;
			keygroup.up[i]=0;
			keygroup.down[i]=0;
		}
	}
}
