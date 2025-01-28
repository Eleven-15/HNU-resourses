#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "displayer.H" 
#include "Key.h"
#include "beep.h"

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��
#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* ��С����     0         1         2         3         4         5         6         7         8         9        */
#endif
unsigned int a=1100;//����Ƶ��
unsigned int last_time=200;//����ʱ��
												 
void myKey_callback()
{ 
	if(GetKeyAct(enumKey1) ==	enumKeyPress) 
		{	if(a < 4000) a+=100;
		}
	if(GetKeyAct(enumKey3) ==	enumKeyPress) 
		{	if(a > 400) a-=100;
		}
	Seg7Print(0,0,0,0,a/1000,a/100%10,a/10%10,a%10);	
	SetBeep(a,last_time);
}

void main() 
{ DisplayerInit();  
	KeyInit();
	BeepInit();
	SetEventCallBack(enumEventKey,myKey_callback);
	SetDisplayerArea(4,7);	
  Seg7Print(0,0,0,0,a/1000,a/100%10,a/10%10,a%10);	
	
	SetBeep(a,last_time);
/*
	Beep_freq:����Ƶ��
	Beep_time:����ʱ��=10*Beep_time(mS)����������180�ͻ����1.8s
*/
	
  MySTC_Init();	    
	while(1)             	
		{ MySTC_OS();    
		}	             
}                 