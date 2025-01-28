#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "displayer.H" 
#include "key.H" 
#include "beep.H" 

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��
#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* ��С����     0         1         2         3         4         5         6         7         8         9        */
#endif

char a;

void myKey_callback()
{ char k;
	SetBeep(1000,10);
	k=GetKeyAct(enumKey1);
	if( k == enumKeyPress ) a |=0x01;
	  else if( k == enumKeyRelease ) a &=~0x01;
	k=GetKeyAct(enumKey2);
	if( k == enumKeyPress ) a |=0x02;
	  else if( k == enumKeyRelease ) a &=~0x02;
	k=GetKeyAct(enumKey3);
	if( k == enumKeyPress ) a |=0x04;
	  else if( k == enumKeyRelease ) a &=~0x04;
}

void my10mS_callback()
{ LedPrint(a);
}

void main() 
{ DisplayerInit();  
	KeyInit();
	BeepInit();
	SetDisplayerArea(0,7);	
  Seg7Print(1,2,3,4,5,6,7,8);	
	SetEventCallBack(enumEventSys10mS, my10mS_callback);
	SetEventCallBack(enumEventKey, myKey_callback);
  MySTC_Init();	    
	while(1)             	
		{ MySTC_OS();    
		}	             
}                 