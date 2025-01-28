//����������ʾ�֡��롢����
#include "STC15F2K60S2.H"
#include "displayer.h"
#include "beep.h"
#include "Key.h"
#include "sys.h"

code unsigned long SysClock=11059200;         
//���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��

#ifdef _displayer_H_                          
//��ʾģ��ѡ��ʱ���롣���������ʾ������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15    */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-  */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* ��С����     0         1         2         3         4         5         6         7         8         9        */
#endif
unsigned int time=0;     //����ʱ
bit flag_t=0;      //=0��ֹͣ��ʱ��=1����ʱ

void mykey()
{	
	unsigned char status;
	status=GetKeyAct(enumKey1);	

	if (flag_t == 0)            
	 { if ( status == enumKeyPress )    {time=0; /*SetBeep(800,100);*/}    
	 //���°�������ʱ���㡢����Ԥ��
     if (time == 0)
					if (status== enumKeyRelease) {flag_t=1; /*SetBeep(1500,20);*/}    
			 //�ɿ���������ʼ�������������
	 }
  else                                       
		//�������ڼ�ʱ
	 { if (flag_t == 1)   
			 if (status == enumKeyPress) { flag_t=0; /*SetBeep(1000,20);*/ }     //���ֹͣ
	 }		
}

void my1mSfun()
{ 
	unsigned char d0,d1,d2,d3,d4,d5,d6,d7;
	if(flag_t ==1)  time++;
	
	//min
	d7=((time/1000)/60)/10;
	d6=((time/1000)/60)%10;
	d5=12;//�̺�-
	//s
	d4=(time/1000)%60/10;
	d3=(time/1000)%10+16;
	//ms
	d2=(time/100)%10;
	d1=(time/10)%10;
	d0=(time%10);
	
	Seg7Print(d7,d6,d5,d4,d3,d2,d1,d0);
}

void main()
{ 
	DisplayerInit();
	BeepInit();
	KeyInit();
  SetEventCallBack(enumEventSys1mS, my1mSfun);	
	SetEventCallBack(enumEventKey,mykey);
	
  SetDisplayerArea(0,7);
  LedPrint(0);

  MySTC_Init();
  while(1)
   { MySTC_OS();
   }
}