//功能：双通道秒表，K3、K1独立控制两个秒表计时开始和结束，计时分辨率0.01S
#include "STC15F2K60S2.H"
#include "displayer.h"
#include "beep.h"
#include "Key.h"
#include "sys.h"

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致

#ifdef _displayer_H_                          //显示模块选用时必须。（数码管显示译码表，用戶可修改、增加等） 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* 序号:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* 显示:   0   1    2    3    4     5    6    7   8    9  (无)   下-  中-  上-  上中-  中下-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* 带小数点     0         1         2         3         4         5         6         7         8         9        */
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