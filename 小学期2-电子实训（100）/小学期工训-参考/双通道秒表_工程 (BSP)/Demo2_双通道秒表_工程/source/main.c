//���ܣ�˫ͨ�����K3��K1����������������ʱ��ʼ�ͽ�������ʱ�ֱ���0.01S
#include "STC15F2K60S2.H"
#include "displayer.h"
#include "beep.h"
#include "Key.h"
#include "sys.h"

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��

#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* ��С����     0         1         2         3         4         5         6         7         8         9        */
#endif
unsigned int time1,time2;
bit flag_t1=0,flag_t2=0;

void mykey()
{	if (GetKeyAct(enumKey3) == enumKeyPress) 
     { flag_t1=~flag_t1; 
       if (flag_t1) time1=0; 
       SetBeep(1000,20);
     }
	if (GetKeyAct(enumKey1) == enumKeyPress) 
    { flag_t2=~flag_t2; 
      if (flag_t2) time2=0; 
      SetBeep(1500,20);
    }
}

void my10mSfun()
{ unsigned char d0,d1,d2,d3,d4,d5,d6,d7;
	if(flag_t1 ==1)  time1++;
	if(flag_t2 ==1)  time2++;	
	
	d0=time1/1000%10; if (d0==0) d0=10;
	d1=time1/100%10+16;
	d2=time1/10%10;
	d3=time1%10;
	
	d4=time2/1000%10;if (d4==0) d4=10;
	d5=time2/100%10+16;
	d6=time2/10%10;
	d7=time2%10;
	Seg7Print(d0,d1,d2,d3,d4,d5,d6,d7);
}

void main()
{ DisplayerInit();
	BeepInit();
	KeyInit();
	
  SetEventCallBack(enumEventSys10mS, my10mSfun);	
	SetEventCallBack(enumEventKey,mykey);
	
  SetDisplayerArea(0,7);
  LedPrint(0);

  MySTC_Init();
  while(1)
   { MySTC_OS();
   }
}