//秒表：数码管显示分、秒、毫秒
#include "STC15F2K60S2.H"
#include "displayer.h"
#include "beep.h"
#include "Key.h"
#include "sys.h"

code unsigned long SysClock=11059200;         
//必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致

#ifdef _displayer_H_                          
//显示模块选用时必须。（数码管显示译码表，用戶可修改、增加等） 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* 序号:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15    */
                /* 显示:   0   1    2    3    4     5    6    7   8    9  (无)   下-  中-  上-  上中-  中下-  */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* 带小数点     0         1         2         3         4         5         6         7         8         9        */
#endif
unsigned int time=0;     //秒表计时
bit flag_t=0;      //=0，停止计时，=1，计时

void mykey()
{	
	unsigned char status;
	status=GetKeyAct(enumKey1);	

	if (flag_t == 0)            
	 { if ( status == enumKeyPress )    {time=0; /*SetBeep(800,100);*/}    
	 //按下按键：计时清零、发令预备
     if (time == 0)
					if (status== enumKeyRelease) {flag_t=1; /*SetBeep(1500,20);*/}    
			 //松开按键：开始比赛、发令比赛
	 }
  else                                       
		//如果秒表还在计时
	 { if (flag_t == 1)   
			 if (status == enumKeyPress) { flag_t=0; /*SetBeep(1000,20);*/ }     //秒表停止
	 }		
}

void my1mSfun()
{ 
	unsigned char d0,d1,d2,d3,d4,d5,d6,d7;
	if(flag_t ==1)  time++;
	
	//min
	d7=((time/1000)/60)/10;
	d6=((time/1000)/60)%10;
	d5=12;//短横-
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